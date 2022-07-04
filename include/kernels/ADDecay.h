#pragma once
#include "ADKernel.h"

class ADDecay : public ADKernel
{
public:
  static InputParameters validParams();
  ADDecay(const InputParameters & params);
protected:
  virtual ADReal computeQpResidual() override;
  const MaterialProperty<Real> & _decay_constant;
};
