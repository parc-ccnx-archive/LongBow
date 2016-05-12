/*
 * Copyright (c) 2013-2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
/**
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#include <LongBow/unit-test.h>

#include <LongBow/longBow_TestRunner.h>
#include <LongBow/longBow_Properties.h>

#include <LongBow/private/longBow_String.h>
#include <LongBow/private/longBow_Memory.h>
#include <LongBow/private/longBow_ArrayList.h>

struct LongBowTestRunner {
    const char *name; /**< The name of this LongBow test runner. */

    LongBowStatus (*testRunnerSetup)(LongBowTestRunner *); /**< The Test Runner Setup function */

    void (*testRunner)(LongBowTestRunner *); /**< The Test Case Runner function */

    LongBowStatus (*testRunnerTearDown)(LongBowTestRunner *); /**< The Test Runner TearDown function */

    LongBowArrayList *fixtures; /**< The  LongBowTestFixtures of this Test Runner */

    LongBowConfig *configuration; /**< The LongBowConfiguration for this Test Runner. */

    /**
     * The clipboard of information shared between the fixture setup,
     * the test case, and the fixture tear-down.
     */    
    LongBowClipBoard *clipBoard;
};

void
longBowTestRunner_ConfigHelp(void)
{
    printf("Test Runner options:\n");
    printf("  --set <testRunnerName>/iterations=<count>  Run the named test runner <count> times\n");
}

bool
longBowTestRunner_Config(LongBowConfig *config, const char *parameter)
{
    bool result = false;
    LongBowArrayList *tokens = longBowString_Tokenise(parameter, "-=");
    if (tokens != NULL) {
        if (longBowArrayList_Length(tokens) == 2) {
            result = longBowConfig_SetProperty(config, longBowArrayList_Get(tokens, 0), longBowArrayList_Get(tokens, 1));
        }
        longBowArrayList_Destroy(&tokens);
    }
    return result;
}

const char *
longBowTestRunner_GetName(const LongBowTestRunner *testRunner)
{
    assert(testRunner != NULL);
    return testRunner->name;
}

void
longBowTestRunner_AddFixture(LongBowTestRunner *testRunner, LongBowTestFixture *testFixture)
{
    longBowArrayList_Add(testRunner->fixtures, testFixture);
}

LongBowTestRunner *
longBowTestRunner_Create(const char *name,
                         LongBowTestRunnerSetUp *setup,
                         LongBowTestRunnerRun *runner,
                         LongBowTestRunnerTearDown *tearDown)
{
    LongBowTestRunner *testRunner = longBowMemory_Allocate(sizeof(LongBowTestRunner));

    if (testRunner != NULL) {
        testRunner->name = name;
        testRunner->testRunnerSetup = setup;
        testRunner->testRunner = runner;
        testRunner->testRunnerTearDown = tearDown;
        testRunner->fixtures = longBowArrayList_Create((void (*)(void **)) longBowTestFixture_Destroy);
        testRunner->clipBoard = longBowClipBoard_Create();
    }
    return testRunner;
}

void
longBowTestRunner_Destroy(LongBowTestRunner **testRunnerPtr)
{
    if (testRunnerPtr != NULL) {
        LongBowTestRunner *testRunner = *testRunnerPtr;

        longBowArrayList_Destroy(&testRunner->fixtures);
        if (testRunner->clipBoard) {
            longBowClipBoard_Destroy(&testRunner->clipBoard);
        }
        if (testRunner != NULL) {
            longBowMemory_Deallocate((void **) testRunnerPtr);
        }
    }
}

