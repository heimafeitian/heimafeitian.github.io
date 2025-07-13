isolcpus=1-31,65-95,33-63,97-127 nohz_full=1-31,65-95,33-63,97-127 rcu_nocbs=1-31,65-95,33-63,97-127 intel_pstate=disable intel_idle.max_cstate=1 processor.max_cstates=1 CONFIG_INTEL_UNCORE_FREQ_CONTROL=m

Test Case 1 – Cryptodev SW

Cryptodev performance for (AES-CBC128/SHA1-HMAC)

AESNI_MB PMD command line:
1C1T：
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 1,10 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly

1C2T
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 1,10,74 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly

2C4T
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 1,10,74,11,75 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly

4C8T
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 1,10,74,11,75,12,76,13,77 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly



Cryptodev performance for ((AES-CBC-128/SHA2-256-HMAC)

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10 -n 6 -- --buffer-sz \
64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput -- \
auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz \
16 --auth-op generate --burst-sz 32 --total-ops 10000000 --silent -- \
digest-sz 16 --auth-algo sha2-256-hmac --cipher-algo aes-cbc --cipher-op \
Encrypt --csv-friendly

Cryptodev performance for (AES-GCM-128)

支持 性能不如 AES-GCM——PMD
####./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_mb --aead-op encrypt --burst-sz 32 --total-ops 10000000 --silent --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12


AESNI_MB PMD command line:
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_gcm_pmd_1 -l 1,10 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_gcm --aead-op encrypt --burst-sz 32 --total-ops 10000000 --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12 --csv-friendly

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_gcm_pmd_1 -l 1,10,74 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_gcm --aead-op encrypt --burst-sz 32 --total-ops 10000000 --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12 --csv-friendly 

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_gcm_pmd_1 -l 1,10,74,11,75 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_gcm --aead-op encrypt --burst-sz 32 --total-ops 10000000 --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12 --csv-friendly 

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_gcm_pmd_1 -l 1,10 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_gcm --aead-op encrypt --burst-sz 32 --total-ops 10000000 --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12 --csv-friendly 

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_gcm_pmd_1 -l 1,10,74,11,75,12,76,13,77 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_gcm --aead-op encrypt --burst-sz 32 --total-ops 10000000 --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12 --csv-friendly 






echo 4 > /sys/bus/pci/drivers/4xxx/0000:76:00.0/sriov_numvfs
echo 4 > /sys/bus/pci/drivers/4xxx/0000:7a:00.0/sriov_numvfs

./dpdk-devbind.py -b vfio-pci 0000:76:00.1 0000:7a:00.1 



cd /app/test
./dpdk-test -l1 -n1 -a 0000:76:00.1
RTE>>cryptodev_qat_autotest



QAT SYM crypto PMD can be tested by running the test application:

cd ./<build_dir>/app/test
./dpdk-test -l1 -n1 -a <your qat bdf>
RTE>>cryptodev_qat_autotest
QAT ASYM crypto PMD can be tested by running the test application:

cd ./<build_dir>/app/test
./dpdk-test -l1 -n1 -a <your qat bdf>
RTE>>cryptodev_qat_asym_autotest
QAT compression PMD can be tested by running the test application:

cd ./<build_dir>/app/test
./dpdk-test -l1 -n1 -a <your qat bdf>
RTE>>compressdev_autotest


------------------------------------------------------------------------------------------------------------------------------
devtype:devtype crypto_scheduler:
one device
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 \
--vdev crypto_scheduler_pmd_1,worker=0000:76:00.1_qat_sym,mode=round-robin -l 9,10 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput \
--auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_scheduler --cipher-iv-sz 16 --auth-op generate --burst-sz 32 \
--total-ops 30000000 --silent --digest-sz 20 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly 



two device 
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 -a 0000:7a:00.1 \
--vdev crypto_scheduler_pmd_1,worker=0000:76:00.1_qat_sym,worker=0000:7a:00.1_qat_sym,mode=round-robin -l 9,10 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput \
--auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_scheduler --cipher-iv-sz 16 --auth-op generate --burst-sz 32 \
--total-ops 30000000 --silent --digest-sz 20 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly 


two device 2 core
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 -a 0000:7a:00.1 \
--vdev crypto_scheduler_pmd_1,worker=0000:76:00.1_qat_sym,worker=0000:7a:00.1_qat_sym,mode=round-robin -l 9,10,11 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput \
--auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_scheduler --cipher-iv-sz 16 --auth-op generate --burst-sz 32 \
--total-ops 30000000 --silent --digest-sz 20 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt

#########
Number of needed queue pairs is higher than the maximum number of queue pairs per device.
Lower the number of cores or increase the number of crypto devices



./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 -a 0000:7a:00.1 \
--vdev crypto_scheduler_pmd_1,worker=0000:76:00.1_qat_sym,worker=0000:7a:00.1_qat_sym,mode=round-robin -l 9,10,11,12 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput \
--auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_scheduler --cipher-iv-sz 16 --auth-op generate --burst-sz 32 \
--total-ops 30000000 --silent --digest-sz 20 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt




aes-cbc-sha1
 
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 -a 0000:7a:00.1 \
--vdev crypto_scheduler_pmd_1,worker=0000:76:00.1_qat_sym,worker=0000:7a:00.1_qat_sym,mode=round-robin -l 9,10 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 \
--devtype crypto_scheduler --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 30000000 --silent --digest-sz 20 \
--auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly 
 
 
 
aes-cbc-sha2

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 \
--vdev crypto_scheduler_pmd_1,worker=0000:76:00.1_qat_sym,mode=round-robin -l 9,10 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 \
--devtype crypto_scheduler --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 30000000 --silent --digest-sz 32 \
--auth-algo sha2-256-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly 

 
AES-GCM-128

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 \
--vdev crypto_scheduler_pmd_1,worker=0000:76:00.1_qat_sym,mode=round-robin -l 9,10 -n 6 \
-- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 \
--devtype crypto_scheduler --aead-op encrypt --burst-sz 32 --total-ops 30000000 --silent --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12 --csv-friendly 

----------------------------------------------------------------------------------------------------------------------------------------------------------------

devtype:devtype qat


one device
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1  \
-l 1,10 -n 4 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput \
--auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_qat --cipher-iv-sz 16 --auth-op generate --burst-sz 32 \
--total-ops 30000000 --silent --digest-sz 20 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly 

another one
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem  -a 0000:7a:00.1 \
-l 1,74 -n 4 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput \
--auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_qat --cipher-iv-sz 16 --auth-op generate --burst-sz 32 \
--total-ops 30000000 --silent --digest-sz 20 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly 


two device


./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem -a 0000:76:00.1 -a 0000:7a:00.1 \
-l 1,10,74 -n 4 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput \
--auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_qat --cipher-iv-sz 16 --auth-op generate --burst-sz 32 \
--total-ops 30000000 --silent --digest-sz 20 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt --csv-friendly 


Intel® Multi-Buffer crypto for IPSec Commands Performance





ZUC-256
~/intel-ipsec-mb/perf/ipsec_perf --cipher-algo zuc-eea3-256 --hash-algo zuc-eia3-256
SNOW-V
~/intel-ipsec-mb/perf/ipsec_perf --aead-algo snow-v-aead





openssl dev performance

1C1T
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_openssl -l 1,10 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 \
--devtype crypto_openssl --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac \
--cipher-algo aes-cbc --cipher-op encrypt --csv-friendly


1C2T


./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_openssl -l 1,10,74 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 \
--devtype crypto_openssl --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac \
--cipher-algo aes-cbc --cipher-op encrypt --csv-friendly

2C4T:
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_openssl -l 1,10,74,11,75 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 \
--devtype crypto_openssl --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac \
--cipher-algo aes-cbc --cipher-op encrypt --csv-friendly


4C8T:
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_openssl -l 1,10,74,11,75,12,76,13,77 -n 6 \
-- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 \
--devtype crypto_openssl --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac \
--cipher-algo aes-cbc --cipher-op encrypt --csv-friendly












root@ipmtest:/home/jack/dpdk-stable-22.11.2/build/app# ./dpdk-test-crypto-perf -l 9,10,11,12 -n 4 --vdev crypto_openssl -- --devtype crypto_openssl --aead-algo aes-gcm --aead-key-sz 16 --aead-iv-sz 12 --aead-op encrypt --aead-aad-sz 16 --digest-sz 16 --optype aead --silent --ptest throughput --burst-sz 32 --buffer-sz 64 --total-ops 1000 
EAL: Detected CPU lcores: 128
EAL: Detected NUMA nodes: 2
EAL: Detected static linkage of DPDK
EAL: Multi-process socket /var/run/dpdk/rte/mp_socket
EAL: Selected IOVA mode 'PA'
EAL: 4096 hugepages of size 2097152 reserved, but no mounted hugetlbfs found for that size
EAL: VFIO support initialized
CRYPTODEV: Creating cryptodev crypto_openssl
CRYPTODEV: Initialisation parameters - name: crypto_openssl,socket id: 0, max queue pairs: 8
TELEMETRY: No legacy callbacks, legacy socket not created
Allocated pool "sess_mp_0" on socket 0
    lcore id    Buf Size  Burst Size    Enqueued    Dequeued  Failed Enq  Failed Deq        MOps        Gbps  Cycles/Buf

          10          32          32          10          10           0           0      0.8594      0.2200     2327.20
          11          32          32          10          10           0           0      0.9919      0.2539     2016.40
          12          32          32          10          10           0           0      1.1204      0.2868     1785.00

root@ipmtest:/home/jack/dpdk-stable-22.11.2/build/app# ./dpdk-test-crypto-perf -l 9,10,11,12 -n 4 --vdev crypto_openssl -- --devtype crypto_openssl --aead-algo aes-gcm --aead-key-sz 16 --aead-iv-sz 12 --aead-op encrypt --aead-aad-sz 16 --digest-sz 16 --optype aead --silent --ptest throughput --burst-sz 32 --buffer-sz 128 --total-ops 10 --test-name aead_buff_64 --test-file test_aes_gcm.data
EAL: Detected CPU lcores: 128
EAL: Detected NUMA nodes: 2
EAL: Detected static linkage of DPDK
EAL: Multi-process socket /var/run/dpdk/rte/mp_socket
EAL: Selected IOVA mode 'PA'
EAL: 4096 hugepages of size 2097152 reserved, but no mounted hugetlbfs found for that size
EAL: VFIO support initialized
CRYPTODEV: Creating cryptodev crypto_openssl
CRYPTODEV: Initialisation parameters - name: crypto_openssl,socket id: 0, max queue pairs: 8
TELEMETRY: No legacy callbacks, legacy socket not created
Allocated pool "sess_mp_0" on socket 0
    lcore id    Buf Size  Burst Size    Enqueued    Dequeued  Failed Enq  Failed Deq        MOps        Gbps  Cycles/Buf

          10         128          32          10          10           0           0      0.8306      0.8506     2407.80
          11         128          32          10          10           0           0      1.0683      1.0939     1872.20
          12         128          32          10          10           0           0      1.1334      1.1606     1764.60

root@ipmtest:/home/jack/dpdk-stable-22.11.2/build/app#




./dpdk-l2fwd-crypto -l 1 -n 4 --vdev="crypto_aesni_mb,socket_id=0,max_nb_sessions=128" -- -p 1 --cdev SW --chain CIPHER_HASH --cipher_algo "aes-cbc" --auth_algo "sha1-hmac"


./dpdk-test-crypto-perf -l 1,2,34 --vdev crypto_aesni_mb_pmd -a 0000:00:00.0 -- --ptest throughput --devtype crypto_aesni_mb --optype auth-only --auth-algo aes-cmac --auth-op generate --auth-key-sz 16 --digest-sz 4 --total-ops 10000000 --burst-sz 32 --buffer-sz 16:16:2048 --silent --csv-friendly






Test Case 2 – Cryptodev SW
Cryptodev performance for (AES-CBC128/SHA1-HMAC)
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10,74 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10,74,11,75 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt




root@ipmtest:/home/jack/dpdk-stable-22.11.2/build_MB/app# ./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha1-hmac --cipher-algo aes-cbc --cipher-op encrypt
EAL: Detected CPU lcores: 128
EAL: Detected NUMA nodes: 2
EAL: Detected static linkage of DPDK
EAL: Multi-process socket /var/run/dpdk/rte/mp_socket
EAL: Selected IOVA mode 'VA'
EAL: VFIO support initialized
CRYPTODEV: Creating cryptodev crypto_aesni_mb_pmd_1
CRYPTODEV: Initialisation parameters - name: crypto_aesni_mb_pmd_1,socket id: 0, max queue pairs: 8
ipsec_mb_create() line 168: IPSec Multi-buffer library version used: 1.3.0

TELEMETRY: No legacy callbacks, legacy socket not created
Allocated pool "sess_mp_0" on socket 0
# Crypto Performance Application Options:
#
# cperf test: throughput
#
# size of crypto op / mbuf pool: 8192
# total number of ops: 10000000
# buffer sizes: 64 128 256 512 1024 2048
# burst sizes: 32

# segment size: 2060
#
# cryptodev type: crypto_aesni_mb
#
# number of queue pairs per device: 1
# crypto operation: cipher-then-auth
# sessionless: no
# out of place: no
#
# auth algorithm: sha1-hmac
# auth operation: generate
# auth key size: 64
# auth iv size: 0
# auth digest size: 12
#
# cipher algorithm: aes-cbc
# cipher operation: encrypt
# cipher key size: 16
# cipher iv size: 16
#
    lcore id    Buf Size  Burst Size    Enqueued    Dequeued  Failed Enq  Failed Deq        MOps        Gbps  Cycles/Buf

          10          64          32    10000000    10000000           0           0      6.0704      3.1080      329.47
          10         128          32    10000000    10000000           0           0      5.2776      5.4043      378.96
          10         256          32    10000000    10000000           0           0      4.2866      8.7789      466.57
          10         512          32    10000000    10000000           0           0      3.0963     12.6824      645.93
          10        1024          32    10000000    10000000           0           0      2.0529     16.8177      974.21
          10        2048          32    10000000    10000000           0           0      1.2108     19.8385     1651.74




Cryptodev performance for (AES-CBC128/SHA2-256-HMAC)

./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --silent -- digest-sz 16 --auth-algo sha2-256-hmac --cipher-algo aes-cbc --cipher-op encrypt
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha2-256-hmac --cipher-algo aes-cbc --cipher-op encrypt



root@ipmtest:/home/jack/dpdk-stable-22.11.2/build_MB/app# ./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_mb_pmd_1 -l 9,10 -n 6 -- --buffer-sz 64,128,256,512,1024,2048 --optype cipher-then-auth --ptest throughput --auth-key-sz 64 --cipher-key-sz 16 --devtype crypto_aesni_mb --cipher-iv-sz 16 --auth-op generate --burst-sz 32 --total-ops 10000000 --digest-sz 12 --auth-algo sha2-256-hmac --cipher-algo aes-cbc --cipher-op encrypt
EAL: Detected CPU lcores: 128
EAL: Detected NUMA nodes: 2
EAL: Detected static linkage of DPDK
EAL: Multi-process socket /var/run/dpdk/rte/mp_socket
EAL: Selected IOVA mode 'VA'
EAL: VFIO support initialized
CRYPTODEV: Creating cryptodev crypto_aesni_mb_pmd_1
CRYPTODEV: Initialisation parameters - name: crypto_aesni_mb_pmd_1,socket id: 0, max queue pairs: 8
ipsec_mb_create() line 168: IPSec Multi-buffer library version used: 1.3.0

TELEMETRY: No legacy callbacks, legacy socket not created
Allocated pool "sess_mp_0" on socket 0
# Crypto Performance Application Options:
#
# cperf test: throughput
#
# size of crypto op / mbuf pool: 8192
# total number of ops: 10000000
# buffer sizes: 64 128 256 512 1024 2048
# burst sizes: 32

# segment size: 2060
#
# cryptodev type: crypto_aesni_mb
#
# number of queue pairs per device: 1
# crypto operation: cipher-then-auth
# sessionless: no
# out of place: no
#
# auth algorithm: sha2-256-hmac
# auth operation: generate
# auth key size: 64
# auth iv size: 0
# auth digest size: 12
#
# cipher algorithm: aes-cbc
# cipher operation: encrypt
# cipher key size: 16
# cipher iv size: 16
#
    lcore id    Buf Size  Burst Size    Enqueued    Dequeued  Failed Enq  Failed Deq        MOps        Gbps  Cycles/Buf

          10          64          32    10000000    10000000           0           0      4.6200      2.3654      432.90
          10         128          32    10000000    10000000           0           0      3.9123      4.0062      511.21
          10         256          32    10000000    10000000           0           0      3.0587      6.2643      653.87
          10         512          32    10000000    10000000           0           0      2.0966      8.5876      953.94
          10        1024          32    10000000    10000000           0           0      1.3508     11.0658     1480.59
          10        2048          32    10000000    10000000           0           0      0.7722     12.6525     2589.84

Cryptodev performance for (AES-GCM-128)
./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_gcm_pmd_1 -l 9,10 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_gcm --aead-op encrypt --burst-sz 32 --total-ops 10000000 --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12

root@ipmtest:/home/jack/dpdk-stable-22.11.2/build_MB/app# ./dpdk-test-crypto-perf --socket-mem 2048,0 --legacy-mem --vdev crypto_aesni_gcm_pmd_1 -l 9,10 -n 6 -- --aead-key-sz 16 --buffer-sz 64,128,256,512,1024,2048 --optype aead --ptest throughput --aead-aad-sz 16 --devtype crypto_aesni_gcm --aead-op encrypt --burst-sz 32 --total-ops 10000000 --digest-sz 16 --aead-algo aes-gcm --aead-iv-sz 12
EAL: Detected CPU lcores: 128
EAL: Detected NUMA nodes: 2
EAL: Detected static linkage of DPDK
EAL: Multi-process socket /var/run/dpdk/rte/mp_socket
EAL: Selected IOVA mode 'VA'
EAL: VFIO support initialized
CRYPTODEV: Creating cryptodev crypto_aesni_gcm_pmd_1
CRYPTODEV: Initialisation parameters - name: crypto_aesni_gcm_pmd_1,socket id: 0, max queue pairs: 8
ipsec_mb_create() line 168: IPSec Multi-buffer library version used: 1.3.0

TELEMETRY: No legacy callbacks, legacy socket not created
Allocated pool "sess_mp_0" on socket 0
# Crypto Performance Application Options:
#
# cperf test: throughput
#
# size of crypto op / mbuf pool: 8192
# total number of ops: 10000000
# buffer sizes: 64 128 256 512 1024 2048
# burst sizes: 32

# segment size: 2064
#
# cryptodev type: crypto_aesni_gcm
#
# number of queue pairs per device: 1
# crypto operation: aead
# sessionless: no
# out of place: no
#
# aead algorithm: aes-gcm
# aead operation: encrypt
# aead key size: 16
# aead iv size: 12
# aead digest size: 16
# aead aad size: 16
#
    lcore id    Buf Size  Burst Size    Enqueued    Dequeued  Failed Enq  Failed Deq        MOps        Gbps  Cycles/Buf

          10          64          32    10000000    10000000           0           0     15.8612      8.1209      126.09
          10         128          32    10000000    10000000           0           0     15.0799     15.4418      132.63
          10         256          32    10000000    10000000           0           0     11.9572     24.4883      167.26
          10         512          32    10000000    10000000           0           0      9.6999     39.7307      206.19
          10        1024          32    10000000    10000000           0           0      6.9602     57.0180      287.35
          10        2048          32    10000000    10000000           0           0      4.1790     68.4689      478.58
