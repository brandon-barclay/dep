//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "depTestApp.h"
#include "depApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
depTestApp::validParams()
{
  InputParameters params = depApp::validParams();
  return params;
}

depTestApp::depTestApp(InputParameters parameters) : MooseApp(parameters)
{
  depTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

depTestApp::~depTestApp() {}

void
depTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  depApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"depTestApp"});
    Registry::registerActionsTo(af, {"depTestApp"});
  }
}

void
depTestApp::registerApps()
{
  registerApp(depApp);
  registerApp(depTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
depTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  depTestApp::registerAll(f, af, s);
}
extern "C" void
depTestApp__registerApps()
{
  depTestApp::registerApps();
}
