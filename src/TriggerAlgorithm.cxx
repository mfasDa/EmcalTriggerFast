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
#include "TriggerAlgorithm.h"

/**
 * Constructor
 */
TriggerAlgorithm::TriggerAlgorithm() :
fTriggerSetup(NULL)
{
}

int RawPatch::GetUniqueID() const {
	// normalize row and col by the index of the subregion
	int subregionSize  = ((fPatchSize == 16) || (fPatchSize == 8)) ? 4 : 1, neta = 48/subregionSize;
	return int(fCol)/subregionSize + int(fRow)/subregionSize * neta;
}
