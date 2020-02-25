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
Any extra information and documentation can be found on the [wiki](https://github.com/codmf/assertions/wiki).

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
