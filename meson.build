project('pax', 'cpp',
    default_options: [
        'cpp_std=c++11',
        'warning_level=3',
        'werror=true',
    ],
    version: '0.1.0',
    license: 'MIT',
)

cpp = meson.get_compiler('cpp')

pax_define = []
pax_header = [
    include_directories('header'),
]
pax_depend = [
    cpp.find_library('m', required: true),
    cpp.find_library('SDL2', required: true),
]

subdir('source/pax/Base')
subdir('source/pax/Memory')
subdir('source/pax/Signal')
subdir('source/pax/Engine')

executable('pax',
    sources:             ['source/main_signal.cpp'],
    include_directories: pax_header,
    dependencies:        pax_depend,
    link_with:           pax_define,
)
