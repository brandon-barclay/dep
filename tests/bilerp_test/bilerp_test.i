[Mesh]
  [box]
  type = GeneratedMeshGenerator
  dim = 3
  nx = 200
  ny = 200
  nz = 1
  xmin = 0
  xmax = 3
  ymin = 0
  ymax = 3
  zmin = 0.0
  zmax = 3
  []
[]

[Variables]
  [cs137]
    order = FIRST
    family = LAGRANGE

    [InitialCondition]
      type = ConstantIC
      value = 0.0 # no cs initially
    []
  []
[]

[Kernels]
  [advection]
    type = STAdvection
    variable = cs137
    upwinding_type = full
  []
  [diffusion]
    type = ADDiffusion
    variable = cs137
  []
  [time]
    type = MassLumpedTimeDerivative
    variable = cs137
  []
[]

[BCs]
  [open]
    type = MaterialOutflowBC
    variable = cs137
    boundary = '0 2 3 4 5'
  []
  [bottom]
    type = ADDepositionBC
    variable = cs137
    boundary = '1'
    settling_velocity = 0.001 # in meters per minute
  []
[]

[Materials]
  [plume]
    type = Air
    use_velocity = true
    velocity_file_name = "p1_wind_data.csv"
    velocity_file_name_p2 = "p2_wind_data.csv"
    location_p2 = '0.5 0.5 0'
    location_p1 = '2.5 2.5 0'

    diffusivity = 1.0 # needs to be in meters
    decay_constant = 7.285e-10 # needs to be in minutes
    settling_velocity = -0.001 # needs to be in meters per minute
    num_time_points = 2 # must match wind data csv file
    use_bilerp = true

    outputs = exodus
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 10
  dt = 1 # minutes
  automatic_scaling = true
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
