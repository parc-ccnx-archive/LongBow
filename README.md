LongBow
=======
_The Best Defense is a Good Offense_

The LongBow C language software framework

# Deprecated Code #
This repository is no longer active.  See the [Community ICN](https://wiki.fd.io/view/Cicn) project
for the latest code.  The [CICN Code Repository](https://github.com/FDio/cicn) should be used for all new projects.

## Quick Start ##
```
$ git clone git@github.com:parc-ccnx-archive/LongBow.git LongBow
$ mkdir LongBow.build
$ cd LongBow.build
$ cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} ../LongBow
$ make
$ make test
$ make install
```

## Introduction ##

LongBow is a C language software framework that combines the fail-fast philosophy of an offensive-stance of program development and xUnit style unit testing.

Using LongBow's to aid an offensive-development stance is largely a matter of using its entry and exit assertions in your code.  Similarly using LongBow's unit-test framework uses the same entry and exit assertions in the unit test cases themselves.  The runtime assertions and the unit-test assertions work together in the unit test framework and do not conflict.

This framework grew out of the need for a unit testing for Test Driven Development on the [CCNx Distillery software distribution](https://github.com/parc-ccnx-archive/CCNx_Distillery).

Two other test frameworks were considered and used to develop unit tests: Unity and GoogleTest.  Ultimately Unity wash't used (although this framework is indebted to Unity for inspiration) mainly due to ease-of-use problems, and Googletest was not used mainly because it is a C++ framework, is not compatible with some features of C99, and is difficult to use.

## Using LongBow ##

### Distillery ###

Libparc is part of [CCNx Distillery](https://github.com/parc-ccnx-archive/CCNx_Distillery). You may want to get the software via that distribution if you want to work on CCNx.

### Platforms ###

Libparc has been tested in:

- Ubuntu 14.04 (x86_64)
- MacOSX 10.10
- MacOSX 10.11

Other platforms and architectures may work.

### Dependencies ###

- c99 (clang / gcc)
- CMake 3.4
- Python 2.7

While the LongBow unit test framework and runtime assertions don't have any unusual requirements other than CMake, the software quality development tools that LongBow provides can make use of the following tools:

- Doxygen
- Uncrustify

If these tools are provided to LongBow, the utility scripts will provide more value to the programmer.

### Getting Started ###

LongBow is built using cmake. You will need to have CMake 3.4 installed in order to build it.

```
Download LongBow
$ git clone git@github.com:parc-ccnx-archive/LongBow.git LongBow

Create build directory
$ mkdir LongBow.build
$ cd LongBow.build

Prepare the build, give an install directory
$ cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} ../LongBow

Compile the software
$ make

Run unit tests
$ make test

Install the software
$ make install
```

This will create the `include` and `lib` directories containing the necessary files to compile with LongBow in the `${INSTALL_DIR}`.


### Using LongBow ###

#### LongBow Lib

To use LongBow in your software you will need to link your programs to the LongBow libraries.  Longbow comes as a set of libraries. A main library and a set of reporting libraries.  Your software will need to link to the main library (`liblongbow`) and one of the reporting libraries.  Currently there are 2 reporting libraries available `longbow-textplain` and `longbow-ansiterm`.

```
LONGBOW_DIR=<directory-where-longbow-is-installed>

-I${LONGBOW_DIR}/include -L${LONGBOW_DIR}/lib -llongbow -llongbow_textplain.a
```

#### LongBow Unit Testing

LongBow unit testing works in conjuction with the LongBow library. Please take a look at the examples and the documentation for information on how to write unit tests.  You can also look at some of the software that uses LongBow for unit testing as examples.  A good starting point would be [Libparc](https://github.com/parc-ccnx-archive/Libparc).

#### LongBow Utilities

LongBow comes with a set of utilities (scripts) to make C programs better. This includes code analysis and reporting tools. You will find these in the `${INSTALL_DIR}/bin` directory. Each of those utilities should come with a `-h` option that will give you online help. For more information please check the LongBow documentation.

### GDB and LongBow ###
LongBow uses signals to interrupt program flow when an assertion fails.
When using `gdb` this will cause `gdb` to stop running of the test which probably isn't what you want.
You probably would prefer that gdb just ignore the signal and let the LongBow unit test signal handler take care of the signal.
To do this, you must configure `gdb` to ignore the signal and to allow it to pass to the programme being executed.

`handle 6 nostop pass`

### Contact ###

### Contact ###

- [LongBow GitHub](https://github.com/parc-ccnx-archive/LongBow)
- [CCNx Website](http://www.ccnx.org/)
- [CCNx Mailing List](https://www.ccnx.org/mailman/listinfo/ccnx/)

### License ###

This software is distributed under the following license:

```
Copyright (c) 2013,2014,2015,2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

################################################################################
#
# PATENT NOTICE
#
# This software is distributed under the BSD 2-clause License (see LICENSE
# file).  This BSD License does not make any patent claims and as such, does
# not act as a patent grant.  The purpose of this section is for each contributor
# to define their intentions with respect to intellectual property.
#
# Each contributor to this source code is encouraged to state their patent
# claims and licensing mechanisms for any contributions made. At the end of
# this section contributors may each make their own statements.  Contributor's
# claims and grants only apply to the pieces (source code, programs, text,
# media, etc) that they have contributed directly to this software.
#
# There is no guarantee that this section is complete, up to date or accurate. It
# is up to the contributors to maintain their portion of this section and up to
# the user of the software to verify any claims herein.
#
# Do not remove this header notification.  The contents of this section must be
# present in all distributions of the software.  You may only modify your own
# intellectual property statements.  Please provide contact information.

- Palo Alto Research Center, Inc
This software distribution does not grant any rights to patents owned by Palo
Alto Research Center, Inc (PARC). Rights to these patents are available via
various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
intellectual property used by its contributions to this software. You may
contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
```
<!-- Start of StatCounter Code for Default Guide -->
<script type="text/javascript">
//<![CDATA[
var sc_project=11081165; 
var sc_invisible=0; 
var sc_security="5698c63a"; 
var scJsHost = (("https:" == document.location.protocol) ?
"https://secure." : "http://www.");
document.write("<sc"+"ript type='text/javascript' src='" +
scJsHost+
"statcounter.com/counter/counter_xhtml.js'></"+"script>");
//]]>
</script>
<noscript>
<div class="statcounter">
<a title="shopify site analytics" href="http://statcounter.com/shopify/"
class="statcounter"><img class="statcounter" src="http://c.statcounter.com/11081165/0/5698c63a/0/" alt="shopify site analytics" />
</a></div></noscript>
<!-- End of StatCounter Code for Default Guide -->

