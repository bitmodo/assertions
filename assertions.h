/**
 * Assertions assertion library v1.0.0
 * This is a header-only C library to help write better tests
 * using a more complete assert than the one provided in the
 * standard C library.
 *
 * A lot of the design of this library is influenced by Criterion's
 * assertions, but there is hardly any code actually used from it,
 * apart from variadic utility macros.
 */

#ifndef ASSERTIONS_H
#define ASSERTIONS_H

#include <stdlib.h>
#include <stdio.h>

// Utility macros
// All of these macros are pretty much helpers and are not meant to be
// used outside of this header. They are really just here to make complex
// things more simple. All of these macros are internal, as they have the
// "ASSERTS_" prefix. Any macro with that prefix is subject to change at
// any time without warning.

// Expand the parameter. This is usefull when calling a macro from another
// macro to ensure that it expands completely when the preprocessor runs.
#define ASSERTS_EXPAND(x) x

// Get the tail of the variadic arguments. This will check to see how many
// arguments there are, and if there are more than 1, it just returns everything
// after the first. This allows there to be only 1 argument.
#define ASSERTS_VA_TAIL(...)                ASSERTS_EXPAND(ASSERTS_VA_TAIL_HELPER(ASSERTS_VA_TAIL_SELECT(_, __VA_ARGS__), __VA_ARGS__))

// Helper macros for getting the tail of variadic arguments. These are what actually
// implement the functionality.
#define ASSERTS_VA_TAIL_HELPER(N, ...)      ASSERTS_EXPAND(ASSERTS_VA_TAIL_HELPER_(N, __VA_ARGS__))
#define ASSERTS_VA_TAIL_HELPER_(N, ...)     ASSERTS_EXPAND(ASSERTS_VA_TAIL_HELPER_ ## N(__VA_ARGS__))
#define ASSERTS_VA_TAIL_HELPER_1(Head)
#define ASSERTS_VA_TAIL_HELPER_2(Head, ...) __VA_ARGS__

// Get the head of the variadic arguments. This will just return whatever the first
// argument is, and disregard the rest.
#define ASSERTS_VA_HEAD(...)                ASSERTS_EXPAND(ASSERTS_VA_HEAD_HELPER(ASSERTS_VA_TAIL_SELECT(_, __VA_ARGS__), __VA_ARGS__))

// Helper macros for getting the head of variadic arguments. These are what actually
// implement the functionality.
#define ASSERTS_VA_HEAD_HELPER(N, ...)      ASSERTS_EXPAND(ASSERTS_VA_HEAD_HELPER_(N, __VA_ARGS__))
#define ASSERTS_VA_HEAD_HELPER_(N, ...)     ASSERTS_EXPAND(ASSERTS_VA_HEAD_HELPER_ ## N(__VA_ARGS__))
#define ASSERTS_VA_HEAD_HELPER_1(Head)      Head
#define ASSERTS_VA_HEAD_HELPER_2(Head, ...) Head

// Construct a printf based on the number of arguments. This takes the file and line
// to print at, and variadic arguments. It requires at least one, being the condition
// that is being checked. The ones after that are optional. Without any extra arguments,
// This will print a generic error message and a string version of the condition. With
// one argument, it uses it as a format string instead of the generic error message. With
// anything over one argument, they are used as format arguments being passed into printf.
#define ASSERTS_VA_PRINTF(File, Line, ...)                           ASSERTS_EXPAND(ASSERTS_VA_PRINTF_HELPER(File, Line, ASSERTS_VA_HEAD(__VA_ARGS__), ASSERTS_VA_TAIL_SELECT(__VA_ARGS__), ASSERTS_VA_TAIL(__VA_ARGS__)))

