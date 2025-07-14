Created day: 2022-07-15


This patch adds a new EAL API that will be able to passively track core busyness.

The busyness is calculated by relying on the fact that most DPDK API's
will poll for packets. Empty polls can be counted as "idle", while
non-empty polls can be counted as busy. To measure lcore busyness, we
simply call the telemetry timestamping function with the number of polls
a particular code section has processed, and count the number of cycles
we've spent processing empty bursts. The more empty bursts we encounter,
the less cycles we spend in "busy" state, and the less core busyness
will be reported.

In order for all of the above to work without modifications to the
application, the library code needs to be instrumented with calls to
the lcore telemetry busyness timestamping function. The following parts
of DPDK are instrumented with lcore telemetry calls:

- All major driver API's:
  - ethdev
  - cryptodev
  - compressdev
  - regexdev
  - bbdev
  - rawdev
  - eventdev
- Some additional libraries:
  - ring
  - distributor

To avoid performance impact from having lcore telemetry support, a
global variable is exported by EAL, and a call to timestamping function
is wrapped into a macro, so that whenever telemetry is disabled, it only
takes one additional branch and no function calls are performed. It is
also possible to disable it at compile time by commenting out
RTE_LCORE_BUSYNESS from build config.

This patch also adds a telemetry endpoint to report lcore busyness, as well as telemetry endpoints to enable/disable lcore telemetry.

~~~~~

Below are instructions for installing the patches, rebuilding them for DPDK 2X.11, and testing their functionality with sample applications.


The telemetry patches that automatically track core busyness for PMD’s are located here:
https://github.com/intel/CommsPowerManagement/tree/master/ipm/patches
There are 2 directories here, one for VPP and one for DPDK.
The DPDK directory contains subdirectories for each release of DPDK supported, namely 20.11, 21.11, and 22.11
Clone this repository using git to the local machine
:git clone https://github.com/intel/CommsPowerManagement/
Change to the directory containing the patches for 21.11 (or the release on your machine)
: cd comms-power-management/IPM/patches/dpdk/21.11#
Copy the patches to the dpdk source directory
:~/ comms-power-management/IPM/patches/dpdk/21.11# cp * /root/dpdk-stable-21.11.2/
5. Apply the telemetry patch as follows and rebuild DPDK
:cd /root/dpdk-stable-21.11.2/
:~/dpdk-stable-21.11.2# patch -p1 < 0001-eal-add-lcore-busyness-telemetry.patch
:~/dpdk-stable-21.11.2# patch -p1 < 0002-eal-add-cpuset-lcore-telemetry-entries.patch
:~/IPM/dpdk-stable-21.11.2# cd build
:~/IPM/dpdk-stable-21.11.2/build#
:~/IPM/dpdk-stable-21.11.2/build# ninja

2.Test case 1: testpmd
 # app/dpdk-testpmd -l 1-3 -n 4 -a 15:00.0  -- -i --rxq=4 --txq=4 --nb-cores=2  --nb-ports=1  
   testpmd> set fwd mac
   Set mac packet forwarding mode
   testpmd> start
 # usertools/dpdk-telemetry.py
   Connecting to /var/run/dpdk/rte/dpdk_telemetry.v2
   {"version": "DPDK 20.11.0", "pid": 58365, "max_output_len": 16384}
   -->
  ==> stats info for different traffic volum.
  IXIA traffic Rate 0G 
  {"/eal/lcore/busyness": {"1": -1, "2": 0, "3": 0}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 0, "3": 0}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 0, "3": 0}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 0, "3": 0}}
  -->
  
  IXIA traffic Rate 10G 
  {"/eal/lcore/busyness": {"1": -1, "2": 12, "3": 12}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 12, "3": 12}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 12, "3": 12}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 12, "3": 12}}
  -->
  
  IXIA traffic Rate 50G 
  {"/eal/lcore/busyness": {"1": -1, "2": 44, "3": 44}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 44, "3": 43}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 44, "3": 43}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 45, "3": 43}}
  -->
  
  IXIA traffic Rate 100G 
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 99}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 100}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 100}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 100}}
 
 
3.Test case 2: distributor
  //https://doc.dpdk.org/guides-20.11/sample_app_ug/dist_app.html
  #/examples/dpdk-distributor -l 1-7 -n 4 -a  -- -p 1
  .....
  Distributor on core 2
  Rx on core 3
  Tx on core 4
  tx id 4, dist id 2, rx id 3
  Starting thread 0 as worker, lcore_id 5
  Starting thread 1 as worker, lcore_id 6
  Core 5 acting as worker core.
  
  Core 6 acting as worker core.
  Starting thread 2 as worker, lcore_id 7
  
  Core 7 acting as worker core.
  
  Core 4 doing packet TX.
  
  Core 2 acting as distributor core.
  
  Core 3 doing packet RX.
  .......
  #
  
  #/usertools/dpdk-telemetry.py
  Connecting to /var/run/dpdk/rte/dpdk_telemetry.v2
  {"version": "DPDK 20.11.0", "pid": 77580, "max_output_len": 16384}
  -->
  
    ==> stats info for different traffic volum.
  
  
  IXIA traffic Rate 0G
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 0, "3": 0, "4": 0, "5": 0, "6": 0, "7": 0}}
  
  IXIA traffic Rate 5G
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 54, "3": 12, "4": 15, "5": 12, "6": 11, "7": 11}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 55, "3": 12, "4": 15, "5": 12, "6": 11, "7": 11}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 54, "3": 12, "4": 14, "5": 12, "6": 11, "7": 11}}
  
  IXIA traffic Rate 20G
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 37, "4": 23, "5": 35, "6": 34, "7": 36}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 37, "4": 24, "5": 35, "6": 34, "7": 36}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 37, "4": 24, "5": 35, "6": 34, "7": 36}}
  
  IXIA traffic Rate 100G
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 91, "4": 50, "5": 89, "6": 91, "7": 0}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 91, "4": 49, "5": 88, "6": 91, "7": 0}}
  --> /eal/lcore/busyness
  {"/eal/lcore/busyness": {"1": -1, "2": 100, "3": 91, "4": 48, "5": 88, "6": 91, "7": 0}}



4.Stats explanation  
 Giving all threads that are running with a dpdk application

 numbers between "" are the logical cores
 -1 indicates unused by the dpdk application
 0 indicates the core is at 0% utilization. Utilization is on a scale 0-100
 So for instance core 33 is unused and core 34 has 0% utilization



https://patches.dpdk.org/project/dpdk/patch/20220824162442.631456-4-kevin.laatz@intel.com/


https://github.com/intel-innersource/networking.dataplane.dpdk.dpdk.git



