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

	void Set(int row, int col, Detector det){
		fRow = row;
		fCol = col;
		fDetector = det;
	}

	int GetRow() const { if(fDetector == kUndefined) throw TriggerChannelException(); return fRow; }
	int GetCol() const { if(fDetector == kUndefined) throw TriggerChannelException(); return fCol; }

	bool IsEMCAL() const { if(fDetector == kEMCAL) return true; return false; }
	bool IsDCALPHOS() const { if(fDetector == kDCALPHOS) return true; return false; }

private:
	Detector		fDetector;
	int 			fRow;
	int 			fCol;
};

class TriggerMappingEmcalSimple {
public:
	TriggerMappingEmcalSimple();
	virtual ~TriggerMappingEmcalSimple();

	TriggerChannel GetPositionFromEtaPhi(double eta, double phi) const;
	bool IsEMCAL(double eta, double phi) const;
	bool IsDCALPHOS(double eta, double phi) const;

protected:
	class SectorPhi{
	public:
		SectorPhi(int sectorID, double phiMin, double phiMax, int nrow);
		~SectorPhi() {}

		int	 		GetSectorID() const { return fSectorID; }
		int	 		GetNumberOfRows() const { return fNRows; }
		double	 	GetPhiMin() const { return fMinimum; }
		double 		GetPhiMax() const { return fMaximum; }

		bool IsInSector(double phi)  const { return phi > fMinimum && phi < fMaximum; }
		int GetRowNumberInSector(double phi) const;

	private:
		int 			fSectorID;			///< ID of the sector, starting from 0 (Indices separate for EMCAL and DCAL)
		double 			fMinimum;			///< Min. phi of the sector (0 - 2 pi)
		double			fMaximum;			///< Max. phi of the sector (0 - 2 pi)
		int 			fNRows;  			///< Number of rows in a sector in phi (12 for big supermodules, 4 for small)
	};

	const SectorPhi *FindSector(double phi, bool isEMCAL) const;
	const SectorPhi *FindSectorEMCAL(double phi) const;
	const SectorPhi *FindSectorDCALPHOS(double phi) const;
	TriggerChannel GetPositionFromEtaPhiEMCAL(double eta, double phi) const;
	TriggerChannel GetPositionFromEtaPhiDCALPHOS(double eta, double phi) const;

	std::vector<SectorPhi>		fPhiLimitsEMCAL;
	std::vector<SectorPhi> 		fPhiLimitsDCALPHOS;
	double						fEtaMin;
	double						fEtaMax;
	double						fEtaSizeFOR;
};

#endif /* TRIGGERMAPPINGEMCALSIMPLE_H_ */
