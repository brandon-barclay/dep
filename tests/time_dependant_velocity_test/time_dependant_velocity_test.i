[Mesh]
  [box]
  type = GeneratedMeshGenerator
  dim = 3
  nx = 5
  ny = 5
  nz = 5
  xmin = 0
  xmax = 10000
  ymin = 0
  ymax = 10000
  zmin = 0.0
  zmax = 10000
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

[DiracKernels]
  [srce]
    variable = cs137
    type = PieceWisePointSource
    rates = '1.1e11 0' # in Bq/m^3? In mol/m^3?
    activation_times = '0.0 12000' # minutes
    point = '5000 5000 35'
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
    velocity_file_name = "wind_velocity_data.csv"
    diffusivity = 1.0 # needs to be in meters
    decay_constant = 7.285e-10 # needs to be in minutes
    settling_velocity = -0.001 # needs to be in meters per minute
    num_time_points = 3 # must match wind data csv file
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
