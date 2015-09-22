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
#include <cstring>

#include "TriggerChannelMap.h"

/**
 * Constructor, initializing channel map with the dimensions needed
 * @param ncols Number of columns
 * @param nrows Number of rows
 */
TriggerChannelMap::TriggerChannelMap(int ncols, int nrows):
    fNADCCols(ncols),
    fNADCRows(nrows),
    fADC(NULL)
{
  fADC = new double[fNADCCols][fNADCRows];
  memset(fADC, 0, sizeof(double) * fNADCCols * fNADCRows);
}

/**
 * Destructor
 */
TriggerChannelMap::~TriggerChannelMap() {
  delete[] fADC;
}

/**
 * Set ADC value for position (col, row). Checks for boundary.
 * @param col Column of the position
 * @param row Row of the position
 * @param ADC The value to set
 */
void TriggerChannelMap::SetADC(int col, int row, double adc) {
  if(row >= fNADCRows || col >= fNADCCols)
	  throw BoundaryException(row, col, fNADCRows, fNADCCols);
  }
  fADC[col][row] = adc;
}

/**
 * Add ADC value for position (col, row). Checks for boundary.
 * @param col Column of the position
 * @param row Row of the position
 * @param ADC The value to set
 */
void TriggerChannelMap::AddADC(int col, int row, double adc) {
  if(row >= fNADCRows || col >= fNADCCols)
	  throw BoundaryException(row, col, fNADCRows, fNADCCols);
  }
  fADC[col][row] = += adc;
}

/**
 * Set the ADC values stored in the 2D map again to 0
 */
void TriggerChannelMap::Reset() {
  memset(fADC, 0, sizeof(double) * fNADCCols * fNADCRows);
}

/**
 * Get ADC value at position (col, row). Checks for boundary.
 * @param col Column of the position
 * @param row Row of the position
 * @return ADC value at the given position
 */
double TriggerChannelMap::GetADC(int col, int row) const {
  if(row >= fNADCRows || col >= fNADCCols)
	  throw BoundaryException(row, col, fNADCRows, fNADCCols);
  return fADC[col][row];
}
