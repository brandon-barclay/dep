#include "ADDepositionBC.h"
#include <iostream>

registerMooseObject("depApp", ADDepositionBC);

InputParameters
ADDepositionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("settling_velocity", "settling velocity of the airborne particulate");
  return params;
}

ADDepositionBC::ADDepositionBC(const InputParameters & params)
: ADIntegratedBC(params),
  _settling_velocity(getMaterialProperty<Real>("settling_velocity"))
{

}

ADReal
ADDepositionBC::computeQpResidual()
{
  //std::cout << "dep amount : " << _test[_i][_qp] * _u[_qp] * _settling_velocity << "\n" ;
  return 0;// _test[_i][_qp] * _u[_qp] * _settling_velocity;
}
