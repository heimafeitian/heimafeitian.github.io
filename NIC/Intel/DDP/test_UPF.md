


case1:单端口上行RSS
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

case2:单端口下行RSS

flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

case3:单端口上下行RSS

flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

case4：单端口上下行FDIR+RSS

flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

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

case5：5个端口上下行RSS

flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end




case6：6个端口上下行RSS


flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end



flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end



case7：6个端口上行FDIR


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

case8 6个端口上行FDIR+RSS和下行RSS


flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end




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







====================================================================


flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end


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

flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end





flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.1 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.2 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.3 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.4 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.5 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.6 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.7 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.8 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.9 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.10 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.11 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.12 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.13 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.14 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.15 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.16 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.17 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.18 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.19 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.20 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.21 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.22 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.23 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 dst is 192.168.0.24 / udp / gtpu / end actions mark id 1 / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end




============================================================
6个端口下行RSS+5个端口上行RSS 出现

flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end



flow create 4 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 4 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 5 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 5 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end



flow create 4 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


6个端口下行RSS+6个端口上行RSS 不出现


flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end




=====================================================================================
2个下行RSS和1个上行RSS 出现
flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end



=======================================================================================================================
1个上行RSS+1个下行RSS 出现
flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


cd /home/jack/dpdk-20.11/usertools/

rmmod ice

modprobe ice
echo 32 >  /sys/class/net/ens786f0/device/sriov_numvfs    
echo 32 >  /sys/class/net/ens786f1/device/sriov_numvfs   
 
modprobe vfio-pci

./dpdk-devbind.py --bind=vfio-pci 0000:1a:01.0 0000:1a:01.1 0000:1a:01.2 0000:1a:11.0 0000:1a:11.1 0000:1a:11.2 0000:1a:01.3 0000:1a:01.4 0000:1a:01.5 0000:1a:11.3 0000:1a:11.4 0000:1a:11.5

cd ../build/app/

./dpdk-testpmd -c 0xff -n 4 -a 0000:1a:01.0 -a 0000:1a:01.1 -a 0000:1a:01.2 -a 0000:1a:11.0 -a 0000:1a:11.1 -a 0000:1a:11.2  -a 0000:1a:01.3 -a 0000:1a:01.4 -a 0000:1a:01.5 -a 0000:1a:11.3 --file-prefix=pfu1 --log-level=net_iavf:8  -- -i --forward-mode=rxonly --rxq=16 --txq=16





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






出现

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end



不出现
flow create 7 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 7 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end





flow create 0 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / end actions rss types ipv4 l3-dst-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv6 / end actions rss types ipv6 l3-dst-only end key_len 0 queues end / end


flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end


flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end














flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 0 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 1 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 2 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 3 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end

flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv4 / end actions rss types ipv4 l3-src-only end key_len 0 queues end / end
flow create 6 ingress pattern eth / ipv4 / udp / gtpu / ipv6 / end actions rss types ipv6 l3-src-only end key_len 0 queues end / end
