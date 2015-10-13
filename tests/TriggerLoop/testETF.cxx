#include "TriggerSetup.h"
#include "TriggerMaker.h"
#include "TriggerBitConfig.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <boost/random.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/random/uniform_real.hpp>

// This is a typedef for a random number generator.
// Try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
typedef boost::random::mt19937 base_generator_type;

int main()
{
	using namespace boost::math;
	//using namespace boost::multiprecision;
	using namespace boost::random;
	base_generator_type generator(42);
	generator.seed(static_cast<unsigned int>(std::time(0)));
	const double pi = constants::pi<double>();
	boost::uniform_real<> uni_dist(0, 1);
	boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);

	TriggerSetup tsetup;
	tsetup.SetThresholds(100., 100., 0., 0.);
	tsetup.SetTriggerBitConfig(TriggerBitConfigNew());
	TriggerMaker tm;
	tm.SetTriggerSetup(tsetup);

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(2);

	int nevents = 10;
	for (unsigned int iev = 0; iev < nevents; iev++)
	{
		tm.Reset();
		int nparticles = uni() * 100;
		std::cout << "[i] Evevt: " << iev << " N particles: " << nparticles << std::endl;
		for (unsigned int ip = 0; ip < nparticles; ip++)
		{
			double phi_v = uni() * pi * 2.;
			double eta_v = uni() * 2. - 1.;
			double ene_v = uni() * 100.;
			std::cout << "[i] phi,eta,ene: "
			          << phi_v << " \t"
			          << eta_v << " \t"
			          << ene_v
			          << std::endl;
			tm.FillChannelMap(eta_v, phi_v, ene_v);
		}
		const TriggerChannelMap &emc = tm.GetEMCALChannels();
		int ncols = emc.GetNumberOfCols();
		int nrows = emc.GetNumberOfRows();
		int nadc  = 0;
		for (int ic = 0; ic < ncols; ic++)
		{
			for (int ir = 0; ir < nrows; ir++)
			{
				double adc = emc.GetADC(ic, ir);
				std::cout << nadc++ << " " << ic << " " << ir << " " << adc << std::endl;
			}
		}
		std::vector<RawPatch> patches = tm.GetPatches();
		for (std::vector<int>::size_type ip = 0; ip != patches.size(); ip++)
		{
			RawPatch &p = patches[ip];
			std::cout << "- patch: " << ip
			          << " adc = " << p.GetADC()
			          << " EMCal/DCal = " << p.IsEMCAL() << "/" << p.IsDCALPHOS()
			          << std::endl;
		}
		std::cout << "gam emcal max: " << tm.GetMaxGammaEMCAL().GetADC() << std::endl;
		std::cout << "gam  dcal max: " << tm.GetMaxGammaDCALPHOS().GetADC() << std::endl;
		std::cout << "jet emcal max: " << tm.GetMaxJetEMCAL().GetADC() << std::endl;
		std::cout << "jet  dcal max: " << tm.GetMaxJetDCALPHOS().GetADC() << std::endl;
	} // event loop
};