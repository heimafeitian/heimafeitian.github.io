
https://github.com/intel/asynch_mode_nginx/tree/v0.4.9/test/performance_bkm

Topology：
[CLIENT(s)][1.1.1.1/24]<------>[1.1.1.2/24][[port 443]NGINX Server]
------------------------------------------------------------------------------------------------------------
running OpenSSL Speed tests with QAT

asym:
taskset -c 1-3 ./openssl speed -elapsed -multi 3 rsa2048

taskset -c 1-3 ./openssl speed -engine qatengine -elapsed -multi 3 -async_jobs 72 rsa2048

sym:
taskset -c 32,96,36,100 ./openssl speed -multi 4 -engine qatengine -elapsed -evp aes-128-gcm

openssl check：
watch -n 2 cat /sys/kernel/debug/qat_4xxx_0000:76:00.0/fw_counters
watch -n 2 cat /sys/kernel/debug/qat_4xxx_0000:7a:00.0/fw_counters
watch -n 2 cat /sys/kernel/debug/qat_4xxx_0000:f3:00.0/fw_counters
watch -n 2 cat /sys/kernel/debug/qat_4xxx_0000:f7:00.0/fw_counters
----------------------------------------------------------------------------------------------------------------

worker_cpu_affinity 

32和64

63                                      31
1000 0000 0000 0000 0000 0000 0000 0000 1000 0000 0000 0000 0000 0000 0000 0000

         63                                      31
    0001 0000 0000 0000 0000 0000 0000 0000 0001 0000 0000 0000 0000 0000 0000 0000 0000

63/127

0100 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0100000000000000000000000000000000000000000000000000000000000000


0111 1111 1111 1111 1000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 00000

1000000000000000000000000000000000000000000000000000000000000001 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000


worker_cpu_affinity  01 11 11 11 11 11 11 11 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 11 11 11 11 11 11 11 11 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0;





配置IP:
 
ip addr delete 1.1.1.1/24 dev ens785f0
ip addr add 1.1.1.1/24 dev ens785f0
ip addr add 1.1.1.2/24 dev ens43f1
 
 ---------------------------------------------------------------------------
生成 NGINX_CERTS：
 
openssl req -x509 -sha256 -nodes -days 365 -newkey rsa:2048 -keyout server.key -out server.crt -sbuj "/C=CN/ST=Beijing/L=Beijing/O=Example Inc./OU=Web Security/CN=example.com"
 
Country Name (2 letter code) [AU]:CH

State or Province Name (full name) [Some-State]:BJ

Locality Name (eg, city) []:BJ

Organization Name (eg, company) [Internet Widgits Pty Ltd]:personal

Organizational Unit Name (eg, section) []:personal

Common Name (e.g. server FQDN or YOUR name) []:Nick

Email Address []:admin@test.com
 ---------------------------------------------------------------------------


https://10.239.173.82:443

wrk -t8 -c200 -d30s --latency  "https://10.239.173.48:443/intex.html"
10M_443_file.htm
wrk -t8 -c200 -d30s --latency   "https://10.239.173.82:443/10M_443_file.html"

nginx conf:

TLSv1.3
openssl s_client -tls1_3 -ciphersuites TLS_AES_128_GCM_SHA256 -connect 10.239.255.145:443 -sess_out my_ses


ssl_protocols TLSv1.3;
ssl_ciphers ECDHE-ECDSA-AES256-GCM-SHA384;
ssl_conf_command Ciphersuites TLS_AES_128_GCM_SHA256:TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256;
ssl_prefer_server_ciphers off;

https://serverfault.com/questions/1023766/nginx-with-only-tls1-3-cipher-suites
https://wiki.ith.intel.com/pages/viewpage.action?pageId=1920382056


Test:

./bulk.pl --servers 1 --cipher TLS_AES_128_GCM_SHA256 --clients 200 --time 60


./connection.sh --servers 1 --cipher TLS_AES_128_GCM_SHA256 --clients 200 --time 60





