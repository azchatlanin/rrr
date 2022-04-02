# https://pixorblog.wordpress.com/2019/07/27/a-meson-starter-script-for-c-projects
project(
  'rrr', 
  'cpp', 
  version : '0.0.1', 
  default_options : ['cpp_std=c++2a']
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

deps = [ 
  dependency('threads'), 
  dependency('ncurses'), 
  dependency('menu'), 
]

args = [
  '-lpanel',
  '-lncursesw',
  '-lncursesutf8',
  '-lmenu'
]

inc = []

hack = subproject('hack')
deps += hack.get_variable('logger_dep')

subdir('src')
subdir('bin')
#subdir('tests')






