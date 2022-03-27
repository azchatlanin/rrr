headers = ['info_bar.hpp']
sources = ['info_bar.cpp']

deps += layer_dep

lib = library(
  'info_bar',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

info_bar_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
