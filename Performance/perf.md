BKM
BOOT_IMAGE=/vmlinuz-3.10.0-693.21.1.el7.x86_64 root=/dev/mapper/vg_sys-lv_root ro rd.md.uuid=c39d9f31:15a23700:70952dc4:0a16de48 
rd.md.uuid=b0b5ff26:9e50ba20:a1b14582:3a875252 crashkernel=512M rd.lvm.lv=vg_sys/lv_root nopti
rdblacklist=igb,ixgbe,igbvf,ixgbevf,tg3,radeon,openvswitch,i40e,qla2xxx,ice,nouveau modules-load=bonding 
blacklist=openvswitch acpi_pad.disable=1 console=tty0 console=ttyS0,115200n8 
udev.event-timeout=180, rd.udev.event-timeout=180 tsc=noirqtime intel_pstate=disable 
intel_iommu=on iommu=pt nospectre_v1=off spectre_v2=off spec_store_bypass_disable=off 
pti=off mds=off l1tf=off tsx_async_abort=off kvm.nx_huge_pages_recovery_ratio=0 audit=1 
audit_backlog_limit=8192 isolcpus=11,12,13,14,15,16,17,18,19,20,21,23,25,27,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,9 
default_hugepagesz=1G hugepagesz=1G hugepages=130 hugepagesz=2M hugepages=0


PFU pod

16 FP




redhat:
grub：

00字节 单流40个包
6430（2.6GHZ uncore2.1或者2.2） XCC 多Die 数据 PFU性能类似
1、18.39MPPS DDP+DPI（媒体面核和DPI核合1） 18HT  2PFU 
  
2、24.43MPPS DDP 非DPI 18HT     2PFU

3、20.31MPPS DPI 4+18 media  2PFU    1LIG+4TCPO+1scan 主流发货场景  22.81MPPS      (22.81-20.31)/20.31 =12 %

4、23.45MPPS 非DDP 非 DPI 2PFU

非合1

5、17.89MPPS 非DDP+DPI 4+4+14 + 1(LIG加密)+4(TCPO TCP优化)+1(scan内部业务使用)= 28HT
-------------------------------------------------------------------------------
CPU 核布局


24HT (4+(4dpi+14 media)+1(LIG)+1(scan))          12P*2    1 OS Pcore   25P/28      剩3P
28HT (4+(4dpi+14 media)+1(LIG)+4(TCPO)+1(scan))  14P*2  + 1 OS Pcore   29P/32      剩3P 

-----------------------------------------------------------------------------


OS 1P core 2HT

Gen to Gen：
6330N 28P core 2.6GHZ  
            4+18                  18
          dis/dpi   dis/oDPI   DDP/DIP   DDP/oDPI
6430      20.31     23.45       18.39     24.43
6438N     22.81     26.83       20.21     27.61
6428N     20.88     25.21       19.06     26.08
5420+     21.98     26.28       19.87     26.94  without TCPO 4 threads
6330N     17.28     NA          NA        NA
7763/64   31M/175G             34M / 190G        CPU @80%  娄总说比SPR高30% (Milan 4个UPF 不均匀，总线有问题，AMD 说Genoa解决总线问题，性能会更好，可能翻倍，intel单核性能好）
7A23/48	  30M               
		  
		  
24*4  96core
		
AMD created a custom SKU for central bidding, Milan 7A23 48C 2.8GHz. AMD 1S/2S vs IA 2S/4S.

7A23     
31*(700+20)*8	 
	 




6438N > 5420+ > 6428N > 6430 > 6330N
205W     205W   185W    270W    165W
3300$    1800$  3200$   2100$    2029$
2.6      2.7    2.5     2.6      2.6
32       28     32      32       28

移动全球合作伙伴大会：

NRE======
UPM 钱没变 开源进展 PMP--->source code？？CNDA--->(BIS/open source)
周建锋

C 面:SMF/AMF control plan +++++ 时间点
U 面:UPF 







48HT 规格




48HT

120个核



			NUMA0 48HT (2+(4dpi+36 media)+1(LIG)+4(TCPO)+1(scan)) 

socket0
			NUMA1 48HT (2+(4dpi+36 media)+1(LIG)+4(TCPO)+1(scan)) 


200多G 单Server 

ARM  10      比xeon 140%
Xeon 7

144

瓶颈点在内存




