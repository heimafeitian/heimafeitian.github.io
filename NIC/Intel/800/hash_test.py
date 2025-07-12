echo 0 > /sys/bus/pci/devices/0000\:3d\:00.0/sriov_numvfs
echo 1 > /sys/bus/pci/devices/0000\:3d\:00.0/sriov_numvfs
ip link set ens66 vf 0 mac 00:11:22:33:44:55
ip link set ens66 vf 0 trust on
ip link set ens66 vf 0 spoofchk off
./usertools/dpdk-devbind.py -b vfio-pci 3d:01.0
./build/app/dpdk-testpmd -l 1-10 -n 4 -a 3d:01.0 -- --nb-cores=8 --rxq=4 --txq=4 -i

1
port config all rss all
port config 0 rss-hash-key ipv4-udp 6d5a56da255b0ec24167253d43a38fb0d0ca2bcbae7b30b477cb2da38030f20c6a42b73bbeac01fa000000000000000000000000
flow create 0 ingress pattern eth / ipv4 / udp / end actions rss func symmetric_toeplitz types ipv4-udp end key_len 0 queues end / end
set fwd rxonly
set verbose 1
start



ZTE:

case1

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.2", src="192.172.0.2")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.77", src="192.172.0.77")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.100", src="192.172.0.100")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")



case2

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.2.1", src="192.172.2.1")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.3.1", src="192.172.3.1")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.4.1", src="192.172.4.1")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")


case3

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.3.2.1", src="192.3.2.1")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.4.2.1", src="192.4.2.1")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.5.2.1", src="192.5.2.1")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")








symmetric_toeplitz

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.1.2", src="192.172.0.2")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.172.0.2", src="192.168.1.2")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.1.2", src="192.172.0.2")/UDP(sport=23,dport=22)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.172.0.2", src="192.168.1.2")/UDP(sport=23,dport=22)/("X"*480)],iface="ens13")




sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.1.10", src="192.172.0.10")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.1.11", src="192.172.0.11")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.1.12", src="192.172.0.12")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")


sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.1.11", src="192.172.0.12")/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")







sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.4", src="192.168.0.2")\
/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.70", src="192.168.0.2")\
/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.80", src="192.168.0.2")\
/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")

sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.81", src="192.168.0.2")\
/UDP(sport=22,dport=23)/("X"*480)],iface="ens13")


sendp([Ether(dst="00:11:22:33:44:55", src="68:05:CA:BB:26:E0")/IP(dst="192.168.0.2", src="192.168.0.60")\
/UDP(sport=23,dport=22)/("X"*480)],iface="ens13")
