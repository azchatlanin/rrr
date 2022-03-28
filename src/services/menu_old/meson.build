headers = [ 'menu.hpp' ]
sources = [ 'menu.cpp' ]

lib = library(
  'menu',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

menu_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
