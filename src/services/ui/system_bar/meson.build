headers = ['system_bar.hpp']
sources = ['system_bar.cpp']

deps += managers_dep

lib = library(
  'system_bar',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

system_bar_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
