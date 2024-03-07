project('light', 'cpp',
  default_options: [
    'cpp_std=c++11',
    'warning_level=3',
    'werror=true',
  ],
  version: '0.1.0',
  license: 'MIT',
)


cpp = meson.get_compiler('cpp')

light_define = []
light_header = [
  include_directories('header'),
]
light_depend = [
  cpp.find_library('m', required: true),
  cpp.find_library('SDL2', required: true),
]

subdir('source/light/Base')
subdir('source/light/Memory')
subdir('source/light/Engine')

executable('light',
  sources:             [
    'source/main_events.cpp',
    'source/game/Piece.cpp',
    'source/game/Game_State.cpp',
    'source/game/Floor_Layer.cpp',
    'source/game/Actor_Layer.cpp',
    'source/game/Controls.cpp',
  ],
  include_directories: [light_header],
  dependencies:        [light_depend],
  link_with:           [light_define],
)
