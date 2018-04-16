# CUTE
## C Unit Testing Environment

This project defines a *[xUnit](https://en.wikipedia.org/wiki/XUnit)*-like unit
testing environment in C.



## I. Description


### 1. Unit tests

#### a) A unit test is a procedure

A unit test is a no-parameter procedure, *i.e.* a function of profile:

    void test_proc(void);

designed to execute a block of instructions that concerns a singular feature
of a development under specific circumstances to verify its behavior.

### b) Unit test are indenpendent

The tests are supposed independent, the order of execution of the tests should
not be a concern; indenpendence of the tests can be achieved using `setUp` and
`tearDown` features of a test case, see after.


### 2. Test cases

A test case is a structure that contains several tests that are semantically
related; generally these are tests on the same feature. This allows to easily
run a coherent number of tests at once.

A test case can be given up to four helper functions:
`initiate` and `terminate` functions,  to be run respectively before and after
all tests, to ensure the adequate isolation of the environment, and
`setUp` and `tearDown` functions, to be run respectively before and after each
test, to enforce test independence.


### 3. Test suites

A test suite is a container for several test cases. These cases may be loosely
related, they will generally concern features of the same project but not the
same feature -- if they did they should be merged into a single test case.
Like test cases for tests, this structure allows to run multiple test cases
easily.


### 4. Assertions and assumptions

#### a) Assertions

An assertion is an instruction that evaluates an expression representing a
condition and, if the condition is not met (evaluates to a `false` value), stops
immediately the execution.

An assertion is generally the principal instruction in a unit test, whose
structure will resemble:

> 1. execute one or more instructions on the object under test
> 2. Verify with an assertion that the object is in the expected state.

There are two kind of assertions:

**Runtime assertions**
The assertion is evaluated during the execution of the program. The execution is
stopped by sending a `SIGABRT` signal that, unlike a call to `abort(3)` or the
standard `assert(3)` can be handled and recovered from.

**Compile-time assertions**
The expression is evaluated during the compilation of the source code and on
failure, the compilation is invalidated. This type of assertion is mostly used
to ensure the validity of the building environment:

    CUTE_compileTimeAssert(sizeof(int) == 8, "Architecture must be 64 bits");

#### b) Assumptions

An assumption is an instriction that ensures that the block defined after it
will not run in an invalid state: like an assertion, it evaluates an expression
but unlike assertions, it will not fail if the condition is not met, but rather
return silently from the function, optionally with a default value.



## II. Structure of the project


The features of the project are declared in several sets of headers, all inside
the directory `inc`.


### 1. Common header: `cute.h`

This header contains common declarations for the project (like function
attributes) and is included by all the headers in the project. However, it can
also be used to include the whole project if `#include`d directly.


### 2. Assertions: `cute_assert.h`

This header declares:
 - the two types of assertions, `CUTE_runTimeAssert(cond)` and
   `CUTE_compileTimeAssert(cond, message)` as macros,
 - the assumptions, `CUTE_assume(cond)` for a `void` function and
   `CUTE_assumeValue(cond, value)` for a function with a return type, and
 - the function `CUTE_fail()` that fails unconditionally by sending an abort
   signal (this is the function called in `CUTE_runTimeAssert`).


### 3. Test headers: `cute_test.h`

This header is to be included to provide the declarations of unit tests and
related: test cases, test suites.
These declarations are spread across different sub-headers, but those are all
dependent on `cute_test.h` and can not be `#include`d directly.

#### a) Test results: `cute_result.h`

This header declares:
 - the enumeration `CUTE_TestStatus`, that contains several
   constants to describe the status of a test after execution (see III.1),
 - the structure `CUTE_TestResult`, that contains the information about a test
   after it has been executed,
 - the structure `CUTE_RunResults`, that contains the results of all the tests
   in a case after its execution.
 - two functions to allocate and free, respectively, an instance of
   `CUTE_RunResults` to the adequate size.

### b) Test case: `cute_case.h`

This header declares the structure `CUTE_TestCase`, defined opaquely in
`src/cute_case.c` and functions to manipulate the structure.

### c) Test suite: `cute_suite.h`

This header declare the structure `CUTE_TestSuite` defined opaquely in
`src/cute_suite.c` and functions to operate on it.

### d) Test loggers: `cute_log.h`

This header declares an interface to log the results of the tests run in a file,
or on `stdout` by default. An enumeration controls the format of the output:
simple text, XML, or enhanced console output (box-drawing characters and ANSI
color codes). See IV. for more details.



## III. Running tests


### 1. Different test statutes

The enumeration `CUTE_TestStatus` provides a consequent number of possible
outcomes for a test:
 - *success*, the test passed without error
 - *failure*, an assertion failed inside the test
 - *error*, an error was detected in the test (zero division, floating-point
   error),
 - *ignored*, the test was not run (see after)
 - *skipped*, exectuion of the test was stopped by the user (see 3.)
 - *canceled*, the whole test case was canceled (see 4.)


### 2. Ignoring tests

A test procedure whose name starts with an uppercase `I` will not be executed;
its status will be `CUTE_STATUS_IGNORED` in the result structure.
Therefore, if a test has to be ignored at any time, prepending its declared name
with an `I` will suffice to not run it.


### 3. Skipping tests

A single running test can be stopped when the program receives a `SIGTSTP`
signal. Therefore,  when run interactively on console, a test can be skipped by
hitting Ctrl-Z.

*NOTE*: Actually, typing Ctrl-Z sends a `SIGTSTP` signal, *and* sends the
process to the background -- to return it to the foreground the user has to
enter `fg` afterwards.


### 4. Cancelling tests

Running of a whole test case can be stopped on reception of a signal `SIGINT` or
`SIGQUIT`; so, when run from a terminal emulator, hitting Ctrl-C or Ctrl-\ will
cancel the running test case.

*NOTE*: it is planned to implement the stopping of the whole program on a
`SIGQUIT`, not just the running test case.

When a test case is canceled, all the pending tests are marked as canceled too,
and the `terminate` function is still called before the case returns.



## IV. Logging results


The header `cute_log.h` provides the function `CUTE_logResults`, that prints the
test results it is given in a file with specified format; the format is taken
from the enumeration `CUTE_LogFormat`. The results are given as two parameters:
first, an integer defined as the size of the next parameter, an array of
constant pointers to `CUTE_RunResults` instances. The given file must be a valid
file handle (*stdio*'s `FILE*`) and be opened for writing.



## V. Technicals


### 1. Portability and standards compliance

The project is currently designed for GNU/Linux platforms, it was compiled using
GCC but should work fine with any POSIX- and C11-compliant compiler.


### 2. Compile and install

You can compile the project by running:

    make

and install it with:

    make install

possibly with `sudo` rights.


### 3. Test and use case example

To test the project, simply run:

    make test

The directory `test` contains a test program of the project, and can serve in
the same time as an example on how to use the different structures of the
project.
