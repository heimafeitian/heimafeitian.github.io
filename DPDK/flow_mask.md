


flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / UDP dst spec 1 dst mask 3 / end actions queue index 1 / mark id 1 / end

flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / UDP dst spec 2 dst mask 3 / end actions queue index 2 / mark id 2 / end


inputset:IP dst, UDP dport
inputset mask:IP dst 0xffffffff, UDP dport:0x3

22.11

flow create 0 ingress pattern raw pattern spec 00112233445500000000000208004500001C0000000000110000C0A80014C0A800150016000100080000 pattern mask 000000000000000000000000000000000000000000000000000000000000FFFFFFFF0000000300000000 / end actions queue index 1 / mark id 1 / end
flow create 0 ingress pattern raw pattern spec 00112233445500000000000208004500001C0000000000110000C0A80014C0A800150016000200080000 pattern mask 000000000000000000000000000000000000000000000000000000000000FFFFFFFF0000000300000000 / end actions queue index 2 / mark id 2 / end


sendp([Ether(dst="00:11:22:33:44:55")/IP(src="192.168.0.20",dst="192.168.0.21")/UDP(sport=22,dport=1)/Raw('x' * 80)],iface="ens786f0") 
sendp([Ether(dst="00:11:22:33:44:55")/IP(src="192.168.0.20",dst="192.168.0.21")/UDP(sport=22,dport=2)/Raw('x' * 80)],iface="ens786f0")




23.11

flow create 0 ingress group 2  pattern raw pattern spec 00112233445500000000000208004500001C0000000000110000C0A80014C0A800150016000100080000 pattern mask 000000000000000000000000000000000000000000000000000000000000FFFFFFFF0000000300000000 / end actions queue index 1 / mark id 1 / end
flow create 0 ingress group 2  pattern raw pattern spec 00112233445500000000000208004500001C0000000000110000C0A80014C0A800150016000200080000 pattern mask 000000000000000000000000000000000000000000000000000000000000FFFFFFFF0000000300000000 / end actions queue index 2 / mark id 2 / end





flow create 0 ingress group 2 pattern raw pattern spec 00000000000000000000000008004500001400004000401000000000000001020304 pattern mask 000000000000000000000000000000000000000000000000000000000000ffffffff / end actions  queue index 3 / mark id 3 / end









[root@dcpae-643-centos-51 app]#
[root@dcpae-643-centos-51 app]#
[root@dcpae-643-centos-51 app]#
[root@dcpae-643-centos-51 app]# ./dpdk-testpmd -c 0xff -n 4  -w 0000:1a:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=4 --txq=4
EAL: Detected 72 lcore(s)
EAL: Detected 2 NUMA nodes
Option -w, --pci-whitelist is deprecated, use -a, --allow option instead
EAL: Detected static linkage of DPDK
EAL: Multi-process socket /var/run/dpdk/vf0/mp_socket
EAL: Selected IOVA mode 'VA'
EAL: No available 2048 kB hugepages reported
EAL: VFIO support initialized
EAL: Using IOMMU type 1 (Type 1)
EAL: Probe PCI driver: net_iavf (8086:1889) device: 0000:1a:01.0 (socket 0)
iavf_execute_vf_cmd(): Cmd 26 not supported
iavf_set_hena(): Failed to execute command of OP_SET_RSS_HENA
iavf_default_rss_disable(): fail to disable default RSS,lack PF support
TELEMETRY: No legacy callbacks, legacy socket not created
Interactive-mode selected
Set rxonly packet forwarding mode
testpmd: create a new mbuf pool <mb_pool_0>: n=203456, size=2176, socket=0
testpmd: preferred mempool ops selected: ring_mp_mc

Warning! port-topology=paired and odd forward ports number, the last port will pair with itself.

