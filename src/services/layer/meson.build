headers = ['layer.hpp']
sources = ['layer.cpp']

lib = library(
  'layer',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

layer_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
