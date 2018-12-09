project('libarray', 'c', version: '0.1.0', default_options : ['c_std=c99'])

array_src = ['array.c']

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: true)

executable('test-array-1', array_src + ['test-array-1.c'], include_directories: [], dependencies: [])
executable('test-array-2', array_src + ['test-array-2.c'], include_directories: [], dependencies: [])
executable('test-array-3', array_src + ['test-array-3.c'], include_directories: [], dependencies: m_dep)
