pax_engine = static_library('pax-engine',
  include_directories: [pax_header],
  sources: [
    'Kernel/State.cpp',
    'Kernel/Timer.cpp',
    'Kernel/View.cpp',
    'Kernel/Grid_Layer.cpp',
    'Kernel/Grid.cpp',
    'Kernel/Display.cpp',
    'Kernel/Painter.cpp',
    'Kernel/Screen.cpp',
    'Signal/System_Source.cpp',
    'Signal/Keybd_Signal.cpp',
    'Signal/Mouse_Signal.cpp',
    'Signal/Display_Signal.cpp',
    'Engine.cpp',
  ],
)

pax_define = pax_define + [pax_engine]
