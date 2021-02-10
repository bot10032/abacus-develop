#ifndef Mulliken_Charge_H
#define Mulliken_Charge_H

//#include "../src_pw/tools.h"
#include "../src_pw/tools.h"
#include "ORB_gen_tables.h"
#include "../src_global/sltk_grid_driver.h"
#include "LCAO_matrix.h"
#include "LCAO_matrix.h"
#include "../src_lcao/global_fp.h"
#include "../src_lcao/wfc_dm_2d.h"
#include "../src_global/lapack_connector.h"
#include "../src_global/scalapack_connector.h"
#include "../src_global/matrix.h"
#include "../src_global/complexmatrix.h"
#include <vector>
#include "../src_external/src_pdiag/pdiag_double.h"
#include "../src_external/src_pdiag/GenELPA.h"



class Mulliken_Charge
{
	public:

	Mulliken_Charge();
	~Mulliken_Charge();

	double**  DecMulP ;
	double**  MecMulP ;
	double***  ADecMulP ;
	Wfc_Dm_2d M;

	complex<double> *mug;

	void cal_mulliken(void);

	void stdout_mulliken(void);

	private:

};
#endif
