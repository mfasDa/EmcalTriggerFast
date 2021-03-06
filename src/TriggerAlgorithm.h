#ifndef ALIEMCALTRIGGERALGORITHM_H
#define ALIEMCALTRIGGERALGORITHM_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <vector>

class PatchContainer;
class TriggerChannelMap;
class TriggerSetup;

/**
 * @class RawPatch
 * @brief Helper structure for raw patches
 *
 * Stores minimal information of reconstructed patches, such as row, column, and
 * reconstructed amplitude
 */
class RawPatch{
	/**
	 * Default constructor, initializing all values with -1
	 */
public:
	enum Patchtype {
		kAny,
		kEMCALpatch,
		kDCALPHOSpatch,
		kEMCALpatchGA,
		kEMCALpatchJE,		
		kEMCALpatchJE8x8,		
		kDCALpatchGA,		
		kDCALpatchJE,				
		kDCALpatchJE8x8,				
		kUndefPatch
	};

	RawPatch():
		fCol(0),
		fRow(0),
		fADC(-1.),
		fTriggerBits(0),
		fPatchSize(0),
		fPatchType(kUndefPatch)
	{}
	/**
	 * Constructor, initializing position and amplitude
	 * @param col Starting col
	 * @param row Starting row
	 * @param adc Patch amplitude
	 */
	RawPatch(unsigned char col, unsigned char row, double adc, unsigned int triggerBits):
		fCol(col),
		fRow(row),
		fADC(adc),
		fTriggerBits(triggerBits),
		fPatchSize(0),
		fPatchType(kUndefPatch)
	{}
	/**
	 * Destructor
	 */
	~RawPatch() {}

	/**
	 * Comparison operator, comparing to other in terms of ADC value
	 * @param other Object to compare with
	 * @return True if this adc is smaller, false otherwise
	 */
	bool operator<(const RawPatch & other) const {
		return fADC < other.fADC;
	}

	/**
	 * Set the type of the patch (EMCAL or DCAL-PHOS)
	 * @param ptype Type of the patch
	 */
	void SetPatchType(Patchtype ptype) { fPatchType = ptype; }

	/**
	 * Set the size of the patch
	 * @param patchsize
	 */
	void SetPatchSize(unsigned char patchsize) { fPatchSize = patchsize; }

	/**
	 * Get starting row of the patch
	 * @return starting row
	 */
	unsigned char GetRowStart() const { return fRow; }
	/**
	 * Get Starting column of the patch
	 * @return starting column
	 */
	unsigned char GetColStart() const { return fCol; }
	/**
	 * Get the patch amplitude
	 * @return the patch amplitude
	 */
	double GetADC() const { return fADC; }

	/**
	 * Get the size of the patch
	 * @return size of the patch
	 */
	unsigned char GetPatchSize() const { return fPatchSize; }

	/**
	 * Get the trigger bits
	 */
	int GetTriggerBits() const { return fTriggerBits; }

	/**
	 * Check whether patch is of type EMCAL
	 * @return True if patch is of type EMCAL, false otherwise
	 */
	bool IsEMCAL() const { return fPatchType == kEMCALpatch; }

	/**
	 * Check whether patch is of type DCAL-PHOS
	 * @return True if patch is of type DCAL-PHOS, false otherwise
	 */
	bool IsDCALPHOS() const { return fPatchType == kDCALPHOSpatch; }

	/**
	 * Get unique ID of the patch, calculated, from col, row and subregion size
	 * @return Unique ID of the patch;
	 */
	int GetUniqueID() const;

private:
	unsigned char         	fCol;           ///< Lower left column in col-row coordinate space
	unsigned char      		fRow;           ///< Lower left row in col-row coordinate space
	double      			fADC;           ///< ADC value of the raw patch
	unsigned int         	fTriggerBits;   ///< Tigger bit settings
	unsigned char			fPatchSize;	    ///< Patch size
	Patchtype				fPatchType;		///< Type of the trigger patch
};

/**
 * @class TriggerAlgorithm
 * @brief Base class for EMCAL trigger algorithms
 *
 * Base class for trigger algorithm implementations for the EMCAL trigger.
 */
class TriggerAlgorithm {
public:
	TriggerAlgorithm();
	virtual ~TriggerAlgorithm() {}

	virtual std::vector<RawPatch> FindPatches(const TriggerChannelMap * channels) const = 0;
	/**
	 * Set the trigger channel ADC map used to create the trigger patches
	 * @param inputdata input
	 */
	void SetTriggerSetup(TriggerSetup *triggersetup) { fTriggerSetup = triggersetup; }

protected:
	TriggerSetup  		              *fTriggerSetup;       ///< Trigger setup data
};

#endif /* TRIGGERALGORITHM_H */
