1、设置环境变量
RTE_SDK是代码顶层目录
RTE_TARGET是选择编译平台，这里是64位linux系统，使用gcc编译。



export RTE_SDK=/home/jack/dpdk-stable-18.11.11
export RTE_TARGET=x86_64-native-linuxapp-gcc
export EXTRA_CFLAGS="-O3 -g"
make -j 10 install T=$RTE_TARGET DESTDIR=/home/jack/dpdk-stable-18.11.11/dpdk




export RTE_SDK=/home/jack/dpdk-stable-19.11.1
export RTE_TARGET=x86_64-native-linuxapp-gcc


# port stop 0
# port detach 0
# port attach af:01.0
# port start 0




https://jira.devtools.intel.com/browse/DPDK-26785

https://jira.devtools.intel.com/browse/DPDK-26672


2、
配置巨页
2048
echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
mount -t hugetlbfs nodev /mnt/huge


mkdir /mnt/huge
mount -t hugetlbfs pagesize=1GB /mnt/huge



3、编译安装
DESTDIR是安装目录

make -j 10 install T=$RTE_TARGET DESTDIR=/home/jack/dpdk-stable-18.11.11/dpdk


modprobe uio
insmod igb_uio.ko




python3 dpdk-devbind.py --bind=igb_uio 18:0a.0

python3 dpdk-devbind.py --bind=igb_uio 0000:1a:00.0
python3 dpdk-devbind.py --bind=igb_uio 0000:1a:01.1

python3 dpdk-devbind.py --bind=ice 0000:1a:00.0

python3 dpdk-devbind.py --bind=vfio-pci 0000:86:02.0 0000:86:02.1
python3 dpdk-devbind.py --bind=igb_uio 0000:1a:01.1


0000:86:02.0 'Ethernet Virtual Function 700 Series 154c' drv=vfio-pci unused=iavf
0000:86:02.1 'Ethernet Virtual Function 700 Series 154c' drv=vfio-pci unused=iavf
./testpmd -l 0-3 -n 4 --vdev 'net_bonding0,mode=2,slave=0000:86:02.0,slave=0000:86:02.1,xmit_policy=l34' -- -i --port-topology=chained

0000:86:10.0 
 ./testpmd -c 0xff -n 4  -w 0000:86:10.0  --log-level=8  -- -i  --forward-mode=io --rxq=1 --txq=1

./testpmd -l 0-3 -n 4 -w 0000:86:02.0 -w 0000:86:02.1 --log-level=pmd.net.i40e.init:8 --log-level=pmd.net.i40e.driver:8 -- -i
port stop all
create bonded device 2 1
set bonding balance_xmit_policy 2 l34
add bonding slave 0 2
add bonding slave 1 2
set bonding mac_addr 2 00:11:22:00:33:44
port start 2

https://jira.devtools.intel.com/browse/DPDK-26047





./dpdk-testpmd -c 0xff -n 4  -a 0000:18:00.1  --log-level=pmd.net.i40e.init:8 --log-level=pmd.net.i40e.driver:8  -- -i --disable-rss  --pkt-filter-mode=perfect --forward-mode=rxonly --rxq=4 --txq=4

./dpdk-testpmd -c 0xff -n 4  -a 0000:1a:00.1  --log-level=pmd.net.iavf.init:8 --log-level=pmd.net.iavf.driver:8  -- -i --disable-rss  --pkt-filter-mode=perfect --forward-mode=rxonly --rxq=4 --txq=4


flow create 0 ingress pattern eth / ipv4  / tcp src is 1024 / end actions queue index 1 / mark id 1 / end


flow create 0 ingress pattern eth / ipv4  / tcp src is 1025 / end actions queue index 2 / mark id 2 / end

spec 1 dst mask 15

flow create 0 ingress pattern eth / ipv4  / tcp src spec 1  src mask 1 / end actions queue index 1 / end


flow create 0 ingress pattern eth / ipv4  / tcp src spec 0  src mask 1  / end actions queue index 2 / end





 flow create 0 ingress pattern eth / ipv4  / tcp dst spec 1 dst mask 15 / end actions queue index 1 / mark id 1 / end

 flow create 0 ingress pattern eth / ipv4  / tcp dst spec 2 dst mask 15 / end actions queue index 2 / mark id 2 / end





