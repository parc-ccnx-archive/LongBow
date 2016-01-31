/*
 * Copyright (c) 2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
 * All rights reserved.
 *  
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution. 
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <LongBow/testing.h>

LONGBOW_TEST_RUNNER(longBow_Status)
{
    // The following Test Fixtures will run their corresponding Test Cases.
    // Test Fixtures are run in the order specified, but all tests should be idempotent.
    // Never rely on the execution order of tests or share state between them.
    LONGBOW_RUN_TEST_FIXTURE(Global);
    LONGBOW_RUN_TEST_FIXTURE(Local);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(longBow_Status)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(longBow_Status)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, longBowStatus_ToString);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, longBowStatus_ToString)
{
    char *expected;
    char *actual;

    expected = "Succeeded";
    actual = longBowStatus_ToString(LONGBOW_STATUS_SUCCEEDED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Warning";
    actual = longBowStatus_ToString(LongBowStatus_WARNED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Tear Down Warning";
    actual = longBowStatus_ToString(LongBowStatus_TEARDOWN_WARNED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Skipped";
    actual = longBowStatus_ToString(LONGBOW_STATUS_SKIPPED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Unimplemented";
    actual = longBowStatus_ToString(LongBowStatus_UNIMPLEMENTED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Impotent";
    actual = longBowStatus_ToString(LongBowStatus_IMPOTENT);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Failed";
    actual = longBowStatus_ToString(LONGBOW_STATUS_FAILED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Stopped";
    actual = longBowStatus_ToString(LongBowStatus_STOPPED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Tear Down Failed";
    actual = longBowStatus_ToString(LONGBOW_STATUS_TEARDOWN_FAILED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Setup Failed";
    actual = longBowStatus_ToString(LONGBOW_STATUS_SETUP_FAILED);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    expected = "Memory Leak";
    actual = longBowStatus_ToString(LONGBOW_STATUS_MEMORYLEAK);
    assertTrue(strcmp(expected, actual) == 0, "Expected '%s', actual '%s'", expected, actual);
    free(actual);

    actual = longBowStatus_ToString(LongBowStatus_SIGNALLED + 1);
    assertNotNull(actual, "Expected longBowStatus_ToString to return non-null value");
    free(actual);
}

LONGBOW_TEST_FIXTURE(Local)
{
}

LONGBOW_TEST_FIXTURE_SETUP(Local)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Local)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

int
main(int argc, char *argv[])
{
    LongBowTestRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(longBow_Status);
    int exitStatus = LONGBOW_TEST_MAIN(argc, argv, testRunner);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
