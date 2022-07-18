#include "ADDeposition.h"

registerMooseObject("depApp", ADDeposition);

InputParameters
ADDeposition::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("concentration", "concentration of deposited radionuclide in air");
  params.addParam<Real>("coefficient", 0.0, "coef to multiply integral");
  return params;
}

ADDeposition::ADDeposition(const InputParameters & params)
  : ADKernel(params),
    _concentration(coupledValue("concentration")),
    _coefficient(getParam<Real>("coefficient"))
{
}

Real
ADDeposition::getIntegralValue()
{
  Real integral_value = 0.0;

  integral_value += (_concentration)[_qp] * _dt;

  return integral_value;

}

ADReal
ADDeposition::computeQpResidual()
{
  Real integral = getIntegralValue();
  return _coefficient * integral ;

}
