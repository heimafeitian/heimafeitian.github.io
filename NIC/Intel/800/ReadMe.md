modprobe uio
insmod igb_uio.ko

1. meson -Dexamples=all -Db_sanitize=address x86_64-native-linuxapp-gcc
2. ninja -C x86_64-native-linuxapp-gcc


python3 dpdk-devbind.py --bind=ice 0000:1a:00.0

python3 dpdk-devbind.py --bind=igb_uio 0000:1a:00.0

python3 dpdk-devbind.py --bind=vfio-pci 0000:18:01.0

python3 dpdk-devbind.py --bind=vfio-pci 0000:b2:01.0 

b_sanitize
--file-prefix=vf0

--file-prefix=vf1

./dpdk-testpmd -c 0x1f -n 4  -w 0000:17:00.1  -- -i  --nb-cores=4 --forward-mode=rxonly --rxq=4 --txq=4


./dpdk-testpmd -l 2-3 -n 4  -w 0000:1a:00.0  --vdev=virtio_user0,path=/dev/vhost-net,queue_size=1024 -- -i --tx-offloads=0x0000002c  --txd=1024 --rxd=1024

PF 

DCF
======================================================================================

./dpdk-testpmd -c 0xf -n 4 -a 0000:1a:01.0,cap=dcf -a 0000:1a:01.1 --log-level="ice,8" -- -i


./dpdk-testpmd -c 0xff -n 4  -w 0000:b2:00.0 --file-prefix=PF --log-level="ice,8" -- -i  --rxq=4 --txq=4

0000:1a:00.0
VF 
./dpdk-testpmd -c 0xff -n 4  -a 0000:3d:09.0 --file-prefix=vf0 --log-level=net_iavf:8 -- -i --forward-mode=rxonly --rxq=4 --txq=4

./dpdk-testpmd -c 0xff -n 4  -w 0000:1a:01.1 --file-prefix=vf1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=4 --txq=4

flow create 0 ingress pattern eth / ipv4 / udp / gtpu teid is 0x12345678 / end actions queue index 1 / mark / end

virsh nodedev-list | grep 18



pkt = Ether(dst="3E:8D:2E:0C:ED:36")/IP(dst="10.114.106.71", src="192.168.10.1")/TCP(sport=1,dport=2001)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)

./dpdk-testpmd -c 0xf -n 4 -a 0000:1a:01.0 --file-prefix=vf0 --log-level=net_iavf:8 -- -i --rxq=16 --txq=16 --disable-rss --rxd=384 --txd=384

sendp([Ether(dst="40:A6:B7:67:22:80",type=0x8100)/Dot1Q(vlan=1,type=0x8100)/Dot1Q(vlan=2,type=0x0800)/IP(src="196.222.232.221")/("X"*480)], iface="ens786")
sendp([Ether(dst="40:A6:B7:67:22:80",type=0x8100)/Dot1Q(vlan=100,type=0x8100)/Dot1Q(vlan=200,type=0x0800)/IP(src="196.222.232.221")/("X"*480)], iface="ens786")

sendp([Ether(dst="40:A6:B7:67:22:80",type=0x8100)/Dot1Q(vlan=100,type=0x8100)/Dot1Q(vlan=300,type=0x0800)/IP(src="196.222.232.221")/("X"*480)], iface="ens786")


sendp([Ether(dst="40:A6:B7:67:22:80",type=0x8100)/Dot1Q(vlan=100,type=0x8100)/Dot1Q(vlan=300,type=0x0800)/IP(src="196.222.232.100")/("X"*480)], iface="ens786")




sendp([Ether(dst="40:A6:B7:67:22:80",type=0x88a8)/Dot1Q(vlan=1,type=0x8100)/Dot1Q(vlan=2,type=0x0800)/IP(src="196.222.232.221")/("X"*480)], iface="ens786")




sendp([Ether(dst="40:A6:B7:67:22:80",type=0x8100)/Dot1Q(vlan=100,type=0x0800)/IP(src="196.222.200.220")/("X"*480)], iface="ens786")
sendp([Ether(dst="40:A6:B7:67:22:80",type=0x8100)/Dot1Q(vlan=20,type=0x0800)/IP(src="196.222.232.220")/("X"*480)], iface="ens786")

sendp([Ether(dst="40:A6:B7:67:22:80",type=0x8100)/Dot1Q(vlan=100,type=0x0800)/IP(src="196.222.200.100")/("X"*480)], iface="ens786")
=====================================



modprobe vfio-pci
modprobe vhost-net



./dpdk-testpmd -l 1, 4-16 -n 4 --vdev=virtio_user0,path=/dev/vhost-net,queues=2,queue_size=1024 -- -i --tx-offloads=0x0000002c --txq=2 --rxq=2 --txd=1024 --rxd=1024


pkt = Ether(dst="DA:94:A3:EF:C7:2F")/Dot1Q(vlan=10)/IP()/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.0.2")/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)


dpdk-testpmd -c f -n 4 –telemetry -- i


(testpmd) -l 2-3 -n 4 \
        --vdev=virtio_user0,path=/dev/vhost-net,queues=2,queue_size=1024 \
        -- -i --tx-offloads=0x0000002c --enable-lro \
        --txq=2 --rxq=2 --txd=1024 --rxd=1024
===========================================================================================================================

VLAN 报文的验证

modprobe vfio-pci

echo 32 >  /sys/class/net/ens801/device/sriov_numvfs    

echo 32 >  /sys/class/net/ens786/device/sriov_numvfs 

echo 4 >  /sys/class/net/ens786f0/device/sriov_numvfs    
echo 32 >  /sys/class/net/ens786f1/device/sriov_numvfs    
modprobe vfio-pci

echo 0 >  /sys/class/net/ens786f0/device/sriov_numvfs    

echo 0 >  /sys/class/net/ens786f1/device/sriov_numvfs   


                                            N30       N60           RAW0          N31           N61           RAW1
											
modprobe vfio-pci											
python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2
python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5


											
./dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5

python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5



./dpdk-testpmd -c 0xf -a 0000:1a:11.0  -n 4 -- -i --rxq=16 --txq=16  --nb-cores=1 --nb-ports=1 --forward-mode=rxonly 



0000:1a:01.3 'Ethernet Adaptive Virtual Function 1889' if=ens786f0v3 drv=iavf unused=vfio-pci
0000:1a:01.4 'Ethernet Adaptive Virtual Function 1889' if=ens786f0v4 drv=iavf unused=vfio-pci
0000:1a:01.5 'Ethernet Adaptive Virtual Function 1889' if=ens786f0v5 drv=iavf unused=vfio-pci


0000:1a:11.3 'Ethernet Adaptive Virtual Function 1889' if=ens786f1v3 drv=iavf unused=vfio-pci
0000:1a:11.4 'Ethernet Adaptive Virtual Function 1889' if=ens786f1v4 drv=iavf unused=vfio-pci
0000:1a:11.5 'Ethernet Adaptive Virtual Function 1889' if=ens786f1v5 drv=iavf unused=vfio-pci



./dpdk-testpmd -c 0xff -n 4  -a 0000:1a:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=txonly --rxq=16 --txq=16

=============================

cd /home/jack/dpdk-20.11/usertools/

rmmod ice

modprobe ice
echo 32 >  /sys/class/net/ens786f0/device/sriov_numvfs    
echo 32 >  /sys/class/net/ens786f1/device/sriov_numvfs   
 
modprobe vfio-pci

./dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5

cd ../build/app/

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2  -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16








VF 不支持带vlan的报文识别

./dpdk-testpmd -c 0xff -n 4  -a 0000:1a:01.0 -a 0000:1a:01.1  --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16
 
 
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

 
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 -a 0000:1a:11.4 -a 0000:1a:11.5    --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


sendp([Ether(src="10:22:33:44:55:66",dst="06:92:26:F8:03:C5")/IP(src="192.168.1.1", dst="192.168.1.2")/Raw("x" * 80)],iface="ens786",count=1)

*sendp([Ether(dst="06:92:26:F8:03:C5",type=0x8100)/Dot1Q(vlan=100,type=0x0800)/IP(src="196.222.200.100")/("X"*480)], iface="ens786")
*sendp([Ether(dst="06:92:26:F8:03:C5",type=0x8100)/Dot1Q(vlan=100,type=0x8100)/Dot1Q(vlan=300,type=0x0800)/IP(src="196.222.232.221")/("X"*480)], iface="ens786")


PF 能够识别带Vlan的报文

python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:00.1

./dpdk-testpmd -c 0xff -n 4  -w 0000:1a:00.1 --file-prefix=PF --log-level="ice,8" -- -i --forward-mode=rxonly --rxq=4 --txq=4




sendp([Ether(src="10:22:33:44:55:66",dst="0E:46:A3:7C:22:22")/IP(src="192.168.1.1", dst="192.168.1.2")/Raw("x" * 80)],iface="ens786",count=100)
sendp([Ether(dst="06:92:26:F8:03:C5",type=0x8100)/Dot1Q(vlan=100,type=0x0800)/IP(src="196.222.200.100")/("X"*480)], iface="ens786")
sendp([Ether(dst="06:92:26:F8:03:C5",type=0x8100)/Dot1Q(vlan=100,type=0x8100)/Dot1Q(vlan=300,type=0x0800)/IP(src="196.222.232.221")/("X"*480)], iface="ens786")


