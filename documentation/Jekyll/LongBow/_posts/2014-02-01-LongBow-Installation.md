---
layout: responsive
title: Installation, Configuration, and Running
categories: toplevel
---

How to install, configure, link, and run LongBow.

## Installation

## Configuration
### LongBow with LLDB

The `lldb` debugger is aware when C files are included.
This induces a problem where the breakpoints in the included files are not set.
But you can configure lldb to set them:
In ~/.lldbinit
settings set target.inline-breakpoint-strategy always

{% highlight c %}
settings set target.inline-breakpoint-strategy always
{% endhighlight %}

### LongBow with GDB

LongBow uses signals to interrupt program flow when an assertion fails.
When using `gdb` this will cause `gdb` to stop running of the test.
This probably isn't what you want and would rather prefer that `gdb`
just ignore the signal and let the LongBow unit test signal handler take care of the signal.
To do this, you must configure `gdb` to ignore the signal and to allow it to pass to the programme being executed.

{% highlight c %}
handle 6 nostop pass
{% endhighlight %}

### Linking and Libraries

There are two LongBow libraries that you must link with your application:
The primary LongBow library, `liblongbow.a` and a LongBow reporter library
which is an implementation of a reporting mechanism for LongBow.

Common LongBow reporter libraries are: `liblongbow-plaintext.a` and `liblongbow-ansiterm.a`
both of which are complete implementations of a reporting library that display the reported information to 
the standard output.  The library `liblongbow-plaintext.a` displays output as simple text
and `liblongbow-ansiterm.a` displays output as an ANSI colorized output.

### Running and Runtime Behavior

Running LongBow means you are running your application that is using the LongBow runtime to
test assertions during runtime,
or you've written a LongBow test using the normal LongBow test runtime.