Configuring Port 0 (socket 0)
iavf_execute_vf_cmd(): Return failure -5 for cmd 45
iavf_add_del_rss_cfg(): Failed to execute command of OP_ADD_RSS_CFG
iavf_execute_vf_cmd(): Return failure -5 for cmd 45
iavf_add_del_rss_cfg(): Failed to execute command of OP_ADD_RSS_CFG
iavf_configure_queues(): request RXDID[22] in Queue[0]
iavf_configure_queues(): request RXDID[22] in Queue[1]
iavf_configure_queues(): request RXDID[22] in Queue[2]
iavf_configure_queues(): request RXDID[22] in Queue[3]

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event
Port 0: 22:6B:E6:2A:61:27
Checking link statuses...
Done
testpmd> set verbose 1
Change verbose level from 0 to 1
testpmd> start
rxonly packet forwarding - ports=1 - cores=1 - streams=4 - NUMA support enabled, MP allocation mode: native
Logical Core 1 (socket 0) forwards packets on 4 streams:
  RX P=0/Q=0 (socket 0) -> TX P=0/Q=0 (socket 0) peer=02:00:00:00:00:00
  RX P=0/Q=1 (socket 0) -> TX P=0/Q=1 (socket 0) peer=02:00:00:00:00:00
  RX P=0/Q=2 (socket 0) -> TX P=0/Q=2 (socket 0) peer=02:00:00:00:00:00
  RX P=0/Q=3 (socket 0) -> TX P=0/Q=3 (socket 0) peer=02:00:00:00:00:00

  rxonly packet forwarding packets/burst=32
  nb forwarding cores=1 - nb forwarding ports=1
  port 0: RX queue number: 4 Tx queue number: 4
    Rx offloads=0x0 Tx offloads=0x10000
    RX queue: 0
      RX desc=512 - RX free threshold=32
      RX threshold registers: pthresh=0 hthresh=0  wthresh=0
      RX Offloads=0x0
    TX queue: 0
      TX desc=512 - TX free threshold=32
      TX threshold registers: pthresh=0 hthresh=0  wthresh=0
      TX offloads=0x10000 - TX RS bit threshold=32
testpmd>
testpmd>
testpmd>
testpmd> flow create 0 ingress pattern eth / ipv4 dst is 17.0.0.4 / tcp dst spec 1 dst mask 15 / end actions queue index 1 / mark id 1 / end
Flow rule #0 created
testpmd> flow list 0
ID      Group   Prio    Attr    Rule
0       0       0       i--     ETH IPV4 TCP => QUEUE MARK
testpmd> flow create 0 ingress pattern eth / ipv4 dst is 17.0.0.4 / tcp dst spec 2 dst mask 15 / end actions queue index 2 / mark id 2 / end
iavf_fdir_add(): Failed to add rule request due to the rule is already existed
iavf_flow_create(): Failed to create flow
port_flow_complain(): Caught PMD error type 2 (flow rule (handle)): Failed to create parser engine.: Invalid argument
testpmd>
testpmd>
testpmd>
testpmd> flow list 0
ID      Group   Prio    Attr    Rule
0       0       0       i--     ETH IPV4 TCP => QUEUE MARK
testpmd> show port info 0

********************* Infos for port 0  *********************
MAC address: 22:6B:E6:2A:61:27
Device name: 0000:1a:01.0
Driver name: net_iavf
Firmware-version: not available
Devargs:
Connect to socket: 0
memory allocation on the socket: 0
Link status: up
Link speed: 100 Gbps
Link duplex: full-duplex
Autoneg status: On
MTU: 1500
Promiscuous mode: enabled
Allmulticast mode: disabled
Maximum number of MAC addresses: 64
Maximum number of MAC addresses of hash filtering: 0
VLAN offload:
  strip off, filter off, extend off, qinq strip off
Hash key size in bytes: 52
Redirection table size: 64
Supported RSS offload flow types:
  ipv4
  ipv4-frag
  ipv4-tcp
  ipv4-udp
  ipv4-sctp
  ipv4-other
  ipv6
  ipv6-frag
  ipv6-tcp
  ipv6-udp
  ipv6-sctp
  ipv6-other
