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
  [Time]
    type = MassLumpedTimeDerivative
    variable = concentration
  []
  [diffusion]
    type = ADHeatConduction
    variable = concentration
  []
[]

[BCs]
  [bottom_deposition]
    type = ADDepositionBC
    variable = concentration
    boundary = 'bottom'
    settling_velocity = 0.001
  []
[]

[Materials]
  [generic]
    type = ADGenericConstantMaterial
    prop_names = 'thermal_conductivity'
    prop_values = '0.005'
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