// Helper macros for creating a printf statement. These are what actually implement
// the functionality.
#define ASSERTS_VA_PRINTF_HELPER(File, Line, Condition, N, ...)      ASSERTS_EXPAND(ASSERTS_VA_PRINTF_HELPER_(File, Line, Condition, N, __VA_ARGS__))
#define ASSERTS_VA_PRINTF_HELPER_(File, Line, Condition, N, ...)     ASSERTS_EXPAND(ASSERTS_VA_PRINTF_HELPER_ ## N(File, Line, Condition, __VA_ARGS__))
#define ASSERTS_VA_PRINTF_HELPER_0(File, Line, Condition, Head)      fprintf(stderr, "[%s:%d] Assertion failed: `" #Condition "`\n", File, Line)
#define ASSERTS_VA_PRINTF_HELPER_1(File, Line, Condition, Head)      fprintf(stderr, "[%s:%d] " Head "\n", File, Line)
#define ASSERTS_VA_PRINTF_HELPER_2(File, Line, Condition, Head, ...) fprintf(stderr, "[%s:%d] " Head "\n", File, Line, __VA_ARGS__)

// Tail selector macro. This takes variadic arguments, and depending
// on how many there are will return 0, 1, or 2. If there is one argument,
// 0 is returned. 1 for two arguments, and 2 for anything over 1.
#define ASSERTS_VA_TAIL_SELECT(...)                      \
    ASSERTS_EXPAND(ASSERTS_VA_TAIL_SELECT64(__VA_ARGS__, \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,                \
            2, 1, 0, _))

// Helper macro for tail select. This is basically where the magic happens.
#define ASSERTS_VA_TAIL_SELECT64(                         \
        _01, _02, _03, _04, _05, _06, _07, _08, _09, _10, \
        _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
        _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
        _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
        _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
        _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
        _61, _62, _63, X, ...)                                           X

// Assertion macros
// These are the macros for the actual implementation of assertions.

#define Assert_impl(File, Line, ...)                         \
  do {                                                       \
    int passed = !!(ASSERTS_VA_HEAD(__VA_ARGS__));           \
    if (!passed) {                                           \
      ASSERTS_VA_PRINTF(File, Line, __VA_ARGS__);            \
      abort();                                               \
    }                                                        \
  } while(0)

/**
 * Assert that an expression is true
 * Make an assertion that the specified expression is true. If it is
 * not, print an error message and abort the program. This macro is
 * variadic to allow for custom error formatting. By default, an
 * error message will be constructed using only the condition. If two
 * arguments are specified, the second will be interpreted as a message
 * string, and will be printed instead of the condition. Any extra arguments
 * will be interpreted as format arguments for the error message.
 *
 * Example:
 * ```c
 * Assert(1);
 * Assert(1, "Expected success");
 * Assert(1, "Expected success with %d", 1);
 * ```
 *
 * Arguments:
 *  - `Condition` This is the condition to be tested. If false, an error will occur
 *  - [_Optional_] `Message` An error message to print if the condition is false
 *  - [_Optional_] `...` Format parameters to pass to the print if the condition is false
 */
#define Assert(...) Assert_impl(__FILE__, __LINE__, __VA_ARGS__)

// Comparison macros
// These are macros to help compare one or more values. They are really just
// here to provide an alternate way of writing an expression, but might receive
// more functionality in the future.

#define ASSERTS_EQ_(Actual, Expected) ((Actual) == (Expected))
/**
 * Check the equality of two values
 * Take two values and make an exact comparison between the two.
 * This is simply a cleaner way to write `Actual == Expected`.
 * If the two values are not of a type that is meant to be directly
 * compared, then don't use this macro. For example, rather than
 * comparing the equality of two strings, it will just compare their
 * pointers and almost always return false.
 *
 * Example:
 * ```c
 * Assert(EQ(1, 1)); // Passes
 * Assert(EQ(0, 1)); // Fails
 * ```
 *
 * Arguments:
 *  - `Actual` The actual value that was calculated
 *  - `Expected` The value that was expected to be received
 */
#define EQ(Actual, Expected) ASSERTS_EXPAND(ASSERTS_EQ_(Actual, Expected))

#define ASSERTS_NOT_(Condition) !(Condition)
/**
 * Invert a condition
 * Take a condition and invert its value. For a zero or false
 * condition, the result is 1, and for a non-zero or true condition,
 * the result is zero. This is simply a cleaner and more expressive
 * way of writing `!Condition`.
 *
 * Example:
 * ```c
 * Assert(Not(0)); // Passes
 * Assert(Not(1)); // Fails
 * ```
 *
 * Arguments:
 *  - `Condition` The condition to negate
 */
