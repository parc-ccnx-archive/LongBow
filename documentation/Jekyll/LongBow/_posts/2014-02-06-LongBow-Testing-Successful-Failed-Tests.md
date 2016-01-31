---
layout: responsive
title: Testing for Successful Failure
categories: toplevel
---

Testing for success is normally straightforward,
and oftentimes test that something fails is important.

This section describes how to specify that a test has an expected result,
and if the actual result is the expected result,
it passes.

To compose a test case that expects a result other than success,
use the `LONGBOW_TEST_CASE_EXPECTS` and assigning the `.event`
structure member explicitly specifying the expected event.

{% highlight c %}
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

#include <LongBow/unit-test.h>

LONGBOW_TEST_RUNNER(LongBow)
{
	LONGBOW_RUN_TEST_FIXTURE(MyFixture);
}

LONGBOW_TEST_RUNNER_SETUP(LongBow)
{
	return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_RUNNER_TEARDOWN(LongBow)
{
	return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(MyFixture)
{
	LONGBOW_RUN_TEST_CASE(MyFixture, alwaysSEGV);
}

LONGBOW_TEST_FIXTURE_SETUP(MyFixture)
{
	return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(MyFixture)
{
	return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE_EXPECTS(MyFixture, alwaysSEGV, .event = &LongBowEventSIGSEGV)
{
	int *p = 0;
	int i = *p;
}

int
main(int argc, char *argv[])
{
	LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(LongBow);
	int status = LONGBOW_TEST_MAIN(argc, argv, testRunner, NULL);
	longBowTestRunner_Destroy(&testRunner);

	exit(status);
}
{% endhighlight %}