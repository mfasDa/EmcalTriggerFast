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
#include "TriggerSetup.h"

/**
 * Default constructor
 */
TriggerSetup::TriggerSetup() :
  TNamed(),
  fThresholds(),
  fTriggerBitConfig()
{
  for( int i = 0; i < 4; i++) fThresholds[i] = -1;
}

/**
 * Copy constructor
 * \param p Reference for the copy
 */
TriggerSetup::TriggerSetup(const TriggerSetup &p) :
  TNamed(p),
  fTriggerBitConfig()
{
  // Copy constructor.
  for( int i = 0; i < 4; i++ ) fThresholds[i] = p.fThresholds[i];
  fTriggerBitConfig.Initialise(p.fTriggerBitConfig);
}

/**
 * Assignment operator
 * @param p Reference for the assignment
 * @return This object
 */
TriggerSetup &TriggerSetup::operator=(const TriggerSetup &p){
  if (this != &p) {
    for( int i = 0; i < 4; i++ )
      fThresholds[i] = p.fThresholds[i];
    fTriggerBitConfig.Initialise(p.fTriggerBitConfig);
  }

  return *this;
}

/**
 * Cleaning function, resets all arrays to 0
 */
void TriggerSetup::Clean(){
  for( int i = 0; i < 4; i++ )
    fThresholds[i] = -1;
}