#define Not(Condition) ASSERTS_EXPAND(ASSERTS_NOT_(Condition))

#define ASSERTS_LT_(Left, Right) ((Left) < (Right))
/**
 * Check if a value is less than another
 * A simple check to see if one value is less than another.
 * This is simply a cleaner and more expressive way of writing
 * `Left < Right`.
 * If the values are not meant to be directly compared, do not
 * use this macro. It compares the values directly without checking
 * for special types, and can cause things like floating point
 * inaccuracy.
 *
 * Example:
 * ```c
 * Assert(LT(0, 1)); // Passes
 * Assert(LT(1, 1)); // Fails
 * Assert(LT(1, 0)); // Fails
 * ```
 *
 * Arguments:
 *  - `Left` The left-hand side of the expression
 *  - `Right` The right-hand side of the expression
 */
#define LT(Left, Right) ASSERTS_EXPAND(ASSERTS_LT_(Left, Right))

#define ASSERTS_LE_(Left, Right) ((Left) <= (Right))
/**
 * Check if a value is less than or equal to another
 * A simple check to see if one value is less than or equal to another.
 * This is simply a cleaner and more expressive way of writing
 * `Left <= Right`.
 * If the values are not meant to be directly compared, do not
 * use this macro. It compares the values directly without checking
 * for special types, and can cause things like floating point
 * inaccuracy.
 *
 * Example:
 * ```c
 * Assert(LE(0, 1)); // Passes
 * Assert(LE(1, 1)); // Passes
 * Assert(LE(1, 0)); // Fails
 * ```
 *
 * Arguments:
 *  - `Left` The left-hand side of the expression
 *  - `Right` The right-hand side of the expression
 */
#define LE(Left, Right) ASSERTS_EXPAND(ASSERTS_LE_(Left, Right))

#define ASSERTS_GT_(Left, Right) ((Left) > (Right))
/**
 * Check if a value is greater than another
 * A simple check to see if one value is greater than another.
 * This is simply a cleaner and more expressive way of writing
 * `Left > Right`.
 * If the values are not meant to be directly compared, do not
 * use this macro. It compares the values directly without checking
 * for special types, and can cause things like floating point
 * inaccuracy.
 *
 * Example:
 * ```c
 * Assert(GT(1, 0)); // Passes
 * Assert(GT(1, 1)); // Fails
 * Assert(GT(0, 1)); // Fails
 * ```
 *
 * Arguments:
 *  - `Left` The left-hand side of the expression
 *  - `Right` The right-hand side of the expression
 */
#define GT(Left, Right) ASSERTS_EXPAND(ASSERTS_GT_(Left, Right))

#define ASSERTS_GE_(Left, Right) ((Left) >= (Right))
/**
 * Check if a value is greater than or equal to another
 * A simple check to see if one value is greater than or equal to another.
 * This is simply a cleaner and more expressive way of writing
 * `Left >= Right`.
 * If the values are not meant to be directly compared, do not
 * use this macro. It compares the values directly without checking
 * for special types, and can cause things like floating point
 * inaccuracy.
 *
 * Example:
 * ```c
 * Assert(GE(1, 0)); // Passes
 * Assert(GE(1, 1)); // Passes
 * Assert(GE(0, 1)); // Fails
 * ```
 *
 * Arguments:
 *  - `Left` The left-hand side of the expression
 *  - `Right` The right-hand side of the expression
 */
#define GE(Left, Right) ASSERTS_EXPAND(ASSERTS_GE_(Left, Right))

#define ASSERTS_ZERO_(Value) (Value) == 0
/**
 * Check if a value is equal to zero
 * A simple check to see if a value is equal to zero. This is
 * simply a cleaner and more expressive way of writing `Value == 0`.
 * If the value is not meant to be directly compared to zero, do not
 * use this macro. It compares the value directly to zero without checking
 * for special types, and can cause things like floating point
 * inaccuracy.
 *
 * ```c
 * Assert(Zero(0)); // Passes
 * Assert(Zero(1)); // Fails
 * ```
 *
 * Arguments:
 *  - `Value` The value to compare with zero
 */
#define Zero(Value) ASSERTS_EXPAND(ASSERTS_ZERO_(Value))

#endif // _ASSERTIONS_H
