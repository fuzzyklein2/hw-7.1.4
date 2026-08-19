# @file meson.build
project(
  'hello7',
  'cpp',
  version : '1.0',
  default_options : ['cpp_std=c++23']
)

gtkmm_dep = dependency('gtkmm-4.0')
fmt_dep = dependency('fmt')
spdlog_dep = dependency('spdlog')
magic_dep = dependency('libmagic')

# Include directory for headers
inc = include_directories('include', 'contrib')

# --- AUTOGEN_SRC_START ---
src_files = [
  'source/config.cpp',
  'source/datetime.cpp',
  'source/environment.cpp',
  'source/filter.cpp',
  'source/fs.cpp',
  'source/globals.cpp',
  'source/logging.cpp',
  'source/main.cpp',
  'source/str.cpp',
]
# --- AUTOGEN_SRC_END ---

# Define executable
executable(
  'hello',
  src_files,
  include_directories: inc,
  dependencies : [
    fmt_dep,
    spdlog_dep,
    gtkmm_dep,
    magic_dep
  ],
)

