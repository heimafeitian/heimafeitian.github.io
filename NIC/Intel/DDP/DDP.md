<img width="1139" height="780" alt="image" src="https://github.com/user-attachments/assets/8525b373-fd44-4cdb-be6e-dbf23ae688fc" />615266-800 Series Controllers Migration Guide_Rev2.0.pdf
617015_E810 DDP Technology Guide_rev3_0.pdf
618651-E810 DDP for Comms TechGuide_Rev2.2.pdf
container-bare-metal-for-2nd-3rd-generation-intel-xeon-scalable-processor.pdf
ddp-guide-intel-ethernet-700-series-controller-gtpv1-profile-app-note.pdf
ddp-solution-brief.pdf
E810 DDP for Comms TechGuide_Rev2.5.pdf
E810_Datasheet_Rev2.3.pdf
Intel Ethernet Controller E810 Dynamic Device Personalization Technology Guide.pdf
IntelEthernet_700800_DDPsupport_CNF_Kubernetes_TechGuide_621832v2.pdf
IntelEthernet800_DDP_TelecomWorkloads_TechGuide_634459v1.pdf
intel-ethernet-controller-700-series-gtpv1-dynamic-device-personalization.pdf
intel-ethernet-controller-800-series-device-personalization-ddp-for-telecommunications-workloads-technology-guide2.pdf



issues：
Enabled 32 VFs, and tried to add some RSS flow rules to those VFs;
Failed to add those RSS flow rules due to ICE_ERR_AQ_ERROR (ENOSPC);
Rootcause:
TCAM Line is 512 for RSS Profile;
Used 50 TCAM lines when started default RSS profile (only enable IP RSS) for 1 VSIG
When PTG changed, copied all profile PTGs from previous VSIG, and generated a new VSIG;
TCAM Line consumed rapidly due to changing RSS flow rules;



Customize default RSS profile (PTG) bitmap;
remove the GTP relative PTGs (18 items)
remove the ESP, AH, NAT_T (6 items)
Advantage: can hold more PTGs for different VFs;
Disadvantage: discard some PTGs support (e.g.: ESP, AH …), that means those unsupported PTGs will flow to queue index 0 by default;

Adjust the creating rules order
launch app with –disable-rss
create a series of rules on demand;
set the default RSS profile;
Advantage: Keep all original default profiles;
Disadvantage: after that, add new rules still perhaps repro this issue;

