headers = ['command_line.hpp']
sources = ['command_line.cpp']

deps += managers_dep

lib = library(
  'command_line',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

command_line_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