pkt = Ether(dst="02:09:C0:39:A6:DB",src="02:09:C0:9E:E1:22")/IP(dst="192.168.10.2", src="192.168.10.1")/TCP(sport=1,dport=2001)/("X"*480)
sendp(pkt,iface="ens802f1",count=1000,inter=5)




pkt = Ether(dst="DA:94:A3:EF:C7:2D")/IP(dst="192.168.10.2", src="192.168.10.1")/TCP(sport=1025,dport=2001)/("X"*480)

sendp(pkt,iface="ens785f1",count=1,inter=1)






pkt = Ether(dst="DA:94:A3:EF:C7:2D")/IP(dst="192.168.10.2", src="192.168.10.1")/TCP(sport=1,dport=2001)/("X"*480)

sendp(pkt,iface="ens785f1",count=1,inter=1)




pkt = Ether(dst="DA:94:A3:EF:C7:2D")/IP(dst="192.168.10.2", src="192.168.10.1")/TCP(sport=0,dport=2001)/("X"*480)

sendp(pkt,iface="ens785f1",count=1,inter=1)









--file-prefix=vf0

--file-prefix=vf1

./dpdk-testpmd -c 0xff -n 4  -w 0000:18:0a.0 -- -i --forward-mode=rxonly --rxq=4 --txq=4

PF 
--log-level="ice,8"

./dpdk-testpmd -c 0xff -n 4  -w 0000:1a:00.0 --file-prefix=PF  -- -i --forward-mode=rxonly --rxq=4 --txq=4

0000:1a:00.0
VF 
./dpdk-testpmd -c 0xff -n 4  -a 0000:86:02.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=4 --txq=4

./dpdk-testpmd -c 0xff -n 4  -w 0000:1a:01.1 --file-prefix=vf1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=4 --txq=4

flow create 0 ingress pattern eth / ipv4 / udp / gtpu teid is 0x12345678 / end actions queue index 1 / mark / end

virsh nodedev-list | grep 18

0000:18:0a.0 


Dot1Q(vlan = 100) 

GTPU test case

======================================================
rmmod i40e
modprobe i40e l4mode=2      
echo 4 >  /sys/class/net/ens802f0/device/sriov_numvfs    



echo 4 >  /sys/class/net/enp24s0f0/device/sriov_numvfs    

echo 0 >  /sys/class/net/ens786f0/device/sriov_numvfs    


echo 0 >  /sys/class/net/ens801f1/device/sriov_numvfs 

PF配置

1、ethtool -K ens785f1 ntuple on
                                                                                             ffff
###ethtool -N ens785f1 flow-type udp4 dst-port 23 user-def 0x8000000000000000 action 0x0100000000   ok

2、ethtool -N ens785f1 flow-type udp4 dst-port 2152 user-def 0x8000000000000000 action 0x0100000000


ethtool -N eno1 flow-type udp4 dst-port 23 user-def 0x8000000000000000 action 0x0100000000


ethtool -U eno1 flow-type tcp4 src-ip 192.168.10.1 dst-ip 192.168.10.2 src-port 2000 dst-port 2001 action 0x0100000000 loc 1

发包：
import sys
from scapy.contrib.gtp import *

pkt = Ether(dst="68:05:CA:BB:26:E0")/IP()/UDP(sport=22,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)





pkt = Ether(dst="68:05:CA:BB:26:E0")/IP(dst="192.168.10.2", src="192.168.10.1")/TCP(sport=2000,dport=2001)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.10.2", src="192.168.10.1")/("X"*480)

sendp(pkt,iface="ens785f1",count=1,inter=1)




pkt = Ether(dst="68:05:CA:BB:26:E0")/Dot1Q(vlan=100)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)


sendp(pkt,iface="ens785f1",count=1,inter=1)


结果：



testpmd> port 0/queue 2: received 1 packets
  src=00:00:00:00:00:00 - dst=68:05:CA:BB:26:E0 - type=0x0800 - length=550 - nb_segs=1 - RSS hash=0xade0dd15 - RSS queue=0x2 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x2
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
testpmd>
testpmd>
testpmd>
testpmd> port 0/queue 0: received 1 packets
  src=00:00:00:00:00:00 - dst=68:05:CA:BB:26:E0 - type=0x0800 - length=550 - nb_segs=1 - RSS hash=0x3170a34f - RSS queue=0x0 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x0
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN




ens785f1

echo 32 >  /sys/class/net/ens785f1/device/sriov_numvfs 












