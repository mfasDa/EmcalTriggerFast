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
#include "TriggerChannelMap.h"
#include "JetTriggerAlgorithm.h"
#include "TriggerSetup.h"

/**
 * Constructor
 */
JetTriggerAlgorithm::JetTriggerAlgorithm():
  TriggerAlgorithm()
{
}

/**
 * Destructor
 */
JetTriggerAlgorithm::~JetTriggerAlgorithm() {
}

/**
 * Gamma trigger algorithm
 * 1. Loop over all rows (- patchsize) to get the starting position of the patch
 * 2. Loop over ADC values in the 16x16 window
 * 3. Sorting of the trigger patches so that the highest energetic patch (main patch is the first)
 * 4. Fill the output trigger object
 * @param channes Input channel map
 * @return vector with trigger patches
 */
std::vector<RawPatch> JetTriggerAlgorithm::FindPatches(const TriggerChannelMap *channels) const {
	std::vector<RawPatch> rawpatches;

	Double_t adcsum(0);
	for(int irow = 0; irow < channels->GetNumberOfRows() - 15; ++irow){
		for(int icol = 0; icol < channels->GetNumberOfCols() - 15; ++icol){
			// 16x16 window
			adcsum = 0;
			for(int jrow = 0; jrow < 16; jrow++)
				for(int jcol = 0; jcol < 16; jcol++)
					adcsum += channels->GetADC(icol + jcol, irow + jrow);

			// make decision, low and high threshold
			Int_t triggerBits(0);
			if(adcsum > fTriggerSetup->GetThresholdJetHigh()) SETBIT(triggerBits, fTriggerSetup->GetTriggerBitConfiguration().GetJetHighBit());
			if(adcsum > fTriggerSetup->GetThresholdJetLow()) SETBIT(triggerBits, fTriggerSetup->GetTriggerBitConfiguration().GetJetLowBit());

			// Set special bit
			if(triggerBits){
				rawpatches.push_back(RawPatch(icol, irow, adcsum, triggerBits));
			}
		}
	}

	// sort patches so that the main patch appears first
	std::sort(rawpatches.begin(), rawpatches.end());
	return rawpatches;
}
