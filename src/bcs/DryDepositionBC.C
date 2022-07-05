#include "DryDepositionBC.h"
#include <iostream>

registerMooseObject("depApp", DryDepositionBC);

InputParameters
DryDepositionBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<Real>("dry_deposition_velocity", "The dry deposition "
                                "velocity to be applied along the boundary.");
  return params;
}

DryDepositionBC::DryDepositionBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _dry_deposition_const(getParam<Real>("dry_deposition_velocity"))
{
}

Real
DryDepositionBC::computeQpResidual()
{
  //std::cout << "dep : " << _test[_i][_qp] * _u[_qp] *  _dry_deposition_const << "\n";
  return _test[_i][_qp] * _u[_qp] *  _dry_deposition_const;
}

Real
DryDepositionBC::computeQpJacobian()
{
  return _test[_i][_qp] * _phi[_j][_qp] * _dry_deposition_const;
}
