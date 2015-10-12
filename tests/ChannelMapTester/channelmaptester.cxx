#include <cstdlib>

#include <TH2.h>
#include <TFile.h>
#include <TMath.h>
#include <TRandom.h>

#include "TriggerMappingEmcalSimple.h"

int main(int argc, const char **argv){
	TriggerMappingEmcalSimple emcalmapping;

	TH2 *hRowColEmcal = new TH2F("hRowColEmcal", "Row-Col position in EMCAL", 50, -0.5, 49.5, 120, -0.5, 119.5),
			*hRowColDcalPhos = new TH2F("hRowColDcalPhos", "Row-Col position in DCAL-PHOS", 50, -0.5, 49.5, 120, -0.5, 119.5),
			*hEtaPhiEmcal = new TH2F("hEtaPhiEmcal", "Eta-phi of particles in EMCAL", 100, -1., 1., 100, 0., 7),
			*hEtaPhiDcalPhos = new TH2F("hEtaPhiDcalPhos", "Eta-phi of particles in DCAL-PHOS", 100, -1., 1., 700., 0, 7.);

	// generate particles flat in eta and phi, and check the positions in
	// EMCAL and DCAL
	for(int ipart = 0; ipart <1000000; ipart++){
		double eta = gRandom->Uniform(-1., 1.),
				phi = gRandom->Uniform(0., 2*TMath::Pi());
		if(emcalmapping.IsEMCAL(eta, phi)){
			hEtaPhiEmcal->Fill(eta, phi);
			TriggerChannel emcalchannel = emcalmapping.GetPositionFromEtaPhi(eta, phi);
			hRowColEmcal->Fill(emcalchannel.GetCol(), emcalchannel.GetRow());
		} else if(emcalmapping.IsDCALPHOS(eta, phi)){
			hEtaPhiDcalPhos->Fill(eta, phi);
			TriggerChannel dcalphoschannel = emcalmapping.GetPositionFromEtaPhi(eta, phi);
			hRowColDcalPhos->Fill(dcalphoschannel.GetCol(), dcalphoschannel.GetRow());
		}
	}
	TFile *out = new TFile("channeltester.root", "RECREATE");
	out->cd();
	hRowColEmcal->Write();
	hRowColDcalPhos->Write();
	hEtaPhiEmcal->Write();
	hEtaPhiDcalPhos->Write();
	out->Close();
	delete out;
	return EXIT_SUCCESS;
}
