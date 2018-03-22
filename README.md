# CUTE
## C Unit Testing Environment

This project defines a *[xUnit](https://en.wikipedia.org/wiki/XUnit)*-like unit
testing environment in C.

A test is a no-parameter procedure, designed to execute the feature under test
in a specific state. The tests are supposed independent, the order of 
execution of the tests is not certified to follow the order of insertion in
the test case. Actually, an upcoming feature of the project is to execute the
tests in parallel, using the `pthread` library. Indenpendence of the 
tests can be achieved using the `setUp` and `tearDown` functions, whose
purpose is to prepare the testing environment before each test, and  clean it
afterwards.
