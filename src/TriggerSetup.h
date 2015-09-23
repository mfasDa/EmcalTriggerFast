#ifndef TRIGGERSETUP_H
#define TRIGGERSETUP_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include "TriggerBitConfig.h"

/**
 * @class TriggerSetup
 */
class TriggerSetup {
public:
	TriggerSetup();
	TriggerSetup(const TriggerSetup &p);
	TriggerSetup &operator=(const TriggerSetup &p);
	/**
	 * Destructor
	 */
	virtual ~TriggerSetup() {}

	double GetThresholdJetLow() const { return fThresholds[2]; }
	double GetThresholdJetHigh() const { return fThresholds[0]; }

	double GetThresholdGammaLow() const { return fThresholds[3]; }
	double GetThresholdGammaHigh() const { return fThresholds[1]; }

	const TriggerBitConfig &GetTriggerBitConfiguration() const { return fTriggerBitConfig; }

	void SetThresholds( double i0, double i1, double i2, double i3 ) {
		fThresholds[0] = i0; fThresholds[1] = i1; fThresholds[2] = i2; fThresholds[3] = i3;}
	void SetTriggerBitConfig(const TriggerBitConfig &ref){
		fTriggerBitConfig.Initialise(ref);
	}

	void Clean();

protected:
	double                                  fThresholds[4];                 ///< per event L1 online thresholds in ADC counts
	TriggerBitConfig                		fTriggerBitConfig;              ///< Trigger bit configuration
};
#endif