Minimum size of RX buffer: 1024
Maximum configurable length of RX packet: 9728
Maximum configurable size of LRO aggregated packet: 0
Current number of RX queues: 4
Max possible RX queues: 256
Max possible number of RXDs per queue: 4096
Min possible number of RXDs per queue: 64
RXDs number alignment: 32
Current number of TX queues: 4
Max possible TX queues: 256
Max possible number of TXDs per queue: 4096
Min possible number of TXDs per queue: 64
TXDs number alignment: 32
Max segment number per packet: 0
Max segment number per MTU/TSO: 0
testpmd>
testpmd>
testpmd> show port info 0

********************* Infos for port 0  *********************
MAC address: 22:6B:E6:2A:61:27
Device name: 0000:1a:01.0
Driver name: net_iavf
Firmware-version: not available
Devargs:
Connect to socket: 0
memory allocation on the socket: 0
Link status: up
Link speed: 100 Gbps
Link duplex: full-duplex
Autoneg status: On
MTU: 1500
Promiscuous mode: enabled
Allmulticast mode: disabled
Maximum number of MAC addresses: 64
Maximum number of MAC addresses of hash filtering: 0
VLAN offload:
  strip off, filter off, extend off, qinq strip off
Hash key size in bytes: 52
Redirection table size: 64
Supported RSS offload flow types:
  ipv4
  ipv4-frag
  ipv4-tcp
  ipv4-udp
  ipv4-sctp
  ipv4-other
  ipv6
  ipv6-frag
  ipv6-tcp
  ipv6-udp
  ipv6-sctp
  ipv6-other
Minimum size of RX buffer: 1024
Maximum configurable length of RX packet: 9728
Maximum configurable size of LRO aggregated packet: 0
Current number of RX queues: 4
Max possible RX queues: 256
Max possible number of RXDs per queue: 4096
Min possible number of RXDs per queue: 64
RXDs number alignment: 32
Current number of TX queues: 4
Max possible TX queues: 256
Max possible number of TXDs per queue: 4096
Min possible number of TXDs per queue: 64
TXDs number alignment: 32
Max segment number per packet: 0
Max segment number per MTU/TSO: 0
testpmd>
testpmd>
testpmd> port 0/queue 1: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xa9f80fb1 - RSS queue=0x1 - FDIR matched ID=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x1
  ol_flags: PKT_RX_RSS_HASH PKT_RX_FDIR PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_FDIR_ID PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd> quit
Telling cores to stop...
Waiting for lcores to finish...

  ------- Forward Stats for RX Port= 0/Queue= 1 -> TX Port= 0/Queue= 1 -------
  RX-packets: 1              TX-packets: 0              TX-dropped: 0

  ---------------------- Forward statistics for port 0  ----------------------
  RX-packets: 1              RX-dropped: 0             RX-total: 1
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ----------------------------------------------------------------------------

  +++++++++++++++ Accumulated forward statistics for all ports+++++++++++++++
  RX-packets: 1              RX-dropped: 0             RX-total: 1
  TX-packets: 0              TX-dropped: 0             TX-total: 0
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Done.

Stopping port 0...
Stopping ports...
Done

Shutting down port 0...
Closing ports...
iavf_execute_vf_cmd(): Return failure -5 for cmd 46
iavf_add_del_rss_cfg(): Failed to execute command of OP_DEL_RSS_INPUT_CFG
iavf_execute_vf_cmd(): Return failure -5 for cmd 46
iavf_add_del_rss_cfg(): Failed to execute command of OP_DEL_RSS_INPUT_CFG
Port 0 is closed
Done

Bye...
[root@dcpae-643-centos-51 app]# ip link show ens786
3: ens786: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP mode DEFAULT group default qlen 1000
    link/ether 40:a6:b7:67:22:80 brd ff:ff:ff:ff:ff:ff
    vf 0     link/ether 22:6b:e6:2a:61:27 brd ff:ff:ff:ff:ff:ff, spoof checking on, link-state auto, trust off
    vf 1     link/ether ca:a9:c1:1a:c0:52 brd ff:ff:ff:ff:ff:ff, spoof checking on, link-state auto, trust off
    vf 2     link/ether 0e:50:02:6b:cd:d0 brd ff:ff:ff:ff:ff:ff, spoof checking on, link-state auto, trust off
    vf 3     link/ether 26:2f:72:b8:24:22 brd ff:ff:ff:ff:ff:ff, spoof checking on, link-state auto, trust off