gdb --args ./dpdk-testpmd -c 0xff -n 4  -a 0000:b2:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


开vlan strip功能收到报文不带vlan

testpmd> port 0/queue 2: received 1 packets
  src=00:00:00:00:00:00 - dst=06:92:26:F8:03:C5 - type=0x0800 - length=514 - nb_segs=1 - RSS hash=0x5babdd0e - RSS queue=0x2 - VLAN tci=0x64 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_NONFRAG  - sw ptype: L2_ETHER L3_IPV4  - l2_len=14 - l3_len=20 - Receive queue=0x2
  ol_flags: PKT_RX_VLAN PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_VLAN_STRIPPED PKT_RX_OUTER_L4_CKSUM_GOOD

sendp([Ether(dst="3E:8D:2E:0C:ED:36",type=0x8100)/Dot1Q(vlan=100,type=0x0800)/IP(src="196.222.200.100")/("X"*480)], iface="ens786")

开QinQ strip功能和vlan strip功能同时开，收到的报文带一层vlan

sendp([Ether(dst="06:92:26:F8:03:C5",type=0x8100)/Dot1Q(vlan=100,type=0x8100)/Dot1Q(vlan=300,type=0x0800)/IP(src="196.222.232.221")/("X"*480)], iface="ens786")


  src=00:00:00:00:00:00 - dst=06:92:26:F8:03:C5 - type=0x8100 - length=518 - nb_segs=1 - RSS hash=0xa9429f21 - RSS queue=0x1 - VLAN tci=0x64 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_NONFRAG  - sw ptype: L2_ETHER_VLAN L3_IPV4  - l2_len=18 - l3_len=20 - Receive queue=0x1
  ol_flags: PKT_RX_VLAN PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_VLAN_STRIPPED PKT_RX_OUTER_L4_CKSUM_GOOD
dump mbuf at 0x1628bb600, iova=0x1628bb680, buf_len=2176
  pkt_len=518, ol_flags=0x4001c3, nb_segs=1, port=0, vlan_tci=100, ptype=0x691
  segment at 0x1628bb600, data=0x1628bb700, len=518, off=128, refcnt=1
  Dump data at [0x1628bb700], len=518


=====================================================================================================================================================================
DCF 功能的验证

echo 16 >  /sys/class/net/ens786f1/device/sriov_numvfs    

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:11.0,cap=dcf -a 0000:1a:11.1 --log-level="ice,8" -- -i --forward-mode=rxonly --rxq=16 --txq=16



ip link set ens786f1 vf 0 trust on

echo 16 >  /sys/class/net/ens786/device/sriov_numvfs    

python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2


python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:11.0,cap=dcf -a 0000:1a:11.1 --log-level="ice,8" -- -i --forward-mode=rxonly --rxq=16 --txq=16

MAC_IPV4_GTPU_TEID_with_mask with last 5 bit

1、create rule:

flow create 0 ingress pattern eth / ipv4 / udp / gtpu teid is 0x12345678 teid mask 0x0000001f / end actions vf id 1 / end


2.send 4 matched pkts and check port 1 received 4 pkts:

import sys
from scapy.contrib.gtp import *

p1 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345618)/Raw("x" *20)
sendp(p1,iface="ens786",count=1,inter=1)

p2 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345638)/Raw("x" *20)
sendp(p2,iface="ens786",count=1,inter=1)

p3 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345658)/Raw("x" *20)
sendp(p3,iface="ens786",count=1,inter=1)

p4 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345678)/Raw("x" *20)
sendp(p4,iface="ens786",count=1,inter=1)



testpmd> port 1/queue 13: received 1 packets
  src=00:00:00:00:00:00 - dst=00:11:22:33:44:55 - type=0x0800 - length=70 - nb_segs=1 - RSS hash=0x8fdacfdd - RSS queue=0xd - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN TUNNEL_GTPU  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - VXLAN packet: packet type =32913, Destination UDP port =2152, VNI = 1193046, last_rsvd = 24 - Receive queue=0xd
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN
dump mbuf at 0x164b88600, iova=0x164b88680, buf_len=2176
  pkt_len=70, ol_flags=0x182, nb_segs=1, port=1, ptype=0x8091
  segment at 0x164b88600, data=0x164b88700, len=70, off=128, refcnt=1
  Dump data at [0x164b88700], len=70
00000000: 00 11 22 33 44 55 00 00 00 00 00 00 08 00 45 00 | .."3DU........E.
00000010: 00 38 00 01 00 00 40 11 7C B2 7F 00 00 01 7F 00 | .8....@.|.......
00000020: 00 01 08 68 08 68 00 24 A3 BE 30 00 00 14 12 34 | ...h.h.$..0....4
00000030: 56 18 78 78 78 78 78 78 78 78 78 78 78 78 78 78 | V.xxxxxxxxxxxxxx
00000040: 78 78 78 78 78 78                               | xxxxxx
port 1/queue 13: received 1 packets
  src=00:00:00:00:00:00 - dst=00:11:22:33:44:55 - type=0x0800 - length=70 - nb_segs=1 - RSS hash=0x8fdacfdd - RSS queue=0xd - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN TUNNEL_GTPU  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - VXLAN packet: packet type =32913, Destination UDP port =2152, VNI = 1193046, last_rsvd = 56 - Receive queue=0xd
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN
dump mbuf at 0x164b87cc0, iova=0x164b87d40, buf_len=2176
  pkt_len=70, ol_flags=0x182, nb_segs=1, port=1, ptype=0x8091
  segment at 0x164b87cc0, data=0x164b87dc0, len=70, off=128, refcnt=1
  Dump data at [0x164b87dc0], len=70
00000000: 00 11 22 33 44 55 00 00 00 00 00 00 08 00 45 00 | .."3DU........E.
00000010: 00 38 00 01 00 00 40 11 7C B2 7F 00 00 01 7F 00 | .8....@.|.......
00000020: 00 01 08 68 08 68 00 24 A3 9E 30 00 00 14 12 34 | ...h.h.$..0....4
00000030: 56 38 78 78 78 78 78 78 78 78 78 78 78 78 78 78 | V8xxxxxxxxxxxxxx
00000040: 78 78 78 78 78 78                               | xxxxxx
port 1/queue 13: received 1 packets
  src=00:00:00:00:00:00 - dst=00:11:22:33:44:55 - type=0x0800 - length=70 - nb_segs=1 - RSS hash=0x8fdacfdd - RSS queue=0xd - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN TUNNEL_GTPU  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - VXLAN packet: packet type =32913, Destination UDP port =2152, VNI = 1193046, last_rsvd = 88 - Receive queue=0xd
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN
dump mbuf at 0x164b87380, iova=0x164b87400, buf_len=2176
  pkt_len=70, ol_flags=0x182, nb_segs=1, port=1, ptype=0x8091
  segment at 0x164b87380, data=0x164b87480, len=70, off=128, refcnt=1
  Dump data at [0x164b87480], len=70
00000000: 00 11 22 33 44 55 00 00 00 00 00 00 08 00 45 00 | .."3DU........E.
00000010: 00 38 00 01 00 00 40 11 7C B2 7F 00 00 01 7F 00 | .8....@.|.......
00000020: 00 01 08 68 08 68 00 24 A3 7E 30 00 00 14 12 34 | ...h.h.$.~0....4
00000030: 56 58 78 78 78 78 78 78 78 78 78 78 78 78 78 78 | VXxxxxxxxxxxxxxx
00000040: 78 78 78 78 78 78                               | xxxxxx
port 1/queue 13: received 1 packets
  src=00:00:00:00:00:00 - dst=00:11:22:33:44:55 - type=0x0800 - length=70 - nb_segs=1 - RSS hash=0x8fdacfdd - RSS queue=0xd - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN TUNNEL_GTPU  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - VXLAN packet: packet type =32913, Destination UDP port =2152, VNI = 1193046, last_rsvd = 120 - Receive queue=0xd
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN
dump mbuf at 0x164b86a40, iova=0x164b86ac0, buf_len=2176
  pkt_len=70, ol_flags=0x182, nb_segs=1, port=1, ptype=0x8091
  segment at 0x164b86a40, data=0x164b86b40, len=70, off=128, refcnt=1
  Dump data at [0x164b86b40], len=70
00000000: 00 11 22 33 44 55 00 00 00 00 00 00 08 00 45 00 | .."3DU........E.
00000010: 00 38 00 01 00 00 40 11 7C B2 7F 00 00 01 7F 00 | .8....@.|.......
00000020: 00 01 08 68 08 68 00 24 A3 5E 30 00 00 14 12 34 | ...h.h.$.^0....4
00000030: 56 78 78 78 78 78 78 78 78 78 78 78 78 78 78 78 | Vxxxxxxxxxxxxxxx
00000040: 78 78 78 78 78 78                               | xxxxxx




