# include "Air.h"
# include "csv.h"

registerMooseObject("depApp", Air);

InputParameters
Air::validParams()
{
  InputParameters params = Material::validParams();

  params.addClassDescription("Material to hold the parameters describing the radionuclide transport");

  params.addParam<Real>("diffusivity", 1.0, "diffusivity coefficient assumed to be Dx = Dy = Dz = D");

  params.addParam<Real>("decay_constant", 0.1, "decay constant of radionuclide");

  params.addParam<Real>("settling_velocity", 0.1, "settling velocity of the radionuclide");

  params.addParam<Real>("wet_scavenge_constant", 0.0, "wet scavenging coefficient of the radionuclide");

  params.addParam<std::string>("velocity_file_name", "Name of file containing {t,x,y,z} velocity data");

  params.addParam<bool>("use_velocity", false, "Use time dependent velocity values");

  return params;
}

Air::Air(const InputParameters & params)
  : Material(params),
    _diffusivity(declareProperty<Real>("diffusivity")),
    _decay_constant(declareProperty<Real>("decay_constant")),
    _settling_velocity(declareProperty<Real>("settling_velocity")),
    _velocity(declareProperty<RealVectorValue>("velocity")),
    _wind_data(),
    _current_index(1),
    _use_velocity(getParam<bool>("use_velocity"))

{
  if( _use_velocity ){
    _velocity_file_name = getParam<std::string>("velocity_file_name");
    _wind_data = get_wind_data(_velocity_file_name);
  }
}

void
Air::computeQpProperties()
{
  _diffusivity[_qp] = getParam<Real>("diffusivity");
  _decay_constant[_qp] = getParam<Real>("decay_constant");
  _settling_velocity[_qp] = getParam<Real>("settling_velocity");

  if( _use_velocity )
  {
    while( _t > _wind_data[_current_index][0] )
    {
      _current_index++;
    }
    auto vel_x = ( _wind_data[_current_index][1] + _wind_data[_current_index - 1][1] ) / 2 ;
    auto vel_y = ( _wind_data[_current_index][2] + _wind_data[_current_index - 1][2] ) / 2 ;
    auto vel_z = ( _wind_data[_current_index][3] + _wind_data[_current_index - 1][3] ) / 2 ;
    _velocity[_qp] = { vel_x, vel_y, vel_z };
  }
  else {
    _velocity[_qp] = {0, 0, 0};
  }
}

std::vector<std::vector<double>> get_wind_data(std::string filename)
{
  std::vector<std::vector<double>> velocities = {};
  io::CSVReader<4> in(filename);
  in.read_header(io::ignore_no_column, "Time", "X_vel", "Y_vel", "Z_vel" );
  double t, x, y, z = 0;
  while(in.read_row(t, x, y, z))
  {
    std::vector<double> temp = {t,x,y,z} ;
    velocities.push_back(temp);
  }
  return velocities;
}
