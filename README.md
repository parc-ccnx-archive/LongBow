LongBow
=======
# Longbow #
_The Best Defense is a Good Offense_

## Introduction ##

LongBow is a C language software framework that combines the fail-fast philosophy of an offensive-stance of program development and xUnit style unit testing.

Using LongBow's to aid an offensive-development stance is largely a matter of using its entry and exit assertions in your code.  Similarly using LongBow's unit-test framework uses the same entry and exit assertions in the unit test cases themselves.  Taken together, the runtime assertions and the unit-test assertions work together in the unit test framework and do not conflict.

This framework grew out of the need for a unit test framework for Test Driven Development on the CCN Application Programming Interface.

Two other test frameworks were considered and used to develop unit tests: Unity and GoogleTest.  Ultimately Unity wash't used (although this framework is indebted to Unity for inspiration) mainly due to ease-of-use problems, and Googletest was not used mainly because it is a C++ framework and is not compatible with some features of C99, and is difficult to use.

### GDB and LongBow ###
LongBow uses signals to interrupt program flow when an assertion fails.
When using `gdb` this will cause `gdb` to stop running of the test which probably isn't what you want.
You probably would prefer that gdb just ignore the signal and let the LongBow unit test signal handler take care of the signal.
To do this, you must configure `gdb` to ignore the signal and to allow it to pass to the programme being executed.

handle 6 nostop pass

## Getting Started ##

Build and install LongBow by executing
```
mkdir build
cmake ..
make
make install
make test
```

This will create the `include` and `lib` directories containing the necessary files to compile with LongBow.

### Compiling ###

Using LongBow

```
LONGBOW=<directory-where-longbow-is-installed>
 -I${LONGBOW}/include -L${LONGBOW}/lib -llongbow -llongbow_textplain.a
```

### License ###

This software is distributed under the following license:

```
Copyright (c) 2013, 2014, 2015, 2016, Xerox Corporation (Xerox)and Palo Alto
Research Center (PARC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Patent rights are not granted under this agreement. Patent rights are
  available under FRAND terms.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
