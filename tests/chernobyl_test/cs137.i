[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 50
  ny = 50
  nz = 50
  xmin = 222500.0
  xmax = 242500.0
  ymin = 222500.0
  ymax = 242500.0
  zmin = 0.0
  zmax = 11322.0
[]

[Variables]
  [cs137]
    order = FIRST
    family = LAGRANGE
    scaling = '1.0e-11'

    [InitialCondition]
      type = ConstantIC
      value = 0.0
    []
  []
[]

[AuxVariables]
  [deposition]
    initial_condition = 0
    #boundary = 'top bottom front back left right'
  []
[]

[AuxKernels]
  [deposition_aux]
    type = VariableTimeIntegrationAux
    variable_to_integrate = cs137
    coefficient = 0.001
    variable = deposition
    order = 2
    #boundary = 'top bottom front back left right'
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
    velocity = '0 0 -0.001'
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
    rates = '1.1e11 0'
    activation_times = '0.0 12000'
    point = '232500.0 232500.0 35'
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
    settling_velocity = 0.001
  []
[]

[Materials]
  [plume]
    type = GenericCaribouMaterial
    u_file_name = u.csv
    v_file_name = v.csv
    w_file_name = w.csv
    dim_file_name = coords.csv
    diffusivity = 1.0
    decay_constant = 7.285e-10
    settling_velocity = -0.001
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 480
  dt = 60
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