testpmd> show fwd stats all

  ------- Forward Stats for RX Port= 1/Queue=13 -> TX Port= 0/Queue=13 -------
  RX-packets: 4              TX-packets: 0              TX-dropped: 0

  ---------------------- Forward statistics for port 0  ----------------------
  RX-packets: 0              RX-dropped: 0             RX-total: 0
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ----------------------------------------------------------------------------

  ---------------------- Forward statistics for port 1  ----------------------
  RX-packets: 4              RX-dropped: 0             RX-total: 4
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ----------------------------------------------------------------------------

  +++++++++++++++ Accumulated forward statistics for all ports+++++++++++++++
  RX-packets: 4              RX-dropped: 0             RX-total: 4
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
testpmd>


3.send 1 mismatched pkts and check port 1 not received pkts:


p5 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345617)/Raw("x" *20)
sendp(p5,iface="ens786",count=1,inter=1)


4、destory rule and re-send step 2 matched pkts check port 1 not received pkts:


flow flush 0

testpmd> show fwd stats all

  ------- Forward Stats for RX Port= 1/Queue=13 -> TX Port= 0/Queue=13 -------
  RX-packets: 4              TX-packets: 0              TX-dropped: 0

  ---------------------- Forward statistics for port 0  ----------------------
  RX-packets: 0              RX-dropped: 0             RX-total: 0
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ----------------------------------------------------------------------------

  ---------------------- Forward statistics for port 1  ----------------------
  RX-packets: 4              RX-dropped: 0             RX-total: 4
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ----------------------------------------------------------------------------

  +++++++++++++++ Accumulated forward statistics for all ports+++++++++++++++
  RX-packets: 4              RX-dropped: 0             RX-total: 4
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
testpmd>



p1 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345678)/Raw("x" *20)
sendp(p1,iface="ens786",count=1,inter=1)


p2 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345688)/Raw("x" *20)
sendp(p2,iface="ens786",count=1,inter=1)
p3 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header(teid=0x12345677)/Raw("x" *20)
sendp(p3,iface="ens786",count=1,inter=1)


p1 = Ether(dst="00:11:22:33:44:55")/IP(dst="192.168.1.2")/UDP()/GTP_U_Header()/Raw("x" *20)
sendp(p1,iface="ens786",count=1,inter=1)

p2 = Ether(dst="00:11:22:33:44:55")/IP(dst="192.168.1.22")/UDP()/GTP_U_Header()/Raw("x" *20)
sendp(p2,iface="ens786",count=1,inter=1)



p1 = Ether(dst="00:11:22:33:44:55")/IP()/UDP()/GTP_U_Header()/GTPPDUSessionContainer()/IP(dst="192.168.1.2")/Raw("x" *20)

sendp(p1,iface="ens786",count=1,inter=1)




p1 = Ether(dst="40:A6:B7:0A:7C:31")/IP(src="192.168.0.1",dst="192.168.0.2",proto=47)/GRE(key_present=1,proto=2048,key=67108863)/IP()/Raw("x" *20)
sendp(p1,iface="ens786",count=1,inter=1)


p1 = Ether()/IP()/GRE()/IP()/TCP()
sendp(p1,iface="ens786",count=1,inter=1)

GRE ================================================================================================================================
testpmd> flow create 0 ingress pattern eth / ipv4 / gre / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
iavf_execute_vf_cmd(): Return failure -5 for cmd 45
iavf_add_del_rss_cfg(): Failed to execute command of OP_ADD_RSS_CFG
iavf_hash_create(): fail to add RSS configure
iavf_flow_create(): Failed to create flow
port_flow_complain(): Caught PMD error type 2 (flow rule (handle)): Failed to create parser engine.: Invalid argument
testpmd>
testpmd>


./dpdk-testpmd -l 0-19 -n 4  -a 0000:1a:00.0 --file-prefix=PF --log-level="ice,8" -- -i  --rxq=16 --txq=16

p1 = Ether(dst="40:A6:B7:0A:7C:31")/IP()/GRE(key_present=1,proto=2048,key=6710886)/IP(dst="1.1.1.1")/UDP()
sendp(p1,iface="ens786",count=1,inter=1)



p2 = Ether(dst="40:A6:B7:0A:7C:31")/IP()/GRE()/IPv6()/UDP()
sendp(p2,iface="ens786",count=1,inter=1)

p1 = Ether(dst="40:A6:B7:0A:7C:31")/IPv6(nh=47)/GRE()/IP()/UDP()/Raw('x'*40)
sendp(p1,iface="ens786",count=1,inter=1)
p2 = Ether(dst="40:A6:B7:0A:7C:31")/IPv6(nh=47)/GRE(proto=0x86dd)/IPv6()/UDP()/Raw('x'*40)
sendp(p2,iface="ens786",count=1,inter=1)


=======================================================================================
OPPO ip + L4 port mask


./dpdk-testpmd -c 0xff -n 4  -a 0000:1a:00.0 --file-prefix=PF --log-level="ice,8" -- -i --forward-mode=rxonly --rxq=16 --txq=16

./dpdk-testpmd -c 0xff -n 4  -a 0000:1a:11.0  --file-prefix=PF --log-level="ice,8" -- -i --forward-mode=rxonly --rxq=4 --txq=4


./dpdk-testpmd -c 0xff -n 4  -w 0000:1a:00.0 --file-prefix=PF  -- -i --forward-mode=rxonly --rxq=4 --txq=4


flow create 0 ingress pattern eth / ipv4 dst is 10.114.106.71 / tcp dst spec 2 dst mask 7 / end actions queue index 0 / end

flow create 0 ingress pattern eth / ipv4 dst is 10.114.106.71 / tcp dst spec 1 dst mask 7 / end actions queue index 1 / end



pkt = Ether(dst="40:A6:B7:67:22:84")/IP(dst="10.114.106.71", src="192.168.10.1")/TCP(sport=1,dport=2001)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)


pkt = Ether(dst="40:A6:B7:0A:7C:31")/IP(dst="10.114.106.71", src="192.168.10.1")/TCP(sport=0,dport=2002)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)


pkt = Ether(dst="40:A6:B7:67:22:84")/IP(dst="10.114.106.71", src="192.168.10.1")/TCP(sport=2000,dport=2002)/("X"*480)

sendp(pkt,iface="ens786f1",count=1,inter=1)


pkt = Ether(dst="40:A6:B7:67:28:A8")/IP(dst="10.114.106.71", src="192.168.10.1")/TCP(sport=2000,dport=10)/("X"*480)

sendp(pkt,iface="ens786f1",count=1,inter=1)

==============================================================================================================================
ZTE GTPU inner sip


ice_vc_handle_rss_cfg---》ice_add_rss_cfg_wrap--》ice_add_rss_cfg--》ice_add_rss_cfg_sync

./dpdk-testpmd -c 0xf -a 0000:1a:11.0  -n 4 -- -i --rxq=16 --txq=16  --nb-cores=1 --nb-ports=1 --forward-mode=rxonly 






#flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / rss queues 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 / end

flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end








sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="192.168.10.2")/("X"*480)],iface="ens786")