https://developer.aliyun.com/article/597750
https://www.sdnlab.com/21094.html

https://www.intel.com/content/www/us/en/developer/articles/guide/building-software-acceleration-features-in-the-intel-qat-engine-for-openssl.html

4.7	Set Up Intel® QAT Device Plugin for Kubernetes
To easily manage Intel® QAT available resources under Kubernetes, Intel developed the QAT device plugin as part of the Intel device plugins for Kubernetes. The supported devices are determined by the VF device drivers available in the Linux Kernel. Below is a list of supported devices:
•	Intel® Xeon® with Intel® C62X Series Chipset
•	Intel® Atom™ Processor C3000
•	Intel® Communications Chipset 8925 to 8955 Series
The Intel® QAT device plugin provides access to Intel® QAT VF to the container. Like the FEC device plugin, each container can request a certain number of Intel® QAT VF resources and run network applications, with these resources.
The Intel® QAT device plugin supports two modes of using the Intel® QAT VF resources – DPDK and kernel. This document only shows the DPDK mode. The kernel-mode usage is following the same procedure. Refer to the Intel® QAT device plugin github for all the details:
https://github.com/intel/intel-device-plugins-for-kubernetes/blob/master/cmd/qat_plugin/README.md
4.7.1	Getting the Source Code From Github
Assume you have set up the go environment already. Run below command to get source code from Github:
$ export MY_GOPATH=$(go env GOPATH)
$ mkdir -p $MY_GOPATH/src/github.com/intel
$ git clone https://github.com/intel/intel-device-plugins-for-kubernetes
$ cd $MY_GOPATH/src/github.com/intel/intel-device-plugins-for-kubernetes
$ git checkout v0.15.0
4.7.2	Build or Download the Docker Image
Update the Intel® QAT device plugin Dockerfile ($MY_GOPATH/src/github.com/intel/intel-device-plugins-for-kubernetes/build/docker/intel-qat-plugin.Dockerfile) with below changes:
ARG CLEAR_LINUX_BASE=clearlinux/golang@sha256:3b7841bb4fc15d6b6cfb3bdef12f385696efa9915541223848774a071c29be03
FROM ${CLEAR_LINUX_BASE} as builder
ARG CLEAR_LINUX_VERSION="--version=30970"
ARG TAGS_KERNELDRV=
ENV http_proxy <your_proxy>
ENV https_proxy <your_proxy>
…
Go to folder “$MY_GOPATH/src/github.com/intel/intel-device-plugins-for-kubernetes” and build QAT device plugin Docker image:
cd $MY_GOPATH/src/github.com/intel/intel-device-plugins-for-kubernetes/
make intel-qat-plugin
…
Successfully tagged intel/intel-qat-plugin:0.15.0
If you meet Docker image build issues in the step above, download the pre-built image from Docker Hub. In this document, version 0.15.0 is used. Download the correct version of the image using the below command:
$ docker pull intel/intel-qat-plugin:0.15.0
You can download the correct version of your need.
4.7.3	Deploy QAT device plugin as a DaemonSet
Configure the SR-IOV VF on the worker node. This worker node has integrated the Intel® QAT in the CPU and three Intel® QAT PFs b5:00.0, b7:00.0, b9:00.0
$ echo 16 > /sys/bus/pci/drivers/c6xx/0000:b5:00.0/sriov_numvfs
$ echo 16 > /sys/bus/pci/drivers/c6xx/0000:b7:00.0/sriov_numvfs
$ echo 16 > /sys/bus/pci/drivers/c6xx/0000:b9:00.0/sriov_numvfs
So a total 48 VFs are configured on the worker node, and these VFs are bound to VF kernel driver initially.
Update the DPDK driver and max VF devices number in the configmap of the Intel® QAT plugin. Here vfio is used since it’s more robust and secure (another reason is that this issue is encountered when using igb_uio).
$ vi $MY_GOPATH/src/github.com/intel/intel-device-plugins-for-kubernetes/deployments/qat_plugin/qat_plugin_default_configmap.yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: intel-qat-plugin-config
data:
  DPDK_DRIVER: "vfio-pci"
  KERNEL_VF_DRIVERS: "dh895xccvf,c6xxvf,c3xxxvf,d15xxvf"
  MAX_NUM_DEVICES: "32"
  DEBUG: "false"
