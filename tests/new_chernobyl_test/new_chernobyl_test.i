[Mesh]
  [box]
  type = GeneratedMeshGenerator
  dim = 3
  nx = 50
  ny = 50
  nz = 50
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

[AuxVariables]
  [deposition]
    initial_condition = 0 # no deposition initially
  []
[]

[AuxKernels]
  [deposition_aux]
    type = VariableTimeIntegrationAux
    variable_to_integrate = cs137
    coefficient = 0.001 # Settling velocity in m/min
    variable = deposition
    order = 2
    boundary = '1'
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
    velocity = '0 0 -0.001' # in m/minute
  []
  [decay]
    type = ADDecay
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
    type = GenericCaribouMaterial
    u_file_name = u.csv
    v_file_name = v.csv
    w_file_name = w.csv
    dim_file_name = coords.csv
    diffusivity = 1.0 # needs to be in meters
    decay_constant = 7.285e-10 # needs to be in minutes
    settling_velocity = -0.001 # needs to be in meters per minute
    outputs = exodus
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 480
  dt = 60 # minutes
  automatic_scaling = true
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
