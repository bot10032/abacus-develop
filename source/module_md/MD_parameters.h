#ifndef MD_PARAMETERS_H
#define MD_PARAMETERS_H

#include "../module_base/constants.h"

class MD_parameters
{
public:
    MD_parameters()
	{
		rstMD = 0;
		mdtype = 2;
		dt = 1;
		tfirst = 0;
		tlast = -1;
		recordFreq = 1;

		// useless
		NVT_tau=0;
		NVT_control=1;
		mdoutputpath="mdoutput";
		fixTemperature=1;
		ediff=1e-4;
		ediffg=1e-3;

		// Classic MD 
		md_potential = "FP";
		rcut_lj = 8.5;        
		epsilon_lj = 0.01032; 
		sigma_lj = 3.405;     

		// MSST
		direction = 2;
		Qmass = 1;
		velocity = 0;
		viscosity = 0;
		tscale = 0.01;

		// NHC
		tfreq = 1;
		MNHC = 4;
	};
    ~MD_parameters(){};

    int rstMD;          // 1: restart MD, 0: no restart MD
	int mdtype;         // -1: FIRE, 0: NVE, 1: NVT ADS, 2: NVT NHC, 3: NPT, 4: MSST 
    double dt ;         // Time increment (hbar/E_hartree)
    double tfirst;      // Temperature (in Hartree, 1 Hartree ~ 3E5 K)
    double tlast;       // Target temperature
    int recordFreq;     // The period to dump MD information for monitoring and restarting MD

	// useless
    int NVT_control;
    double NVT_tau;
    std::string mdoutputpath;// output directory of md files: .ion .vel
	double ediff;       //parameter for constrain 
	double ediffg;      //parameter for constrain
    int fixTemperature;

	// Classic MD               // liuyu 2021-07-30
	std::string md_potential;   // choose potential: LJ, DP, FP
	double rcut_lj;             // cutoff radius of LJ potential (\AA)
	double epsilon_lj;          // the value of epsilon for LJ potential (eV)
	double sigma_lj;            // the value of sigma for LJ potential (\AA)

	// MSST
	int direction;              // shock direction: 0, 1, 2
	double velocity;            // shock velocity (\AA/fs)
	double Qmass;               // cell mass-like parameter (mass^2/length^4)
	double viscosity;           // artificial viscosity (mass/length/time)
	double tscale;              // reduction in initial temperature (0~1)

	// NHC
	double tfreq;               // Oscillation frequency, used to determine Qmass of NHC
	int MNHC;                   // num of NHC
};


#endif