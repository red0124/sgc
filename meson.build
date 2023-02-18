project(
  'sgc',
  ['c'],
  default_options:
    ['warning_level=3',
     'buildtype=debugoptimized',
     'wrap_mode=forcefallback'],
  version: '1.1.0',
  meson_version: '>=0.54.0')

sgc_dep = declare_dependency(
  include_directories: include_directories('include'),
  )

meson.override_dependency('sgc', sgc_dep)

if not meson.is_subproject()
  subdir('test')
endif
