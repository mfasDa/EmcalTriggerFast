#ifndef TRIGGERMAPPINGEMCALSIMPLE_H_
#define TRIGGERMAPPINGEMCALSIMPLE_H_
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */
#include <exception>
#include <vector>

class TriggerChannel{
public:
	enum Detector{
		kEMCAL,
		kDCALPHOS,
		kUndefined,
	};
	class TriggerChannelException : public std::exception{
	public:
		TriggerChannelException() {}
		virtual ~TriggerChannelException() throw() {}
		const char *what() const throw() {
			return "Trigger channel not existing";
		}
	};

	TriggerChannel():
		fDetector(kUndefined),
		fRow(0),
		fCol(0)
	{}
	~TriggerChannel() {}

	void Set(Int_t row, Int_t col, Detector det){
		fRow = row;
		fCol = col;
		fDetector = det;
	}

	Int_t GetRow() const { if(!fDetector == kUndefined) throw TriggerChannelException(); return fRow; }
	Int_t GetCol() const { if(!fDetector == kUndefined) throw TriggerChannelException(); return fCol; }

	Bool_t IsEMCAL() const { if(fDetector == kEMCAL) return true; return false; }
	Bool_t IsDCALPHOS() const { if(fDetector == kDCALPHOS) return true; return false; }

private:
	Detector		fDetector;
	Int_t 			fRow;
	Int_t 			fCol;
}

class TriggerMappingEmcalSimple {
public:
	TriggerMappingEmcalSimple();
	virtual ~TriggerMappingEmcalSimple() {}

	TriggerChannel GetPositionFromEtaPhi(Double_t eta, Double_t phi) const;
	Bool_t IsEMCAL(Double_t eta, Double_t phi) const;
	Bool_t IsDCALPHOS(Double_t eta, Double_t phi) const;

protected:
	class SectorPhi{
	public:
		SectorPhi(Int_t sectorID, double phiMin, double phiMax, Int_t nrow);
		~SectorPhi() {}

		Int_t	 		GetSectorID() const { return fSectorID; }
		Int_t	 		GetNumberOfRows() const { return fNRows; }
		Double_t	 	GetPhiMin() const { return fMinimum; }
		Double_t 		GetPhiMax() const { return fMaximum; }

		Bool_t IsInSector(Double_t phi)  const { return phi > fMinimum && phi < fMaximum; }
		Int_t GetRowNumberInSector(Double_t phi) const;

	private:
		Int_t 			fSectorID;			///< ID of the sector, starting from 0 (Indices separate for EMCAL and DCAL)
		Double_t 		fMinimum;			///< Min. phi of the sector (0 - 2 pi)
		Double_t		fMaximum;			///< Max. phi of the sector (0 - 2 pi)
		Int_t 			fNRows;  			///< Number of rows in a sector in phi (12 for big supermodules, 4 for small)
	};

	const SectorPhi *FindSector(Double_t phi, Bool_t isEMCAL) const;
	const SectorPhi *FindSectorEMCAL(Double_t phi) const;
	const SectorPhi *FindSectorDCALPHOS(Double_t phi) const;
	TriggerChannel GetPositionFromEtaPhiEMCAL(Double_t eta, Double_t phi) const;
	TriggerChannel GetPositionFromEtaPhiDCALPHOS(Double_t eta, Double_t phi) const;

	std::vector<SectorPhi>		fPhiLimitsEMCAL;
	std::vector<SectorPhi> 		fPhiLimitsDCALPHOS;
	Double_t					fEtaMin;
	Double_t					fEtaMax;
	Double_t					fEtaSizeFOR;
};

#endif /* TRIGGERMAPPINGEMCALSIMPLE_H_ */