LongBowTestRunner *
longBowTestRunner_Run(LongBowTestRunner *testRunner)
{
    LongBowConfig *configuration = longBowTestRunner_GetConfiguration(testRunner);
    unsigned long iterations = longBowConfig_GetUint32(configuration, 1,
                                                       "%s/iterations", longBowTestRunner_GetName(testRunner));

    if (longBowConfig_IsTrace(configuration)) {
        longBowReportTesting_Trace("%s: setup", longBowTestRunner_GetName(testRunner));
    }
    LongBowStatus setupStatus = (*testRunner->testRunnerSetup)(testRunner);

    if (setupStatus != LONGBOW_STATUS_SETUP_SKIPTESTS) {
        if (!longBowStatus_IsSuccessful(setupStatus)) {
            char *statusString = longBowStatus_ToString(setupStatus);
            printf("Warning: %s setup returned: %s.\n", testRunner->name, statusString);
            free(statusString);
            return testRunner;
        }

        for (unsigned long i = 0; i < iterations; i++) {
            if (longBowConfig_IsTrace(configuration)) {
                longBowReportTesting_Trace("%s: run", longBowTestRunner_GetName(testRunner));
            }
            (*testRunner->testRunner)(testRunner);
        }

        if (longBowConfig_IsTrace(configuration)) {
            longBowReportTesting_Trace("%s: tear-down", longBowTestRunner_GetName(testRunner));
        }

        LongBowStatus tearDownStatus = (*testRunner->testRunnerTearDown)(testRunner);
        if (!longBowStatus_IsSuccessful(tearDownStatus)) {
            char *statusString = longBowStatus_ToString(tearDownStatus);
            printf("Warning: %s tear-down returned: %s.\n", testRunner->name, statusString);
            free(statusString);
            return testRunner;
        }
    }

    return testRunner;
}

char *
longBowTestRunner_ToString(const LongBowTestRunner *runner)
{
    LongBowString *string = longBowString_CreateFormat("%s", longBowTestRunner_GetName(runner));

    char *cString = longBowString_ToString(string);
    longBowString_Destroy(&string);
    return cString;
}

LongBowTestFixture *
longBowTestRunner_GetFixture(const LongBowTestRunner *testRunner, size_t index)
{
    return longBowArrayList_Get(testRunner->fixtures, index);
}

size_t
longBowTestRunner_GetFixtureCount(const LongBowTestRunner *testRunner)
{
    return longBowArrayList_Length(testRunner->fixtures);
}

LongBowConfig *
longBowTestRunner_GetConfiguration(const LongBowTestRunner *testRunner)
{
    return testRunner->configuration;
}

LongBowStatus
longBowTestRunner_GetStatus(const LongBowTestRunner *testRunner)
{
    LongBowStatus result = LONGBOW_STATUS_SUCCEEDED;

    // Just return the status of the first non-successful Test Fixture.
    size_t nTestFixtures = longBowTestRunner_GetFixtureCount(testRunner);
    for (size_t i = 0; i < nTestFixtures; i++) {
        LongBowTestFixture *fixture = longBowTestRunner_GetFixture(testRunner, i);
        if (!longBowTestFixture_IsSuccessful(fixture)) {
            result = longBowTestFixture_GetStatus(fixture);
            break;
        }
    }
    return result;
}

bool
longBowTestRunner_IsSuccessful(const LongBowTestRunner *testRunner)
{
    return longBowStatus_IsSuccessful(longBowTestRunner_GetStatus(testRunner));
}

bool
longBowTestRunner_IsFailed(const LongBowTestCase *testCase)
{
    return longBowStatus_IsFailed(longBowTestCase_GetStatus(testCase));
}

bool
longBowTestRunner_IsWarning(const LongBowTestRunner *testCase)
{
    return longBowStatus_IsWarning(longBowTestRunner_GetStatus(testCase));
}

bool
longBowTestRunner_IsIncomplete(const LongBowTestCase *testCase)
{
    return longBowStatus_IsIncomplete(longBowTestCase_GetStatus(testCase));
}

void
longBowTestRunner_SetConfiguration(LongBowTestRunner *testRunner, LongBowConfig *config)
{
    testRunner->configuration = config;
}

LongBowClipBoard *
longBowTestRunner_GetClipBoard(const LongBowTestRunner *testRunner)
{
    return testRunner->clipBoard;
}

bool
longBowTestRunner_SetClipBoardData(const LongBowTestRunner *testRunner, void *shared)
{
    return longBowClipBoard_Set(longBowTestRunner_GetClipBoard(testRunner), "testRunner", shared);
}

void *
longBowTestRunner_GetClipBoardData(const LongBowTestRunner *testRunner)
{
    return longBowClipBoard_Get(longBowTestRunner_GetClipBoard(testRunner), "testRunner");
}
