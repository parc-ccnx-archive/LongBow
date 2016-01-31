---
layout: article
title: Sharing Test State With Fixture Setup and Tear Down
categories:
- testing
---

Every test case has associated with it a private "clipboard" that contains data shared
between the test case fixture setup and teardown functions.
This shared state is used to provide specific environment or initialized
variables for the test and for the test to communicate specialized
information to the teardown function.

For example, consider a test case while is expected to fail as the result of testing a failure condition.  
If the test case fails, there is no automatic way to catch and unwind all of the
state that has been established in the test case.
This leads, for example, to memory leaks, file descriptor leaks,
and other resources the must be released after the test is complete.
Especially if the unit tests are run in one process,
the process must continue to run other tests and resource leaks will adversely affect the following tests.
In this example, the test fixture setup function allocates the necessary resources
and puts references to them into the clipboard.
The unit test gets these references, uses them, and fails.
The tear-down function, in turn, obtains the resources from the clipboard and deallocates them.

Here is an example:

{% highlight c %}
#include <stdio.h>
#include <string.h>

#include <LongBow/testing.h>
#include <LongBow/debugging.h>

LONGBOW_TEST_RUNNER(testClipboard)
{
    LONGBOW_RUN_TEST_FIXTURE(Global);
}

LONGBOW_TEST_RUNNER_SETUP(testClipboard)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_RUNNER_TEARDOWN(testClipboard)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, testClipboard);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    char *testData = strdup("Hello World");
    longBowTestCase_SetClipBoardData(testCase, testData, free);
    
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, testClipboard)
{
    char *testData = longBowTestCase_GetClipBoardData(testCase);
    printf("Shared state '%s'\n", testData);
}

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(testClipboard);
    int exitStatus = LONGBOW_TEST_MAIN(argc, argv, testRunner);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
{% endhighlight %}