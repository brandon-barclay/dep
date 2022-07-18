#include "ADOutflowBC.h"

registerMooseObject("depApp", ADOutflowBC);

InputParameters
ADOutflowBC::validParams()
{
   InputParameters params = ADIntegratedBC::validParams();
   params.addClassDescription("outflow of material");
   return params;
}

ADOutflowBC::ADOutflowBC(const InputParameters & params)
  : ADIntegratedBC(params)
  {

  }

ADReal
ADOutflowBC::computeQpResidual()
{
  return -_test[_i][_qp] * _grad_u[_qp] * _normals[_qp];
}
