project('assertions', 'c',
        license: 'Unlicense',
        version: '1.0')

compiler = meson.get_compiler('c')
errored = false

if not compiler.has_header('stdlib.h')
    errored = true
    warning('The compiler cannot find the stdlib header. Make sure you have a C standard library installed.')
endif
if not compiler.has_header('stdio.h')
    errored = true
    warning('The compiler cannot find the stdio header. Make sure you have a C standard library installed.')
endif

if not compiler.has_function('fprintf', prefix: '#include <stdio.h>')
    errored = true
    warning('The compiler could not find the fprintf function. Make sure you have a C standard library installed')
endif
if not compiler.has_function('abort', prefix: '#include <stdlib.h>')
    errored = true
    warning('The compiler could not find the abort function. Make sure you have a C standard library installed')
endif

if errored
    error('Cannot continue the build as there are errors with the environment')
endif

assertions_files = files('assertions.h')
install_headers(assertions_files)
assertions_inc = include_directories('.')
assertions_dep = declare_dependency(include_directories: [assertions_inc])

subdir('test')
