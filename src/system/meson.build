headers = [
  'config.hpp',
]
sources = []

uuid_dep = dependency('uuid')
if uuid_dep.found()
  deps += uuid_dep
  args += '-luuid'
endif

lib = library(
  'system',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

system_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
