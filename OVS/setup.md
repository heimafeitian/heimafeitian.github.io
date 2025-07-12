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


# others

 
brctl addbr br0
brctl addif br0 enp136s0f0 ; dhclient br0 ;ifconfig enp136s0f0 0.0.0.0
 
service irqbalance stop
 
echo 100 > /proc/sys/vm/nr_hugepages
/opt/esc/openvswitch-2.11.0/utilities/ovs-appctl -t ovs-vswitchd exit
/opt/esc/openvswitch-2.11.0/utilities/ovs-appctl -t ovsdb-server exit

sleep 1
modprobe vfio
modprobe vfio-pci


 /usr/bin/chmod a+x /dev/vfio
 /usr/bin/chmod 0666 /dev/vfio/*

modprobe vfio-pci
/usr/bin/chmod a+x /dev/vfio
/usr/bin/chmod 0666 /dev/vfio/*


#modprobe uio
#insmod /opt/esc/dpdk-18.11/x86_64-native-linuxapp-gcc/kmod/igb_uio.ko
sleep 1
/opt/esc/dpdk-18.11/usertools/dpdk-devbind.py --bind=vfio-pci 86:00.1
#/opt/esc/dpdk-18.11/usertools/dpdk-devbind.py --bind=vfio-pci af:00.1
#/opt/esc/dpdk-18.11/usertools/dpdk-devbind.py --bind=vfio-pci af:00.0
#/opt/esc/dpdk-18.11/usertools/dpdk-devbind.py --bind=vfio-pci af:00.1
sleep 1
export PATH=$PATH:/usr/local/share/openvswitch/scripts
sleep 1
export PATH=$PATH:/usr/local/share/openvswitch/scripts
sleep 1
rm -rf /usr/local/var/run/openvswitch/
rm -rf /usr/local/etc/openvswitch/
rm -rf /tmp/conf.db
rm -rf /usr/local/var/log/openvswitch/
mkdir -p /usr/local/etc/
mkdir -p /usr/local/etc/openvswitch
mkdir -p /usr/local/var/run/openvswitch/
mkdir -p /usr/local/var/log/openvswitch/

cd /opt/esc/openvswitch-2.11.0
/opt/esc/openvswitch-2.11.0/ovsdb/ovsdb-tool create /usr/local/etc/openvswitch/conf.db vswitchd/vswitch.ovsschema
export DB_SOCK=/usr/local/var/run/openvswitch/db.sock
/opt/esc/openvswitch-2.11.0/ovsdb/ovsdb-server --remote=punix:/usr/local/var/run/openvswitch/db.sock \
    --remote=db:Open_vSwitch,Open_vSwitch,manager_options \
    --private-key=db:Open_vSwitch,SSL,private_key \
    --certificate=db:Open_vSwitch,SSL,certificate \
    --bootstrap-ca-cert=db:Open_vSwitch,SSL,ca_cert \
    --pidfile --detach --log-file
	
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait init
/opt/esc/openvswitch-2.11.0/vswitchd/ovs-vswitchd --pidfile --detach --log-file
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-init=true
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-socket-mem="2048"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-lcore-mask=400000000040000
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-hugepage-dir=/dev/hugepages
#/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:pmd-cpu-mask=40000000040000
#/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:pmd-cpu-mask=1000001000
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:pmd-cpu-mask=1000000000100000
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:max-idle=30000
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Open_vSwitch . Other_config:hw-offload=true
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl --no-wait set Open_vSwitch . other_config:dpdk-init=true
/opt/esc/openvswitch-2.11.0/utilities/ovs-ctl --no-ovsdb-server --db-sock="$DB_SOCK" start 
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl get Open_vSwitch . dpdk_initialized

##/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Open_vSwitch . other_config:userspace-tso-enable=true

sleep 1
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl del-br br1
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-br br1 -- set bridge br1 datapath_type=netdev
sleep 1
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 phy0 -- set Interface phy0 type=dpdk options:dpdk-devargs=0000:86:00.1 ofport_request=31
#/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 phy0 -- set Interface phy0 type=dpdk options:dpdk-devargs=0000:af:00.1 ofport_request=31
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-1 -- set Interface vhost-user-1 type=dpdkvhostuser ofport_request=1
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-2 -- set Interface vhost-user-2 type=dpdkvhostuser ofport_request=2
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-3 -- set Interface vhost-user-3 type=dpdkvhostuser ofport_request=3
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-4 -- set Interface vhost-user-4 type=dpdkvhostuser ofport_request=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-5 -- set Interface vhost-user-5 type=dpdkvhostuser ofport_request=5
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-6 -- set Interface vhost-user-6 type=dpdkvhostuser ofport_request=6
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-7 -- set Interface vhost-user-7 type=dpdkvhostuser ofport_request=7
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-8 -- set Interface vhost-user-8 type=dpdkvhostuser ofport_request=8
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-9 -- set Interface vhost-user-9 type=dpdkvhostuser ofport_request=9
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-10 -- set Interface vhost-user-10 type=dpdkvhostuser ofport_request=10
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-11 -- set Interface vhost-user-11 type=dpdkvhostuser ofport_request=11
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-12 -- set Interface vhost-user-12 type=dpdkvhostuser ofport_request=12
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-13 -- set Interface vhost-user-13 type=dpdkvhostuser ofport_request=13
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-14 -- set Interface vhost-user-14 type=dpdkvhostuser ofport_request=14
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-15 -- set Interface vhost-user-15 type=dpdkvhostuser ofport_request=15
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-16 -- set Interface vhost-user-16 type=dpdkvhostuser ofport_request=16



/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl del-flows br1
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:01:00:00:00:01,dl_src=3c:fd:fe:b1:12:11,action=output:1
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:02:00:00:00:02,dl_src=3c:fd:fe:b1:12:11,action=output:2
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:03:00:00:00:03,dl_src=3c:fd:fe:b1:12:11,action=output:3
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:04:00:00:00:04,dl_src=3c:fd:fe:b1:12:11,action=output:4
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:05:00:00:00:05,dl_src=3c:fd:fe:b1:12:11,action=output:5
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:06:00:00:00:06,dl_src=3c:fd:fe:b1:12:11,action=output:6
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:07:00:00:00:07,dl_src=3c:fd:fe:b1:12:11,action=output:7
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:08:00:00:00:08,dl_src=3c:fd:fe:b1:12:11,action=output:8
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:09:00:00:00:09,dl_src=3c:fd:fe:b1:12:11,action=output:9
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:10:00:00:00:10,dl_src=3c:fd:fe:b1:12:11,action=output:10
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:1a:00:00:00:1a,dl_src=3c:fd:fe:b1:12:11,action=output:11
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:1b:00:00:00:1b,dl_src=3c:fd:fe:b1:12:11,action=output:12
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:1c:00:00:00:1c,dl_src=3c:fd:fe:b1:12:11,action=output:13
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:1d:00:00:00:1d,dl_src=3c:fd:fe:b1:12:11,action=output:14
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:1e:00:00:00:1e,dl_src=3c:fd:fe:b1:12:11,action=output:15
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:1f:00:00:00:1f,dl_src=3c:fd:fe:b1:12:11,action=output:16
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=1,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=2,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=3,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=4,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=5,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=6,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=7,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=8,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=9,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=10,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=11,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=12,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=13,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=14,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=15,idle_timeout=0,action=output:31
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 in_port=16,idle_timeout=0,action=output:31


/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_rxq=2
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy0 other_config:pmd-rxq-affinity="0:20,1:20"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:60,1:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-2 other_config:pmd-rxq-affinity="0:60,1:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-3 other_config:pmd-rxq-affinity="0:60,1:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-4 other_config:pmd-rxq-affinity="0:60,1:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-5 other_config:pmd-rxq-affinity="0:60,1:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-6 other_config:pmd-rxq-affinity="0:60,1:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:21,1:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-2 other_config:pmd-rxq-affinity="0:21,1:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-3 other_config:pmd-rxq-affinity="0:21,1:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-4 other_config:pmd-rxq-affinity="0:21,1:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-5 other_config:pmd-rxq-affinity="0:21,1:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-6 other_config:pmd-rxq-affinity="0:21,1:21"

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy0 other_config:pmd-rxq-affinity="0:20,1:20,2:20,3:20"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-2 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-3 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-4 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-5 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-6 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-7 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-8 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-9 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-10 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-11 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-12 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-13 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-14 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-15 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-16 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-2 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-3 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-4 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-5 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-6 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-7 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-8 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-9 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-10 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-11 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-12 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-13 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-14 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-15 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-16 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21"

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy0 other_config:pmd-rxq-affinity="0:20,1:20,2:20,3:20,4:20,5:20,6:20,7:20,8:20"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21,4:21,5:21,6:21,7:21,8:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-2 other_config:pmd-rxq-affinity="0:21,1:21,2:21,3:21,4:21,5:21,6:21,7:21,8:21"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60,4:60,5:60,6:60,7:60,8:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60,4:60,5:60,6:60,7:60,8:60"


/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl dump-flows br1
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl show br1
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl show

sleep 0.5s
#/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-2 -- set Interface vhost-user-2 type=dpdkvhostuser
sleep 1
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl dump-flows br1
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl show br1
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl show

/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl del-flows br1     # clean flows on Bridge firstly
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 nw_dst=1.1.1.3,action=output:4
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 nw_dst=1.1.1.4,action=output:5
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 dl_type=0x0800,nw_dst=1.1.1.5,action=output:6
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 dl_type=0x0800,nw_dst=1.1.1.6,action=output:7
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 dl_type=0x0800,nw_dst=1.1.1.7,action=output:8
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 dl_type=0x0800,nw_dst=1.1.1.8,action=output:9
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 dl_type=0x0800,nw_dst=1.1.1.9,action=output:10
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br1 dl_type=0x0800,nw_dst=1.1.1.10,action=output:11
$OVS_DIR/utilities/ovs-vsctl show   # check flow set up success

/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl del-flows br1
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:01:00:00:00:01,dl_src=3c:fd:fe:b1:18:91,action=output:1
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:02:00:00:00:02,dl_src=3c:fd:fe:b1:18:91,action=output:2
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:03:00:00:00:03,dl_src=3c:fd:fe:b1:18:91,action=output:3
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:04:00:00:00:04,dl_src=3c:fd:fe:b1:18:91,action=output:4
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:05:00:00:00:05,dl_src=3c:fd:fe:b1:18:91,action=output:5
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:06:00:00:00:06,dl_src=3c:fd:fe:b1:18:91,action=output:6
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:07:00:00:00:07,dl_src=3c:fd:fe:b1:18:91,action=output:7
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl add-flow br1 dl_dst=00:08:00:00:00:08,dl_src=3c:fd:fe:b1:18:91,action=output:8



Example with other type flows :
$OVS_DIR/utilities/ovs-ofctl add-flow br0 dl_type=0x0800,nw_dst=17.17.17.17,action=output:2
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br0 dl_type=0x0800,nw_proto=6,nw_src=34.34.34.34,dl_dst=01:02:03:04:05:06,nw_tos=0,action=output:2
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br0 dl_type=0x0800,nw_proto=6,nw_src=17.18.19.20,nw_dst=34.35.36.37,dl_dst=01:02:03:04:05:06,dl_src=07:08:09:0A:0B:0C,tcp_dst=2827,nw_tos=0,action=output:2
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br0 dl_type=0x0800,nw_proto=6,nw_dst=34.35.36.37,dl_src=07:08:09:0A:0B:0C,action=output:2
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br0 dl_type=0x0800,nw_proto=6,nw_src=17.18.19.20,action=output:2
/opt/esc/openvswitch-2.11.0/utilities/ovs-ofctl/utilities/ovs-ofctl add-flow br0 dl_type=0x0800,nw_proto=17,nw_src=17.18.19.20,nw_dst=34.35.36.37,udp_src=5,action=output:2





/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-1 -- set Interface vhost-user-1 type=dpdkvhostuser mac=\"00:01:00:00:00:01\" ofport_request=1
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-2 -- set Interface vhost-user-2 type=dpdkvhostuser mac=\"00:02:00:00:00:02\" ofport_request=2
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-3 -- set Interface vhost-user-3 type=dpdkvhostuser mac=\"00:03:00:00:00:03\" ofport_request=3
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-4 -- set Interface vhost-user-4 type=dpdkvhostuser mac=\"00:04:00:00:00:04\" ofport_request=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-5 -- set Interface vhost-user-5 type=dpdkvhostuser mac=\"00:05:00:00:00:05\" ofport_request=5
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-6 -- set Interface vhost-user-6 type=dpdkvhostuser mac=\"00:06:00:00:00:06\" ofport_request=6
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-7 -- set Interface vhost-user-7 type=dpdkvhostuser mac=\"00:07:00:00:00:07\" ofport_request=7
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-8 -- set Interface vhost-user-8 type=dpdkvhostuser mac=\"00:08:00:00:00:08\" ofport_request=8















































/opt/esc/openvswitch-2.11.0/utilities/ovs-appctl dpif-netdev/pmd-rxq-show

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_rxq=2

#1:
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-1 -- set Interface vhost-user-1 type=dpdkvhostuser

taskset -c 16,40 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_1.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-1 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:01:00:00:00:01,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:64:18,model=e1000,addr=08 -net tap,ifname=tap1,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :1 &

#/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy0 other_config:pmd-rxq-affinity="0:18,1:60"
#/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:19,1:37"
#2:
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-2 -- set Interface vhost-user-2 type=dpdkvhostuser

taskset -c 17,41 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_2.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-2 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:02:00:00:00:02,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:34:22,model=e1000,addr=08 -net tap,ifname=tap2,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :2 &
#3:
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-3 -- set Interface vhost-user-3 type=dpdkvhostuser

taskset -c 18,42 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_3.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-3 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:03:00:00:00:03,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:34:32,model=e1000,addr=08 -net tap,ifname=tap3,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :3 &
#4:
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-4 -- set Interface vhost-user-4 type=dpdkvhostuser

taskset -c 19,43 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_4.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-4 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:03:00:00:00:03,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:34:42,model=e1000,addr=08 -net tap,ifname=tap4,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :4 &
#5:
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-5 -- set Interface vhost-user-5 type=dpdkvhostuser

taskset -c 20,44 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_5.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-5 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:03:00:00:00:03,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:34:52,model=e1000,addr=08 -net tap,ifname=tap5,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :5 &
#6:
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-6 -- set Interface vhost-user-6 type=dpdkvhostuser

taskset -c 21,45 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_6.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-6 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:03:00:00:00:03,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:34:60,model=e1000,addr=08 -net tap,ifname=tap6,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :6 &
#7：
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-7 -- set Interface vhost-user-7 type=dpdkvhostuser

taskset -c 22,46 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_7.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-7 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:03:00:00:00:03,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:34:72,model=e1000,addr=08 -net tap,ifname=tap7,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :7 &
#8：
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl add-port br1 vhost-user-8 -- set Interface vhost-user-8 type=dpdkvhostuser

taskset -c 23,47 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 2,sockets=1,cores=2,threads=1 -m 8G -object memory-backend-file,id=mem,size=8G,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/home/qemu/ecs_8.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-8 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mac=00:03:00:00:00:03,mq=on,vectors=6,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0 -net nic,macaddr=52:60:00:18:34:82,model=e1000,addr=08 -net tap,ifname=tap8,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :8 &
9:

10:


------5220
1:
taskset -c 19-35,55-71 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 34,sockets=1,cores=34,threads=1 -m 30960 -object memory-backend-file,id=mem,size=30960M,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/var/lib/libvirt/images/centos7.0.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-1 -netdev vhost-user,chardev=charnet0,queues=2,id=hostnet0 -device virtio-net-pci,mq=on,vectors=6,netdev=hostnet0 -chardev socket,id=charnet1,path=/usr/local/var/run/openvswitch/vhost-user-2 -netdev vhost-user,chardev=charnet1,queues=2,id=hostnet1 -device virtio-net-pci,mq=on,vectors=6,netdev=hostnet1 -net nic,macaddr=52:60:00:18:64:22,model=e1000,addr=08 -net tap,ifname=tap1,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :3
2:
taskset -c 19-35,55-71 /opt/esc/qemu/qemu-2.12.0-rc4/build/x86_64-softmmu/qemu-system-x86_64 -name guest=ovs-dpdk -enable-kvm -cpu host -smp 34,sockets=1,cores=34,threads=1 -m 30960 -object memory-backend-file,id=mem,size=30960M,mem-path=/dev/hugepages,share=on -numa node,memdev=mem -mem-prealloc -boot strict=on -drive file=/var/lib/libvirt/images/centos7.0.qcow2,format=qcow2,if=none,id=drive-virtio-disk0 -device virtio-blk-pci,scsi=off,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1 -chardev socket,id=charnet0,path=/usr/local/var/run/openvswitch/vhost-user-1 -netdev vhost-user,chardev=charnet0,queues=4,id=hostnet0 -device virtio-net-pci,mq=on,vectors=10,netdev=hostnet0 -chardev socket,id=charnet1,path=/usr/local/var/run/openvswitch/vhost-user-2 -netdev vhost-user,chardev=charnet1,queues=4,id=hostnet1 -device virtio-net-pci,mq=on,vectors=10,netdev=hostnet1 -net nic,macaddr=52:60:00:18:64:22,model=e1000,addr=08 -net tap,ifname=tap1,script=/opt/esc/qemu/qemu-ifup,downscript=no -vnc :3









/usr/libexec/qemu-kvm -name guest=instance-00000036,debug-threads=on -S -object secret,id=masterKey0,format=raw,file=/var/lib/libvirt/qemu/domain-22-instance-00000036/master-key.aes -machine pc-i440fx-rhel7.6.0,accel=kvm,usb=off,dump-guest-core=off -cpu Skylake-Server-IBRS,ss=on,hypervisor=on,tsc_adjust=on,clflushopt=on,pku=on,avx512vnni=on,md-clear=on,stibp=on,ssbd=on -m 8192 -realtime mlock=off -smp 4,sockets=4,cores=1,threads=1 -object memory-backend-file,id=ram-node0,prealloc=yes,mem-path=/dev/hugepages/libvirt/qemu/22-instance-00000036,share=yes,size=8589934592,host-nodes=1,policy=bind -numa node,nodeid=0,cpus=0-3,memdev=ram-node0 -uuid b6096c14-825f-4cf8-920a-7a3213ec6990 -smbios type=1,manufacturer=RDO,product=OpenStack Compute,version=18.7.5-1wocloud6.1.5.el7,serial=3c31c165-2b46-49bb-a736-4d1332611c92,uuid=b6096c14-825f-4cf8-920a-7a3213ec6990,family=Virtual Machine -no-user-config -nodefaults -chardev socket,id=charmonitor,fd=30,server,nowait -mon chardev=charmonitor,id=monitor,mode=control -rtc base=utc,driftfix=slew -global kvm-pit.lost_tick_policy=delay -no-hpet -no-shutdown -boot strict=on -device piix3-usb-uhci,id=usb,bus=pci.0,addr=0x1.0x2 -drive file=/var/lib/nova/instances/b6096c14-825f-4cf8-920a-7a3213ec6990/disk,format=qcow2,if=none,id=drive-virtio-disk0,cache=none -device virtio-blk-pci,scsi=off,bus=pci.0,addr=0x4,drive=drive-virtio-disk0,id=virtio-disk0,bootindex=1,write-cache=on -chardev socket,id=charnet0,path=/var/run/openvswitch/vhu737dfd78-87,server -netdev vhost-user,chardev=charnet0,queues=4,id=hostnet0 -device virtio-net-pci,mq=on,vectors=10,rx_queue_size=1024,tx_queue_size=1024,netdev=hostnet0,id=net0,mac=fa:16:3e:03:bd:fb,bus=pci.0,addr=0x3 -add-fd set=1,fd=33 -chardev pty,id=charserial0,logfile=/dev/fdset/1,logappend=on -device isa-serial,chardev=charserial0,id=serial0 -device usb-tablet,id=input0,bus=usb.0,port=1 -vnc 0.0.0.0:4 -device cirrus-vga,id=video0,bus=pci.0,addr=0x2 -device virtio-balloon-pci,id=balloon0,bus=pci.0,addr=0x5 -sandbox on,obsolete=deny,elevateprivileges=deny,spawn=deny,resourcecontrol=deny -msg timestamp=on

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_rxq=2
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_rxq=2
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_txq=2
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_txq=2

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_rxq=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_rxq=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_txq=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_txq=4

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_rxq_desc=2048
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_rxq_desc=2048
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_txq_desc=2048
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_txq_desc=2048


/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_rxq=8
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_rxq=8
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy0 options:n_txq=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface phy1 options:n_txq=4

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface vhost-user-1 options:n_rxq=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface vhost-user-2 options:n_rxq=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface vhost-user-1 options:n_txq=4
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set Interface vhost-user-2 options:n_txq=4

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy0 other_config:pmd-rxq-affinity="0:18,1:18,2:18,3:18"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy1 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:18,1:18,2:18,3:18"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-2 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60"

/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy0 other_config:pmd-rxq-affinity="0:18,1:18,2:18,3:18,4:18,5:18,6:18,7:18"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface phy1 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60,4:60,5:60,6:60,7:60"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-1 other_config:pmd-rxq-affinity="0:18,1:18,2:18,3:18,4:18,5:18,6:18,7:18"
/opt/esc/openvswitch-2.11.0/utilities/ovs-vsctl set interface vhost-user-2 other_config:pmd-rxq-affinity="0:60,1:60,2:60,3:60,4:60,5:60,6:60,7:60"

GRUB_CMDLINE_LINUX="crashkernel=auto spectre_v2=retpoline rd.lvm.lv=centos_dcpae-643-unicom-esc/root rd.lvm.lv=centos_dcpae-643-unicom-esc/swap rhgb quiet hugepagesz=1G hugepages=50 default_hugepagesz=1G nmi_watchdog=0 audit=0 nosoftlockup processor.max_cstate=0 hpet=disable mce=off tsc=reliable intel_idle.max_cstate=0 intel_pstate=disable numa_balancing=disable memory_corruption_check=0 isolcpus=4-23,28-47 rcu_nocbs=4-23,28-47 nohz_full=4-23,28-47"

