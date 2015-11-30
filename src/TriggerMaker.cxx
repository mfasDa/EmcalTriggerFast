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
	fTriggerMapping(),
	fBadChannelsEMCAL(),
	fBadChannelsDCALPHOS(),
	fHasRun(false),
	fAcceptPHOSPatches(true),
	fGammaEMCAL(),
	fGammaDCALPHOS(),
	fJetEMCAL(),
	fJetDCALPHOS(),
	fJetEMCAL8x8(),
	fJetDCALPHOS8x8()
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
void TriggerMaker::Reset() {
	fTriggerChannelsEMCAL.Reset();
	fTriggerChannelsDCALPHOS.Reset();
	fGammaEMCAL.clear();
	fGammaDCALPHOS.clear();
	fJetEMCAL.clear();
	fJetDCALPHOS.clear();
	fJetEMCAL8x8.clear();
	fJetDCALPHOS8x8.clear();
	fHasRun = false;
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

void TriggerMaker::FindPatches() {

	fGammaEMCAL     = fGammaTrigger.FindPatches 	(	&fTriggerChannelsEMCAL		);
	fGammaDCALPHOS  = fGammaTrigger.FindPatches 	(	&fTriggerChannelsDCALPHOS	);
	fJetEMCAL       = fJetTrigger.  FindPatches 	(	&fTriggerChannelsEMCAL		);
	fJetDCALPHOS    = fJetTrigger.  FindPatches 	(	&fTriggerChannelsDCALPHOS	);
	fJetEMCAL8x8    = fJetTrigger.  FindPatches8x8	(	&fTriggerChannelsEMCAL		);
	fJetDCALPHOS8x8 = fJetTrigger.  FindPatches8x8	(	&fTriggerChannelsDCALPHOS	);

	fHasRun = true;
}

std::vector<RawPatch> TriggerMaker::GetPatches(const int what) {
	if (fHasRun == false)
		FindPatches();

	std::vector<RawPatch> result;

	if (what == RawPatch::kAny || what == RawPatch::kEMCALpatchGA ) {
		for (std::vector<RawPatch>::iterator patchiter = fGammaEMCAL.begin(); patchiter != fGammaEMCAL.end(); patchiter++) {
			patchiter->SetPatchType(RawPatch::kEMCALpatch);
			result.push_back(*patchiter);
		}
	}

	if (what == RawPatch::kAny || what == RawPatch::kDCALpatchGA ) {
		for (std::vector<RawPatch>::iterator patchiter = fGammaDCALPHOS.begin(); patchiter != fGammaDCALPHOS.end(); patchiter++) {
			if(!fAcceptPHOSPatches && IsPHOSPatch(patchiter->GetColStart(), patchiter->GetRowStart(), 2)) continue;
			patchiter->SetPatchType(RawPatch::kDCALPHOSpatch);
			result.push_back(*patchiter);
		}
	}

	if (what == RawPatch::kAny || what == RawPatch::kEMCALpatchJE ) {
		for (std::vector<RawPatch>::iterator patchiter = fJetEMCAL.begin(); patchiter != fJetEMCAL.end(); patchiter++) {
			patchiter->SetPatchType(RawPatch::kEMCALpatch);
			result.push_back(*patchiter);
		}
	}

	if (what == RawPatch::kAny || what == RawPatch::kDCALpatchJE ) {
		for (std::vector<RawPatch>::iterator patchiter = fJetDCALPHOS.begin(); patchiter != fJetDCALPHOS.end(); patchiter++) {
			if(!fAcceptPHOSPatches && IsPHOSPatch(patchiter->GetColStart(), patchiter->GetRowStart(), 16)) continue;
			patchiter->SetPatchType(RawPatch::kDCALPHOSpatch);
			result.push_back(*patchiter);
		}
	}

	if (what == RawPatch::kAny || what == RawPatch::kEMCALpatchJE8x8 ) {
		for (std::vector<RawPatch>::iterator patchiter = fJetEMCAL8x8.begin(); patchiter != fJetEMCAL8x8.end(); patchiter++) {
			patchiter->SetPatchType(RawPatch::kEMCALpatch);
			result.push_back(*patchiter);
		}
	}

	if (what == RawPatch::kAny || what == RawPatch::kDCALpatchJE8x8 ) {
		for (std::vector<RawPatch>::iterator patchiter = fJetDCALPHOS8x8.begin(); patchiter != fJetDCALPHOS8x8.end(); patchiter++) {
			if(!fAcceptPHOSPatches && IsPHOSPatch(patchiter->GetColStart(), patchiter->GetRowStart(), 8)) continue;
			patchiter->SetPatchType(RawPatch::kDCALPHOSpatch);
			result.push_back(*patchiter);
		}
	}

	return result;
}

bool TriggerMaker::IsPHOSPatch(int col, int row, int size){
	return (col >= kMinEtaPHOS) && (col+size <kMaxEtaPHOS) && (row >= kMinRowPHOS) && (row+size < kMaxRowPHOS);
}

RawPatch TriggerMaker::GetMaxGammaEMCAL()
{
	if (fHasRun == false)
		FindPatches();
	if (fGammaEMCAL.empty())
		return RawPatch();
	else
		return fGammaEMCAL.back();
}

RawPatch TriggerMaker::GetMaxGammaDCALPHOS()
{
	if (fHasRun == false)
		FindPatches();
	if (fGammaDCALPHOS.empty())
		return RawPatch();
	else
		return fGammaDCALPHOS.back();
}

RawPatch TriggerMaker::GetMaxJetEMCAL()
{
	if (fHasRun == false)
		FindPatches();
	if (fJetEMCAL.empty())
		return RawPatch();
	else
		return fJetEMCAL.back();
}

RawPatch TriggerMaker::GetMaxJetDCALPHOS()
{
	if (fHasRun == false)
		FindPatches();
	if (fJetDCALPHOS.empty())
		return RawPatch();
	else
		return fJetDCALPHOS.back();
}

RawPatch TriggerMaker::GetMaxJetEMCAL8x8()
{
	if (fHasRun == false)
		FindPatches();
	if (fJetEMCAL8x8.empty())
		return RawPatch();
	else
		return fJetEMCAL8x8.back();
}

RawPatch TriggerMaker::GetMaxJetDCALPHOS8x8()
{
	if (fHasRun == false)
		FindPatches();
	if (fJetDCALPHOS8x8.empty())
		return RawPatch();
	else
		return fJetDCALPHOS8x8.back();
}

double TriggerMaker::GetMedian(std::vector<RawPatch> v)
{
	double median = 0;
	size_t size = v.size();

	if (size > 0)
	{
		size_t halfsize = v.size() / 2;
		if (size % 2 == 0)
		{
			median = (v[halfsize - 1].GetADC() + v[halfsize].GetADC()) / 2;
		}
		else
		{
			median = v[halfsize].GetADC();
		}
	}
	return median;
}

double TriggerMaker::GetMedianGammaEMCAL()
{
	if (fHasRun == false)
		FindPatches();
	return GetMedian(fGammaEMCAL);
}

double TriggerMaker::GetMedianGammaDCALPHOS()
{
	if (fHasRun == false)
		FindPatches();
	return GetMedian(fGammaDCALPHOS);
}

double TriggerMaker::GetMedianJetEMCAL()
{
	if (fHasRun == false)
		FindPatches();
	return GetMedian(fJetEMCAL);
}

double TriggerMaker::GetMedianJetDCALPHOS()
{
	if (fHasRun == false)
		FindPatches();
	return GetMedian(fJetDCALPHOS);
}

double TriggerMaker::GetMedianJetEMCAL8x8()
{
	if (fHasRun == false)
		FindPatches();
	return GetMedian(fJetEMCAL8x8);
}

double TriggerMaker::GetMedianJetDCALPHOS8x8()
{
	if (fHasRun == false)
		FindPatches();
	return GetMedian(fJetDCALPHOS8x8);
}

/**
 * Fill trigger channel map depending on where the particle hits the detector in the EMCAL DCAL-PHOS surface. Adds the charge
 * to the already existing charge. Doesn't do anything if the particle is outside of the detector acceptance of either of the
 * tow subsystems.
 * @param eta Track/Particle eta
 * @param phi Track/Particle phi
 * @param energy Track/Particle energy
 */
void TriggerMaker::FillChannelMap(double eta, double phi, double energy) {
	TriggerChannel position = fTriggerMapping.GetPositionFromEtaPhi(eta, phi);
	if (position.IsEMCAL()) {
		if (!fBadChannelsEMCAL.HasChannel(position.GetCol(), position.GetRow()))
			fTriggerChannelsEMCAL.AddADC(position.GetCol(), position.GetRow(), energy);
	} else if (position.IsDCALPHOS()) {
		if (!fBadChannelsDCALPHOS.HasChannel(position.GetCol(), position.GetRow()))
			fTriggerChannelsDCALPHOS.AddADC(position.GetCol(), position.GetRow(), energy);
	}
}
