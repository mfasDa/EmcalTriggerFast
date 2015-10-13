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
#include <cstdlib>

#include "TriggerMappingEmcalSimple.h"

/**
 * Constructor, setting EMCAL and DCAL+PHOS dimensions
 *
 * Phi Limits:
 * EMCAL
 * Sector 0: min(1.40413), max(1.73746), dist(0.333328)
 * Sector 1: min(1.7532),  max(2.08653), dist(0.333328)
 * Sector 2: min(2.10226), max(2.43559), dist(0.333328)
 * Sector 3: min(2.45133), max(2.78466), dist(0.333328)
 * Sector 4: min(2.8004),  max(3.13372), dist(0.333328)
 * Sector 5: min(3.14946), max(3.26149), dist(0.112032)
 *
 * DCAL + PHOS
 * Sector 0: min(4.54573), max(4.87905), dist(0.333328)
 * Sector 1: min(4.89479), max(5.22812), dist(0.333328)
 * Sector 2: min(5.24386), max(5.57718), dist(0.333328)
 * Sector 3: min(5.59292), max(5.70495), dist(0.112032)
 */
TriggerMappingEmcalSimple::TriggerMappingEmcalSimple():
	fPhiLimitsEMCAL(),
	fPhiLimitsDCALPHOS(),
	fEtaMin(-0.668305),
	fEtaMax(0.668305),
	fEtaSizeFOR()
{
	fEtaSizeFOR = (fEtaMax - fEtaMin) / 48;
	fPhiLimitsEMCAL.push_back(SectorPhi(0, 1.40413, 1.73746, 12));
	fPhiLimitsEMCAL.push_back(SectorPhi(1, 1.7532, 2.08653, 12));
	fPhiLimitsEMCAL.push_back(SectorPhi(2, 2.10226, 2.43559, 12));
	fPhiLimitsEMCAL.push_back(SectorPhi(3, 2.45133, 2.78466, 12));
	fPhiLimitsEMCAL.push_back(SectorPhi(4, 2.8004, 3.13372, 12));
	fPhiLimitsEMCAL.push_back(SectorPhi(5, 3.14946, 3.26149, 4));

	fPhiLimitsDCALPHOS.push_back(SectorPhi(0, 4.54573, 4.87905, 12));
	fPhiLimitsDCALPHOS.push_back(SectorPhi(1, 4.89479, 5.22812, 12));
	fPhiLimitsDCALPHOS.push_back(SectorPhi(2, 5.24386, 5.57718, 12));
	fPhiLimitsDCALPHOS.push_back(SectorPhi(3, 5.59292, 5.70495, 4));
}

/**
 * Destructor, nothing to do
 */
TriggerMappingEmcalSimple::~TriggerMappingEmcalSimple() {
}

/**
 * Map the position of the trigger channel. Always returns a trigger channel postition (also if outside the EMCAL
 * or DCAL+PHOS acceptance), which can however be undefined. In case of accessing row or col of an undefined trigger
 * position an exception is thrown.
 * @param eta Eta of the particle
 * @param phi Phi of the particle
 * @return The trigger channel corresponding to the Eta-Phi position of the particle.
 */
TriggerChannel TriggerMappingEmcalSimple::GetPositionFromEtaPhi(double eta, double phi) const{
	if(IsEMCAL(eta, phi)){
		return GetPositionFromEtaPhiEMCAL(eta, phi);
	} else if(IsDCALPHOS(eta, phi)){
		return GetPositionFromEtaPhiDCALPHOS(eta, phi);
	}
	return TriggerChannel();
}

/**
 * Check whether particle is in the EMCAL trigger active area
 * @param eta Particle Eta
 * @param phi Particle Phi
 * @return True if the particle is in the active area of the EMCAL trigger, false otherwise
 */
bool TriggerMappingEmcalSimple::IsEMCAL(double eta, double phi) const{
	if(eta < fEtaMin || eta > fEtaMax) return false;
	bool hasfound(false);
	for(std::vector<SectorPhi>::const_iterator phiit = fPhiLimitsEMCAL.begin(); phiit != fPhiLimitsEMCAL.end(); ++phiit){
		if(phiit->IsInSector(phi)){
			hasfound = true;
			break;
		}
	}
	return hasfound;
}

/**
 * Check whether particle is in the DCAL+PHOS trigger active area
 * @param eta Particle Eta
 * @param phi Particle Phi
 * @return True if the particle is in the active area of the EMCAL trigger, false otherwise
 */
bool TriggerMappingEmcalSimple::IsDCALPHOS(double eta, double phi) const{
	if(eta < fEtaMin || eta > fEtaMax) return false;
	bool hasfound(false);
	for(std::vector<SectorPhi>::const_iterator phiit = fPhiLimitsDCALPHOS.begin(); phiit != fPhiLimitsDCALPHOS.end(); ++phiit){
		if(phiit->IsInSector(phi)){
			hasfound = true;
			break;
		}
	}
	return hasfound;
}

/**
 * Map eta and phi to trigger position in EMCAL. Mapping is done in the following way:
 * - linear model between min and max phi using a constant size in phi of the FastOR
 * @param eta Particle Eta
 * @param phi Particle Phi
 * @return Trigger position in the EMCAL
 */
