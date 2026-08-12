# @file meson.build
project(
  'hello7',
  'cpp',
  version : '1.0',
  default_options : ['cpp_std=c++23']
)

# gtkmm_dep = dependency('gtkmm-4.0')
fmt_dep = dependency('fmt')
spdlog_dep = dependency('spdlog')

# Include directory for headers
inc = include_directories('include', 'contrib')

# --- AUTOGEN_SRC_START ---
src = [
  'source/config.cpp',
  'source/datetime.cpp',
  'source/environment.cpp',
  'source/fs.cpp',
  'source/globals.cpp',
  'source/logging.cpp',
  'source/main.cpp',
]
# --- AUTOGEN_SRC_END ---

# Define executable
executable(
  'hello',
  src,
  include_directories: inc,
#  dependencies : gtkmm_dep
  dependencies : [
    fmt_dep,
    spdlog_dep,
  ],
)

