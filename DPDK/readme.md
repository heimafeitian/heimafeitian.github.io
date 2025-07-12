DPDK

Intel:
https://www.intel.cn/content/www/cn/zh/developer/topic-technology/networking/dpdk.html


L3FWD:
meson -Dlibdir=lib -Dexamples=l3fwd -Dc_args=-DRTE_LIBRTE_I40E_16BYTE_RX_DESC --default-library=static x86_64-nativelinuxapp-gcc build2

./dpdk-testpmd -l 5,6 -n 6 -a 0000:18:00.0 -a 0000:18:00.1 -- -i --portmask=0x3 --txd=2048 --rxd=2048 --txq=2 --rxq=2 --forward=io -a

./dpdk-l3fwd -l 1 -n 4 -a 0000:18:00.0 -a 0000:18:00.1 -- -p 0x3 --config='(0,0,1),(1,0,1)' --eth-dest=0,00:10:94:00:00:09 --eth-dest=1,00:10:94:00:00:0A  

./dpdk-l3fwd -l 1,2,19,20 -n 4 -a 0000:18:00.0 -a 0000:18:00.1 -- -p 0x3 --config='(0,0,1),(0,1,2),(1,0,19),(1,1,20)' --eth-dest=0,00:10:94:00:00:09 --eth-dest=1,00:10:94:00:00:0A  