TriggerChannel TriggerMappingEmcalSimple::GetPositionFromEtaPhiEMCAL(double eta, double phi) const{
	TriggerChannel result;
	int row(-1), col(-1);
	// first get the row
	const SectorPhi *emcsec = FindSectorEMCAL(phi);
	if(!emcsec) 		// dead area
		return result;
	if(emcsec->GetSectorID() == 0){
		row = emcsec->GetRowNumberInSector(phi);
	} else {
		int rowsec = emcsec->GetRowNumberInSector(phi);
		row = 0;
		for(int isec = 0; isec < 6; isec++){
			if(isec < emcsec->GetSectorID()) row += fPhiLimitsEMCAL[isec].GetNumberOfRows();
			else break;
		}
		row += rowsec;
	}
	// then get the column
	// assume linear model, mapping from positive to negative eta as obtained from fastor + cell mapping from AliEMCALGeometry
	for(int coliter = 0; coliter < 48; coliter++){
		if(eta > fEtaMax - (coliter+1) * fEtaSizeFOR && eta < fEtaMax - coliter * fEtaSizeFOR){
			col = coliter;
			break;
		}
	}

	if(col >= 0)
		result.Set(row, col, TriggerChannel::kDCALPHOS);
	return result;
}

/**
 * Map eta and phi to trigger position in EMCAL. Mapping is done in the following way:
 * - linear model between min and max phi using a constant size in phi of the FastOR
 * @param eta Particle Eta
 * @param phi Particle Phi
 * @return Trigger position in the EMCAL
 */
TriggerChannel TriggerMappingEmcalSimple::GetPositionFromEtaPhiDCALPHOS(double eta, double phi) const{
	TriggerChannel result;
	int row(-1), col(-1);
	// first get the row
	// first get the row
	const SectorPhi *emcsec = FindSectorDCALPHOS(phi);
	if(!emcsec) 		// dead area
		return result;
	if(emcsec->GetSectorID() == 0){
		row = emcsec->GetRowNumberInSector(phi);
	} else {
		int rowsec = emcsec->GetRowNumberInSector(phi);
		row = 0;
		for(int isec = 0; isec < 4; isec++){
			if(isec < emcsec->GetSectorID()) row += fPhiLimitsDCALPHOS[isec].GetNumberOfRows();
			else break;
		}
		row += rowsec;
	}
	// then get the column
	// assume linear model, mapping from positive to negative eta as obtained from fastor + cell mapping from AliEMCALGeometry
	for(int coliter = 0; coliter < 48; coliter++){
		if(eta > fEtaMax - (coliter+1) * fEtaSizeFOR && eta < fEtaMax - coliter * fEtaSizeFOR){
			col = coliter;
			break;
		}
	}

	if(col >= 0)
		result.Set(row, col, TriggerChannel::kDCALPHOS);
	return result;
}

/**
 * Find the sector according to the given phi angle, either in the EMCAL or in the DCAL/PHOS
 * @param phi Phi of the track/particle
 * @param isEMCAL Switch whether to test EMCAL or DCAL/PHOS
 * @return Full sector information (NULL if not found)
 */
const TriggerMappingEmcalSimple::SectorPhi *TriggerMappingEmcalSimple::FindSector(double phi, bool isEMCAL) const {
	if(isEMCAL) return FindSectorEMCAL(phi);
	else return FindSectorDCALPHOS(phi);
}

/**
 * Find the sector in the EMCAL for a given phi of the particle/track
 * @param phi Particle/Track phi
 * @return Sector information according to the phi (NULL if not found)
 */
const TriggerMappingEmcalSimple::SectorPhi *TriggerMappingEmcalSimple::FindSectorEMCAL(double phi) const {
	const SectorPhi *result = NULL;
	for(std::vector<SectorPhi>::const_iterator secit = fPhiLimitsEMCAL.begin(); secit != fPhiLimitsEMCAL.end(); ++secit){
		if(secit->IsInSector(phi)){
			result = &(*secit);
			break;
		}
	}
	return result;
}

/**
 * Find the sector in the DCAL/PHOS for a given phi of the particle/track
 * @param phi Particle/Track phi
 * @return Sector information according to the phi (NULL if not found)
 */
const TriggerMappingEmcalSimple::SectorPhi *TriggerMappingEmcalSimple::FindSectorDCALPHOS(double phi) const {
	const SectorPhi *result = NULL;
	for(std::vector<SectorPhi>::const_iterator secit = fPhiLimitsDCALPHOS.begin(); secit != fPhiLimitsDCALPHOS.end(); ++secit){
		if(secit->IsInSector(phi)){
			result = &(*secit);
			break;
		}
	}
	return result;
}

/**
 * Initialize the Sector with mandatory information to map the position into a row number
 * @param sectorID ID of the sector, starting from 0
 * @param phiMin Min. phi of the sector
 * @param phiMax Max. phi of the sector
 * @param nrow Number of rows in the sector
 */
TriggerMappingEmcalSimple::SectorPhi::SectorPhi(int sectorID, double phiMin, double phiMax, int nrow):
	fSectorID(sectorID),
	fMinimum(phiMin),
	fMaximum(phiMax),
	fNRows(nrow)
{}

/**
 * Calculate row number in sector from the phi of the particle / track
 * @param phi
 * @return Row number of the FastOR within the chamber (-1 if not found)
 */
int TriggerMappingEmcalSimple::SectorPhi::GetRowNumberInSector(double phi) const {
	int rownumber = -1;
	double phiwidth = (fMaximum - fMinimum) / fNRows;
	int rowcounter = 0;
	for(double phiiter = fMinimum; phiiter < fMaximum; phiiter += phiwidth){
		if(phi > phiiter && phi < phiiter + phiwidth){
			rownumber = rowcounter;
			break;
		}
		rowcounter++;
	}
	return rownumber;
}
