#ifndef GAMMATRIGGERALGORITHM_H
#define GAMMATRIGGERALGORITHM_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include "TriggerAlgorithm.h"

class PatchContainer;
class TriggerChannelMap;

/**
 * @class GammaTriggerAlgorithm
 * @brief Implementation of the EMCAL gamma trigger algorithm using ADC values
 *
 * This class implements the EMCAL Level1 algorithm finding gamma patches. The patch
 * finding algorithm is described and implemented in the function FindPatches.
 */
class GammaTriggerAlgorithm: public TriggerAlgorithm {
public:
	GammaTriggerAlgorithm();
	virtual ~GammaTriggerAlgorithm();

	std::vector<RawPatch> FindPatches(TriggerChannelMap * channels) const;

};
#endif /* GammaTriggerAlgorithm_H */
