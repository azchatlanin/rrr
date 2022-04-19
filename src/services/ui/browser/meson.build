headers = ['browser.hpp', 'history/history.hpp']
sources = ['browser.cpp', 'history/history.cpp']

lib = library(
  'browser',
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

browser_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
