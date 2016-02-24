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
/** *
 * @author Glenn Scott <Glenn.Scott@parc.com>, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
// Include the file(s) containing the functions to be tested.
// This permits internal static functions to be visible to this Test Framework.

#include <LongBow/testing.h>
#include <LongBow/debugging.h>

#include <stdio.h>
#include <inttypes.h>

#include <LongBow/longBow_Properties.h>
#include "../private/longBow_Memory.h"

LONGBOW_TEST_RUNNER(test_longBow_Properties)
{
    // The following Test Fixtures will run their corresponding Test Cases.
    // Test Fixtures are run in the order specified, but all tests should be idempotent.
    // Never rely on the execution order of tests or share state between them.
    LONGBOW_RUN_TEST_FIXTURE(Global);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(test_longBow_Properties)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(test_longBow_Properties)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, CreateDestroy);
    LONGBOW_RUN_TEST_CASE(Global, longBowProperties_Set);
    LONGBOW_RUN_TEST_CASE(Global, longBowProperties_Get);
    LONGBOW_RUN_TEST_CASE(Global, longBowProperties_Length);
    LONGBOW_RUN_TEST_CASE(Global, longBowProperties_Exists);
}

static uint64_t _setupAllocations;

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    _setupAllocations = longBowMemory_OutstandingAllocations();
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    uint64_t leaks = longBowMemory_OutstandingAllocations() - _setupAllocations;
    if (leaks != 0) {
        printf("%s leaks %" PRId64 " allocations.\n", longBowTestCase_GetFullName(testCase), leaks);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, CreateDestroy)
{
    LongBowProperties *properties = longBowProperties_Create();
    longBowProperties_Destroy(&properties);
}

LONGBOW_TEST_CASE(Global, longBowProperties_Set)
{
    LongBowProperties *properties = longBowProperties_Create();
    longBowProperties_Set(properties, "name", "value");
    longBowProperties_Destroy(&properties);
}

LONGBOW_TEST_CASE(Global, longBowProperties_Get)
{
    LongBowProperties *properties = longBowProperties_Create();
    char *expected = "value";
    longBowProperties_Set(properties, "name", expected);

    const char *actual = longBowProperties_Get(properties, "name");

    assertTrue(strcmp(expected, actual) == 0, "Expected %s, actual %s", expected, actual);
    longBowProperties_Destroy(&properties);
}

LONGBOW_TEST_CASE(Global, longBowProperties_Length)
{
    LongBowProperties *properties = longBowProperties_Create();
    assertTrue(longBowProperties_Length(properties) == 0, "Expected empty longBowProperties to be 0 length");

    char *expected = "value";
    longBowProperties_Set(properties, "name", expected);
    assertTrue(longBowProperties_Length(properties) == 1, "Expected longBowProperties to be 1 length");

    const char *actual = longBowProperties_Get(properties, "name");

    assertTrue(strcmp(expected, actual) == 0, "Expected %s, actual %s", expected, actual);
    longBowProperties_Destroy(&properties);
}

LONGBOW_TEST_CASE(Global, longBowProperties_Exists)
{
    char *expected = "value";

    LongBowProperties *properties = longBowProperties_Create();
    assertFalse(longBowProperties_Exists(properties, expected), "Expected longBowProperties_Exists to be false");

    longBowProperties_Set(properties, "name", expected);
    assertTrue(longBowProperties_Exists(properties, "name"), "Expected longBowProperties_Exists to be true");

    longBowProperties_Destroy(&properties);
}

int
main(int argc, char *argv[argc])
{
    LongBowTestRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(test_longBow_Properties);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
