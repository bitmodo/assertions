# Assertions
[![License](https://img.shields.io/github/license/codmf/assertions)](https://github.com/codmf/assertions/blob/master/UNLICENSE)
[![Releases](https://img.shields.io/github/v/release/codmf/assertions?include_prereleases&sort=semver)](https://github.com/codmf/assertions/releases)
[![Build status](https://img.shields.io/github/workflow/status/codmf/assertions/Build%20&%20test%20CI)](https://github.com/codmf/assertions/actions)

Assertions is a single file header-only assertions library for C and C++.
The reason behind this is the lack of an assertion library for C.
There is [Snowhouse](https://github.com/banditcpp/snowhouse), but that is for C++ and isn't header-only.
The only other real assertions can only be found in test libraries, and most aren't header-only and single file.

This project fills the gap!
It provides a simple, easy-to-use library for writing assertions that don't use any dependencies.

## Usage
Assertions is meant to be dead simple to setup and use.
To use it, it isn't even necessary to clone the repository or install anything!

### Intalling
Installing Assertions is as simple as copying the header file into your project.

The first option is to copy the header file directly from this repository into your project.
This has some key advantages over the other option.
Firstly, you get all of the documentation and information provided in that file.
This can be useful if you ever expect to be modifying the file, as you will have all of the necessary descriptions of everything.
However, this method also comes with some down sides.
When pulling the file directly from the repository, you may run into issues.
Since you are taking the code from the development channel, you may get code that is broken or still in development.

The second option is to get the header file from a release.
By getting an official release file, you can make sure you aren't getting any buggy or broken code.
You are also getting a version that is minified, so you aren't getting any of the extra comments or empty lines.
However, since the code is minified, it may be more difficult to figure out what everything is doing.

### Using
Using Assertions is meant to be extremely simple.
Once you have the file setup, you are set to actually start using it.

First, you need to include it in your code.
To do this, you'll need an include statement that looks like this:

```c
#include "assertions.h"
```

Now that you have it included, you'll be able to utilize any of the provided macros.

#### `Assert`
This is the main Assertions macro.
It is a drop-in replacement for the C provided `assert`.
The definition of the macro is variadic, but it actually requires at least one argument, being the condition.
When the condition is zero or false, a message will be printed and the program will be aborted, but if the condition is non-zero or true, the process will continue.

The condition of this macro doesn't actually need to use the utility macros provided.
It is pretty much just passed into an `if` statement and used like that, so any condition could be used.

This macro also can take a format message.
This refers to all arguments after the first one.
The format message and arguments use the `printf` format, as they are passed directly to it.
The order goes condition, message, format arguments.
Both the message and format arguments are optional and not required.

If no format message is specified, a default one will be used instead.
This will include a message stating that an assertion failed as well as the condition that failed.

All error messages will include the file and line that the assertion was on.

**Arguments:**
 - `Condition`: The condition to test. If false, abort.
 - [_Optional_] `Message`: An optional format message, passed to `printf` on failure.
 - [_Optional_] `Arguments`: Optional format arguments, passed with `Message` to `printf` on failure.

**Example:**
```c
Assert(1);                                 // Passes
Assert(1, "Expected success");             // Passes
Assert(1, "Expected success with %d", 1);  // Passes

Assert(0);                                 // Fails
Assert(0, "Expected failure");             // Fails
Assert(0, "Expected failure with %d", 0);  // Fails
```

#### `EQ`
A simple equality comparison between two values.
This is basically just a cleaner and more expressive way of writing `Actual == Expected`.

If the values are not meant to be directly compared, don't use this macro.
For example, rather than actually comparing two strings, this will compare their pointers and almost always return false.

**Arguments:**
 - `Actual`: The value that was actually calculated.
 - `Expected`: The value that was expected.

**Example:**
```c
Assert(EQ(1, 1));  // Passes
Assert(EQ(1, 0));  // Fails
```

#### `Not`
Negate the value of a condition.
This is basically just a cleaner and more expressive way of writing `!Condition`.

The condition passed as a parameter doesn't need to be from another utility macro.
It basically just returns the not operator with the condition appended to the end.

**Arguments:**
 - `Condition`: The condition to negate.

**Example:**
```c
Assert(Not(1 == 0));    // Passes
Assert(Not(1 == 1));    // Fails

Assert(Not(EQ(1, 0)));  // Passes
Assert(Not(EQ(1, 1)));  // Fails
```

#### `LT`
A simple check to see if one value is less than another.
This is basically a cleaner and more expressive way of writing `Left < Right`.

If the values are not meant to be directly compared, don't use this macro.
It compares the values directly without checking for special types.
This means that things like floating point inaccuracy is likely if you do use this.

**Arguments:**
 - `Left`: The left hand side of the expression.
 - `Right`: The right hand side of the expression.

**Example:**
```c
Assert(LT(0, 1));  // Passes
Assert(LT(1, 1));  // Fails
Assert(LT(1, 0));  // Fails
```

#### `LE`
A simple check to see if one value is less than or equal to another.
This is basically a cleaner and more expressive way of writing `Left <= Right`.

If the values are not meant to be directly compared, don't use this macro.
It compares the values directly without checking for special types.
This means that things like floating point inaccuracy is likely if you do use this.

**Arguments:**
 - `Left`: The left hand side of the expression.
 - `Right`: The right hand side of the expression.

**Example:**
```c
Assert(LE(0, 1));  // Passes
Assert(LE(1, 1));  // Passes
Assert(LE(1, 0));  // Fails
```

#### `GT`
A simple check to see if one value is greater than another.
This is basically a cleaner and more expressive way of writing `Left > Right`.

If the values are not meant to be directly compared, don't use this macro.
It compares the values directly without checking for special types.
This means that things like floating point inaccuracy is likely if you do use this.

**Arguments:**
 - `Left`: The left hand side of the expression.
 - `Right`: The right hand side of the expression.

**Example:**
```c
Assert(GT(1, 0));  // Passes
Assert(GT(1, 1));  // Fails
Assert(GT(0, 1));  // Fails
```

#### `GE`
A simple check to see if one value is greater than or equal to another.
This is basically a cleaner and more expressive way of writing `Left >= Right`.

If the values are not meant to be directly compared, don't use this macro.
It compares the values directly without checking for special types.
This means that things like floating point inaccuracy is likely if you do use this.

**Arguments:**
 - `Left`: The left hand side of the expression.
 - `Right`: The right hand side of the expression.

**Example:**
```c
Assert(GE(1, 0));  // Passes
Assert(GE(1, 1));  // Passes
Assert(GE(0, 1));  // Fails
```

#### `Zero`
A simple check to see if a value is equal to zero.
This is basically a cleaner and more expressive way of writing `Value == 0`.

This can be useful for when you want to check if a pointer is null.

**Arguments:**
 - `Value`: The value to compare with zero.

**Example:**
```c
Assert(Zero(0));  // Passes
Assert(Zero(1));  // Fails
```

## Other information
Here is just a bit of other information that I thought might be useful when you're browsing through the code or trying to figure something out.

### Naming scheme
You may have noticed that all of the macros provided by this project are either entirely uppercase or are capitalized.
This naming scheme is primarily chosen to eliminate conflict with the C provided `assert` macro.
By naming our macro `Assert` with a capital "a", we can allow users to use the C macro as well as ours at the same time.
The other macros basically just follow this same name scheme in order to make everything consistent.

### Internal macros
Internal macros are used throughout Assertions.
These are macros that are prefixed with `ASSERTS_`.
These macros are subject to change at any time, without warning, and they are not guaranteed to have documentation.

The reason behind these macros is to be able to achieve a higher level of functionality.
These macros allow us to achieve the optional arguments feature on the main `Assert` macro.
Without these, we wouldn't be able to achieve that functionality, and would have to define separate macros for each different type of call.

### Test layout
The layout of the `test` folder is the required `meson.build` file, and all of the individual tests.
Each different test is defined in its own separate file.
By separating each situation in its own file, we are able to know exactly what is going wrong if there is a test fails, rather than having to read the test output to find the issue.

### Using `assert` in tests
The C provided `assert` macro is used in all utility macro tests.
This is because we want to ensure that each test is independent.
That means that if one part of the project stops working, a whole slew of tests won't fail, because they don't depend on each other.

The builtin `assert` macro is used so that if our `Assert` macro stops working, our tests for the utility macros won't all start failing.
