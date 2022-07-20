#pragma once
#include "Material.h"
#include <vector>

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

  MaterialProperty<RealVectorValue> & _velocity;

  std::vector<std::vector<double>> _wind_data;

  std::string _velocity_file_name;

  int _current_index;

  bool _use_velocity;

  Real _num_time_points;
};
