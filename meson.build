# https://pixorblog.wordpress.com/2019/07/27/a-meson-starter-script-for-c-projects
project(
  'rrr', 
  'cpp', 
  version : '0.0.1', 
  default_options : ['cpp_std=c++20']
)

add_project_arguments (
  '-pedantic', 
  '-Wno-comment',
  '-Wno-gnu-zero-variadic-macro-arguments',
  '-Wunused-but-set-variable',
  language: 'cpp'
)

deps = [ 
  dependency('threads'), 
  dependency('ncurses'), 
  dependency('menu'), 
]

args = [
  '-lpanel',
  '-lncurses',
  '-lmenu'
]

tools = subproject('tools')
logger_dep = tools.get_variable('logger_dep')
exception_dep = tools.get_variable('exception_dep')
container_dep = tools.get_variable('container_dep')

deps += logger_dep
deps += exception_dep
deps += container_dep

inc = []
inc += include_directories('subprojects')

subdir('src')
subdir('bin')
#subdir('tests')
