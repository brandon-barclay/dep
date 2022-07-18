#pragma once

#include "ADKernel.h"

class ADDeposition : public ADKernel
{
public:
  static InputParameters validParams();
  ADDeposition(const InputParameters & params);
protected:
  Real getIntegralValue() ;
  virtual ADReal computeQpResidual();
  const VariableValue & _concentration ;
  const Real _coefficient;
};
