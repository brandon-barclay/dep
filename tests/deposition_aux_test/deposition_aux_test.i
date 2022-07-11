[Mesh]
  type = GeneratedMesh
  dim = 3
  xmin = 0
  xmax = 100
  ymin = 0
  ymax = 100
  zmin = 0
  zmax = 100
  nx = 25
  ny = 25
  nz = 25
[]

[Variables]
  [concentration]
  []
[]

[AuxVariables]
  [deposition]
    initial_condition = 0
    #boundary = 'top bottom front back left right'
  []
[]

[ICs]
  [ic_concentration]
    type = ConstantIC
    variable = concentration
    value = 0
  []
[]

[Kernels]
  [advection]
    type = ConservativeAdvection
    variable = concentration
    velocity = '0.3 0.3 0.0'
  []
  [settling]
    type = ConservativeAdvection
    variable = concentration
    velocity = '0.0 0.0 -1.0'
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

[AuxKernels]
  [deposition_aux]
    type = DepositionAux
    variable = deposition
    concentration = concentration
    execute_on = timestep_end
    deposition_velocity = 0.1
    #boundary = 'top bottom front back left right'
  []
[]

[Functions]
  [switch_off]
    type = ParsedFunction
    value = 'if(t < 45.01, 100, 0)'
  []
[]

[DiracKernels]
  [point_source]
    type = FunctionDiracSource
    variable = concentration
    function = switch_off
    point = '10 20 5'
  []
[]

[BCs]
  [bottom]
    type = DryDepositionBC
    variable = concentration
    boundary = 'bottom'
    dry_deposition_velocity = 0.1
  []
[]

[Materials]
  [Air]
    type = Air
    settling_velocity = 0.1
    decay_constant = 0.01
  []
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 300
  dt = 1
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
