project('assertions', 'c',
        license: 'Unlicense',
        version: '1.0',
        default_options : ['c_std=c99'])

compiler = meson.get_compiler('c')
errored = false

checks = [
    {'type': 'header', 'name': 'stdlib.h'},
    {'type': 'header', 'name': 'stdio.h'},
    {'type': 'header', 'name': 'stddef.h'},
    {'type': 'header', 'name': 'stdint.h'},
    
    {'type': 'function', 'name': 'fprintf', 'prefix': '#include <stdio.h>'},
    {'type': 'function', 'name': 'abort', 'prefix': '#include <stdlib.h>'},
]

foreach check : checks
    type = check.get('type')
    name = check.get('name')

    if type == 'header'
        if not compiler.check_header(name)
            errored = true
            warning('The compiler cannot find the ' + name + ' header. Make sure you have a C standard library installed.')
        endif
    elif type == 'function'
        if not compiler.has_function(name, prefix: check.get('prefix'))
            errored = true
            warning('The compiler could not find the ' + name + ' function. Make sure you have a C standard library installed.')
        endif
    endif
endforeach

if errored
    error('Cannot continue the build as there are errors with the environment')
endif

assertions_files = files('assertions.h')
install_headers(assertions_files)
assertions_inc = include_directories('.')
assertions_dep = declare_dependency(include_directories: [assertions_inc])

subdir('test')
