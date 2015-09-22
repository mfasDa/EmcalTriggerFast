#ifndef TRIGGERBITCONFIG_H
#define TRIGGERBITCONFIG_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <exception>
#include <sstream>
#include <string>

class TriggerBitConfig {
public:
	class InvalidConfigurationException : public std::exception{
	public:
		InvalidConfigurationException(std::string bitname):
			fMessage("")
		{
			std::stringstream msgbuilder;
			msgbuilder << "Invalid trigger configuration: " << bitname << " bit < 0"
		}
		virtual ~InvalidConfigurationException() throw() {}

		const char *what() const throw() {
			return fMessage.c_str();
		}

	private:
		std::string 				fMessage;
	};

	TriggerBitConfig();
	TriggerBitConfig(Int_t l0bit, Int_t j1bit, Int_t j2bit, Int_t g1bit, Int_t g2bit, Int_t mcoffset);
	virtual ~TriggerBitConfig() {}

	void Initialise(const TriggerBitConfig &ref);

	Int_t GetLevel0Bit() const { if(fL0Bit < 0) throw InvalidConfigurationException("Level0"); return fL0Bit; }
	Int_t GetJetHighBit() const { if(fJHighBit < 0) throw InvalidConfigurationException("JetHigh"); return fJHighBit; }
	Int_t GetJetLowBit() const { if(fJLowBit < 0) throw InvalidConfigurationException("JetLow"); return fJLowBit; }
	Int_t GetGammaHighBit() const { if(fGHighBit < 0) throw InvalidConfigurationException("GammaHigh"); return fGHighBit; }
	Int_t GetGammaLowBit() const { if(fGLowBit < 0) throw InvalidConfigurationException("GammaLow"); return fGLowBit; }
	Int_t GetTriggerTypesEnd() const {if(fTriggerTypesEnd < 0) throw InvalidConfigurationException("MCOffset"); return fTriggerTypesEnd; }

protected:
	Int_t fL0Bit;      			///< Level0 bit
	Int_t fJHighBit;   			///< Jet High bit
	Int_t fJLowBit;    			///< Jet Low bit
	Int_t fGHighBit;   			///< Gamma High bit
	Int_t fGLowBit;    			///< Gamma Low bit
	Int_t fTriggerTypesEnd;   	///< Monte-Carlo offset
};

class TriggerBitConfigOld : public TriggerBitConfig{
public:
	TriggerBitConfigOld();
	virtual ~TriggerBitConfigOld() {}
};

class TriggerBitConfigNew : public TriggerBitConfig{
public:
	TriggerBitConfigNew();
	virtual ~TriggerBitConfigNew() {}
};

#endif /* TRIGGERBITCONFIG_H */
