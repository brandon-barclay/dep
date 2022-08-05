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

  void time_dependent_velocity_setup();

  void bilerp_points_setup();

  std::vector<std::vector<double>> get_wind_data( std::vector<std::vector<double>> wind_data,
                                                  std::string velocity_file_name );

  MaterialProperty<Real> & _diffusivity;

  MaterialProperty<Real> & _decay_constant;

  MaterialProperty<Real> & _settling_velocity;

  MaterialProperty<RealVectorValue> & _velocity;

  std::vector<double> _location_p1;

  std::vector<double> _location_p2;

  std::vector<double> _location_p3;

  std::vector<double> _location_p4;

  std::vector<std::vector<double>> _wind_data; // ( X1, Y1 )

  std::vector<std::vector<double>> _wind_data_p1; // (X1, Y1 )

  std::vector<std::vector<double>> _wind_data_p2; // ( X2, Y2 )

  std::vector<std::vector<double>> _wind_data_p3; // ( X1, Y2 ) Imaginary point

  std::vector<std::vector<double>> _wind_data_p4; // ( X2, Y1 ) Imaginary point

  std::string _velocity_file_name;

  std::string _velocity_file_name_p2;

  int _current_index;

  bool _use_velocity;

  bool _use_bilerp;

  Real _num_time_points;
};
