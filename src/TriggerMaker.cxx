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
#include "TriggerMaker.h"

/**
 * Constructor, initializing channel maps for EMCAL and DCAL-PHOS
 */
TriggerMaker::TriggerMaker() :
	fJetTrigger(),
	fGammaTrigger(),
	fTriggerChannelsEMCAL(48, 64),
	fTriggerChannelsDCALPHOS(48, 40),
	fTriggerMapping()
{
	fJetTrigger.SetTriggerSetup(&fTriggerSetup);
	fGammaTrigger.SetTriggerSetup(&fTriggerSetup);
}

/**
 * Destructor
 */
TriggerMaker::~TriggerMaker() {
}

/**
 * Reset channel maps
 */
void TriggerMaker::Reset(){
	fTriggerChannelsEMCAL.Reset();
	fTriggerChannelsDCALPHOS.Reset();
}

/**
 * Main function to reconstruct trigger patches in the EMCAL and in the DCAL-PHOS.
 * Patches are found using the trigger channels map, which has to be filled from outside.
 * The order in the output list is:
 * #- EMCAL gamma
 * #- DCAL-PHOS gamma
 * #- EMCAL jet
 * #- DCAL-PHOS jet
 * @return vector with all trigger patches.
 */
std::vector<RawPatch> TriggerMaker::FindPatches() const {
	std::vector<RawPatch> result;

	// First run gamma triggers on EMCAL and DCAL-PHOS channels ...
	std::vector<RawPatch> gammaEMCAL = fGammaTrigger.FindPatches(&fTriggerChannelsEMCAL);
	for(std::vector<RawPatch>::iterator patchiter = gammaEMCAL.begin(); patchiter != gammaEMCAL.end(); patchiter++){
		patchiter->SetPatchType(RawPatch::kEMCALpatch);
		result.push_back(*patchiter);
	}
	std::vector<RawPatch> gammaDCALPHOS = fGammaTrigger.FindPatches(&fTriggerChannelsDCALPHOS);
	for(std::vector<RawPatch>::iterator patchiter = gammaDCALPHOS.begin(); patchiter != gammaDCALPHOS.end(); patchiter++){
		patchiter->SetPatchType(RawPatch::kDCALPHOSpatch);
		result.push_back(*patchiter);
	}

	// ... then run triggers on EMCAL and DCAL-PHOS channels
	std::vector<RawPatch> jetEMCAL = fJetTrigger.FindPatches(&fTriggerChannelsEMCAL);
	for(std::vector<RawPatch>::iterator patchiter = jetEMCAL.begin(); patchiter != jetEMCAL.end(); patchiter++){
		patchiter->SetPatchType(RawPatch::kEMCALpatch);
		result.push_back(*patchiter);
	}
	std::vector<RawPatch> jetDCALPHOS = fJetTrigger.FindPatches(&fTriggerChannelsDCALPHOS);
	for(std::vector<RawPatch>::iterator patchiter = jetDCALPHOS.begin(); patchiter != jetDCALPHOS.end(); patchiter++){
		patchiter->SetPatchType(RawPatch::kDCALPHOSpatch);
		result.push_back(*patchiter);
	}

	return result;
}

/**
 * Fill trigger channel map depending on where the particle hits the detector in the EMCAL DCAL-PHOS surface. Adds the charge
 * to the already existing charge. Doesn't do anything if the particle is outside of the detector acceptance of either of the
 * tow subsystems.
 * @param eta Track/Particle eta
 * @param phi Track/Particle phi
 * @param energy Track/Particle energy
 */
void TriggerMaker::FillChannelMap(double eta, double phi, double energy){
	TriggerChannel position = fTriggerMapping.GetPositionFromEtaPhi(eta, phi);
	if(position.IsEMCAL()){
		fTriggerChannelsEMCAL.AddADC(position.GetCol(), position.GetRow(), energy);
	} else if(position.IsDCALPHOS()){
		fTriggerChannelsDCALPHOS.AddADC(position.GetCol(), position.GetRow(), energy);
	}
}
