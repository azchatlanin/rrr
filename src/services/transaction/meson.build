headers = [
  'transaction.hpp'
]
sources = []

lib = library(
  'transaction',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

transaction_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
