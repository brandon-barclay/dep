#include "ADSettling.h"

registerMooseObject("depApp", ADSettling);

InputParameters
ADSettling::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("Kernel to implement gravitational settling");
  params.addRequiredCoupledVar("concentration", "c");
  return params;
}

ADSettling::ADSettling(const InputParameters & params)
  : ADKernel(params),
    _settling_velocity(getMaterialProperty<Real>("settling_velocity")),
    _grad_concentration(coupledGradient("concentration"))
    {

    }

ADReal
ADSettling::computeQpResidual()
{
  if( _u[_qp] <= 0.0 ){
    return 0;
  }
  else {
    return - _settling_velocity[_qp] * _test[_i][_qp] * _grad_concentration[_qp](2);
  }
}
