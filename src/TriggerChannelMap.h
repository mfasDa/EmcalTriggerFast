#ifndef TRIGGERCHANNELMAP_H
#define TRIGGERCHANNELMAP_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <exception>
#include <sstream>
#include <string>

class TriggerChannelMap{
public:
	class BoundaryException : public std::exception{
	public:
		BoundaryException():
			exception(),
			fMessage(""),
			fRow(),
			fCol(),
			fNRow(),
			fNCol()
		{
		}
		BoundaryException(int row, int col, int nrow, int ncol):
			exception(),
			fMessage(""),
			fRow(row),
			fCol(col),
			fNRow(nrow),
			fNCol(ncol)
		{
			std::stringstream msgstream;
			msgstream << "Boundary exception: row(" << fRow << ", max " << fNRow -1 << "), col(" << fCol << ", max " << fNCol -1 << ")";
			fMessage = msgstream.str().c_str();
		}
		virtual ~BoundaryException() throw() {}

		int GetRow() const throw() { return fRow; }
		int GetCol() const throw() { return fCol; }
		int GetNRow() const throw() { return fNRow; }
		int GetNCol() const throw() { return fNCol; }

		const char *what() const throw(){
			return fMessage.c_str();
		}
	private:
		std::string 			fMessage;			///< Error message
		int						fRow;				///< Row of the position
		int						fCol;				///< Col of the position
		int						fNRow;				///< Number of rows in the channel map
		int						fNCol;				///< Number of cols in the channel map
	};

	TriggerChannelMap(int cols, int rows);
	virtual ~TriggerChannelMap();

	void Reset();

	void SetADC(int col, int row, double adc);
	void AddADC(int col, int row, double adc);
	double GetADC(int col, int row) const;
	/**
	 * Get the number of columns in the map
	 * @return The number of colums
	 */
	int GetNumberOfCols() const { return fNADCCols; }
	/**
	 * Get the number of rows in the map
	 * @return The number of cols
	 */
	int GetNumberOfRows() const { return fNADCRows; }

protected:
	int                     fNADCCols;      ///< Number of columns
	int                     fNADCRows;      ///< Number of rows
	double                  *fADC;          ///< Array of Trigger ADC values
};

#endif /* TRIGGERCHANNELMAP_H */
