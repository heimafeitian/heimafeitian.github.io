cd /home/jack/dpdk-20.11/usertools/

rmmod ice

modprobe ice

echo 32 >  /sys/class/net/ens786f0/device/sriov_numvfs    
echo 32 >  /sys/class/net/ens786f1/device/sriov_numvfs   
 
modprobe vfio-pci

./dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5

cd ../build/app/




./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0f000:1a:11.2  -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


1


 
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 -a 0000:1a:11.4 -a 0000:1a:11.5    --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


PFU0

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

PFU1
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3     --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16




=========================================================================
DPDK20.11 
patch 验证：


patch -p1 < rss.patch



case1：

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2 --file-prefix=pfu1 --log-level=net_iavf:8 -- -i --forward-mode=rxonly --rxq=16 --txq=16


./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 --file-prefix=pfu2 --log-level=net_iavf:8 -- -i --forward-mode=rxonly --rxq=16 --txq=16


flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions count identifier 0x1234  / end


------------------------------------------------------------------------------------------------------------------------------------
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2  -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16





1、添加出错的case
如下是目前发现最精简的case，只要中间夹杂着PF1的VF的RSS 规则，再次添加上行的RSS就会死锁。并且和顺序有关系。
case1:Fail
Port3 Port4 Port2属于PF0
Port6属于PF1

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end

case2:Fail
Port3 Port4 Port2属于PF0
Port7属于PF1

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end



case3：7端口添加下行(普通的V4/V6)RSS规则+6端口添加上行（GTPU）RSS规则
flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

case4：6端口添加下行(普通的V4/V6)RSS规则+7端口添加上行（GTPU）RSS规则

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


case5：7端口添加下行(普通的V4/V6)RSS规则+7端口添加上行（GTPU）RSS规则
flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

case6：6端口添加下行(普通的V4/V6)RSS规则+6端口添加上行（GTPU）RSS规则

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

-------------------------------------------------------------------------------------------------------------------------------

PFU0

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

PFU1
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3  -a 0000:1a:11.4 -a 0000:1a:11.5  --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16



flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 5 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end


flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end


flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end

flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end


I have verified over DPDK 20.11 and DPDK 21.11，not the dpdk-next-net-intel version, the patch can resolve the add issue but the delete issue is still the same as before。


DPDK version:
DPDK20.11
http://static.dpdk.org/rel/dpdk-20.11.tar.gz

[root@localhost ~]# ethtool -i ens786f0
driver: ice
version: 1.3.2
firmware-version: 2.32 0x80005d1d 1.2877.0
expansion-rom-version:
bus-info: 0000:1a:00.0
supports-statistics: yes
supports-test: yes
supports-eeprom-access: yes
supports-register-dump: yes
supports-priv-flags: yes

DPDK version:

DPDK21.11

http://static.dpdk.org/rel/dpdk-21.11.tar.gz

ICE driver and firmware-version:

[root@localhost ~]# ethtool -i ens786f0
driver: ice
version: 1.6.7
firmware-version: 3.02 0x8000826c 1.2992.0
expansion-rom-version:
bus-info: 0000:1a:00.0
supports-statistics: yes
supports-test: yes
supports-eeprom-access: yes
supports-register-dump: yes
supports-priv-flags: yes
----------------------------------------------------------------------------------------------------
case info

echo 32 >  /sys/class/net/ens786f0/device/sriov_numvfs    
echo 32 >  /sys/class/net/ens786f1/device/sriov_numvfs   
 
modprobe vfio-pci

./dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5

cd ../build/app/

===============================================================C0===============================================================
rmmod ice

modprobe ice

echo 32 >  /sys/class/net/ens801/device/sriov_numvfs 

echo 32 >  /sys/class/net/ens802/device/sriov_numvfs 


./dpdk-devbind.py --bind=vfio-pci 0000:af:01.0 0000:af:01.1 0000:af:01.2 0000:af:01.3 0000:af:01.4 0000:af:01.5 0000:b2:01.0 0000:b2:01.1 0000:b2:01.2 0000:b2:01.3 0000:b2:01.4 0000:b2:01.5

PFU0

./dpdk-testpmd -c 0xff -n 4 -a 0000:af:01.0 -a 0000:af:01.1 -a 0000:af:01.2 -a 0000:b2:01.0 -a 0000:b2:01.1 -a 0000:b2:01.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

PFU1

./dpdk-testpmd -c 0xff -n 4 -a 0000:af:01.3 -a 0000:af:01.4 -a 0000:af:01.5 -a 0000:b2:01.3 -a 0000:b2:01.4 -a 0000:b2:01.5  --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16



==================================================================================================================================






PFU0

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --disable-rss --forward-mode=rxonly --rxq=16 --txq=16

PFU1

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3  -a 0000:1a:11.4 -a 0000:1a:11.5  --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --disable-rss --forward-mode=rxonly --rxq=16 --txq=16

------------------------------------------------------------------------------------------------------------------------

1、Each testpmd cmdlie input the below flow entries


flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end 

flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end 

flow create 5 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end 


2、 one process flow flush 0/1/2/3/4/5

3、the other one process flow flush 0/1/2/3/4/5 and the issue reproduce

testpmd> flow flush 0
testpmd> flow flush 1
iavf_execute_vf_cmd(): No response or return failure (-5) for cmd 46
iavf_add_del_rss_cfg(): Failed to execute command of OP_DEL_RSS_INPUT_CFG
iavf_hash_destroy(): fail to del RSS configure
iavf_flow_destroy(): Failed to destroy flow
iavf_flow_flush(): Failed to flush flows
port_flow_complain(): Caught PMD error type 2 (flow rule (handle)): Failed to delete rss rule.: Operation not permitted
testpmd>





====================================================
dpdk-21.11


cd /home/jack/dpdk-21.11/usertools/

rmmod ice

modprobe ice

echo 32 >  /sys/class/net/ens786f0/device/sriov_numvfs    
echo 32 >  /sys/class/net/ens786f1/device/sriov_numvfs   
 
modprobe vfio-pci

./dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5

cd ../build/app/




PFU0

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2   --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16

PFU1
./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3  -a 0000:1a:11.4 -a 0000:1a:11.5  --file-prefix=pfu2 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16


(mark+rss 必现)

(mark不+rss 必现)

flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end





















精简case




flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end 

flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end 

flow create 5 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end 



一个删除完，在另一个删除时候会出错。




============================================================




case1：7端口添加下行(普通的V4/V6)RSS规则
flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end


case2：6端口添加上行（GTPU）RSS规则
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


case3：7端口添加下行(普通的V4/V6)RSS规则+6端口添加上行（GTPU）RSS规则
flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

case4：6端口添加下行(普通的V4/V6)RSS规则+7端口添加上行（GTPU）RSS规则

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


case5：7端口添加下行(普通的V4/V6)RSS规则+7端口添加上行（GTPU）RSS规则
flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

case6：6端口添加下行(普通的V4/V6)RSS规则+6端口添加上行（GTPU）RSS规则

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

case7：1端口添加下行(普通的V4/V6)RSS规则+0端口添加上行（GTPU）RSS规则
flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


case8：7端口添加上行（GTPU）RSS规则+6端口添加下行(普通的V4/V6)RSS规则

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end


case9：6端口添加上行（GTPU）RSS规则+7端口添加下行(普通的V4/V6)RSS规则

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end


case10：0端口添加下行(普通的V4/V6)RSS规则+1端口添加上行（GTPU）RSS规则
flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end



flow create 8 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 8 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 9 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 9 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
