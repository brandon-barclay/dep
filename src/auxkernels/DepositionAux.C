#include "DepositionAux.h"

registerMooseObject("depApp", DepositionAux);

InputParameters
DepositionAux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredParam<Real>("deposition_velocity", "The dry deposition "
                                "velocity to be applied along the boundary.");
  params.addRequiredCoupledVar("concentration", "concentration of radionuclide");
  return params;
}

DepositionAux::DepositionAux(const InputParameters & params)
: AuxKernel(params),
  _deposition_velocity(getParam<Real>("deposition_velocity")),
  _concentration(coupledValue("concentration"))
{
  _deposited = 0;
}

Real
DepositionAux::computeValue()
{
      auto res = _concentration[_qp] *  _deposition_velocity;
      if( res > 0) {_deposited += res; }
      return _deposited ;

}
