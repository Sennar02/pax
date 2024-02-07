project('light', 'cpp',
  default_options: [
    'cpp_std=c++11',
    'warning_level=3',
    'werror=false',
  ],
  version: '0.1.0',
  license: 'MIT',
)

light_header = include_directories('header')

cpp = meson.get_compiler('cpp')

light_depend = [cpp.find_library('m', required: true)]
light_define = []

subdir('source/light/Base')

executable('light',
  sources:             ['source/main.cpp'],
  include_directories: [light_header],
  dependencies:        [light_depend],
  link_with:           [light_define],
)