sendp([Ether(dst="3E:31:44:23:19:FB")/IP(dst="192.168.0.21")/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.2", src="192.168.10.2")/("X"*480)],iface="ens786")

sendp([Ether(dst="3E:31:44:23:19:FB")/IP(dst="192.168.0.21")/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.3", src="192.168.10.2")/("X"*480)],iface="ens786")



sendp([Ether(dst="3E:31:44:23:19:FB")/IP(dst="192.168.0.21")/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.1", src="192.168.10.1",frag=6)/("X"*480)],iface="ens786")

sendp([Ether(dst="06:92:26:F8:03:C5")/IP(dst="192.168.0.21")/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.1", src="192.168.10.3")/ICMP()/("X"*480)],iface="ens786")

sendp([Ether(dst="06:92:26:F8:03:C5")/IP(dst="192.168.0.21")/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.1", src="192.168.10.1")/TCP()/("X"*480)],iface="ens786")

sendp([Ether(dst="06:92:26:F8:03:C5")/IP(dst="192.168.0.21")/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.1", src="192.168.10.1")/UDP()/("X"*480)],iface="ens786")









import sys
from scapy.contrib.gtp import *
--------------------------




flow create 0 ingress pattern eth / ipv4 dst is 200.10.10.200 / udp / gtpu / end actions mark id 4 /  end

flow create 0 ingress pattern eth / ipv4 dst is 200.10.10.200 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end

flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 0 ingress pattern eth type is 0x0806 / end actions rss types 
flow create 0 ingress pattern eth  / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end


sendp(Ether(dst="06:92:26:F8:03:C5")/IP(dst="200.10.10.200",src="172.16.2.10")/UDP()/GTP_U_Header()/IP(src="192.168.0.11",dst="172.20.0.1")/Raw("x" *20),iface='ens786')
sendp(Ether(dst="06:92:26:F8:03:C5")/IP(dst="200.10.10.200",src="172.16.2.10")/UDP()/GTP_U_Header()/IP(src="192.168.0.12",dst="172.20.0.1")/Raw("x" *20),iface='ens786')
sendp(Ether(dst="06:92:26:F8:03:C5")/IP(dst="200.10.10.200",src="172.16.2.10")/UDP()/GTP_U_Header()/IP(src="192.168.0.12",dst="172.20.0.2")/Raw("x" *20),iface='ens786')





sendp([Ether(dst="00:11:22:33:44:55")/IP()/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.10.1", src="192.168.0.2")/("X"*480)],iface="enp134s0f0")
sendp([Ether(dst="00:11:22:33:44:55")/IP()/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.1", src="192.168.10.2")/("X"*480)],iface="enp134s0f0")


Txony
./dpdk-testpmd -c 0xff -n 4  -a 0000:1a:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16 




frag:

FDIR:

./dpdk-testpmd -c 0xff -n 4  -a 0000:b2:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --rxq=16 --txq=16 

./dpdk-testpmd -c 0xff -n 4  -a 0000:b2:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16 


RSS
./dpdk-testpmd -c 0xff -n 4  -a 0000:b2:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16 --disable-rss


FDIR:
flow create 0 ingress pattern eth / ipv4 / end actions rss types eth ipv4-frag end key_len 0 queues end / end
flow validate 0 ingress pattern eth / ipv4 fragment_offset spec 0x2000 fragment_offset mask 0x2000 / end actions queue index 1 / mark id 1 / end
flow create 0 ingress pattern eth / ipv4 fragment_offset spec 0x2000 fragment_offset mask 0x2000 / end actions queue index 1 / mark id 1 / end


flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / end actions rss types eth ipv4-frag end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / ipv6_frag_ext / end actions rss types ipv6-frag end key_len 0 queues end / end

p = Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.13', id=47750)/Raw('X'*666)
pkts=fragment(p, fragsize=500)
sendp(pkts, iface="ens786")


p = Ether(src='00:11:22:33:44:66', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.13', id=47751)/Raw('X'*666)
pkts=fragment(p, fragsize=500)
sendp(pkts, iface="ens786")


p=Ether()/IP(id=47750)/Raw('X'*666); 
pkts=fragment(p, 500)

sendp(pkts,iface="ens786",count=1,inter=1)


p = Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.10.1', dst='10.114.106.72', id=47750)/Raw('X'*666)
pkts=fragment(p, fragsize=500)
sendp(pkts, iface="ens786")


p = Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.10.1', dst='10.114.106.71', id=47754)/Raw('X'*666)
pkts=fragment(p, fragsize=500)
sendp(pkts, iface="ens786")

p = Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.10.10', dst='10.114.106.72', id=47750)/Raw('X'*666)
sendp(p, iface="ens786")

p = Ether()/IPv6()/IPv6ExtHdrFragment(id=47750)/Raw('X'*666)
pkts=fragment6(p, 500)
sendp(pkts, iface="ens786")



p=Ether()/IP(id=47750)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)

p=Ether()/IP(id=47751)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)


pkts = Ether(dst="3E:8D:2E:0C:ED:36")/IP(dst="10.114.106.72", src="192.168.10.1")/Raw("X"*480)

sendp(pkts,iface="ens786",count=1,inter=1)



sendp([Ether(dst="06:92:26:F8:03:C5")/IP(dst="192.168.0.21")/UDP(dport=2152)/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.0.1", src="192.168.10.1")/UDP()/("X"*480)],iface="ens786")




	/*
	 * spec and mask are valid, enforce using full mask to make sure the
	 * complete value is used correctly.
	 */
	if ((mask->hdr.fragment_offset & RTE_BE16(MLX5_IPV4_FRAG_OFFSET_MASK))
			!= RTE_BE16(MLX5_IPV4_FRAG_OFFSET_MASK))
		return rte_flow_error_set(error, EINVAL,
					  RTE_FLOW_ERROR_TYPE_ITEM_MASK,
					  item, "must use full mask for"
					  " fragment_offset");
	/*
	 * Match on fragment_offset 0x2000 means MF is 1 and frag-offset is 0,
	 * indicating this is 1st fragment of fragmented packet.
	 * This is not yet supported in MLX5, return appropriate error message.
	 */
	if (fragment_offset_spec == RTE_BE16(RTE_IPV4_HDR_MF_FLAG))
		return rte_flow_error_set(error, ENOTSUP,
					  RTE_FLOW_ERROR_TYPE_ITEM, item,
					  "match on first fragment not "
					  "supported");
	if (fragment_offset_spec && !last)
		return rte_flow_error_set(error, ENOTSUP,
					  RTE_FLOW_ERROR_TYPE_ITEM, item,
					  "specified value not supported");
	/* spec and last are valid, validate the specified range. */
	fragment_offset_last = last->hdr.fragment_offset &
			       mask->hdr.fragment_offset;
	/*
	 * Match on fragment_offset spec 0x2001 and last 0x3fff
	 * means MF is 1 and frag-offset is > 0.
	 * This packet is fragment 2nd and onward, excluding last.
	 * This is not yet supported in MLX5, return appropriate
	 * error message.
	 */
	if (fragment_offset_spec == RTE_BE16(RTE_IPV4_HDR_MF_FLAG + 1) &&
	    fragment_offset_last == RTE_BE16(MLX5_IPV4_FRAG_OFFSET_MASK))
		return rte_flow_error_set(error, ENOTSUP,
					  RTE_FLOW_ERROR_TYPE_ITEM_LAST,
					  last, "match on following "
					  "fragments not supported");
	/*
	 * Match on fragment_offset spec 0x0001 and last 0x1fff
	 * means MF is 0 and frag-offset is > 0.
	 * This packet is last fragment of fragmented packet.
	 * This is not yet supported in MLX5, return appropriate
	 * error message.
	 */
	if (fragment_offset_spec == RTE_BE16(1) &&
	    fragment_offset_last == RTE_BE16(RTE_IPV4_HDR_OFFSET_MASK))
		return rte_flow_error_set(error, ENOTSUP,
					  RTE_FLOW_ERROR_TYPE_ITEM_LAST,
					  last, "match on last "
					  "fragment not supported");
	/*
	 * Match on fragment_offset spec 0x0001 and last 0x3fff
	 * means MF and/or frag-offset is not 0.
	 * This is a fragmented packet.
	 * Other range values are invalid and rejected.
	 */

p = Ether(src='00:11:22:33:44:55', dst='A4:BF:01:4B:4A:FE')/IP(src='192.168.6.11', dst='10.11.12.13', id=47750)/Raw('X'*666)
pkts=fragment(p, fragsize=500)
sendp(pkts, iface="ens786")



sendp([Ether(dst=RandMAC(),src=RandMAC())/IP(src=RandIP())/Raw('x' * 20)],iface="ens817f0",count=10)


p = Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.14', id=47750)/Raw('X'*666)
pkts=fragment(p, fragsize=500)
sendp(pkts, iface="ens817f0")


p = Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.11.11', dst='10.11.12.12', id=47750)/TCP(sport=2005,dport=2005)/Raw('X'*666)
pkts=fragment(p, fragsize=200)
sendp(pkts, iface="ens817f0")



TCP(sport=1,dport=2001)




p=Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.13', id=47750)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)

p=Ether(src='00:11:22:33:44:66', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.13', id=47750)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)

p=Ether(src='00:11:22:33:44:55', dst='63E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.13', id=47750)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)
p=Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.12', dst='10.11.12.13', id=47750)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)
p=Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.14', id=47750)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)
p=Ether(src='00:11:22:33:44:55', dst='3E:8D:2E:0C:ED:36')/IP(src='192.168.6.11', dst='10.11.12.13', id=47751)/Raw('X'*666); pkts=fragment(p, 500)
sendp(pkts,iface="ens786",count=1,inter=1)





=checksum offloads============================

VF 
./dpdk-testpmd -c 0xff -n 4  -a 0000:b2:01.0   -a 0000:b2:01.1 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --portmask=0x3 --enable-rx-cksum --rxq=1 --txq=1

set fwd csum
set verbose 1
start


1.good ip checksum + good udp checksum.

pkt = Ether(dst="0E:46:A3:7C:22:22")/IP(dst="10.114.106.71", src="192.168.10.1")/TCP(sport=1,dport=2001)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)


2.bad ip checksum + bad udp checksum
pkt = Ether(dst="3E:8D:2E:0C:ED:36")/IP(dst="10.114.106.71", src="192.168.10.1",chksum=0x0)/UDP(sport=1,dport=2001,chksum=0x1234)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)

3.good ip checksum + bad udp checksum
pkt = Ether(dst="3E:8D:2E:0C:ED:36")/IP(dst="10.114.106.71", src="192.168.10.1")/UDP(sport=1,dport=2001,chksum=0x1234)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)


4.bad ip checksum + good udp checksum
pkt = Ether(dst="3E:8D:2E:0C:ED:36")/IP(dst="10.114.106.71", src="192.168.10.1",chksum=0x0)/UDP(sport=1,dport=2001)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)



https://jira.devtools.intel.com/browse/DPDK-7134?jql=project%20%3D%20DPDK%20AND%20text%20~%20PKT_TX_UDP_CKSUM



810网卡的IAVF驱动不支持GTP（UDP）隧道的checksum卸载
testpmd> show port 0 tx_offload capabilities
Tx Offloading Capabilities of port 0 :
  Per Queue :
  Per Port  : VLAN_INSERT IPV4_CKSUM UDP_CKSUM TCP_CKSUM SCTP_CKSUM TCP_TSO OUTER_IPV4_CKSUM QINQ_INSERT VXLAN_TNL_TSO GRE_TNL_TSO IPIP_TNL_TSO GENEVE_TNL_TSO MULTI_SEGS MBUF_FAST_FREE

testpmd>

普通IPv6可以的。
========================================================================================================================================================================================================
参考如下：
VF 
./dpdk-testpmd -c 0xff -n 4  -a 0000:18:01.0   --file-prefix=vf0 --log-level=net_iavf:8  -- -i --portmask=0x3 --enable-rx-cksum --rxq=1 --txq=1

port stop all
csum set udp hw 0
csum set udp hw 1

set fwd csum
set verbose 1
port start all
start


testpmd> port 0/queue 0: received 1 packets
  src=52:00:00:00:00:00 - dst=3E:8D:2E:0C:ED:36 - type=0x86dd - length=108 - nb_segs=1 - hw ptype: L2_ETHER L3_IPV6_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV6 L4_UDP  - l2_len=14 - l3_len=40 - l4_len=8 - Receive queue=0x0
  ol_flags: RTE_MBUF_F_RX_L4_CKSUM_BAD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN
-----------------
port=0, mbuf=0x11e33cb240, pkt_len=108, nb_segs=1:
rx: l2_len=14 ethertype=86dd l3_len=40 l4_proto=17 l4_len=8 flags=RTE_MBUF_F_RX_L4_CKSUM_BAD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN
tx: m->l2_len=14 m->l3_len=40 m->l4_len=8
tx: flags=RTE_MBUF_F_TX_UDP_CKSUM RTE_MBUF_F_TX_IPV6

=======================================================================================================================================================================
发包
sendp([Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IPv6(src="::1")/UDP(chksum=0xf)/("X"*46)], iface="ens786")

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
debug

[root@dcpae-centos-64-jack ~]# tcpdump -xxx -vvv -nnn -i ens786
dropped privs to tcpdump
tcpdump: listening on ens786, link-type EN10MB (Ethernet), capture size 262144 bytes
21:28:05.678760 IP6 (hlim 64, next-header UDP (17) payload length: 54) ::1.53 > ::1.53: [bad udp cksum 0x000f -> 0x0f27!] 22616 updateDA% [b2&3=0x5858] [22616a] [22616q] [22616n] [22616au][|domain]
        0x0000:  3e8d 2e0c ed36 5200 0000 0000 86dd 6000
        0x0010:  0000 0036 1140 0000 0000 0000 0000 0000
        0x0020:  0000 0000 0001 0000 0000 0000 0000 0000
        0x0030:  0000 0000 0001 0035 0035 0036 000f 5858
        0x0040:  5858 5858 5858 5858 5858 5858 5858 5858
        0x0050:  5858 5858 5858 5858 5858 5858 5858 5858
        0x0060:  5858 5858 5858 5858 5858 5858
21:28:05.679405 IP6 (hlim 64, next-header UDP (17) payload length: 54) ::1.53 > ::1.53: [udp sum ok] 22616 updateDA% [b2&3=0x5858] [22616a] [22616q] [22616n] [22616au][|domain]
        0x0000:  0200 0000 0001 0e46 a37c 2222 86dd 6000
        0x0010:  0000 0036 1140 0000 0000 0000 0000 0000
        0x0020:  0000 0000 0001 0000 0000 0000 0000 0000
        0x0030:  0000 0000 0001 0035 0035 0036 0f27 5858
        0x0040:  5858 5858 5858 5858 5858 5858 5858 5858
        0x0050:  5858 5858 5858 5858 5858 5858 5858 5858
        0x0060:  5858 5858 5858 5858 5858 5858



sendp([Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IPv6(src="::1")/UDP(chksum=0xf)/("X"*46)], iface="ens786")

sendp([Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IP(chksum=0x0)/SCTP(chksum=0xf)/("X"*48)], iface="ens786")

sendp([Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IPv6(src="::1")/TCP(chksum=0xf)/("X"*46)], iface="ens786")

sendp([Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IP(chksum=0x0)/UDP(chksum=0xf)/("X"*46)], iface="ens786")

sendp([Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IP(chksum=0x0)/TCP(chksum=0xf)/("X"*46)], iface="ens786")



not support in VF port

#csum set outer-udp hw 0
#rx_vxlan_port add 4789 0

#csum set outer-udp hw 1
#rx_vxlan_port add 4789 1

port stop all

csum set ip hw 0
csum set udp hw 0
csum set tcp hw 0
csum set sctp hw 0
csum set outer-ip hw 0
csum parse-tunnel on 0


csum set ip hw 1
csum set udp hw 1
csum set tcp hw 1
csum set sctp hw 1
csum set outer-ip hw 1
csum parse-tunnel on 1

set fwd csum
set verbose 1
port start all
start



pkt=Ether(dst="3E:8D:2E:0C:ED:36")/IP(dst="192.168.0.21",chksum=0x0)/UDP(dport=2152,chksum=0x1234)/GTP_U_Header(gtp_type=255, teid=0x123456)\
/IP(dst="192.168.0.1", src="192.168.10.1",chksum=0x0)/UDP(chksum=0x1234)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)

sendp([Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IPv6(src="::1")/UDP(chksum=0xf)/("X"*46)], iface="ens786")



p5=Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IPv6()/TCP(sport=22, chksum=0xe38)/("X"*48)
sendp(p5,iface="ens786",count=1,inter=1)

p6=Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IPv6()/UDP(sport=22, chksum=0xe38)/("X"*48)
sendp(p6,iface="ens786",count=1,inter=1)

p7=Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")/IPv6()/SCTP(sport=22, chksum=0x0)/("X"*48)
sendp(p7,iface="ens786",count=1,inter=1)



./dpdk-testpmd -c 0xff -n 4  -a 0000:b2:00.0  --file-prefix=PF --log-level=net_iavf:8  -- -i --rxq=16 --txq=16
PF
./dpdk-testpmd -c 0xff -n 4  -a 0000:b2:00.0  --file-prefix=PF --log-level=net_iavf:8  -- -i --portmask=0x3 --enable-rx-cksum --rxq=1 --txq=1




port stop all

csum set ip hw 0
csum set udp hw 0
csum set tcp hw 0
csum set sctp hw 0
csum set outer-ip hw 0
csum parse-tunnel on 0
csum set outer-udp hw 0
rx_vxlan_port add 4789 0


set fwd csum
set verbose 1
port start all
start

----------------------------------------------------------------

port stop all
csum set udp hw 0
csum set udp hw 1

set fwd csum
set verbose 1
port start all
start
===========================================

Driver version：version: 1.6.7.1
Firmware version：3.10 0x8000dc37 1.3106.0
DPDK version：19.11
Or DDP version：
OS/kernel version:
Test step:
CPU info：]
============================



arp1=Ether(src=“00:0c:29:e2:bb:15”,dst=“FF:FF:FF:FF:FF:FF”)/ARP(op=1,hwsrc=“00:0c:29:e2:bb:15”,hwdst=“00:00:00:00:00:00”,psrc=“192.168.80.250”,pdst=“192.168.80.251”)


Ether(dst="3E:8D:2E:0C:ED:36", src="52:00:00:00:00:00")


Ether(src=“00:0c:29:e2:bb:15”,dst=“FF:FF:FF:FF:FF:FF”)/ARP()

arp1=Ether(dst="40:A6:B7:67:22:84", src="00:0c:29:e2:bb:86")/ ARP(op=1,hwsrc="00:0c:29:e2:bb:15",hwdst="00:00:00:00:00:00",psrc="192.168.80.250",pdst="192.168.80.251")
sendp(arp1,iface="ens786",count=1,inter=1)

arp1=Ether(dst="40:A6:B7:67:22:84", src="00:0c:29:e2:bb:85")/ ARP(op=1,hwsrc="00:0c:29:e2:bb:15",hwdst="00:00:00:00:00:00",psrc="192.168.80.250",pdst="192.168.80.251")
sendp(arp1,iface="ens786",count=1,inter=1)




***********************ARP packet************************
flow create 0 ingress pattern eth type is 0x0806 / end actions rss types eth end key_len 0 queues end / end




l3=Ether(dst="6a:0f:d0:b6:4b:9b", src="00:0c:29:e2:bb:86")/IP(dst="1.1.1.1", src="192.168.10.1")/TCP(sport=0,dport=2002)/("X"*480)
sendp(l3,iface="ens801",count=10000000,inter=1)




./dpdk-testpmd -c 0xff -n 4  -w 0000:b2:01.0 --file-prefix=PF --log-level='.*,8'  -- -i --forward-mode=rxonly --rxq=4 --txq=4







testpmd> set fwd txonly
Set txonly packet forwarding mode
testpmd> set txpkts 1000
testpmd> set eth-peer 0 70:C7:F2:C0:4F:97
testpmd> set  eth-peer 1 70:C7:F2:C0:4F:9



./t-rex-64  -f cap2/imix_64_fast.yaml -m 10gbps -d 200 -c 10



./t-rex-64  -f cap2/imix_64_fast.yaml -m 50gbps -d 200 -c 17


start -f cap2/imix_64_fast.yaml -m 10mbps -a




stateless

./t-rex-64  -i


./trex-console

start -f stl/udp_1pkt_simple.py -m 10gbps

tui

----------------------------

Thash


./dpdk-testpmd -c 0x1f -n 4  -a 0000:18:01.0  --file-prefix=vf0 --log-level=net_iavf:8 -- -i --forward-mode=rxonly --rxq=4 --txq=4

http://doc.dpdk.org/dts/test_plans/kernelpf_iavf_test_plan.html?highlight=rss%20hash%20key#test-case-vf-rss-hash-key

http://doc.dpdk.org/dts/test_plans/ice_advanced_iavf_rss_test_plan.html#


port config 0 rss-hash-key ipv4 1b9d58a4b961d9cd1c56ad1621c3ad51632c16a5d16c21c3513d132c135d132c13ad1531c23a51d6ac49879c499d798a7d949c8a


045F2A40EB6DC0AEE05D
8F8D556CBC0BF7AAFD3E
354E8B89CE4942489CFC
93426882B20EAC8BD2BD
3D7144E3FAD23535F2E9
8555
52-Byte default



intel_rss_key
Assume that the random key byte-stream is:
0x6d, 0x5a, 0x56, 0xda, 0x25, 0x5b, 0x0e, 0xc2,
0x41, 0x67, 0x25, 0x3d, 0x43, 0xa3, 0x8f, 0xb0,
0xd0, 0xca, 0x2b, 0xcb, 0xae, 0x7b, 0x30, 0xb4,
0x77, 0xcb, 0x2d, 0xa3, 0x80, 0x30, 0xf2, 0x0c,
0x6a, 0x42, 0xb7, 0x3b, 0xbe, 0xac, 0x01, 0xfa,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00



static uint8_t rss_intel_key[40] = {
	0x6D, 0x5A, 0x56, 0xDA, 0x25, 0x5B, 0x0E, 0xC2,
	0x41, 0x67, 0x25, 0x3D, 0x43, 0xA3, 0x8F, 0xB0,
	0xD0, 0xCA, 0x2B, 0xCB, 0xAE, 0x7B, 0x30, 0xB4,
	0x77, 0xCB, 0x2D, 0xA3, 0x80, 0x30, 0xF2, 0x0C,
	0x6A, 0x42, 0xB7, 0x3B, 0xBE, 0xAC, 0x01, 0xFA,
};


port config all rss all
port config 0 rss-hash-key ipv4 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000
port config 0 rss-hash-key ipv4-udp 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000
port config 0 rss-hash-key ipv4-tcp 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000




MAC_IPV4_ALL
port config all rss all
port config 0 rss-hash-key ipv4 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000
flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 end key_len 0 queues end / end


sendp([Ether(dst="CE:45:C8:0F:35:6D")/IP(dst="161.142.100.80",src="66.9.149.187")/("X"*480)],iface="ens804f0")------------>(DIP SIP)RSS hash=0x323e8fc2


testpmd> port 0/queue 2: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=514 - nb_segs=1 - RSS hash=0x323e8fc2 - RSS queue=0x2 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_NONFRAG  - sw ptype: L2_ETHER L3_IPV4  - l2_len=14 - l3_len=20 - Receive queue=0x2
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN



sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="65.69.140.83",src="199.92.111.2")/("X"*480)],iface="ens801")--------------->(DIP SIP) RSS hash=0xd718262a

testpmd> port 0/queue 2: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=514 - nb_segs=1 - RSS hash=0xd718262a - RSS queue=0x2 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_NONFRAG  - sw ptype: L2_ETHER L3_IPV4  - l2_len=14 - l3_len=20 - Receive queue=0x2
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN


---------------
MAC_IPV4_UDP_ALL
port config all rss all
port config 0 rss-hash-key ipv4-udp 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000
flow create 0 ingress pattern eth / ipv4 / udp / end actions rss types ipv4-udp end key_len 0 queues end / end

sendp([Ether(dst="B4:96:91:AE:6C:B9")/IP(dst="161.142.100.80",src="66.9.149.187")/UDP(dport=1766,sport=2794)/("X"*480)],iface="ens804f0")

sendp([Ether(dst="CE:45:C8:0F:35:6D")/IP(dst="161.142.100.80",src="66.9.149.187")/UDP(dport=1766,sport=2794)/("X"*480)],iface="ens804f0")


sendp([Ether(dst="CE:45:C8:0F:35:6D")/IP(dst="161.142.100.80",src="66.9.149.187", proto =30)/UDP(dport=1766,sport=2794)/("X"*480)],iface="ens804f0")

testpmd> port 0/queue 3: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=522 - nb_segs=1 - RSS hash=0x38a3076b - RSS queue=0x3 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x3
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN


SourceAddress, DestinationAddress, SourcePort, DestinationPort:
Input[12] = @12-15, @16-19, @20-21, @22-23
Result = ComputeHash(Input, 12)
+protocol

确定硬件是怎么计算hash值的，特别是使用的key及key的length

SourceAddress, DestinationAddress, SourcePort, DestinationPort, Protocol
or
Protocol, SourceAddress, DestinationAddress, SourcePort, DestinationPort

or 



-----------------------

MAC_IPV4_UDP_L4DST
 
./dpdk-testpmd -c 0x1f -n 4  -a 0000:18:01.0  --file-prefix=vf0  -- -i --forward-mode=rxonly --rxq=4 --txq=4
port config all rss all
port config 0 rss-hash-key ipv4 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000

flow create 0 ingress pattern eth / ipv4 / udp / end actions rss types ipv4-udp l4-dst-only end key_len 0 queues end / end

sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="161.142.100.80",src="66.9.149.187")/UDP(dport=1766,sport=2794)/("X"*480)],iface="ens801")


testpmd> port 0/queue 2: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=522 - nb_segs=1 - RSS hash=0xa512a6ca - RSS queue=0x2 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x2
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN



>>> sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="161.142.100.80",src="66.9.149.187")/UDP(dport=1766,sport=2794)/("X"*480)],iface="ens801")
.
Sent 1 packets.
>>>
>>>
>>> sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="161.142.100.88",src="66.9.149.187")/UDP(dport=1766,sport=2794)/("X"*480)],iface="ens801")
.
Sent 1 packets.
>>> sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="161.142.100.80",src="66.9.149.18")/UDP(dport=1766,sport=2794)/("X"*480)],iface="ens801")
.
Sent 1 packets.
>>>
>>> sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="161.142.100.80",src="66.9.149.18")/UDP(dport=1766,sport=2796)/("X"*480)],iface="ens801")
.
Sent 1 packets.


