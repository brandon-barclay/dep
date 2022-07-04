#include "ADDeposition.h"
#include <iostream>

registerMooseObject("depApp", ADDeposition);

InputParameters
ADDeposition::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("Kernel to compute the deposition of radionuclide on the ground");
  return params;
}

ADDeposition::ADDeposition(const InputParameters & params)
: ADKernel(params),
  _settling_velocity(getMaterialProperty<Real>("settling_velocity"))
  {
  }

ADReal
ADDeposition::computeQpResidual()
{
  std::cout << "deposition value : " << -_u[_qp] * _settling_velocity[_qp] * _grad_test[_i][_qp](2) << "\n" ;
  //return -_u[_qp] * _settling_velocity[_qp] * _grad_test[_i][_qp](2); // This is the negative Z settling ?
  return -_settling_velocity[_qp] * _grad_u[_qp];
}

// Kevin was using this as a kernel to effectively simulate a gravity term, and the
// BC was used to accumulate particulate on the ground?
