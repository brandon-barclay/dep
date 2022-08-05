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

  params.addParam<bool>( "use_velocity", false, "Use time dependent velocity values" );

  params.addParam<Real>( "num_time_points", 0, "number of time steps in wind data" );

  params.addParam<bool>( "use_bilerp", false, "Use bilinear interpolation for velocity" );

  params.addParam<std::string>( "velocity_file_name",
                                "Name of file containing {t,x,y,z} velocity data for point 1" );

  params.addParam<std::string>( "velocity_file_name_p2", "name of file with wind velocity data for point 2");

  params.addParam<std::vector<double>>( "location_p1", "x,y,z location of point 1" );

  params.addParam<std::vector<double>>( "location_p2", "x,y,z location of point 2" );

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
    _use_velocity( getParam<bool>( "use_velocity" ) ),
    _use_bilerp( getParam<bool>( "use_bilerp" ) )
{
  if ( ( _use_bilerp ) == true && ( _use_velocity == false ) ) {
    mooseError("dont do that");
  }
  if ( _use_velocity ) { time_dependent_velocity_setup(); }
  if ( _use_bilerp ) { bilerp_points_setup(); }

}

void
Air::bilerp_points_setup()
{

  _location_p1 = getParam<std::vector<double>>( "location_p1" );
  _location_p2 = getParam<std::vector<double>>( "location_p2" );

  _location_p3 = {_location_p1[0], _location_p2[1], 0.0};
  _location_p4 = {_location_p2[0], _location_p1[1], 0.0};

  _velocity_file_name_p2 = getParam<std::string>( "velocity_file_name_p2" );

  _wind_data_p1 = {_wind_data};
  _wind_data_p2 = get_wind_data( {}, _velocity_file_name_p2 );
  _wind_data_p3 = {};
  _wind_data_p4 = {};

  double vx_p1, vx_p2, vy_p1, vy_p2, vz_p1, vz_p2;
  for( int i = 0; i < _wind_data_p1.size(); i++ )
  {
    auto time = _wind_data_p1[i][0];
    vx_p1 = _wind_data_p1[i][1];
    vx_p2 = _wind_data_p2[i][1];
    vy_p1 = _wind_data_p1[i][2];
    vy_p2 = _wind_data_p2[i][2];
    vz_p1 = _wind_data_p1[i][3];
    vz_p2 = _wind_data_p2[i][3];
    _wind_data_p3.push_back( {time, vx_p2, vy_p1, vz_p1} );
    _wind_data_p4.push_back( {time, vx_p1, vy_p2, vz_p1} );
  }
}



void
Air::time_dependent_velocity_setup()
{
  _num_time_points = getParam<Real>( "num_time_points" );
  _velocity_file_name = getParam<std::string>( "velocity_file_name" );
  _wind_data = get_wind_data( {}, _velocity_file_name );
}

