
TPMI：


2023-779074-TPMI-Software Platform-R1_0.pdf
575576_NM_5.0_External_Interface_Spec_Rev1_1.pdf

root@dcpae643du01:~# cpupower idle-info
CPUidle driver: intel_idle
CPUidle governor: menu
analyzing CPU 0:

Number of idle states: 4
Available idle states: POLL C1 C1E C6
POLL:
Flags/Description: CPUIDLE CORE POLL IDLE
Latency: 0
Usage: 9375
Duration: 77522
C1:
Flags/Description: MWAIT 0x00
Latency: 1
Usage: 7186
Duration: 505079
C1E:
Flags/Description: MWAIT 0x01
Latency: 4
Usage: 5839301
Duration: 3199827482
C6:
Flags/Description: MWAIT 0x20
Latency: 170
Usage: 5214705
Duration: 3710485901



cpupower idle-set -d 1
cpupower idle-set -d 2
cpupower idle-set -d 3


cpupower idle-set -d 1   (for C1 disable)
cpupower idle-set -d 2   (for C1E disable)
cpupower idle-set -d 3   (for C6 disable)


BIOS
C1E diable
C6 disable
packet c state = c6 no retention

check the Result



 
 cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor


 cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq
 
 
 cpupower -c all frequency-info
 
 cpupower -c all frequency-set -g performance
 
 cpupower -c all frequency-set -g powersave
 
 cpupower frequency-info
 
 cpupower frequency-set -g performance
 
 
 
cpupower -c all frequency-set -f 0.8GHZ


