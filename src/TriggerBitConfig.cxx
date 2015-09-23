/********************************************************************************
 *  Fast simulation tool for the trigger response of the ALICE EMCAL-DCAL       *
 *  Detector system                                                             *
 *  Copyright (C) 2015  Markus Fasel, ALICE Collaboration                       *
 *                                                                              *
 *  This program is free software: you can redistribute it and/or modify        *
 *  it under the terms of the GNU General Public License as published by        *
 *  the Free Software Foundation, either version 3 of the License, or           *
 *  (at your option) any later version.                                         *
 *                                                                              *
 *  This program is distributed in the hope that it will be useful,	            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 *  GNU General Public License for more details.                                *
 *                                                                              *
 *  You should have received a copy of the GNU General Public License           *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.       *
 ********************************************************************************/
#include "TriggerBitConfig.h"

/**
 * Dummy constructor for the configuraiton base classes, not to be callled
 */
TriggerBitConfig::TriggerBitConfig():
fL0Bit(-1),
fJHighBit(-1),
fJLowBit(-1),
fGHighBit(-1),
fGLowBit(-1),
fTriggerTypesEnd(-1)
{
}

/**
 * Constructor initialising the configurations. Used by the inheriting classes
 * @param l0bit	Bit for Level0 (not used here)
 * @param jhighbit Bit for Jet High (EJ1)
 * @param jlowbit Bit for Jet Low (EJ2)
 * @param ghighbit Bit for Gamma High (EG1)
 * @param glowbit Bit for Gamma Low (EG2)
 * @param mcoffset Monte Carlo offset bit (not used here)
 */
TriggerBitConfig::TriggerBitConfig(
		int l0bit,
		int jhighbit,
		int jlowbit,
		int ghighbit,
		int glowbit,
		int mcoffset):
			fL0Bit(l0bit),
			fJHighBit(jhighbit),
			fJLowBit(jlowbit),
			fGHighBit(ghighbit),
			fGLowBit(glowbit),
			fTriggerTypesEnd(mcoffset)
{
}

/**
 * Initialise from other object
 * @param ref Reference used to initialize this object
 */
void TriggerBitConfig::Initialise(const TriggerBitConfig& ref) {
	fL0Bit = ref.GetLevel0Bit();
	fJHighBit = ref.GetJetHighBit();
	fJLowBit = ref.GetJetLowBit();
	fGHighBit = ref.GetGammaHighBit();
	fGLowBit = ref.GetGammaLowBit();
	fTriggerTypesEnd = ref.GetTriggerTypesEnd();
}

/**
 * Settings for the 2-bit configuration
 */
TriggerBitConfigOld::TriggerBitConfigOld():
    		TriggerBitConfig(0,2,2,1,1,3)
{
}

/**
 * Settings for the 4-bit configuration
 */
TriggerBitConfigNew::TriggerBitConfigNew():
    		TriggerBitConfig(0,3,4,1,2,5)
{
}

