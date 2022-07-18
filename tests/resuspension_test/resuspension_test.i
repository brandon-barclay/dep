[Mesh]
    type = GeneratedMesh
    dim = 3
    nx = 25
    ny = 25
    nz = 25
    xmin = 0
    xmax = 10000
    ymin = 0
    ymax = 10000
    zmin = 0.0
    zmax = 10000
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
    [deposition]
      boundary = '1'
      initial_condition = 0
    []
  []

  [AuxVariables]
    [deposition_aux]
      initial_condition = 0 # no deposition initially
    []
  []

  [AuxKernels]
    [deposition_aux_kernel]
      type = VariableTimeIntegrationAux
      variable_to_integrate = cs137
      coefficient = 0.01 # Settling velocity in m/min
      variable = deposition_aux
      order = 2
      boundary = '1'
    []
  []

  [Kernels]
    [advection_cs]
      type = STAdvection
      variable = cs137
      upwinding_type = full
    []
    [diffusion_cs]
      type = ADDiffusion
      variable = cs137
    []
    [time_cs]
      type = MassLumpedTimeDerivative
      variable = cs137
    []
    [settling_cs]
      type = ConservativeAdvection
      variable = cs137
      velocity = '0 0 -0.01' # in m/minute
    []
    [decay_cs]
      type = ADDecay
      variable = cs137
    []
    [deposition_kernel]
      type = ADDeposition
      variable = deposition
      concentration = cs137
      coefficient = 0.01
      boundary = '1'
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
      settling_velocity = 0.01 # in meters per minute
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
      settling_velocity = -0.01 # needs to be in meters per minute
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
