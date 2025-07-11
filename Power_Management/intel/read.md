Also, here are some backup references as fyi.

Influence industry workload developers to adopt power technology.




Improve perf/watt Energy efficient

Save power

	

The Data Plane Development Kit (dpdk.org) is the key software component in high speed networking workloads.




Many Network Function Virtualization (NFV) workloads use DPDK and other use similar design patterns to achieve performance goals.




It is a community software project at dpdk.org.

	

2017 - 2019

Power Aware Packet Processing 2017 v1

Power Aware Packet Processing 2017 v2

Recent Power Management Enhancements in DPDK 2018

Recent Power Management Enhancements in DPDK 2019







Data Plane Development Kit Enhanced Telemetry used for power load detection and actions

	

Understanding the utilization of a platform and application is key to understanding current load and potential overload conditions, giving the network operator an opportunity to monitor and react to meet Service Level Agreements (SLAs).

	

Enhanced Utilization Telemetry for Polling Workloads with collectd and the Data Plane Development Kit (DPDK))




Kubernetes Orchestration

	

Kubecon EU 2020

Demonstrated power consumption telemetry from a server can be used to scale out/in workloads across a data centre

	

Uses Horizontal POD autoscaling and

Telemetry Aware Scheduling Technology Guide & Industry Presentation




British Telecom (BT) and Intel

	

Resource Tuning for Energy Efficiency Slicing




Prioritise CPU Power and RDT resources to




We demonstrate how Speed Select Technology Base Frequency (SST-BF) increases network throughput for telecoms workloads

	

2021 24th Conference on Innovation in Clouds, Internet and Networks and Workshops (ICIN) - IEEE

Resource Tuning for Energy Efficient Slicing




https://ieeexplore.ieee.org/document/9385531




--~15-45% Improvement in throughput for ~5% increase in power using IA technologies in same TDP

--Reduce power consumption by 20% using SST vs Turbo

--Achieve multi-tenant isolation “worst to best” performance improvement of ~35% using SST and RDT.




Your Intel Technologies for Resource Tuning Energy Efficient Network Slices Technology Guide is now available on INB at https://networkbuilders.intel.com/solutionslibrary/intel-technologies-for-resource-tuning-energy-efficient-network-slices




The doc is also available on DPG Resources at https://dpgresources.intel.com/asset-library/resource-tuning-energy-efficient-network-slices/

 

Balancing NFV Performance and Energy Efficiency

 

SST-CP

https://ieeexplore.ieee.org/document/9758133

SST -CP achieved a performance improvement for the 5G core User Plane Function (UPF) of 4.2% while reducing processor socket power consumption by 21%.
Introducing Cache Allocation Technology (CAT) and Memory Bandwidth Allocation (MBA) into the set-up further boosted the performance improvement in the presence of the Noisy Neighbour workload, with an improvement in UPF throughput of 17%.
This was accompanied by a server-wide power reduction of 31 %.
For an additional test set-up applying the same high and low priority workloads on both processor sockets, the aggregated UPF (for two 5G cores) throughput was improved in the presence of a NN by 21% (via combined use of SST-CP, CAT and MBA). This was accompanied by a server-wide power reduction of 18%







Intracom

and Intel

	

Intracom Telecom Machine Learning Boosts NFV Energy Efficiency

	

The Intracom Telecom NFV Resource Intelligence™ (NFV-RI™) and Intel® Xeon® Scalable processors with Enhanced Intel SpeedStep® Technology predict virtual network function traffic loads to optimize power savings







Capgemini and Intel

	

A smart way to enable sustainable 5G networks

	

https://www.capgemini.com/wp-content/uploads/2022/06/Project-Bose-A-smart-way-to-enable-sustainable-5G-networks_whitepaper_July-22.pdf




Ericsson Power Saving 5G Core

	




	

https://www.ericsson.com/49e08a/assets/local/reports-papers/ericsson-technology-review/docs/2022/energy-efficient-packet-processing-in-5g-mobile-systems.pdf




Power Technology Papers




Enhanced Power Management for Low-Latency Workloads

P state benefits for NFV (new for ICX)

	

Power Management – Enhanced Power Management for Low-Latency Workloads Technology Guide (intel.com)







High-level overview of many of the power management features in the 3rd Generation Intel® Xeon® Scalable processors

 

	

Power Management - Technology Overview Technology Guide (intel.com)




Intel® Turbo Boost Technology – Using Intel® Turbo Boost Technology for Communications Workloads Technology Guide

	

https://dpgresources.intel.com/asset-library/intel-turbo-boost-technology-using-intel-turbo-boost-technology-for-communications-workloads-technology-guide/




https://cdrdv2.intel.com/v1/dl/getContent/727967




Intel Speed Select Technology Focused

Use Cases and tools for SST-Core Power

	

Intel® Speed Select Technology - Core Power (Intel® SST-CP) Overview Technology Guide

https://networkbuilders.intel.com/solutionslibrary/intel-speed-select-technology-core-power-intel-sst-cp-overview-technology-guide

 




Deploy Open Virtual Switch with SST-BF

	

Intel® Speed Select Technology – Base Frequency Priority CPU Management for Open vSwitch* (OVS*)

https://builders.intel.com/docs/networkbuilders/intel-speed-select-technology-base-frequency-priority-cpu-management-for-open-vswitch.pdf



Deploying Container Workloads with Kubernetes

 

	

Intel® Speed Select Technology - Base Frequency (Intel® SST-BF) with Kubernetes*

https://builders.intel.com/docs/networkbuilders/intel-speed-select-technology-base-frequency-with-kubernetes-application-note.pdf

 




User Guide for SST-BF, configuration guide

	

Intel® Speed Select Technology – Base Frequency - Enhancing Performance

https://builders.intel.com/docs/networkbuilders/intel-speed-select-technology-base-frequency-enhancing-performance.pdf

 




Automating Openstack Compute Node Cluster Provisioning with Ansible (SST focus)

 

	

Intel® SST-BF Configuration Automation on OpenStack* Compute Host App Note

https://builders.intel.com/docs/networkbuilders/intel-speed-select-technology-base-frequency-configuration-automation-on-openstack-compute-host.pdf

 




Upstream Operating System Support for Linux (kernel.org)

	

Intel(R) Speed Select Technology User Guide — The Linux Kernel documentation

 


