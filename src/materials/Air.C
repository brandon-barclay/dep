#include "Air.h"
#include <fstream>

registerMooseObject( "depApp", Air );

InputParameters
Air::validParams()
{
  InputParameters params = Material::validParams();

  params.addClassDescription(
      "Material to hold the parameters describing the radionuclide transport" );

  params.addParam<Real>(
      "diffusivity", 1.0, "diffusivity coefficient assumed to be Dx = Dy = Dz = D" );

  params.addParam<Real>( "decay_constant", 0.1, "decay constant of radionuclide" );

  params.addParam<Real>( "settling_velocity", 0.1, "settling velocity of the radionuclide" );

  params.addParam<Real>(
      "wet_scavenge_constant", 0.0, "wet scavenging coefficient of the radionuclide" );

  params.addParam<std::string>( "velocity_file_name",
                                "Name of file containing {t,x,y,z} velocity data" );

  params.addParam<bool>( "use_velocity", false, "Use time dependent velocity values" );

  params.addParam<Real>( "num_time_points", 0, "number of time steps in wind data" );

  return params;
}

Air::Air( const InputParameters & params )
  : Material( params ),
    _diffusivity( declareProperty<Real>( "diffusivity" ) ),
    _decay_constant( declareProperty<Real>( "decay_constant" ) ),
    _settling_velocity( declareProperty<Real>( "settling_velocity" ) ),
    _velocity( declareProperty<RealVectorValue>( "velocity" ) ),
    _wind_data(),
    _current_index( 0 ),
    _use_velocity( getParam<bool>( "use_velocity" ) )
{
  if ( _use_velocity )
  // split this into a function for readability //
  {
    _num_time_points = getParam<Real>( "num_time_points" );
    _velocity_file_name = getParam<std::string>( "velocity_file_name" );
    _wind_data = {};
    std::ifstream file( _velocity_file_name );
    std::string line = "";
    getline( file, line ); // should remove header //
    int i = 0;
    while ( i < _num_time_points )
    {
      getline( file, line );
      i++;
      std::vector<std::string> split_line = {};
      std::string delimiter = " ";
      std::size_t pos = 0;
      std::string token;

      while ( ( pos = line.find( delimiter ) ) != std::string::npos )
      {
        token = line.substr( 0, pos );
        split_line.push_back( token );
        line.erase( 0, pos + delimiter.length() );
      }

      std::vector<double> split_line_double = {};

      for ( auto elem : split_line )
      {
        auto num = std::stod( elem );
        split_line_double.push_back( num );
      }

      _wind_data.push_back( split_line_double );
    }
    file.close();
  }
}

double lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

void
Air::computeQpProperties()
{

  _diffusivity[_qp] = getParam<Real>( "diffusivity" );
  _decay_constant[_qp] = getParam<Real>( "decay_constant" );
  _settling_velocity[_qp] = getParam<Real>( "settling_velocity" );

  if ( _use_velocity )
  {

    if ( _current_index + 2 < _wind_data.size() - 1 )
    {

      while ( _t >= _wind_data[_current_index + 1][0] )
      {
        _current_index++;
      }

    }

    auto dt = _wind_data[_current_index + 1][0] - _wind_data[_current_index][0];
    auto norm_t = (_t - _wind_data[_current_index][0]) / dt;

    if( norm_t > 1.0 ) {
      norm_t = 1.0;
    }

    auto vel_x = lerp(_wind_data[_current_index][1], _wind_data[_current_index + 1][1], norm_t) ;
    auto vel_y = lerp(_wind_data[_current_index][2], _wind_data[_current_index + 1][2], norm_t) ;
    auto vel_z = lerp(_wind_data[_current_index][3], _wind_data[_current_index + 1][3], norm_t) ;

    //auto vel_x = _wind_data[_current_index][1];
    //auto vel_y = _wind_data[_current_index][2];
    //auto vel_z = _wind_data[_current_index][3];
    _velocity[_qp] = { vel_x, vel_y, vel_z };
  }
  else
  {
    _velocity[_qp] = { 0, 0, 0 };
  }
}
