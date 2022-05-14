gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')

test(
  'navigation',
  executable(
    'up_down',
    'src/navigation/up_down.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'navigation',
  executable(
    'left_right',
    'src/navigation/left_right.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'navigation',
  executable(
    'empty_dir',
    'src/navigation/empty_dir.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'preview',
  executable(
    'preview',
    'src/preview/preview.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'history',
  executable(
    'history',
    'src/history/history.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'command_line',
  executable(
    'mkdir',
    'src/command_line/mkdir.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'command_line',
  executable(
    'autofill',
    'src/command_line/autofill.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'command_line',
  executable(
    'remove',
    'src/command_line/remove.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'select',
  executable(
    'select',
    'src/select/select.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'command_line',
  executable(
    'command_line',
    'src/command_line/touch.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'command_line',
  executable(
    'multiremove',
    'src/command_line/multiremove.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'command_line',
  executable(
    'paste',
    'src/command_line/paste.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

test(
  'command_line',
  executable(
    'move',
    'src/command_line/move.cpp',
    dependencies: [ deps, gtest_dep ]
  ),
  is_parallel : false
)

# HERE
# move
# rename
#
