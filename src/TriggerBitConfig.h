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
			msgbuilder << "Invalid trigger configuration: " << bitname << " bit < 0";
			fMessage = msgbuilder.str();
		}
		virtual ~InvalidConfigurationException() throw() {}

		const char *what() const throw() {
			return fMessage.c_str();
		}

	private:
		std::string 				fMessage;
	};

	TriggerBitConfig();
	TriggerBitConfig(int l0bit, int j1bit, int j2bit, int g1bit, int g2bit, int mcoffset);
	virtual ~TriggerBitConfig() {}

	void Initialise(const TriggerBitConfig &ref);

	int GetLevel0Bit() const { if(fL0Bit < 0) throw InvalidConfigurationException("Level0"); return fL0Bit; }
	int GetJetHighBit() const { if(fJHighBit < 0) throw InvalidConfigurationException("JetHigh"); return fJHighBit; }
	int GetJetLowBit() const { if(fJLowBit < 0) throw InvalidConfigurationException("JetLow"); return fJLowBit; }
	int GetGammaHighBit() const { if(fGHighBit < 0) throw InvalidConfigurationException("GammaHigh"); return fGHighBit; }
	int GetGammaLowBit() const { if(fGLowBit < 0) throw InvalidConfigurationException("GammaLow"); return fGLowBit; }
	int GetTriggerTypesEnd() const {if(fTriggerTypesEnd < 0) throw InvalidConfigurationException("MCOffset"); return fTriggerTypesEnd; }

protected:
	int fL0Bit;      			///< Level0 bit
	int fJHighBit;   			///< Jet High bit
	int fJLowBit;    			///< Jet Low bit
	int fGHighBit;   			///< Gamma High bit
	int fGLowBit;    			///< Gamma Low bit
	int fTriggerTypesEnd;   	///< Monte-Carlo offset
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
