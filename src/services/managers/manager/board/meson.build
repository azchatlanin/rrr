headers = [ 'state_manager/state_manager.hpp', 'manager/manager.hpp' ]
sources = [ 'state_manager/state_manager.cpp' ]

lib = library(
  'board',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

board_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
