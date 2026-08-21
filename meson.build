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
apps_inc = include_directories('hw7', 'contrib')

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

hw7_deps = [
  fmt_dep,
  spdlog_dep,
  gtkmm_dep,
  magic_dep,
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
  'apps/peroxide.cpp',
  include_directories: apps_inc,
  dependencies: hw7_deps,
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