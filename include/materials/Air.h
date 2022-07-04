#pragma once
#include "Material.h"

class Air : public Material
{
  public:
  Air(const InputParameters & params);
  static InputParameters validParams();
protected:
  virtual void computeQpProperties() override;

  MaterialProperty<Real> & _diffusivity;

  MaterialProperty<Real> & _decay_constant;

  MaterialProperty<Real> & _settling_velocity;

  MaterialProperty<Real> & _wet_scavenge_constant;
};
