gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')

test(
  'create_file_for_test',
  executable(
    'create_file_struct',
    'src/create_file_struct.cpp',
    dependencies: [ deps, gtest_dep ]
  )
)

test(
  'navigation',
  executable(
    'navigation',
    'src/navigation.cpp',
    dependencies: [ deps, gtest_dep ]
  )
)

test(
  'preview',
  executable(
    'preview',
    'src/preview.cpp',
    dependencies: [ deps, gtest_dep ]
  )
)
