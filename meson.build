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
midi_dep = dependency('rtmidi')

# Include directory for headers
inc = include_directories('include', 'contrib')
apps_inc = include_directories('hw7', 'contrib')
peroxide_inc = include_directories('hw7', 'contrib', 'peroxide')

# --- AUTOGEN_SRC_START ---
src_files = [
  'source/config.cpp',
  'source/datetime.cpp',
  'source/environment.cpp',
#  'source/filter.cpp',
  'source/fs.cpp',
  'source/globals.cpp',
  'source/logging.cpp',
  'source/main.cpp',
  'source/str.cpp',
]
# --- AUTOGEN_SRC_END ---

lib_sources = files(
  'source/config.cpp',
  'source/datetime.cpp',
  'source/environment.cpp',
  'source/filter.cpp',
  'source/fs.cpp',
  'source/globals.cpp',
  'source/logging.cpp',
  'source/str.cpp',
)

# --- PEROXIDE SOURCE FILES START ---
peroxide_src_files = [
  'peroxide/clip.cpp',
  'peroxide/globals.cpp',
  'peroxide/keyboard.cpp',
  'peroxide/main.cpp',
  'peroxide/midi.cpp',
  'peroxide/peroxide.cpp',
  'peroxide/player.cpp',
  'peroxide/song.cpp',
]
# --- PEROXIDE SOURCE FILES END ---

hw7_deps = [
  fmt_dep,
  spdlog_dep,
  gtkmm_dep,
  magic_dep,
]

h2o2_deps = [
  fmt_dep,
  spdlog_dep,
  gtkmm_dep,
  magic_dep,
  midi_dep,
]

libhw7 = static_library(
  'hw7',
  lib_sources,
  include_directories: inc,
  dependencies: hw7_deps,
)

executable(
  'hello',
  'apps/hello.cpp',
  include_directories: inc,
  dependencies: hw7_deps,
  link_with: libhw7,
)

executable(
  'goodbye',
  'apps/goodbye.cpp',
  include_directories: inc,
  dependencies: hw7_deps,
  link_with: libhw7,
)

executable(
  'peroxide',
  peroxide_src_files,
  include_directories: peroxide_inc,
  dependencies: h2o2_deps,
  link_with: libhw7,
)

# libhw7 = static_library(
#   'hw7',
#   lib_sources,
#   include_directories: inc,
#   dependencies: [
#     fmt_dep,
#     spdlog_dep,
#     gtkmm_dep,
#     magic_dep,
#   ],
# )

# executable(
#   'hello',
#   'apps/hello.cpp',
#   include_directories: inc,
#   dependencies: [
#     fmt_dep,
#     spdlog_dep,
#     gtkmm_dep,
#     magic_dep,
#   ],

#   link_with: libhw7,
# )

# executable(
#   'goodbye',
#   'apps/goodbye.cpp',
#   include_directories: inc,
#   dependencies: [
#     fmt_dep,
#     spdlog_dep,
#     gtkmm_dep,
#     magic_dep,
#   ],

#   link_with: libhw7,
# )