[Mesh]
  [box]
  type = GeneratedMeshGenerator
  dim = 3
  nx = 125
  ny = 125
  nz = 30
  xmin = 0
  xmax = 50000
  ymin = 0
  ymax = 50000
  zmin = 0.0
  zmax = 1000
  []
[]

[Variables]
  [cs137]
    initial_condition = 0
  []
[]

[AuxVariables]
  [deposition]
    initial_condition = 0
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
  [settling]
    type = ConservativeAdvection
    variable = cs137
    velocity = '0.0 0.0 -0.1'
  []
  [decay]
    type = ADDecay
    variable = cs137
  []
[]

[AuxKernels]
  [deposition_aux]
    type = VariableTimeIntegrationAux
    variable_to_integrate = cs137
    coefficient = 0.1
    variable = deposition
    order = 3
  []
[]

[DiracKernels]
  [srce]
    variable = cs137
    type = PieceWisePointSource
    rates = '1.1e11 0' # in Bq/m^3? In mol/m^3?
    activation_times = '0.0 18000' # minutes
    point = '12500 12500 35'
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
    settling_velocity = 0.01 # in meters per minute
  []
[]

[Materials]
  [plume]
    type = Air
    use_velocity = true
    velocity_file_name = "converted_pickering_wind_data.csv"
    diffusivity = 1.0 # needs to be in meters
    decay_constant = 7.285e-10 # needs to be in minutes
    settling_velocity = -0.01 # needs to be in meters per minute
    num_time_points = 360 # must match wind data csv file
    #outputs = exodus
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 500
  dt = 60 # minutes
  automatic_scaling = true
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
