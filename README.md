# Fast simulation of the ALICE EMCAL/DCAL trigger response

The fast trigger simulation runs the ALICE EMCAL/DCAL trigger algorithms on a map of charges of particles deposited in the 
EMCAL. Using a simplified trigger channel mapping, the position of a particle in eta and phi is mapped to a trigger channel. 
The class TriggerMaker makes this transparent to the user. It is the users responsibility to 
- Determine the energy deposit in the detector
- Define the trigger thresholds (as function of energy)
- select the patches found by the trigger maker (function FindPatches)

The following simplifications are applied:
- No gaps between fastors within a supermodule
- Gaps between PHOS and DCAL in eta are ignored.
- PHOS mapping is part of the EMCAL mapping (assumption: PHOS towers ~ 1/4 of DCAL towers)
