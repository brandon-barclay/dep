[Mesh]
  type = GeneratedMesh
  dim = 3
  xmin = 0
  xmax = 100
  ymin = 0
  ymax = 100
  zmin = 0
  zmax = 100
  nx = 25
  ny = 25
  nz = 25
[]

[Variables]
  [concentration]
    initial_condition = 1
  []
[]

[AuxVariables]
  [deposition]
    initial_condition = 0
  []
[]

[Kernels]
  [Time]
    type = MassLumpedTimeDerivative
    variable = concentration
  []
[]

[AuxKernels]
  [deposition_aux]
    type = VariableTimeIntegrationAux
    variable_to_integrate = concentration
    coefficient = 0.1
    variable = deposition
    order = 2
    boundary = '0 1 2'
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 10
  dt = 1.0
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
