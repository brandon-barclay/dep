//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ConstantOutflowBC.h"
#include "Function.h"

registerMooseObject("depApp", ConstantOutflowBC);

InputParameters
ConstantOutflowBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<RealVectorValue>("velocity", "The velocity vector");
  return params;
}

ConstantOutflowBC::ConstantOutflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _velocity(getParam<RealVectorValue>("velocity"))
{
}

Real
ConstantOutflowBC::computeQpResidual()
{
  return _test[_i][_qp] * _u[_qp] * _velocity * _normals[_qp];
}

Real
ConstantOutflowBC::computeQpJacobian()
{
  return _test[_i][_qp] * _phi[_j][_qp] * _velocity * _normals[_qp];
}
