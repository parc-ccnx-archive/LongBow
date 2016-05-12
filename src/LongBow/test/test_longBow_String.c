/*
 * Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this section is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this section contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this section is complete, up to date or accurate. It
 * # is up to the contributors to maintain their portion of this section and up to
 * # the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this section must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 *
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */

// Include the file(s) containing the functions to be tested.
// This permits internal static functions to be visible to this Test Runner.
#include <stdio.h>
#include <inttypes.h>

#include "../private/longBow_String.c"

#include <LongBow/unit-test.h>

LONGBOW_TEST_RUNNER(longBow_String)
{
    // The following Test Fixtures will run their corresponding Test Cases.
    // Test Fixtures are run in the order specified here, but every test must be idempotent.
    // Never rely on the execution order of tests or share state between them.
    LONGBOW_RUN_TEST_FIXTURE(Global);
    LONGBOW_RUN_TEST_FIXTURE(Static);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(longBow_String)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(longBow_String)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, longBowString_Create);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_Append);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_Append_Append);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_Format);

    LONGBOW_RUN_TEST_CASE(Global, longBowString_StartsWith_True);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_StartsWith_False);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_Tokenise);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_Tokenise_empty);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_Tokenise_NULL);
    LONGBOW_RUN_TEST_CASE(Global, longBowString_CoreDump);
}

static uint64_t _outstandingAllocations;

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    _outstandingAllocations = longBowMemory_OutstandingAllocations();
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    if (longBowMemory_OutstandingAllocations() > _outstandingAllocations) {
        printf("%s: memory leak\n", longBowTestCase_GetName(testCase));
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, longBowString_Create)
{
    LongBowString *string = longBowString_Create(128);
    assertNotNull(string, "Expected non-NULL result from longBowString_Create");

    longBowString_Destroy(&string);
    assertNull(string, "Expected the instance pointer to be NULL after longBowString_Destroy");
}

LONGBOW_TEST_CASE(Global, longBowString_Append)
{
    char *expected = "Hello World";
    LongBowString *string = longBowString_Create(0);
    longBowString_Append(string, expected);

    assertTrue(strcmp(expected, string->buffer) == 0,
               "Expected buffer to contain '%s', actual '%s'", expected, string->buffer);
    longBowString_Destroy(&string);
}

LONGBOW_TEST_CASE(Global, longBowString_Append_Append)
{
    char *expected = "Hello World";
    LongBowString *string = longBowString_Create(0);
    longBowString_Append(string, "Hello");
    longBowString_Append(string, " ");
    longBowString_Append(string, "World");

    assertTrue(strcmp(expected, string->buffer) == 0,
               "Expected buffer to contain '%s', actual '%s'", expected, string->buffer);
    longBowString_Destroy(&string);
}

LONGBOW_TEST_CASE(Global, longBowString_Format)
{
    char *expected = "Hello World";
    LongBowString *string = longBowString_Create(0);
    longBowString_Format(string, "%s", expected);

    assertTrue(strcmp(expected, string->buffer) == 0,
               "Expected buffer to contain '%s', actual '%s'", expected, string->buffer);
    longBowString_Destroy(&string);
}

LONGBOW_TEST_CASE(Global, longBowString_StartsWith_True)
{
    bool actual = longBowString_StartsWith("abcde", "abc");
    assertTrue(actual, "Expected true");
}

LONGBOW_TEST_CASE(Global, longBowString_StartsWith_False)
{
    bool actual = longBowString_StartsWith("abcde", "ayz");

    assertFalse(actual, "Expected false");
}

LONGBOW_TEST_CASE(Global, longBowString_Tokenise)
{
    LongBowArrayList *actual = longBowString_Tokenise("--t.x=10", "-=");

    assertTrue(strcmp("t.x", longBowArrayList_Get(actual, 0)) == 0,
               "Expected first token to be t.x, actual %s", (char *) longBowArrayList_Get(actual, 0));
    assertTrue(strcmp("10", longBowArrayList_Get(actual, 1)) == 0,
               "Expected first token to be 10, actual %s", (char *) longBowArrayList_Get(actual, 1));

    longBowArrayList_Destroy(&actual);
}

LONGBOW_TEST_CASE(Global, longBowString_Tokenise_empty)
{
    LongBowArrayList *actual = longBowString_Tokenise("", "-=");

    assertTrue(longBowArrayList_Length(actual) == 0, "Expected zero length LongBowArrayList, actual %zd", longBowArrayList_Length(actual));

    longBowArrayList_Destroy(&actual);
}

LONGBOW_TEST_CASE(Global, longBowString_Tokenise_NULL)
{
    LongBowArrayList *actual = longBowString_Tokenise(NULL, "-=");

    assertTrue(longBowArrayList_Length(actual) == 0, "Expected zero length LongBowArrayList, actual %zd", longBowArrayList_Length(actual));

    longBowArrayList_Destroy(&actual);
}

LONGBOW_TEST_CASE(Global, longBowString_CoreDump)
{
    //assertFalse(true, "foo");
}

LONGBOW_TEST_FIXTURE(Static)
{
}

LONGBOW_TEST_FIXTURE_SETUP(Static)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Static)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

int
main(int argc, char *argv[])
{
    LongBowTestRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(longBow_String);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