{RTE_IPV4(0, 0, 0, 0), RTE_IPV4(0, 0, 0, 0),
        0, 1766, 0xd2d0a5de, 0x5c2b394a},


this can works




---------------------------------------------------------------------------------------------------------------------

test_thash



sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="65.69.140.83",src="199.92.111.2")/UDP(dport=4739,sport=14230)/("X"*480)],iface="ens801")



flow create 0 ingress pattern eth / ipv4 / tcp / end actions rss types ipv4-tcp l4-dst-only end key_len 0 queues end / end



sendp([Ether(dst="6A:0F:D0:B6:4B:9B")/IP(dst="161.142.100.80",src="66.9.149.187")/TCP(dport=1766,sport=2794)/("X"*480)],iface="ens801")



flow create 0 ingress pattern eth / ipv4 / end actions rss func symmetric_toeplitz types ipv4 end key_len 0 queues end / end


flow create 0 ingress pattern eth / ipv4 / udp / end actions rss types ipv4-udp end key_len 0 queues end / end

sendp([Ether(dst="6A:0F:D0:B6:4B:9B", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.1", src="192.168.0.2")/UDP(sport=22,dport=33)/("X"*480)],iface="ens801")
sendp([Ether(dst="6A:0F:D0:B6:4B:9B", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.1", src="192.168.0.2")/UDP(sport=32,dport=23)/("X"*480)],iface="ens801")
sendp([Ether(dst="6A:0F:D0:B6:4B:9B", src="68:05:CA:BB:26:E0")/IP(dst="192.168.1.1", src="192.168.0.2")/UDP(sport=22,dport=23)/("X"*480)],iface="ens801")
sendp([Ether(dst="6A:0F:D0:B6:4B:9B", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.1", src="192.168.1.2")/UDP(sport=22,dport=23)/("X"*480)],iface="ens801")



----------------------------------------------------------------------------------------------------
symmetric MAC_IPV4


port config all rss all
port config 0 rss-hash-key ipv4 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000



flow create 0 ingress pattern eth / ipv4 / end actions rss func symmetric_toeplitz types ipv4 end key_len 0 queues end / end



-------------------------------------
MAC_IPV4_L3DST:
port config all rss all
port config 0 rss-hash-key l3-dst-only 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000

flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end







testpmd> port 0/queue 1: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=522 - nb_segs=1 - RSS hash=0x1db6cffd - RSS queue=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x1
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd> port 0/queue 1: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=522 - nb_segs=1 - RSS hash=0x1db6cffd - RSS queue=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x1
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd> port 0/queue 1: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=522 - nb_segs=1 - RSS hash=0x1db6cffd - RSS queue=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x1
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN
port 0/queue 1: received 1 packets
  src=A4:BF:01:51:39:21 - dst=6A:0F:D0:B6:4B:9B - type=0x0800 - length=522 - nb_segs=1 - RSS hash=0x1db6cffd - RSS queue=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x1
  ol_flags: RTE_MBUF_F_RX_RSS_HASH RTE_MBUF_F_RX_L4_CKSUM_GOOD RTE_MBUF_F_RX_IP_CKSUM_GOOD RTE_MBUF_F_RX_OUTER_L4_CKSUM_UNKNOWN



Thash

RTE>>thash_autotest
 + ------------------------------------------------------- +
 + Test Suite : thash autotest
 + ------------------------------------------------------- +
**********rte_softrss RTE_THASH_V4_L3_LEN=2 i =0  rss_l3=3c76361c
***********rte_softrss RTE_THASH_V4_L4_LEN =3 i =0  rss_l3l4=3c76361c
**********rte_softrss_be RTE_THASH_V4_L3_LEN=2 i =0  rss_l3l4=3c76361c
**********rte_softrss_be RTE_THASH_V4_L4_LEN=3 i =0  rss_l3l4=3c76361c


需要修改代码可以保持一致



{RTE_IPV4(0, 0, 0, 0), RTE_IPV4(161, 142, 100, 80),
        0, 0, 0x323e8fc2, 0x51ccc178},
{RTE_IPV4(0,0,0,0), RTE_IPV4(161, 142, 100, 80),
        0, 0, 0xd718262a, 0xc626b0ea},


                if(i==1)
                {
                rss_l3 = rte_softrss((uint32_t *)&tuple,
                                1, default_rss_key);
                rss_l3l4 = rte_softrss((uint32_t *)&tuple,
                                1, default_rss_key);
                }

{
                rss_l3 = rte_softrss((uint32_t *)&tuple,
                                RTE_THASH_V4_L3_LEN, default_rss_key);
                rss_l3l4 = rte_softrss((uint32_t *)&tuple,
                                RTE_THASH_V4_L4_LEN, default_rss_key);


}







#include<stdlib.h>
#include<signal.h>
#include<getopt.h>

#include<rte_eal.h>
#include<rte_ethdev.h>
#include<rte_thash.h>


#define RTE_TEST_RX_DESC_DEFAULT 512
#define RTE_TEST_TX_DESC_DEFAULT 512
static volatile bool force_quit = false;
static uint8_t nb_rx_queue = 1;
static uint16_t listen_port = 61440;
static uint16_t nb_ports_available = 0;

static struct action_rss_data {
    struct rte_flow_action_rss conf;
    uint16_t queue[128];
}rss_data;

static uint8_t rss_key[] = {
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
    0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A, 0x6D, 0x5A,
};

static struct rte_eth_conf port_conf = {
    .rxmode = {
        .mq_mode = ETH_MQ_RX_RSS,
        .max_rx_pkt_len = 9018,
        .split_hdr_size = 0,
        .offloads = DEV_RX_OFFLOAD_IPV4_CKSUM |
                    DEV_RX_OFFLOAD_UDP_CKSUM |
                    DEV_RX_OFFLOAD_TCP_CKSUM |
                    DEV_RX_OFFLOAD_SCATTER |
                    DEV_RX_OFFLOAD_JUMBO_FRAME,
    },
    .rx_adv_conf = {
        .rss_conf = {
            .rss_key = rss_key,
            .rss_key_len = sizeof(rss_key),
            .rss_hf = ETH_RSS_IPV4 | \
	                ETH_RSS_FRAG_IPV4 | \
                    ETH_RSS_NONFRAG_IPV4_OTHER | \
                    ETH_RSS_IPV6 | \
                    ETH_RSS_FRAG_IPV6 | \
                    ETH_RSS_NONFRAG_IPV6_OTHER | \
                    ETH_RSS_NONFRAG_IPV4_UDP | \
	                ETH_RSS_NONFRAG_IPV6_UDP | \
                    ETH_RSS_NONFRAG_IPV4_TCP | \
	                ETH_RSS_NONFRAG_IPV6_TCP,
        },
    },
    .txmode = {
        .mq_mode = ETH_MQ_TX_NONE,
    },
};

static int test_setup_flow(uint16_t proto, uint16_t listen_port, uint16_t portid) {
    struct rte_flow_attr attr = {};
    struct rte_flow_item items[4] = {};
    struct rte_flow_error error = {};
    int ret;

    attr = (const struct rte_flow_attr) {
        .group = 0,
        .priority = 0,
        .ingress = 1,
        .egress = 0,
        .reserved = 0,
    };

    struct rte_flow_item_eth item_eth_spec = {};
    struct rte_flow_item_eth item_eth_mask = {};

    struct rte_flow_item_ipv4 item_ipv4_spec;
    struct rte_flow_item_ipv4 item_ipv4_mask;
    memset(&item_ipv4_spec, 0, sizeof(struct rte_flow_item_ipv4));
    memset(&item_ipv4_mask, 0, sizeof(struct rte_flow_item_ipv4));

    items[0] = (struct rte_flow_item) {
        .type = RTE_FLOW_ITEM_TYPE_ETH,
        .spec = &item_eth_spec,
        .mask = &item_eth_mask,
    };

    items[1] = (struct rte_flow_item) {
        .type = RTE_FLOW_ITEM_TYPE_IPV4,
        .spec = &item_ipv4_spec,
        .mask = &item_ipv4_mask,
    };

    struct rte_flow_item_udp item_udp_spec = {
        .hdr = {
            .src_port = 0,
            .dst_port = htons(listen_port),
         }
    };
    struct rte_flow_item_udp item_udp_mask = {
        .hdr = {
            .src_port = 0,
            .dst_port = 0xFFFF,
        }
    };

    struct rte_flow_item_tcp item_tcp_spec = {
        .hdr = {
            .src_port = 0,
            .dst_port = htons(listen_port),
        }
    };
    struct rte_flow_item_tcp item_tcp_mask = {
        .hdr = {
            .src_port = 0,
            .dst_port = 0xFFFF,
        }
    };

    switch (proto) {
        case IPPROTO_UDP:
            items[2] = (struct rte_flow_item) {
                .type = RTE_FLOW_ITEM_TYPE_UDP,
                .spec = &item_udp_spec,
                .mask = &item_udp_mask,
            };
            break;
        case IPPROTO_TCP:
            items[2] = (struct rte_flow_item) {
                .type = RTE_FLOW_ITEM_TYPE_TCP,
                .spec = &item_tcp_spec,
                .mask = &item_tcp_mask,
            };
            break;
        default: assert(false);
    }

    items[3] = (struct rte_flow_item) {
        .type = RTE_FLOW_ITEM_TYPE_END,
    };

    struct action_rss_data rss_data = {
        .conf = (struct rte_flow_action_rss) {
            .func = RTE_ETH_HASH_FUNCTION_DEFAULT,
            .level = 0,
            .types = port_conf.rx_adv_conf.rss_conf.rss_hf,
            .key_len = sizeof(rss_key),
            .queue_num = nb_rx_queue,
            .key = rss_key,
            .queue = rss_data.queue,
        },
        .queue = { 0 },
    };

    struct rte_flow_action_rss action_rss;
    uint8_t i;
    for (i = 0; i< nb_rx_queue; i++) {
        rss_data.queue[i] = i;
    }
    action_rss = rss_data.conf;

    const struct rte_flow_action actions[] = {
        { RTE_FLOW_ACTION_TYPE_VF,
            &(const struct rte_flow_action_vf) {
                    .original = 1,
                }
        },
        { RTE_FLOW_ACTION_TYPE_RSS,
            &action_rss,
        },
        { RTE_FLOW_ACTION_TYPE_END, NULL},
    };
    
    struct rte_flow *flow;
    flow = rte_flow_create(portid, &attr, items, actions, &error);
    if (flow == NULL) {
        printf("[ERROR] Create flow failed, ret=%d, err=%s\n", ret, error.message);
        return -1;
    }
    return 0;
}

static uint16_t test_check_rss(struct rte_mbuf *m) {
    uint32_t rss_hw, rss_soft;
    rss_hw = m->hash.rss;
    struct rte_ether_hdr *eth = rte_pktmbuf_mtod(m, struct rte_ether_hdr*);
    struct rte_ipv4_hdr *iph = (void *)(eth + 1);
    struct rte_tcp_hdr *tph;
    struct rte_udp_hdr *udh;
    struct rte_ipv4_tuple rss_v4;

    rss_v4.src_addr = rte_be_to_cpu_32(iph->src_addr);
    rss_v4.dst_addr = rte_be_to_cpu_32(iph->dst_addr);
    switch (iph->next_proto_id) {
        case IPPROTO_TCP:
            tph = (void*)iph + ((iph->version_ihl & 0x0f) << 2);
            rss_v4.sport = rte_be_to_cpu_16(tph->src_port);
            rss_v4.dport = rte_be_to_cpu_16(tph->dst_port);
            break;
        case IPPROTO_UDP:
            udh = (void*)iph + ((iph->version_ihl & 0x0f) << 2);
            rss_v4.sport = rte_be_to_cpu_16(udh->src_port);
            rss_v4.dport = rte_be_to_cpu_16(udh->dst_port);
            break;
    }
    rss_soft = rte_softrss((uint32_t *)&rss_v4,
        RTE_THASH_V4_L4_LEN, rss_key);
    printf("\nhw rss 0x%x, soft rss 0x%x\n", rss_hw, rss_soft);
}


static void print_usage() {
    fprintf(stderr, "   -p, listen port\n"
            "   -n, number of rx_queues for each port\n"
            "   -t, setup one tx_queue at least\n");
}

static void signal_handler(int signum) {
    if (signum == SIGINT || signum == SIGTERM) {
        printf("\n\nSignal %d received, preparing to exit...\n", signum);
        force_quit = true;
    }
}

static void test_main_loop(void) {
    struct rte_mbuf *pkts_burst[256];
    struct rte_mbuf *m;
    unsigned lcore_id;
    uint16_t i, j, k, nb_rx;

    lcore_id = rte_lcore_id();
    if (lcore_id != rte_get_main_lcore()) {
        return;
    }

    while (!force_quit) {
        for (i = 0; i < nb_ports_available; i++) {
            for (j = 0; j < nb_rx_queue; j ++) {
                nb_rx = rte_eth_rx_burst(i, j, pkts_burst, 64);
                if (nb_rx > 0) {
                    for (k = 0; k < nb_rx; k++) {
                        m = pkts_burst[k];
                        rte_prefetch0(rte_pktmbuf_mtod(m, void *));
                        test_check_rss(m);
                        rte_pktmbuf_free(m);
                    }
                }
            }
        }
    }
}

static void disable_broadcast(uint16_t portid) {
    int ret;
    struct rte_ether_addr maddr = {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
    };
    ret = rte_eth_dev_mac_addr_add(portid, &maddr, 0);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Failed to set broadcast mac\n");
    }
    ret = rte_eth_dev_mac_addr_remove(portid, &maddr);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Failed to remove broadcast mac\n");
    }
}

int main(int argc, char **argv) {
    int ret, nb_ports;
    uint16_t nb_rxd = RTE_TEST_RX_DESC_DEFAULT, nb_txd = RTE_TEST_TX_DESC_DEFAULT;
    uint16_t portid;

    struct rte_mempool *pktmbuf_pool;

    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Invalid EAL arguments\n");
    }
    argc -= ret;
    argv += ret;

    uint32_t nb_tx_queue = 1;
    int ch;
    while ((ch = getopt(argc, argv, "p:n:t:")) != -1) {
        switch (ch) {
            case 'p':
                sscanf(optarg, "%hu", &listen_port);
                break;
            case 'n':
                sscanf(optarg, "%hhu", &nb_rx_queue);
                break;
            case 't':
                sscanf(optarg, "%u", &nb_tx_queue);
                break;
            default:
                print_usage();
                break;
        }
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    nb_ports = rte_eth_dev_count_avail();
    if (nb_ports == 0) {
        rte_exit(EXIT_FAILURE, "No Ethernet ports - bye\n");
    }

    pktmbuf_pool = rte_pktmbuf_pool_create(
        "mbuf_pool", 8192U, 256, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id()
    );

    RTE_ETH_FOREACH_DEV(portid) {
        struct rte_eth_rxconf rxq_conf;
        struct rte_eth_txconf txq_conf;
        struct rte_eth_conf local_port_conf = port_conf;
        struct rte_eth_dev_info dev_info;

        rte_eth_dev_info_get(portid, &dev_info);

        if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE) {
            local_port_conf.txmode.offloads |= DEV_TX_OFFLOAD_MBUF_FAST_FREE;
        }
        struct rte_flow_error error;
        ret = rte_eth_dev_configure(portid, nb_rx_queue, nb_tx_queue, &port_conf);
        ret = rte_flow_isolate(portid, 1, &error);
        if (ret != 0) {
            printf("[WARNING] flow isolate failed\n");
        }
        rte_eth_promiscuous_disable(portid);
        rte_eth_allmulticast_disable(portid);

        ret = rte_eth_dev_adjust_nb_rx_tx_desc(portid, &nb_rxd, &nb_txd);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot adjust number of descriptors: err=%d, port=%u\n",
                     ret, portid);
        }
        rxq_conf = dev_info.default_rxconf;
        rxq_conf.offloads = local_port_conf.rxmode.offloads;
        uint16_t i;
        for (i = 0; i < nb_rx_queue; i++) {
            ret = rte_eth_rx_queue_setup(portid, i, nb_rxd, rte_eth_dev_socket_id(portid),
                                     &rxq_conf, pktmbuf_pool);
            if (ret < 0) {
                rte_exit(EXIT_FAILURE, "rte_eth_rx_queue_setup:err=%d, port=%u\n",
                        ret, portid);
            }
        }
        txq_conf = dev_info.default_txconf;
        for (i = 0; i < nb_tx_queue; i++) {
            ret = rte_eth_tx_queue_setup(portid, i, nb_txd, rte_eth_dev_socket_id(portid),
                                     &txq_conf);
            if (ret < 0) {
                rte_exit(EXIT_FAILURE, "rte_eth_tx_queue_setup:err=%d, port=%u\n",
                        ret, portid);
            }
        }
        
        ret = rte_eth_dev_start(portid);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "rte_eth_dev_start:err=%d, port=%u\n", ret, portid);
        }

        disable_broadcast(portid);

        ret = test_setup_flow(IPPROTO_UDP, listen_port, portid);
        if (ret != 0) {
            printf("[ERROR] setup udp flow failed\n");
            exit(-1);
        }
        ret = test_setup_flow(IPPROTO_TCP, listen_port, portid);
        if (ret != 0) {
            printf("[ERROR] setup tcp flow failed\n");
            exit(-1);
        }
        nb_ports_available++;
    }
    test_main_loop();
    RTE_ETH_FOREACH_DEV(portid) {
        rte_eth_dev_stop(portid);
        rte_eth_dev_close(portid);
    }
    printf("Bye...\n");


两口bond，每个PFU接管6个Vf，2个N3，2个N6，2个RAW

./dpdk-testpmd -c 0xff -a 0000:1a:11.0  -n 4 --log-level=8  --log-level=pmd.net.iavf.init:8  --log-level=pmd.net.iavf.driver:8 -- -i --rxq=16 --txq=16   --forward-mode=rxonly


./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2    --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16



                                            N30       N60           RAW0          N31           N61           RAW1
python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2

python3 dpdk-devbind.py --bind=vfio-pci 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5

./dpdk-testpmd -c 0xff -a 0000:1a:01.0  -n 4 -- -i --rxq=16 --txq=16   --forward-mode=rxonly 


./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

 
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 -a 0000:1a:11.4 -a 0000:1a:11.5    --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16



./dpdk-testpmd -c 0xff -a 0000:1a:11.0   -n 4 --log-level=8  --log-level=pmd.net.iavf.init:8  --log-level=pmd.net.iavf.driver:8 -- -i --rxq=16 --txq=16   --forward-mode=rxonly






not reproduction

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5  --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


not reproduction

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0  --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3  --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


reproduction

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


not reproduction
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0  -a 0000:1a:11.0 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3  -a 0000:1a:11.3 --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


reproduction

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:11.0 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:11.3 --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16





not reproduction

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:11.0   -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:11.3 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16



PFU

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

 
 IPU
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3   --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16




one

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2  -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16





journalctl  --since "2022-1-7 00:20" --dmesg







匹配业务地址打mark
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / rss / end

上行基于内层SIP做RSS
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

下行基于外层dip做RSS
flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end


import sys
from scapy.contrib.gtp import *


pkt = Ether(dst="3E:31:44:23:19:FB")/IP(dst="192.168.0.1")/UDP(sport=23,dport=2152)\
/GTP_U_Header(gtp_type=255, teid=0x123456)/IP(dst="192.168.1.1", src="192.168.2.1")/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)


pkt = Ether(dst="3E:31:44:23:19:FB")/IP(dst="192.168.2.1")/UDP(sport=23,dport=2152)/("X"*480)

sendp(pkt,iface="ens786",count=1,inter=1)



testpmd> port 0/queue 2: received 1 packets
  src=00:23:7D:6D:61:37 - dst=3E:31:44:23:19:FB - type=0x0800 - length=550 - nb_segs=1 - RSS hash=0xe60786c2 - RSS queue=0x2 - FDIR matched ID=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN TUNNEL_GTPU INNER_L3_IPV4_EXT_UNKNOWN INNER_L4_NONFRAG  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - VXLAN packet: packet type =32913, Destination UDP port =2152, VNI = 4660 - Receive queue=0x2
  ol_flags: PKT_RX_RSS_HASH PKT_RX_FDIR PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_FDIR_ID PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
testpmd> port 0/queue 2: received 1 packets
  src=00:23:7D:6D:61:37 - dst=3E:31:44:23:19:FB - type=0x0800 - length=522 - nb_segs=1 - RSS hash=0xe60786c2 - RSS queue=0x2 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_UDP  - sw ptype: L2_ETHER L3_IPV4 L4_UDP  - l2_len=14 - l3_len=20 - l4_len=8 - Receive queue=0x2
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN







flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / rss / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / rss / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / rss / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / rss / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end


    
    return ret;
}



flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / end actions queue index 1 / mark id 1 / end
