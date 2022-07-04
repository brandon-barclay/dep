[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  nx = 10
  ny = 10
  elem_type = QUAD9
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
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 3
  dt = 1
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
