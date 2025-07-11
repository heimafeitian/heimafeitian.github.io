1.performance checklist

1.1 boot configure CPU Isolation /RCU Callbacks/Tickless Kernel

cat /etc/cmdline

default_hugepagesz=1G hugepagesz=1G hugepages=16 intel_iommu=on
iommu=pt isolcpus=1-21,28-48 nohz_full=1-21,28-48 rcu_nocbs=1-21,28-48


default_hugepagesz=1G hugepagesz=1G hugepages=16 idle=poll
intel_idle.max_cstate=0 pcie_aspm=off intel_iommu=on iommu=pt intel_pstate=disable
processor.max_cstate=1 numa_balancing=disable mce=off isolcpus=$local_cores
nohz_full=$local_cores rcu_nocbs=$local_cores vt.handoff=1


1.2 check Turbo Disabled

rdmsr -x -f 63:0  0x1a0

# Disabling turbo mode (SKL, KBL, CFL, ICL)
wrmsr 0x1a0 0x4000850089 # to enable use 0x850089

1.3 IRQ Affinity
Configuring IRQ affinity so that interrupts for different network queues are affinitized to different CPU
cores can have a huge impact on performance, particularly multi-thread throughput tests.

systemctl disable irqbalance
systemctl stop irqbalance


Find the processors attached to each node using

numactl --hardware
lscpu

1.4 hugepages check
Hugepage support is required for the large memory pool allocation used for packet buffers. By using
hugepage allocations, performance is increased since fewer pages are needed, and therefore less
Translation Lookaside Buffers (TLBs, high speed translation caches), which reduce the time it takes to
translate a virtual page address to a physical page address. Without hugepages, high TLB miss rates
would occur with the standard 4K page size, slowing performance.

cat /proc/meminfo | grep HugePages

1.5 check the memory configuration using dmidecode as follows

Ensure that each memory channel has at least one memory DIMM inserted, and that the memory size for each is at least 4GB. 
Note: this has one of the most direct effects on performance.

dmidecode -t memory | grep Locator

dmidecode -t memory | grep Speed

1.6 Network Interface Card Requirements

Some PCIe x8 slots are actually configured as x4 slots. These slots have insufficient bandwidth for full
line rate with dual port and quad port devices. In addition, if you put a PCIe v3.0-capable adapter into
a PCIe v2.x slot, you cannot get full bandwidth. The software device driver detects this situation and
writes the following message in the system log:

PCI-Express bandwidth available for this card is not sufficient for optimal
performance. For optimal performance a x8 PCI-Express slot is required

lspci -s 03:00.1 -vv | grep LnkSta

1.7 BIOS Settings
The following are some recommendations on BIOS settings. Different platforms will have different BIOS naming so the following is mainly for reference:

Establish the steady state for the system, consider reviewing BIOS settings desired for best performance characteristic e.g. optimize for performance or energy efficiency.
Match the BIOS settings to the needs of the application you are testing.
Typically, Performance as the CPU Power and Performance policy is a reasonable starting point.
Consider using Turbo Boost to increase the frequency on cores.
Disable all virtualization options when you test the physical function of the NIC, and turn on VT-d if you wants to use VFIO.

1.8 check uncore

rdmsr -a -x -f 63:0  0x621

Uncore freq:

To check current uncore freq:

      >>  rdmsr 0x620        (0x620 is the register name)

To change uncore freq:

      >> wrmsr --all 0x620 0x0c0c     (0x0c0c means to change the min and max uncore frequency to 0x0c and 0x0c)
	  
RING frequency can be queried with:

$ rdmsr -d 0x621  # current RING frequency, multiply by 100 to get MHz
9
$ sudo rdmsr 0x620 # RING frequency limits (in HEX!): 0x8 - min, 0x23 - max (translate to DEC and multiply by 100 to get MHz)
823

Fixing uncore frequency

Uncore frequency can be set by writing the same value for both minimum and maximum frequency through MSR 0x620 on each socket. 
In MSR 0x620, bits 0-7 indicate the maximum frequency (in units of 100Mhz) while bits 8-15 capture the minimum frequency. 
For example, if you want to set the uncore frequency to 2700 MHz, you need to write the value 27 (0x1b in hex) for both max and min frequency. 
So, 0x1b1b would be written to MSR 0x620. You can use EMON driver to write to the MSR and the following command will automatically write to both sockets

emon  --write-msr  0x620=0x1b1b


1.9 check CPU frequency

cpupower frequency-info -o


====================================================================================================================================================================================
performance tools

1、PCM (Performance Counter Monitor):  https://software.intel.com/en-us/articles/intel-performance-counter-monitor

pcm

./pcm.x | awk ' /^\s+(2|14|Core|SKT)\s/ {print $0}'


pcm-iio

pcm-pcie

pcm-memory


2、perf

perf top

top 1

3、turbostat/pidstat/mpstat

mpstat -P ALL 1

mpstat -P ALL 1 1 | grep -v Average | tail -n +5 | head -n -1 | awk '{ print (100-$13)}' | egrep --color=always '[^\.][8-9][0-9][\.]?.*|^[8-9][0-9][\.]?.*|100|' | column

4、ethtool -S ethX


ethtool -S ethX
To watch just non-zero counters:
watch -d (ethtool -S ethX) | egrep -v :\ 0 | column


5.Network Counters

netstat -s 


6、Layer 2 flow control can impact TCP performance considerably and is recommended to be disabled for
most workloads. A potential exception is bursty traffic where the bursts are not long in duratio

ethtool -A ethX rx off tx off




======================================================================================================================================



Uncore freq:

To check current uncore freq:

      >>  rdmsr 0x620        (0x620 is the register name)

To change uncore freq:

      >> wrmsr --all 0x620 0x0c0c     (0x0c0c means to change the min and max uncore frequency to 0x0c and 0x0c)
	  
RING frequency can be queried with:

$ rdmsr -d 0x621  # current RING frequency, multiply by 100 to get MHz
9
$ sudo rdmsr 0x620 # RING frequency limits (in HEX!): 0x8 - min, 0x23 - max (translate to DEC and multiply by 100 to get MHz)
823

Fixing uncore frequency

Uncore frequency can be set by writing the same value for both minimum and maximum frequency through MSR 0x620 on each socket. 
In MSR 0x620, bits 0-7 indicate the maximum frequency (in units of 100Mhz) while bits 8-15 capture the minimum frequency. 
For example, if you want to set the uncore frequency to 2700 MHz, you need to write the value 27 (0x1b in hex) for both max and min frequency. 
So, 0x1b1b would be written to MSR 0x620. You can use EMON driver to write to the MSR and the following command will automatically write to both sockets

emon  --write-msr  0x620=0x1b1b



Grub 启动参数：
nomodeset nosoftlockup processor.max_cstate=0 nmi_watchdog=0 hpet=disable mce=off 
isolcpus=1-75 rcu_nocbs=1-75 numa_balancing=disable kthread_cpus=0 irqaffinity=0 idle=poll softlockup_panic=0 audit=0 rdt=l3cat vt.handoff=7 LANG=en_US.UTF-8 hugepagesz=1GB hugepages=50 default_hugepagesz=1GB skew_tick=1

需要使用哪些核就隔离哪些核isolcpus=1-75 rcu_nocbs=1-75

还可以做一下tuned-adm profile throughput-performance
