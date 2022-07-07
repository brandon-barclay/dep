#include "Air.h"

registerMooseObject("depApp", Air);

InputParameters
Air::validParams()
{
  InputParameters params = Material::validParams();

  params.addClassDescription("Material to hold the parameters describing the radionuclide transport");

  params.addParam<Real>("diffusivity", 1.0, "diffusivity coefficient assumed to be Dx = Dy = Dz = D");

  params.addParam<Real>("decay_constant", 0.1, "decay constant of radionuclide");

  params.addParam<Real>("settling_velocity", 0.0, "settling velocity of the radionuclide");

  params.addParam<Real>("wet_scavenge_constant", 0.0, "wet scavenging coefficient of the radionuclide");

  return params;
}

Air::Air(const InputParameters & params)
  : Material(params),
    _diffusivity(declareProperty<Real>("diffusivity")),
    _decay_constant(declareProperty<Real>("decay_constant")),
    _settling_velocity(declareProperty<Real>("settling_velocity")),
    _wet_scavenge_constant(declareProperty<Real>("wet_scavenge_constant"))
{

}

void
Air::computeQpProperties()
{
  _diffusivity[_qp] = getParam<Real>("diffusivity");
  _decay_constant[_qp] = getParam<Real>("decay_constant");
  _settling_velocity[_qp] = getParam<Real>("settling_velocity");
  _wet_scavenge_constant[_qp] = getParam<Real>("wet_scavenge_constant");
}
