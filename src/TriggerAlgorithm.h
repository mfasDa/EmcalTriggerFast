#ifndef ALIEMCALTRIGGERALGORITHM_H
#define ALIEMCALTRIGGERALGORITHM_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

class PatchContainer;
class TriggerChannelMap;
class TriggerSetup;

/**
 * @struct RawPatch
 * @brief Helper structure for raw patches
 *
 * Stores minimal information of reconstructed patches, such as row, column, and
 * reconstructed amplitude
 */
struct RawPatch{
	/**
	 * Default constructor, initializing all values with -1
	 */
	RawPatch():
		fCol(-1.),
		fRow(-1.),
		fADC(-1.),
		fTriggerBits(0)
	{}
	/**
	 * Constructor, initializing position and amplitude
	 * @param col Starting col
	 * @param row Starting row
	 * @param adc Patch amplitude
	 */
	RawPatch(int col, int row, double adc, int triggerBits):
		fCol(col),
		fRow(row),
		fADC(adc),
		fTriggerBits(triggerBits)
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
	 * Get starting row of the patch
	 * @return starting row
	 */
	int GetRowStart() const { return fRow; }
	/**
	 * Get Starting column of the patch
	 * @return starting column
	 */
	int GetColStart() const { return fCol; }
	/**
	 * Get the patch amplitude
	 * @return the patch amplitude
	 */
	double GetADC() const { return fADC; }

	/**
	 * Get the trigger bits
	 */
	int GetTriggerBits() const { return fTriggerBits; }

private:
	int         fCol;           ///< Lower left column in col-row coordinate space
	int         fRow;           ///< Lower left row in col-row coordinate space
	double      fADC;           ///< ADC value of the raw patch
	int         fTriggerBits;   ///< Tigger bit settings
};

/**
 * @class TriggerAlgorithm
 * @brief Base class for EMCAL trigger algorithms
 *
 * Base class for trigger algorithm implementations for the EMCAL trigger.
 */
class TriggerAlgorithm: public TObject {
public:
	TriggerAlgorithm();
	virtual ~TriggerAlgorithm() {}

	PatchContainer *FindPatches(TriggerChannelMap * channels) const = 0;
	/**
	 * Set the trigger channel ADC map used to create the trigger patches
	 * @param inputdata input
	 */
	void SetTriggerSetup(TriggerSetup *triggersetup) { fTriggerSetup = triggersetup; }

protected:
	TriggerSetup  		              *fTriggerSetup;       ///< Trigger setup data
};

#endif /* TRIGGERALGORITHM_H */
