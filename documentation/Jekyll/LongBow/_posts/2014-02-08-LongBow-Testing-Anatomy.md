---
layout: article
title: Anatomy of a Test
categories:
- testing
---
A LongBow test is divided into three sections.  A _test runner_, a _test fixture_, and a _test case_.

# Test Runner
A test runner is the main, or top-level, executable unit in a test.
It's purpose is to setup whatever global state must be established before any tests are performed,
execute each of the subsidairy test fixtures,
and tear-down the global state that was established during the setup and after the test is executed.

A basic test runner consists of the following.
{% highlight c %}
#include <LongBow/testing.h>

LONGBOW_TEST_RUNNER(myRunner)
{
}

LONGBOW_TEST_RUNNER_SETUP(myRunner)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_RUNNER_TEARDOWN(myRunner)
{
    return LONGBOW_STATUS_SUCCEEDED;
}
{% endhighlight %}

These look like functions, and they are, but are composed via C preprocessor macros due to their complexity and in
encapsulating various other concerns.

Each of these functions has a local variable,
`LongBowRunner *testRunner`.
 See the documentation for `LongBowRunner.h` which specifies the functions that manipulate the `LongBowRunner`.
 
Add test fixtures to the test runner.
For example:
 
{% highlight c %} 
LONGBOW_TEST_RUNNER(myRunner)
{
    LONGBOW_RUN_TEST_FIXTURE(Global);
    LONGBOW_RUN_TEST_FIXTURE(Local);
}
{% endhighlight %}

# Test Fixture
A test fixture is a subcomponent which has the same structure as a test runner.
Like the test runner, it's purpose is to setup whatever state must be established before a test is executed,
execute each of the subsidairy test cases,
and lastly tear-down the state that was established during the setup.

{% highlight c %} 
LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, myTest);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}
{% endhighlight %}

