tests = [
    {'name': 'success', 'src': files('success.c')},
    {'name': 'success-message', 'src': files('success_message.c')},
    {'name': 'success-format', 'src': files('success_format.c')},

    {'name': 'fail', 'src': files('fail.c'), 'type': 'fail'},
    {'name': 'fail-message', 'src': files('fail_message.c'), 'type': 'fail'},
    {'name': 'fail-format', 'src': files('fail_format.c'), 'type': 'fail'},

    {'name': 'eq-success', 'src': files('eq_success.c')},
    {'name': 'eq-fail', 'src': files('eq_fail.c'), 'type': 'fail'},

    {'name': 'ge-success', 'src': files('ge_success.c')},
    {'name': 'ge-fail', 'src': files('ge_fail.c'), 'type': 'fail'},
    {'name': 'gt-success', 'src': files('gt_success.c')},
    {'name': 'gt-fail', 'src': files('gt_fail.c'), 'type': 'fail'},

    {'name': 'le-success', 'src': files('le_success.c')},
    {'name': 'le-fail', 'src': files('le_fail.c'), 'type': 'fail'},
    {'name': 'lt-success', 'src': files('lt_success.c')},
    {'name': 'lt-fail', 'src': files('lt_fail.c'), 'type': 'fail'},

    {'name': 'not-success', 'src': files('not_success.c')},
    {'name': 'not-fail', 'src': files('not_fail.c'), 'type': 'fail'},

    {'name': 'zero-success', 'src': files('zero_success.c')},
    {'name': 'zero-fail', 'src': files('zero_fail.c'), 'type': 'fail'},
]

foreach test : tests
    name = test.get('name')
    src = test.get('src')
    type = test.get('type', 'normal')

    if type == 'normal'
        should_fail = false
    elif type == 'fail'
        should_fail = true
    endif

    e = executable('test-' + name, src, dependencies: [assertions_dep])
    test(name, e, should_fail: should_fail)
endforeach
