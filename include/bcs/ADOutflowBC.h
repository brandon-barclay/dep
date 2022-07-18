#pragma once
#include "ADIntegratedBC.h"

class ADOutflowBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();
  ADOutflowBC(const InputParameters & params);
protected:
  virtual ADReal computeQpResidual();
};
