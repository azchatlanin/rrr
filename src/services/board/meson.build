headers = [
  'board.hpp'
]
sources = []

lib = library(
  'board',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

board_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
