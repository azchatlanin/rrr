headers = [ 'manager/board/board.hpp', 'state_manager/state_manager.hpp', 'manager/manager.hpp' ]
sources = [ 'manager/board/board.cpp', 'state_manager/state_manager.cpp' ]

lib = library(
  'managers',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

managers_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