double lerp( float a, float b, float t )
{
    return a + t * ( b - a );
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

    if ( _use_bilerp )
    {
      const Point & current_point = _q_point[_qp];
      double current_x = current_point(0) ;
      double current_y = current_point(1) ;

      auto dt = _wind_data_p1[_current_index + 1][0] - _wind_data_p1[_current_index][0];
      auto norm_t = ( _t - _wind_data_p1[_current_index][0] ) / dt;

      if( norm_t > 1.0 ) { norm_t = 1.0; }
      // Time Interpolation //
      auto vel_x_p1 = lerp( _wind_data_p1[_current_index][1], _wind_data_p1[_current_index + 1][1], norm_t ) ;
      auto vel_y_p1 = lerp( _wind_data_p1[_current_index][2], _wind_data_p1[_current_index + 1][2], norm_t ) ;
      auto vel_x_p2 = lerp( _wind_data_p2[_current_index][1], _wind_data_p2[_current_index + 1][1], norm_t ) ;
      auto vel_y_p2 = lerp( _wind_data_p2[_current_index][2], _wind_data_p2[_current_index + 1][2], norm_t ) ;
      auto vel_x_p3 = lerp( _wind_data_p3[_current_index][1], _wind_data_p3[_current_index + 1][1], norm_t ) ;
      auto vel_y_p3 = lerp( _wind_data_p3[_current_index][2], _wind_data_p3[_current_index + 1][2], norm_t ) ;
      auto vel_x_p4 = lerp( _wind_data_p4[_current_index][1], _wind_data_p4[_current_index + 1][1], norm_t ) ;
      auto vel_y_p4 = lerp( _wind_data_p4[_current_index][2], _wind_data_p4[_current_index + 1][2], norm_t ) ;
      // End Time Interpolation //

      double VX, VY;
      // Interpolate X Velocity//

      // check that were within the interpolation zone //
      if ( ( current_y > _location_p1[1] ) && ( current_y > _location_p2[1] ) )
        {
          VX = ( _location_p1[1] > _location_p2[1] ) ? vel_x_p1 : vel_x_p2 ;
        } else if ( ( current_y < _location_p1[1] ) && ( current_y < _location_p2[1] ))
        {
          VX = ( _location_p1[1] < _location_p2[1] ) ? vel_x_p1 : vel_x_p2 ;
        } else {
          double VX_fxy1 = ( ( _location_p2[0] - current_x ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_x_p1
            + ( ( current_x - _location_p1[0] ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_x_p4 ;
          double VX_fxy2 = ( ( _location_p2[0] - current_x ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_x_p3
            + ( ( current_x - _location_p1[0] ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_x_p2 ;
          VX = ( ( _location_p2[1] - current_y ) / ( _location_p2[1] - _location_p1[1] ) ) * VX_fxy1
            + ( ( current_y - _location_p1[1] ) / ( _location_p2[1] - _location_p1[1] ) ) * VX_fxy2 ;
        }

        // Interpolate Y Velocity //

        // check that were within the interpolation zone //
        if ( ( current_x > _location_p1[0] ) && ( current_x > _location_p2[0] ) )
        {
          VY = ( _location_p1[0] > _location_p2[0] ) ? vel_y_p1 : vel_y_p2;
        } else if ( ( current_x < _location_p1[0] ) && ( current_x < _location_p2[0] ) )
        {
          VY = ( _location_p1[0] < _location_p2[0] ) ? vel_y_p1 : vel_y_p2;
        } else
        {
          double VY_fxy1 = ( ( _location_p2[0] - current_x ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_y_p1
            + ( ( current_x - _location_p1[0] ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_y_p4 ;
          double VY_fxy2 = ( ( _location_p2[0] - current_x ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_y_p3
            + ( ( current_x - _location_p1[0] ) / ( _location_p2[0] - _location_p1[0] ) ) * vel_y_p2 ;
          VY = ( ( _location_p2[1] - current_y ) / ( _location_p2[1] - _location_p1[1] ) ) * VY_fxy1
            + ( ( current_y - _location_p1[1] ) / ( _location_p2[1] - _location_p1[1] ) ) * VY_fxy2 ;
        }

      _velocity[_qp] = { VX, VY, 0.0 };

    } else
    {
      auto dt = _wind_data[_current_index + 1][0] - _wind_data[_current_index][0];
      auto norm_t = ( _t - _wind_data[_current_index][0] ) / dt;

      if( norm_t > 1.0 ) { norm_t = 1.0; }

      auto vel_x = lerp( _wind_data[_current_index][1], _wind_data[_current_index + 1][1], norm_t ) ;
      auto vel_y = lerp( _wind_data[_current_index][2], _wind_data[_current_index + 1][2], norm_t ) ;
      auto vel_z = lerp( _wind_data[_current_index][3], _wind_data[_current_index + 1][3], norm_t ) ;

      _velocity[_qp] = { vel_x, vel_y, vel_z };
    }
  } else
  {
    _velocity[_qp] = { 0, 0, 0 };
  }
}

std::vector<std::vector<double>>
Air::get_wind_data( std::vector<std::vector<double>> wind_data, std::string velocity_file_name )
{
  std::ifstream file( velocity_file_name );
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

    wind_data.push_back( split_line_double );
  }
  file.close();
  return wind_data ;
}
