headers = [ 'file/file.hpp', 'browser.hpp', 'history/history.hpp', 'navigation/navigation.hpp', 'preview/preview.hpp' ]
sources = [ 'file/file.cpp', 'browser.cpp', 'history/history.cpp', 'navigation/navigation.cpp', 'preview/preview.cpp' ]

deps += managers_dep

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
