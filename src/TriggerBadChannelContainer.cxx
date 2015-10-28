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
#include "TriggerBadChannelContainer.h"

void TriggerBadChannelContainer::AddChannel(int col, int row){
  if(HasChannel(col, row)) return;
  fChannels.push_back(TriggerChannelPosition(col, row));
}


bool TriggerBadChannelContainer::HasChannel(int col, int row){
  TriggerChannelPosition test(col, row);
  bool found(false);
  for(std::vector<TriggerChannelPosition>::iterator channeliter = fChannels.begin(); channeliter != fChannels.end(); ++channeliter){
	  if(*channeliter == test){
		  found = true;
		  break;
	  }
  }
  return found;
}

bool TriggerBadChannelContainer::TriggerChannelPosition::operator==(const TriggerChannelPosition &other) const {
  return fCol == other.fCol && fRow == other.fRow;
}

bool TriggerBadChannelContainer::TriggerChannelPosition::operator<(const TriggerBadChannelContainer::TriggerChannelPosition &other) const {
  if(fCol == other.fCol){
    if(fRow == other.fRow) return 0;
    else if(fRow < other.fRow) return -1;
    else return 1;
  }
  else if(fCol < other.fCol) return -1;
  else return 1;
}
