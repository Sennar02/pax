light_engine = static_library('light-engine',
  include_directories: [light_header],
  sources: [
    'Kernel/State.cpp',
    'Kernel/Timer.cpp',
    'Kernel/View.cpp',
    'Kernel/Grid_Layer.cpp',
    'Kernel/Grid.cpp',
    'Kernel/Display.cpp',
    'Kernel/Painter.cpp',
    'Events/Keybd_Event.cpp',
    'Events/Mouse_Event.cpp',
    'Events/Event_Queue.cpp',
    'Engine.cpp',
  ],
)

light_define = light_define + [light_engine]
