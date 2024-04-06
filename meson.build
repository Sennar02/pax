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

pax_header = [include_directories('include')]
pax_define = []
pax_depend = [
    cpp.find_library('m', required: true),
    cpp.find_library('SDL2', required: true),
]

subdir('sources/pax/')

executable('pax_tests',
    include_directories: pax_header,
    dependencies:        pax_depend,
    link_with:           pax_define,
    sources: [
        'sources/test_base.cpp',
        'sources/test_signal.cpp',
        'sources/test_engine.cpp',
        'sources/test.cpp',
    ],
)