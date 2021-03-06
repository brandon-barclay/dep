#pragma once
#include "ADIntegratedBC.h"

class ADDepositionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();
  ADDepositionBC(const InputParameters & params);
protected:
  virtual ADReal computeQpResidual();
  const Real _settling_velocity;
};
