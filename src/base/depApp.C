#include "depApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
depApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  // Do not use legacy material output, i.e., output properties on INITIAL as well as TIMESTEP_END
  params.set<bool>("use_legacy_material_output") = false;

  return params;
}

depApp::depApp(InputParameters parameters) : MooseApp(parameters)
{
  depApp::registerAll(_factory, _action_factory, _syntax);
}

depApp::~depApp() {}

void
depApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"depApp"});
  Registry::registerActionsTo(af, {"depApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
depApp::registerApps()
{
  registerApp(depApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
depApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  depApp::registerAll(f, af, s);
}
extern "C" void
depApp__registerApps()
{
  depApp::registerApps();
}
