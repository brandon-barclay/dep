#pragma once
#include "AuxKernel.h"

class DepositionAux : public AuxKernel
{
public:
  static InputParameters validParams();
  DepositionAux(const InputParameters & params);
protected:
  virtual Real computeValue();
  Real _deposited;
  Real _deposition_velocity;
  const VariableValue & _concentration;
};