[root@dcpae-643-centos-51 app]# ethtool -i ens786
driver: ice
version: 1.6.7
firmware-version: 3.00 0x80008271 1.2992.0
expansion-rom-version:
bus-info: 0000:1a:00.0
supports-statistics: yes
supports-test: yes
supports-eeprom-access: yes
supports-register-dump: yes
supports-priv-flags: yes
[root@dcpae-643-centos-51 app]#
[root@dcpae-643-centos-51 app]#
[root@dcpae-643-centos-51 app]#
[root@dcpae-643-centos-51 app]# ./dpdk-testpmd -c 0xff -n 4  -w 0000:1a:01.0 --file-prefix=vf0 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=4 --txq=4
EAL: Detected 72 lcore(s)
EAL: Detected 2 NUMA nodes
Option -w, --pci-whitelist is deprecated, use -a, --allow option instead
EAL: Detected static linkage of DPDK
EAL: Multi-process socket /var/run/dpdk/vf0/mp_socket
EAL: Selected IOVA mode 'VA'
EAL: No available 2048 kB hugepages reported
EAL: VFIO support initialized
EAL: Using IOMMU type 1 (Type 1)
EAL: Probe PCI driver: net_iavf (8086:1889) device: 0000:1a:01.0 (socket 0)
iavf_execute_vf_cmd(): Cmd 26 not supported
iavf_set_hena(): Failed to execute command of OP_SET_RSS_HENA
iavf_default_rss_disable(): fail to disable default RSS,lack PF support
TELEMETRY: No legacy callbacks, legacy socket not created
Interactive-mode selected
Set rxonly packet forwarding mode
testpmd: create a new mbuf pool <mb_pool_0>: n=203456, size=2176, socket=0
testpmd: preferred mempool ops selected: ring_mp_mc

Warning! port-topology=paired and odd forward ports number, the last port will pair with itself.

Configuring Port 0 (socket 0)
iavf_execute_vf_cmd(): Return failure -5 for cmd 45
iavf_add_del_rss_cfg(): Failed to execute command of OP_ADD_RSS_CFG
iavf_execute_vf_cmd(): Return failure -5 for cmd 45
iavf_add_del_rss_cfg(): Failed to execute command of OP_ADD_RSS_CFG
iavf_configure_queues(): request RXDID[22] in Queue[0]
iavf_configure_queues(): request RXDID[22] in Queue[1]
iavf_configure_queues(): request RXDID[22] in Queue[2]
iavf_configure_queues(): request RXDID[22] in Queue[3]

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event

Port 0: link state change event
Port 0: 22:6B:E6:2A:61:27
Checking link statuses...
Done
testpmd> set verbose 1
Change verbose level from 0 to 1
testpmd> start
rxonly packet forwarding - ports=1 - cores=1 - streams=4 - NUMA support enabled, MP allocation mode: native
Logical Core 1 (socket 0) forwards packets on 4 streams:
  RX P=0/Q=0 (socket 0) -> TX P=0/Q=0 (socket 0) peer=02:00:00:00:00:00
  RX P=0/Q=1 (socket 0) -> TX P=0/Q=1 (socket 0) peer=02:00:00:00:00:00
  RX P=0/Q=2 (socket 0) -> TX P=0/Q=2 (socket 0) peer=02:00:00:00:00:00
  RX P=0/Q=3 (socket 0) -> TX P=0/Q=3 (socket 0) peer=02:00:00:00:00:00

  rxonly packet forwarding packets/burst=32
  nb forwarding cores=1 - nb forwarding ports=1
  port 0: RX queue number: 4 Tx queue number: 4
    Rx offloads=0x0 Tx offloads=0x10000
    RX queue: 0
      RX desc=512 - RX free threshold=32
      RX threshold registers: pthresh=0 hthresh=0  wthresh=0
      RX Offloads=0x0
    TX queue: 0
      TX desc=512 - TX free threshold=32
      TX threshold registers: pthresh=0 hthresh=0  wthresh=0
      TX offloads=0x10000 - TX RS bit threshold=32