VXLAN

ethtool -N ens785f1 flow-type udp4 dst-port 4789 user-def 0x8000000000000000 action 0x010000ffff



x722


echo 4 >  /sys/class/net/eno1/device/sriov_numvfs


ethtool -K eno1 ntuple on

#error ethtool -N eno1 flow-type udp4 dst-port 2152 user-def 0x8000000000000000 action 0x0100000000



SRIOV

 ip link set dev eno1 vf 0 vlan 100
 
./testpmd -c 0xff -n 4  -w 0000:41:02.0 --file-prefix=vf0 -- -i --forward-mode=rxonly --rxq=4 --txq=4

./testpmd -c 0xff -n 4  -w 0000:41:02.1 --file-prefix=vf1 -- -i --forward-mode=rxonly --rxq=4 --txq=4


这个MAC的和带vlan100的都可以到达VM


61 设备上的eno1 需要接一根线到一个10G的服务器上

tcpdump -i eno1 


import sys
from scapy.contrib.gtp import *


pkt = Ether(dst="ff:ff:ff:ff:ff:ff")/Dot1Q(vlan=100)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)

sendp(pkt,iface="ens817f1",count=1,inter=1)


pkt = Ether(dst="2e:fd:3d:51:dd:69")/Dot1Q(vlan=100)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)

sendp(pkt,iface="ens817f1",count=1,inter=1)

pkt = Ether(dst="2e:fd:3d:51:dd:69")/Dot1Q(vlan=10)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)


sendp(pkt,iface="ens817f1",count=1,inter=1)

pkt = Ether(dst="2e:fd:3d:51:dd:69")/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)

sendp(pkt,iface="ens817f1",count=1,inter=1)

pkt = Ether(dst="2e:fd:3d:51:dd:69")/Dot1Q(vlan=100)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)


sendp(pkt,iface="eno1",count=1,inter=1)



pkt = Ether(dst="DA:94:A3:EF:C7:2F")/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)

sendp(pkt,iface="ens817f1",count=1,inter=1)


pkt = Ether(dst="DA:94:A3:EF:C7:2F")/Dot1Q(vlan=100)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)

sendp(pkt,iface="ens817f1",count=1,inter=1)


pkt = Ether(dst="DA:94:A3:EF:C7:2F")/Dot1Q(vlan=10)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)

sendp(pkt,iface="ens817f1",count=1,inter=1)



tcpdump -XX -vvv -nn -i eno1


rte_pktmbuf_dump(stdout, m, MBUF_TEST_DATA_LEN);




pkt = Ether(dst="BA:F2:99:90:3C:85")/IP(dst="192.168.10.2", src="192.168.10.3")/TCP(sport=2000,dport=2001)/("X"*480)

sendp(pkt,iface="ens786f0",count=1,inter=1)

flow create 0 ingress pattern eth / ipv4 / gre / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end



#direct UDP traffic with dstPort=250 to VF 1 (1st VF) with cloud filter
#user-def highest bit indicates it’s cloud filter, action =(8bit VF) + (32bit Queue, 0xffff means traffic to VSI instead of queue)
ethtool -N ens5f0 flow-type udp4 dst-port 250 user-def 0x8000000000000000 action 0x010000ffff

#ethtool -N $PF flow-type udp4 dst-port $dst_port user-def 0x8000000000000000 action 0x0${vfn}0000ffff
这个rule配了不发包
#ethtool -N $PF flow-type udp4 src-port 0 m 0xfffe dst-port $dst_port user-def 0xffffffff00000000 action 0 loc 0
#ethtool -N $PF flow-type udp4 src-port 1 m 0xfffe dst-port $dst_port user-def 0xffffffff00000000 action 1 loc 0

VXLAN

bridge link set dev <DEVICE> hwmode vepa

ethtool -N enp24s0f0 flow-type udp4 dst-port 4789 user-def 0x8000000000000000 action 0x010000ffff





ethtool -N enp24s0f0 flow-type udp4 dst-port 250 user-def 0x8000000000000000 action 0x010000ffff

ethtool -N enp24s0f0 flow-type udp4 dst-port 250 user-def 0x8000000000000000 action 0x010000ffff


ethtool -N enp24s0f0 flow-type udp4 src-port 0 m 0xfffe dst-port 250 user-def 0x8000000000000000 action 0 loc 0
