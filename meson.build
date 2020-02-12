project('assertions', 'c',
        license: 'MIT',
        version: '1.0')

assertions_files = files('assertions.h')
install_headers(assertions_files)
assertions_inc = include_directories('.')
assertions_dep = declare_dependency(include_directories: [assertions_inc])

subdir('test')