testpmd>
testpmd>
testpmd> flow create 0 ingress pattern eth / ipv4 dst is 17.0.0.4 / tcp dst spec 1 dst mask 15 / end actions queue index 1 / mark id 1 / end
Flow rule #0 created
testpmd>
testpmd>
testpmd>
testpmd> flow list 0
ID      Group   Prio    Attr    Rule
0       0       0       i--     ETH IPV4 TCP => QUEUE MARK
testpmd>
testpmd>
testpmd>
testpmd> port 0/queue 1: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xca5209b0 - RSS queue=0x1 - FDIR matched ID=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x1
  ol_flags: PKT_RX_RSS_HASH PKT_RX_FDIR PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_FDIR_ID PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
testpmd>
testpmd> port 0/queue 1: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xca5209b0 - RSS queue=0x1 - FDIR matched ID=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x1
  ol_flags: PKT_RX_RSS_HASH PKT_RX_FDIR PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_FDIR_ID PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
testpmd>
testpmd> flow flush 0
testpmd> flow create 0 ingress pattern eth / ipv4 dst is 17.0.0.4 / tcp dst is 1 / end actions queue index 1 / mark id 1 / end
Flow rule #0 created
testpmd> flow list 0
ID      Group   Prio    Attr    Rule
0       0       0       i--     ETH IPV4 TCP => QUEUE MARK
testpmd>
testpmd>
testpmd>
testpmd> port 0/queue 1: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xca5209b0 - RSS queue=0x1 - FDIR matched ID=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x1
  ol_flags: PKT_RX_RSS_HASH PKT_RX_FDIR PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_FDIR_ID PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
testpmd>
testpmd> port 0/queue 0: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xca5209b0 - RSS queue=0x0 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x0
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
testpmd>
testpmd>
testpmd>
testpmd>
testpmd>
testpmd> port 0/queue 0: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xca5209b0 - RSS queue=0x0 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x0
  ol_flags: PKT_RX_RSS_HASH PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
testpmd>
testpmd> flow flush 0
testpmd>
testpmd>
testpmd>
testpmd> flow create 0 ingress pattern eth / ipv4 dst is 17.0.0.4 / tcp dst spec 1 dst mask 15 / end actions queue index 1 / mark id 1 / end
Flow rule #0 created
testpmd> flow list 0
ID      Group   Prio    Attr    Rule
0       0       0       i--     ETH IPV4 TCP => QUEUE MARK
testpmd> port 0/queue 1: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xca5209b0 - RSS queue=0x1 - FDIR matched ID=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x1
  ol_flags: PKT_RX_RSS_HASH PKT_RX_FDIR PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_FDIR_ID PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd> port 0/queue 1: received 1 packets
  src=22:6B:E6:2A:61:DD - dst=22:6B:E6:2A:61:27 - type=0x0800 - length=534 - nb_segs=1 - RSS hash=0xca5209b0 - RSS queue=0x1 - FDIR matched ID=0x1 - hw ptype: L2_ETHER L3_IPV4_EXT_UNKNOWN L4_TCP  - sw ptype: L2_ETHER L3_IPV4 L4_TCP  - l2_len=14 - l3_len=20 - l4_len=20 - Receive queue=0x1
  ol_flags: PKT_RX_RSS_HASH PKT_RX_FDIR PKT_RX_L4_CKSUM_GOOD PKT_RX_IP_CKSUM_GOOD PKT_RX_FDIR_ID PKT_RX_OUTER_L4_CKSUM_UNKNOWN

testpmd>
