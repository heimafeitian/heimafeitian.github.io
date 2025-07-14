Introduction to eBPF and XDP

https://www.mcorbin.fr/pages/xdp-introduction/

https://developer.aliyun.com/article/947869?utm_content=m_1000346074

https://blog.csdn.net/mseaspring/article/details/125252762

https://blog.csdn.net/daocaokafei/article/details/117337134

https://card.weibo.com/article/m/show/id/2309634602288038871284

https://github.com/iovisor/bpf-docs/blob/master/Express_Data_Path.pdf
https://docs.cilium.io/en/latest/bpf/
https://docs.cilium.io/en/latest/bpf/#bpf-and-xdp-reference-guide
https://www.iovisor.org/technology/xdp
https://prototype-kernel.readthedocs.io/en/latest/networking/XDP/index.html
https://people.netfilter.org/hawk/presentations/xdp2016/xdp_intro_and_use_cases_sep2016.pdf
https://jvns.ca/blog/2017/04/07/xdp-bpf-tutorial/




XDP - eXpress Data Path [Linux]

eXpress Data Path

XDP and AF_XDP Support

https://www.csdn.net/tags/MtzaQgxsODYwMDEtYmxvZwO0O0OO0O0O.html

AF_XDP

https://blog.csdn.net/force_eagle/article/details/117302414

https://lwn.net/Articles/750293/

https://lwn.net/Articles/745934/

http://arthurchiao.art/articles-zh/

https://blog.csdn.net/weixin_37097605/article/details/105109022 

https://lwn.net/Articles/750845/




Another option is to create AF_XDP socket as a sink for packets received in the physical interface and processed by the attached XDP. But there are 2 major limitations:

One cannot create dozens of AF_XDP sockets and use XDP to redirects various traffic classes into own AF_XDP for processing because each AF_XDP socket binds to the TX queue of physical interfaces. Most of the physical and emulated HW supports only a single RX/TX queue per interface. If there’s one AF_XDP already bound, another one will fail. There are few combinations of HW and drivers, which support multiple RX/TX queues but they have 2/4/8 queues, which doesn’t scale with hundreds of containers running in the cloud.
Another limitation is, that XDP can forward traffic to an AF_XDP socket, where the client reads the data. But when the client writes something to AF_XDP, the traffic is going out immediately via the physical interface and XDP cannot see it. Therefore, XDP + AF_XDP is not viable for symmetric operation like encapsulation/decapsulation. Using a veth pair may mitigate this issue.
XDP can (as of November 2019):
Fast incoming packet filtering. XDP can inspect fields in incoming packets and take simple action like DROP, TX to send it out the same interface it was received, REDIRECT to other interface or PASS to kernel stack for processing. XDP can alternate packet data like swap MAC addresses, change ip addresses, ports, ICMP type, recalculate checksums, etc. So obvious usage is for implementing:
Filerwalls (DROP)
L2/L3 lookup & forward
NAT – it is possible to implement static NAT indirectly (two XDP programs, each attached to own interface, processing and forwarding the traffic out, via the other interface). Connection tracking is possible, but more complicated with preserving and exchanging session-related data in TABLES.




https://pantheon.tech/what-is-af_xdp/










组件&特性	最低要求
mini kernel version	> v4.18
libbpf	kernel > v5.1-rc4
need_wakeup	kerner > v5.3-rc1
PMD zero copy	kernel > v5.4-rc1
shared_umem	kernel > v5.10 & libbpf > 0.2.0
busy polling	kernel > 5.11

AF_XDP video:
https://networkbuilders-staging.onsumaye.com/af-xdp-in-kernel-fast-path-address-family-express-data-path
af-xdp-sockets-high-performance-networking-for-cloud-native-networking-technology-guide.pdf
