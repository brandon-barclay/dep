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
  []
[]

[ICs]
  [ic_concentration]
    type = FunctionIC
    variable = concentration
    function = init_condition_function
  []
[]

[Kernels]
  [Time]
    type = MassLumpedTimeDerivative
    variable = concentration
  []
  [grav_settling]
    type = ConservativeAdvection
    variable = concentration
    velocity = '0 0 -1.0'
    upwinding_type = 'full'
  []
[]

[Functions]
  [init_condition_function]
    type = ParsedFunction
    value = 'if( z > 95.0 , 100.0 , 0.0)'
  []
[]

[Materials]
  [Air]
    type = Air
    settling_velocity = 1.0
    decay_constant = 0.01
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 5
  dt = 1.0
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
