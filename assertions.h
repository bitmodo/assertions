/**
 * Assertions assertion library
 * This is a header-only C library to help write better tests
 * using a more complete assert than the one provided in the
 * standard C library.
 *
 * A lot of the design of this library is influenced by Criterion's
 * assertions, but there is hardly any code actually used from it,
 * apart from variadic utility macros.
 */

#ifndef _ASSERTIONS_H
#define _ASSERTIONS_H

#include <stdlib.h>
#include <stdio.h>

// Utility macros

#define ASSERTS_EXPAND(x) x

#define ASSERTS_VA_TAIL(...)                ASSERTS_EXPAND(ASSERTS_VA_TAIL_HELPER(ASSERTS_VA_TAIL_SELECT(_, __VA_ARGS__), __VA_ARGS__))

#define ASSERTS_VA_TAIL_HELPER(N, ...)      ASSERTS_EXPAND(ASSERTS_VA_TAIL_HELPER_(N, __VA_ARGS__))
#define ASSERTS_VA_TAIL_HELPER_(N, ...)     ASSERTS_EXPAND(ASSERTS_VA_TAIL_HELPER_ ## N(__VA_ARGS__))
#define ASSERTS_VA_TAIL_HELPER_1(Head)
#define ASSERTS_VA_TAIL_HELPER_2(Head, ...) __VA_ARGS__

#define ASSERTS_VA_HEAD(...)                ASSERTS_EXPAND(ASSERTS_VA_HEAD_HELPER(ASSERTS_VA_TAIL_SELECT(_, __VA_ARGS__), __VA_ARGS__))

#define ASSERTS_VA_HEAD_HELPER(N, ...)      ASSERTS_EXPAND(ASSERTS_VA_HEAD_HELPER_(N, __VA_ARGS__))
#define ASSERTS_VA_HEAD_HELPER_(N, ...)     ASSERTS_EXPAND(ASSERTS_VA_HEAD_HELPER_ ## N(__VA_ARGS__))
#define ASSERTS_VA_HEAD_HELPER_1(Head)      Head
#define ASSERTS_VA_HEAD_HELPER_2(Head, ...) Head

#define ASSERTS_VA_PRINTF(File, Line, ...)                           ASSERTS_EXPAND(ASSERTS_VA_PRINTF_HELPER(File, Line, ASSERTS_VA_HEAD(__VA_ARGS__), ASSERTS_VA_TAIL_SELECT(__VA_ARGS__), ASSERTS_VA_TAIL(__VA_ARGS__)))

#define ASSERTS_VA_PRINTF_HELPER(File, Line, Condition, N, ...)      ASSERTS_EXPAND(ASSERTS_VA_PRINTF_HELPER_(File, Line, Condition, N, __VA_ARGS__))
#define ASSERTS_VA_PRINTF_HELPER_(File, Line, Condition, N, ...)     ASSERTS_EXPAND(ASSERTS_VA_PRINTF_HELPER_ ## N(File, Line, Condition, __VA_ARGS__))
#define ASSERTS_VA_PRINTF_HELPER_0(File, Line, Condition, Head)      fprintf(stderr, "[%s:%d] Assertion failed: `" #Condition "`\n", File, Line)
#define ASSERTS_VA_PRINTF_HELPER_1(File, Line, Condition, Head)      fprintf(stderr, "[%s:%d] " Head "\n", File, Line)
#define ASSERTS_VA_PRINTF_HELPER_2(File, Line, Condition, Head, ...) fprintf(stderr, "[%s:%d] " Head "\n", File, Line, __VA_ARGS__)

#define ASSERTS_VA_TAIL_SELECT(...)                      \
    ASSERTS_EXPAND(ASSERTS_VA_TAIL_SELECT64(__VA_ARGS__, \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 1, 0, _))

#define ASSERTS_VA_TAIL_SELECT64(                         \
        _01, _02, _03, _04, _05, _06, _07, _08, _09, _10, \
        _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
        _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
        _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
        _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
        _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
        _61, _62, _63, X, ...)                                           X

// Assertion macros

#define Assert_impl(File, Line, ...)                         \
  do {                                                       \
    int passed = !!(ASSERTS_VA_HEAD(__VA_ARGS__));           \
    if (!passed) {                                           \
      ASSERTS_VA_PRINTF(File, Line, __VA_ARGS__);            \
      abort();                                               \
    }                                                        \
  } while(0)

#define Assert(...) Assert_impl(__FILE__, __LINE__, __VA_ARGS__)

// Equality macros

#define EQ(Actual, Ref) ((Actual) == (Ref))

#define Not(Condition) !(Condition)

#define LT(Actual, Ref) ((Actual) < (Ref))

#define LE(Actual, Ref) ((Actual) <= (Ref))

#define GT(Actual, Ref) ((Actual) > (Ref))

#define GE(Actual, Ref) ((Actual) >= (Ref))

#define Zero(Value) (Value) == 0

#endif // _ASSERTIONS_H
