DPDK
Flow Bifurcation/Day02-Session05-JingjingWu-Userspace2016.pdf

Netmap/
netmap a novel framework for fast packet IO.pdf
Revisiting Network IO APIs of the netmap Framework.pdf

virtio_user/
Day02-Session02-Steve Liang-DPDKUSASummit2016 (1).pdf
VIRTIO-USER A New Versatile Channel for Kernel-Bypass Networks.pdf

DPDK Golden Deck - Overview - 20.11.pptx

DPDK_101.pdf

DPDK_BKM v1.3.doc

dpdk-cookbook-759202.pdf

high-speed-packet-processing-with-the-data-plane-development-kit-_-deck_852581.pdf

NP_Application_Capability_October_22.pptx

pci-sig-sr-iov-primer-sr-iov-technology-paper.pdf

Performance_Tuning_via_Lean_Measurements_for_Acceleration_of_Network_Functions_Virtualization.pdf

Updated-India-DPDK-Summit-2018-May-NIC-Perfo.pptx











Intel:
https://www.intel.cn/content/www/cn/zh/developer/topic-technology/networking/dpdk.html


L3FWD:
meson -Dlibdir=lib -Dexamples=l3fwd -Dc_args=-DRTE_LIBRTE_I40E_16BYTE_RX_DESC --default-library=static x86_64-nativelinuxapp-gcc build2

./dpdk-testpmd -l 5,6 -n 6 -a 0000:18:00.0 -a 0000:18:00.1 -- -i --portmask=0x3 --txd=2048 --rxd=2048 --txq=2 --rxq=2 --forward=io -a

./dpdk-l3fwd -l 1 -n 4 -a 0000:18:00.0 -a 0000:18:00.1 -- -p 0x3 --config='(0,0,1),(1,0,1)' --eth-dest=0,00:10:94:00:00:09 --eth-dest=1,00:10:94:00:00:0A  

./dpdk-l3fwd -l 1,2,19,20 -n 4 -a 0000:18:00.0 -a 0000:18:00.1 -- -p 0x3 --config='(0,0,1),(0,1,2),(1,0,19),(1,1,20)' --eth-dest=0,00:10:94:00:00:09 --eth-dest=1,00:10:94:00:00:0A  

