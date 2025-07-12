环境布置脚本 --------OVS-DPDK
——————————————————————————————————————————————————————————————————————————————————————————————
yum -y install epel-release
yum install python-pip
pip install --upgrade pip
pip search six
pip install six

yum install numactl-devel gcc -y
cd /usr/src/
wget http://fast.dpdk.org/rel/dpdk-18.11.2.tar.xz
tar xf dpdk-18.11.2.tar.xz
export DPDK_DIR=`pwd`
cd $DPDK_DIR
export DPDK_TARGET=x86_64-native-linuxapp-gcc
export DPDK_BUILD=$DPDK_DIR/$DPDK_TARGET
make install T=$DPDK_TARGET DESTDIR=install -j 4
export LD_LIBRARY_PATH=$DPDK_DIR/x86_64-native-linuxapp-gcc/lib
cd ~/openvswitch-2.11.1
./boot.sh
./configure --with-dpdk=$DPDK_BUILD
make && make install

arm64-armv8a-linuxapp-gcc
export DPDK_DIR=`pwd`
cd $DPDK_DIR
export DPDK_TARGET=arm64-armv8a-linuxapp-gcc
export DPDK_BUILD=$DPDK_DIR/$DPDK_TARGET
##make install T=$DPDK_TARGET DESTDIR=install
export LD_LIBRARY_PATH=$DPDK_DIR/arm64-armv8a-linuxapp-gcc/lib
cd ~/openvswitch-2.11.1
./boot.sh
./configure --with-dpdk=$DPDK_BUILD
make && make install

运行脚本 -------DPDK
_____________________________________________________________________________________________
cd $DPDK_DIR/$DPDK_TARGET/app
./testpmd -l 0-1 -n 4 -w 65:00.0 -- -i --txd=256
set fwd mac         //rxonly  txonly
set txpkts 256      //设置发包大小


运行脚本 -------OVS-DPDK
_____________________________________________________________________________________________

ovs-appctl -t ovs-vswitchd exit

ovs-appctl -t ovsdb-server exit

export DPDK_DIR=/usr/src/dpdk-stable-18.11.2

##sysctl -w vm.nr_hugepages=2048

sleep 1

modprobe uio
insmod $DPDK_DIR/x86_64-native-linuxapp-gcc/kmod/igb_uio.ko

sleep 1

ifconfig enp101s0f0 down
ifconfig enp101s0f1 down

$DPDK_DIR/usertools/dpdk-devbind.py --bind=igb_uio 81:00.0

sleep 1

$DPDK_DIR/usertools/dpdk-devbind.py --bind=igb_uio 81:00.1

sleep 1

export PATH=$PATH:/usr/local/share/openvswitch/scripts

sleep 1

export PATH=$PATH:/usr/local/share/openvswitch/scripts

sleep 1
rm -rf /usr/local/var/run/openvswitch/
rm -rf /usr/local/etc/openvswitch/
rm -rf /tmp/conf.db
mkdir -p /usr/local/etc/
mkdir -p /usr/local/etc/openvswitch
mkdir -p /usr/local/var/run/openvswitch/

cd openvswitch-2.11.1

ovsdb-tool create /usr/local/etc/openvswitch/conf.db \
    vswitchd/vswitch.ovsschema

export DB_SOCK=/usr/local/var/run/openvswitch/db.sock

ovsdb-server --remote=punix:/usr/local/var/run/openvswitch/db.sock \
    --remote=db:Open_vSwitch,Open_vSwitch,manager_options \
    --private-key=db:Open_vSwitch,SSL,private_key \
    --certificate=db:Open_vSwitch,SSL,certificate \
    --bootstrap-ca-cert=db:Open_vSwitch,SSL,ca_cert \
    --pidfile --detach --log-file

ovs-vsctl --no-wait init

ovs-vswitchd --pidfile --detach --log-file

ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-init=true

ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-socket-mem="2048"

ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-lcore-mask=02

ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-hugepage-dir=/dev/hugepages

ovs-vsctl --no-wait set Open_vSwitch . other_config:pmd-cpu-mask=0x04
#ovs-vsctl --no-wait set Open_vSwitch . other_config:pmd-cpu-mask=0x44   //指定core
#ovs-vsctl --no-wait set Open_vSwitch . other_config:pmd-cpu-mask=0x0C      
      
ovs-vsctl --no-wait set Open_vSwitch . other_config:max-idle=30000

ovs-vsctl set Open_vSwitch . Other_config:hw-offload=true
ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-init=true
ovs-vsctl --no-ovsdb-server --db-sock="$DB_SOCK" start 
ovs-vsctl get Open_vSwitch . dpdk_initialized


sleep 1
ovs-vsctl del-br br1
ovs-vsctl del-br br2
ovs-vsctl del-br br-int
ovs-vsctl del-br br-phy

#ovs-vsctl add-br br1 -- set bridge br1 datapath_type=netdev
#ovs-vsctl add-br br2 -- set bridge br2 datapath_type=netdev
#ovs-vsctl --may-exist add-br br2 \
#                            -- set Bridge br2 datapath_type=netdev \
#                            -- br-set-external-id br2 bridge-id br2 \
#                            -- set bridge br2 fail-mode=standalone
ovs-vsctl --may-exist add-br br-int \
  -- set Bridge br-int datapath_type=netdev \
  -- br-set-external-id br-int bridge-id br-int \
  -- set bridge br-int fail-mode=standalone

ovs-vsctl --may-exist add-br br-phy \
    -- set Bridge br-phy datapath_type=netdev \
    -- br-set-external-id br-phy bridge-id br-phy \
    -- set bridge br-phy fail-mode=standalone \
         other_config:hwaddr=3c:fd:fe:a9:cc:ec
#ovs-vsctl --may-exist add-br br1 \
#                       -- set bridge br1 datapath_type=netdev \
#                       -- br-set-external-id br1 bridge-id br1 \
#                       -- set bridge br1 fail-mode=standalone \
#                          other_config:hwaddr=bb:bb:bb:bb:bb:bb

sleep 1

ovs-vsctl add-port br-phy phy0 -- set Interface phy0 type=dpdk \
      options:dpdk-devargs=0000:01:00.1 ofport_request=1
  
ovs-vsctl add-port br-int phy1 -- set Interface phy1 type=dpdk \
      options:dpdk-devargs=0000:01:00.0 ofport_request=2
  
#ovs-vsctl add-port br-int vxlan1 -- set interface vxlan1 type=vxlan \
#      ofport_request=1 options:remote_ip=172.168.1.2 options:local_ip=172.168.1.1


sleep 1

ovs-ofctl dump-flows br-int

sleep 1

ovs-ofctl del-flows br-int

ovs-ofctl add-flow br-int in_port=1,idle_timeout=0,action=output:2

ovs-ofctl add-flow br-int in_port=2,idle_timeout=0,action=output:1

ovs-ofctl dump-flows br-int

ovs-ofctl show br-int

ip addr add 172.168.1.1/24 dev br-phy
ip link set br-phy up
iptables -F

ovs-vsctl show



