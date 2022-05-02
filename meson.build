# https://pixorblog.wordpress.com/2019/07/27/a-meson-starter-script-for-c-projects
project(
  'rrr', 
  'cpp', 
  version : '0.0.1', 
  default_options : ['cpp_std=c++20']
)

add_project_arguments (
  '-Wpedantic',
  '-Wshadow', 
  '-Wno-comment',
  '-Wunused-but-set-variable',
  language: 'cpp'
)

compiler = meson.get_compiler('cpp')
if compiler.get_id() == 'gcc'
  message('Compiler: GCC')
elif compiler.get_id() == 'clang'
  message('Compiler: LLVM/clang')
endif

args = []
inc = []
deps = []

args += '-lpanel'
args += '-lncursesw'
args += '-lncursesutf8'
args += '-lmenu'


deps += dependency('threads')
deps += dependency('ncurses')
deps += dependency('menu')
deps += subproject('hack').get_variable('logger_dep')

subdir('src')
subdir('bin')
#subdir('tests')






