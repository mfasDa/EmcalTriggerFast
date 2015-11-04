#ifndef SRC_TRIGGERMAKER_H_
#define SRC_TRIGGERMAKER_H_
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include "GammaTriggerAlgorithm.h"
#include "JetTriggerAlgorithm.h"
#include "TriggerChannelMap.h"
#include "TriggerBadChannelContainer.h"
#include "TriggerMappingEmcalSimple.h"
#include "TriggerSetup.h"

class TriggerMaker {
public:
	TriggerMaker();
	virtual ~TriggerMaker();

	void 							Reset();
	void 							FindPatches();
	std::vector<RawPatch>			GetPatches(const int what = RawPatch::kAny);
	RawPatch 						GetMaxGammaEMCAL();
	RawPatch 						GetMaxGammaDCALPHOS();
	RawPatch 						GetMaxJetEMCAL();
	RawPatch 						GetMaxJetDCALPHOS();
	RawPatch 						GetMaxJetEMCAL8x8();
	RawPatch 						GetMaxJetDCALPHOS8x8();

	double 							GetMedian(std::vector<RawPatch> v);

	double 							GetMedianGammaEMCAL();
	double 							GetMedianGammaDCALPHOS();
	double 							GetMedianJetEMCAL();
	double 							GetMedianJetDCALPHOS();
	double 							GetMedianJetEMCAL8x8();
	double 							GetMedianJetDCALPHOS8x8();

	void FillChannelMap(double eta, double phi, double energy);

	/**
	 * Get the map of the EMCAL trigger channels
	 * @return Map of the EMCAL trigger channels
	 */
	const TriggerChannelMap &GetEMCALChannels() const { return fTriggerChannelsEMCAL; }

	/**
	 * Get the map of the EMCAL trigger channels
	 * @return Map of the EMCAL trigger channels
	 */
	const TriggerChannelMap &GetDCALPHOSChannels() const { return fTriggerChannelsDCALPHOS; }

	/**
	 * Get the mapping between eta and phi on the one side and row and col in the EMCAL / DCAL on the other side
	 * @return Mapping for EMCAL and DCAL/PHOS trigger channels
	 */
	const TriggerMappingEmcalSimple &GetTriggerChannelMapping() const { return fTriggerMapping; }

	/**
	 * Setup trigger patch finders
	 * @param setup Configuration of the trigger patch finders
	 */
	void SetTriggerSetup(TriggerSetup &setup) { fTriggerSetup = setup; }

	/**
	 * Add bad channel position in EMCAL in row and col to the list of bad channels.
	 * Bad channels will be ignored when setting the energy
	 * @param col Column of the bad channel
	 * @param row Row of the bad channel
	 */
	void AddBadChannelEMCAL(int col, int row) { fBadChannelsEMCAL.AddChannel(col, row); }

	/**
	 * Add bad channel position in EMCAL in row and col to the list of bad channels.
	 * Bad channels will be ignored when setting the energy
	 * @param col Column of the bad channel
	 * @param row Row of the bad channel
	 */
	void AddBadChannelDCALPHOS(int col, int row) { fBadChannelsDCALPHOS.AddChannel(col, row); }

private:
	JetTriggerAlgorithm				fJetTrigger;						///< Algorithm finding jet patches on a trigger channel map
	GammaTriggerAlgorithm			fGammaTrigger;						///< Algorithm finding gamma patches on a trigger channel map
	TriggerChannelMap				fTriggerChannelsEMCAL;				///< Trigger channels for the EMCAL
	TriggerChannelMap				fTriggerChannelsDCALPHOS;			///< Trigger channels for the combination DCAL-PHOS
	TriggerMappingEmcalSimple		fTriggerMapping;					///< Mapping between trigger channels and eta and phi
	TriggerSetup					fTriggerSetup;						///< Setup of the EMCAL / DCAL-PHOS trigger algorithms
	TriggerBadChannelContainer		fBadChannelsEMCAL;					///< Map with bad EMCAL channels
	TriggerBadChannelContainer		fBadChannelsDCALPHOS;				///< Map with bad DCAL-PHOS channels
	bool							fHasRun;
	std::vector<RawPatch>			fGammaEMCAL;
	std::vector<RawPatch>			fGammaDCALPHOS;
	std::vector<RawPatch>			fJetEMCAL;
	std::vector<RawPatch>			fJetDCALPHOS;
	std::vector<RawPatch>			fJetEMCAL8x8;
	std::vector<RawPatch>			fJetDCALPHOS8x8;
};

#endif /* SRC_TRIGGERMAKER_H_ */
