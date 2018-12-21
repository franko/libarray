project('libarray', 'c', version: '0.1.0', default_options : ['c_std=c99'])

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: true)

array_include_dir = include_directories('include')

subdir('src')
subdir('tests')
