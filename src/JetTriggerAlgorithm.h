#ifndef JETTIRGGERALGORITHM_H
#define JETTIRGGERALGORITHM_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include "TriggerAlgorithm.h"

class PatchContainer;

class JetTirggerAlgorithm: public TriggerAlgorithm {
public:
	JetTirggerAlgorithm();
	virtual ~JetTirggerAlgorithm();

	PatchContainer *FindPatches(TriggerChannelMap * channels) const;
};

#endif /* JETTIRGGERALGORITHM_H */
