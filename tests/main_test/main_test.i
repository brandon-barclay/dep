[Mesh]
  type = GeneratedMesh
  dim = 3
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  zmin = 0
  zmax = 1
  nx = 20
  ny = 20
  nz = 20
[]

[Variables]
  [concentration]
  []
[]

[ICs]
  [ic_concentration]
    type = ConstantIC
    variable = concentration
    value = 1.0
  []
[]

[Kernels]
  [advection]
    type = ConservativeAdvection
    variable = concentration
    velocity = '0 0 0'
  []
  [diffusion]
    type = ADDiffusion
    variable = concentration
  []
  [decay]
    type = ADDecay
    variable = concentration
  []
  [Time]
    type = MassLumpedTimeDerivative
    variable = concentration
  []
[]

[BCs]
[]

[Materials]
  [Air]
    type = Air
    settling_velocity = -0.2
    decay_constant = 0.1
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 25
  dt = 1
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
