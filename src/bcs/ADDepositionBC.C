#include "ADDepositionBC.h"
#include <iostream>

registerMooseObject("depApp", ADDepositionBC);

InputParameters
ADDepositionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("settling_velocity", "settling velocity of particle");
  return params;
}

ADDepositionBC::ADDepositionBC(const InputParameters & params)
: ADIntegratedBC(params),
  _settling_velocity(getParam<Real>("settling_velocity"))
{

}

ADReal
ADDepositionBC::computeQpResidual()
{
  //std::cout << "dep amount : " << _test[_i][_qp] * _u[_qp] * _settling_velocity << "\n" ;
  return _settling_velocity * _test[_i][_qp] * _u[_qp];
}
