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
#include "../longBow_MeasureTime.c"

#include <stdint.h>
#include <inttypes.h>
#include <LongBow/private/longBow_Memory.h>
#include <LongBow/unit-test.h>

LONGBOW_TEST_RUNNER(longBow_MeasureTime)
{
    // The following Test Fixtures will run their corresponding Test Cases.
    // Test Fixtures are run in the order specified here, but every test must be idempotent.
    // Never rely on the execution order of tests or share state between them.
    LONGBOW_RUN_TEST_FIXTURE(Global);
    LONGBOW_RUN_TEST_FIXTURE(Static);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(longBow_MeasureTime)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(longBow_MeasureTime)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, longBowMeasureTime_CountDown);
    LONGBOW_RUN_TEST_CASE(Global, longBowMeasureTime_Report);
    LONGBOW_RUN_TEST_CASE(Global, longBowMeasureTime_Start);
    LONGBOW_RUN_TEST_CASE(Global, longBowMeasureTime_Stop);
    LONGBOW_RUN_TEST_CASE(Global, longBowMeasureTime_Destroy);
    LONGBOW_RUN_TEST_CASE(Global, longBowMeasureTime);
}

uint64_t _setupAllocations;

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

LONGBOW_TEST_CASE(Global, longBowMeasureTime_CountDown)
{
    LongBowMeasureTime *measure = longBowMeasureTime_Start(1);
    assertTrue(measure->iterations == 1, "Expected iterations to be 1, actual %d", measure->iterations);

    longBowMeasureTime_CountDown(measure);
    assertTrue(measure->iterations == 0, "Expected iterations to be 0, actual %d", measure->iterations);

    longBowMeasureTime_Destroy(&measure);
}

LONGBOW_TEST_CASE(Global, longBowMeasureTime_Report)
{
    LongBowMeasureTime *measure = longBowMeasureTime_Start(1);
    assertTrue(measure->iterations == 1, "Expected iterations to be 1, actual %d", measure->iterations);

    longBowMeasureTime_Report(measure, __FILE__, __func__, __LINE__);

    longBowMeasureTime_Destroy(&measure);
}

LONGBOW_TEST_CASE(Global, longBowMeasureTime_Start)
{
    LongBowMeasureTime *measure = longBowMeasureTime_Start(1);
    assertNotNull(measure, "Expected longBowMeasureTime_Start to return non-NULL result.");

    longBowMeasureTime_Destroy(&measure);
}

LONGBOW_TEST_CASE(Global, longBowMeasureTime_Stop)
{
    LongBowMeasureTime *measure = longBowMeasureTime_Start(1);
    assertNotNull(measure, "Expected longBowMeasureTime_Start to return non-NULL result.");
    sleep(2);
    longBowMeasureTime_Stop(measure);

    uint64_t nanos = longBowMeasureTime_GetNanoseconds(measure);
    assertTrue(nanos >= 1000000000ULL, "Expected more than 1,000,000 ns to have elapsed.");

    longBowMeasureTime_Destroy(&measure);
}

LONGBOW_TEST_CASE(Global, longBowMeasureTime_Destroy)
{
    LongBowMeasureTime *measure = longBowMeasureTime_Start(1);
    assertNotNull(measure, "Expected longBowMeasureTime_Start to return non-NULL result.");

    longBowMeasureTime_Destroy(&measure);
    assertNull(measure, "Expected longBowMeasureTime_Destroy to NULL the pointer.");
}

LONGBOW_TEST_CASE(Global, longBowMeasureTime)
{
    longBowMeasureTime(1) {
        sleep(2);
    }
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
    LongBowTestRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(longBow_MeasureTime);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
