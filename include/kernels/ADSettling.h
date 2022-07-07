#pragma once
#include "ADKernel.h"

class ADSettling : public ADKernel
{
public:
  static InputParameters validParams();
  ADSettling(const InputParameters & params);
protected:
  virtual ADReal computeQpResidual();
  const MaterialProperty<Real> & _settling_velocity;
  const VariableGradient & _grad_concentration;
};
