---
layout: responsive
title: Testing
categories: toplevel
---
LongBow testing is based on the xUnit component model consisting of a test
_runner_ executing one or more test _fixtures_,
each of which run one or more _test cases_.

One implements a set of test cases for the functions in a source file,
another is to organise tests around a C structure and the functions that manipulate that structure.

There are also development models that use unit-test testing as part of the development process.
For example, Test Driven Development (TDD) is a model that co-writes the functionality with the
test for that functionality,
resulting in economical code and a high-degree of code-coverage.

For example, consider testing a very simple file, `minimal.c`, containing a single C function:

{% highlight c %}
int
alwaysSucceed()
{
	return 1;
}
{% endhighlight %}

Code for a fully specified LongBow test is:
{% highlight c %}
#include <LongBow/unit-test.h>

#include "minimal.c"

LONGBOW_TEST_RUNNER(Example1)
{
	LONGBOW_RUN_TEST_FIXTURE(FixtureA);
}

LONGBOW_TEST_RUNNER_SETUP(Example1)
{
	return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_RUNNER_TEARDOWN(Example1)
{
	return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(FixtureA)
{
	LONGBOW_RUN_TEST_CASE(FixtureA, alwaysSucceed);
}

LONGBOW_TEST_FIXTURE_SETUP(FixtureA)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(FixtureA)
{
	return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(FixtureA, alwaysSucceed)
{
	assertTrue(alwaysSucceed(), "This must always succeed.");
}

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(Example1);
    int status = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);

    exit(status);
}
{% endhighlight %}

At first glance this appears to be a lot of code just to write for such a small programme.
However, the bulk of the code is to just setup the runtime environment for the test.
This consists of creating the Test Runner and a Test Fixture (at least one, there may be many Test Fixtures).
In turn, each of these have a setup function and a tear-down function.
In this test programme, these functions simply return success.

<ul id="blog-posts" class="posts">
    {% for post in site.categories.testing %}
      <li>
        <h3><a href="{{ site.baseurl }}{{ post.url }}">&raquo; {{ post.title }}</a></h3>
        <p>{{ post.excerpt }}</p>
      </li>
    {% endfor %}
</ul>
