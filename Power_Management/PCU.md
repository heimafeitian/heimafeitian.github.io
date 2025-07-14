Power Control Unit (PCU) Overview
The processor implements a power control unit acting as a core and uncore power and
thermal manager. It runs its firmware (Pcode) on an internal micro-controller and
coordinates the sockets power states.

Summary of the PCU features:
• Manage ACPI requests for P-State and C-State changes from OS and HW
• Manage S-state requests from PCH
• Uncore Frequency Scaling
• Policy control for Intel® UPI, PCIe, and DMI3
• CPU Thermal and Power Optimization Capabilities
• DRAM Thermal and Power Optimization Capabilities
• Provide uncore CSR access and Machine Check Bank access
• RAPL “Running Average Power Limit” DRAM and Socket requests either via BMC
(over PECI electrical interface or MCTP over PCIe) or Node Manager (through
management engine on PCH)
• Respond to over power and over current conditions
• Thermal responses to over temperature conditions for processor and memory
• Hardware Power Management (HWP) Support

C-States
Core C-States are controlled by the Operating System directed configuration and OS
Power Management (OSPM) as defined by the ACPI specification. The OS tells the
threads in a core to go to a particular C-State (using MWAIT(Cx) instruction), cores
(HW) do the thread-level coordination to get each of the threads in the correct core Cx
state and then the boot strap processor (BSP) thread takes the core to the correct Cx
state. OSPM checks CPU utilization periodically and determines the C state used when
the CPU becomes idle during the next period.



HWP Native Mode 
Behavior
HWP can operate cooperatively with software
Software has interfaces to provide constraints and hints to Hardware
HWP Native Mode (with Legacy Support) allows the system to use HWP only with OS that supports HWP S/W interface.
The system uses the legacy p-state interface (_PCT,_PSS, _PPC) for all other operating systems. 

HWP Native Mode with No Legacy Support
Behavior
System always uses HWP (any OS)
Legacy OS will be unable to provide constraints and hints to frequency control
HWP supported starting with kernel 3.19.   i.e.  RHEL 7.x, Ubuntu 15.x.

HWP OOB Mode
Behavior
System uses HWP independent of the OS – out of band
Use case: PM hints and constraints provided via NodeManager's API/PECI service

HWP Disabled
Behavior
The system uses the legacy p-state interface



https://intelpedia.intel.com/ArtemBityutskiy/SPRFastC1E
https://wiki.ith.intel.com/display/PAIVSO/C1E+history+a+little+bit
