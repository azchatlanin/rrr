headers = ['menu_bar.hpp']
sources = ['menu_bar.cpp']

deps += layer_dep

lib = library(
  'menu_bar',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

menu_bar_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
