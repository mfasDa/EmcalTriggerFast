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
	tsetup.SetThresholds(0., 0., 1., 1.);
	tsetup.SetTriggerBitConfig(TriggerBitConfigNew());
	TriggerMaker tm;
	tm.SetTriggerSetup(tsetup);

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(2);

	int nevents = 1000;
	for (unsigned int iev = 0; iev < nevents; iev++)
	{
		int nparticles = uni() * 100;
		std::cout << "[i] Evevt: " << iev << " N particles: " << nparticles << std::endl;
		for (unsigned int ip = 0; ip < nparticles; ip++)
		{
			double phi_v = uni() * pi * 2. - pi;
			double eta_v = uni() * 2. - 1.;
			double ene_v = uni() * 100.;
			std::cout << "[i] phi,eta,ene: "
			          << phi_v << " \t"
			          << eta_v << " \t"
			          << ene_v
			          << std::endl;
			tm.FillChannelMap(eta_v, phi_v, ene_v);
		}
	}
};