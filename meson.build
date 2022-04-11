project('sgc', 'c', 
  default_options : 
  ['warning_level=3', 
   'buildtype=debugoptimized'])

sgc_dep = declare_dependency(
  include_directories: include_directories('include'),
  )

if not meson.is_subproject()
  subdir('test')
endif
