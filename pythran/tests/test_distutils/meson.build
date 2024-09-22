project('pythran-test', 'cpp')

pymod = import('python')
py = pymod.find_installation(modules:['pythran'])

pythran_cmd = [py.path(), '-m', 'pythran.run', '-E', '@INPUT@', '-o', '@OUTPUT@']

pythranrc = join_paths(meson.project_source_root(), 'pythran.rc')

pythran_env = environment()
pythran_env.set('PYTHRANRC', pythranrc)

b_cpp = custom_target(
  'b_cpp',
  output : 'b.cpp',
  input: 'b.py',
  command: pythran_cmd,
  env: pythran_env,
  depend_files: [pythranrc],
)

pythran_cppflags = run_command(py.path(), '-m', 'pythran.config', '--cflags', check:true, env:pythran_env).stdout().strip().split()
pythran_ldflags = run_command(py.path(), '-m', 'pythran.config', '--libs', check:true, env:pythran_env).stdout().strip().split()

py.extension_module(
  'b',
  b_cpp,
  cpp_args: pythran_cppflags,
  link_args: pythran_ldflags,
  install: true,
)
