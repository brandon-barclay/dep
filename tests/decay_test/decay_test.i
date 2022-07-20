[Mesh]
  type = GeneratedMesh
  dim = 3
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  zmin = 0
  zmax = 1
  nx = 10
  ny = 10
  nz = 10
[]

[Variables]
  [concentration]
  []
[]

[ICs]
  [ic_concentration]
    type = ConstantIC
    variable = concentration
    value = 1
  []
[]

[Kernels]
  [Decay]
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
    decay_constant = 0.1
    use_velocity = false
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 10
  dt = 1
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