Create configmap and demonset:
$ cd $GOPATH/src/github.com/intel/intel-device-plugins-for-kubernetes
$ kubectl create -f deployments/qat_plugin/qat_plugin_default_configmap.yaml
$ kubectl create -f deployments/qat_plugin/qat_plugin.yaml
After the Intel® QAT device plugin POD is running on correct nodes, verify the Intel® QAT device plugin is registered, and the Intel® QAT resources are available:
$ kubectl describe node <node name> | grep qat.intel.com/generic
 qat.intel.com/generic: 32
 qat.intel.com/generic: 32
4.7.4	Run DPDK Crypto Test to Consume QAT Device Plugin
Run the DPDK crypto sample app to show how to consume Intel® QAT device plugins in the container environment. Create a below POD configuration file.
$ cat <<EOF > dpdk-qat.yaml
kind: Pod
apiVersion: v1
metadata:
  name: dpdk
spec:
  containers:
  - name: dpdk
    image: centos:centos7.8.2003
    imagePullPolicy: IfNotPresent
    command: [ "/bin/bash", "-c", "--" ]
    args: [ "while true; do sleep 300000; done;" ]
    securityContext:
      readOnlyRootFilesystem: true
      privileged: false
      capabilities:
        add:
          ["IPC_LOCK", "SYS_ADMIN"]
    volumeMounts:
    - mountPath: /var/run/dpdk
      name: dpdk-runtime
    - mountPath: /dev/hugepages
      name: hugepage
    - name: dpdk-path
      mountPath: /opt/dpdk-5g
    - name: usr-path
      mountPath: /root/usr
    resources:
      requests:
        cpu: "3"
        memory: "128Mi"
        qat.intel.com/generic: '4'
        hugepages-1Gi: "1Gi"
      limits:
        cpu: "3"
        memory: "128Mi"
        qat.intel.com/generic: '4'
        hugepages-1Gi: "1Gi"
  restartPolicy: Never
  volumes:
  - name: dpdk-runtime
    emptyDir:
      medium: Memory
  - name: hugepage
    emptyDir:
      medium: HugePages
  - hostPath:
      path: "/opt/dpdk-5g"
    name: dpdk-path
  - hostPath:
      path: "/usr"
    name: usr-path
EOF
In the POD configuration, mount the prebuilt DPDK from host in to container (/opt/dpdk-5g). To keep it simple, some dynamic libraries (/usr/lib and /usr/lib64) needed by DPDK sample app runtime, are mounted to the container (/root/usr). Change the “hugepages-1Gi” part to your configuration (like hugepage-2Mi). Also change qat.intel.com/generic: '4' for your need.
Create the POD/container with above configuration, execute into the container and see the allocated PCIe devices. Get the device address of 4 Intel® QAT devices allocated.
$ kubectl create -f dpdk-qat.yaml
#execute into the container
$ kubectl exec -it dpdk bash
$ printenv | grep QAT
QAT2=0000:b7:01.1
QAT3=0000:b5:01.2
QAT0=0000:b7:02.6
QAT1=0000:b7:02.3
Finally inside container run the dpdk-test-crypto-perf sample app and view the output
$ cd /opt/dpdk-5g/x86_64-native-linuxapp-icc/app
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root/usr/lib64/:/root/usr/lib
$ ./dpdk-test-crypto-perf -c 0xf -w $QAT0 -w $QAT1 -w $QAT2 -w $QAT3 -- --ptest throughput --devtype crypto_qat --optype cipher-only --cipher-algo aes-cbc --cipher-op encrypt --cipher-key-sz 16   --total-ops 10000000 --burst-sz 32 --buffer-sz 1024









