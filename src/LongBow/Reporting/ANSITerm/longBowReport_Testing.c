/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
/**
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#include <LongBow/Reporting/ANSITerm/longBowReport_Runtime.h>
#include <LongBow/Reporting/longBowReport_Testing.h>
#include <LongBow/private/longBow_String.h>

static const LongBowTestRunner *
_testRunnerSilent(const LongBowTestRunner *testRunner)
{
    LongBowStatus status = longBowTestRunner_GetStatus(testRunner);
    if (longBowStatus_IsSuccessful(status)) {
        longBowReportRuntime_GreenPrintf("%s %s\n", longBowTestRunner_GetName(testRunner), longBowStatus_ToString(status));
    } else if (longBowStatus_IsSuccessful(status)) {
        longBowReportRuntime_YellowPrintf("%s %s\n", longBowTestRunner_GetName(testRunner), longBowStatus_ToString(status));
    } else {
        longBowReportRuntime_RedPrintf("%s %s\n", longBowTestRunner_GetName(testRunner), longBowStatus_ToString(status));
    }
    return testRunner;
}

static const LongBowTestRunner *
_testRunnerDetail(const LongBowTestRunner *testRunner)
{
    size_t nFixtures = longBowTestRunner_GetFixtureCount(testRunner);

    printf("\n");
    printf("%s: %zd fixture%s\n", longBowTestRunner_GetName(testRunner), nFixtures, (nFixtures == 1 ? "" : "s"));

    for (size_t i = 0; i < nFixtures; i++) {
        LongBowTestFixture *fixture = longBowTestRunner_GetFixture(testRunner, i);
        longBowReportTesting_TestFixture(fixture);
    }
    return testRunner;
}

const LongBowTestRunner *
longBowReportTesting_TestRunner(const LongBowTestRunner *testRunner)
{
    if (longBowConfig_GetBoolean(longBowTestRunner_GetConfiguration(testRunner), false, "silent")) {
        return _testRunnerSilent(testRunner);
    } else {
        return _testRunnerDetail(testRunner);
    }
}

static unsigned int
_totalSucceeded(const LongBowTestFixtureSummary *summary)
{
    return summary->totalSucceeded + summary->totalWarned + summary->totalTearDownWarned;
}

static unsigned int
_totalWarned(const LongBowTestFixtureSummary *summary)
{
    return summary->totalWarned + summary->totalTearDownWarned;
}

static unsigned int
_totalFailed(const LongBowTestFixtureSummary *summary)
{
    return summary->totalFailed + summary->totalSignalled + summary->totalStopped + summary->totalTearDownFailed;
}

static unsigned int
_totalIncomplete(const LongBowTestFixtureSummary *summary)
{
    return summary->totalSetupFailed + summary->totalSkipped + summary->totalUnimplemented;
}

static void
_reportSummary(const LongBowTestFixture *testFixture)
{
    const LongBowTestFixtureSummary *summary = longBowTestFixture_GetSummary(testFixture);

    char *fixtureString = longBowTestFixture_ToString(testFixture);

    printf("%s: Ran %u test case%s.", fixtureString, summary->totalTested, summary->totalTested == 1 ? "" : "s");
    free(fixtureString);

    if (summary->totalTested > 0) {
        printf(" %d%% (%d) succeeded", _totalSucceeded(summary) * 100 / summary->totalTested, _totalSucceeded(summary));

        if (_totalWarned(summary) > 0) {
            printf(" %d%% (%d) with warnings", _totalWarned(summary) * 100 / _totalSucceeded(summary), _totalWarned(summary));
        }
        if (_totalFailed(summary) != 0) {
            printf(", %d%% (%d) failed", _totalFailed(summary) * 100 / summary->totalTested, _totalFailed(summary));
        }
        if (_totalIncomplete(summary) > 0) {
            printf(", %d%% (%d) incomplete", _totalIncomplete(summary) * 100 / summary->totalTested, _totalIncomplete(summary));
        }
    }

    printf("\n");
}

const LongBowTestFixture *
longBowReportTesting_TestFixture(const LongBowTestFixture *testFixture)
{
    size_t nTestCases = longBowTestFixture_GetTestCaseCount(testFixture);

    _reportSummary(testFixture);

    for (size_t i = 0; i < nTestCases; i++) {
        LongBowTestCase *testCase = longBowTestFixture_GetTestCase(testFixture, i);
        longBowReportTesting_TestCase(testCase);
    }
    return testFixture;
}

const LongBowTestCase *
longBowReportTesting_TestCase(const LongBowTestCase *testCase)
{
    LongBowRuntimeResult *testCaseResult = longBowTestCase_GetActualResult(testCase);

    char *rusageString = longBowReportRuntime_RUsageToString(longBowRuntimeResult_GetRUsage(testCaseResult));
    char *elapsedTimeString = longBowReportRuntime_TimevalToString(longBowRuntimeResult_GetElapsedTime(testCaseResult));
    char *statusString = longBowStatus_ToString(longBowRuntimeResult_GetStatus(testCaseResult));
    char *testCaseString = longBowTestCase_ToString(testCase);
    
    LongBowString *str = longBowString_CreateFormat("%s %s %s %zd %s\n",
                                                    testCaseString,
                                                    elapsedTimeString,
                                                    rusageString,
                                                    longBowRuntimeResult_GetEventEvaluationCount(longBowTestCase_GetActualResult(testCase)),
                                                    statusString);
    char *string = longBowString_ToString(str);

    if (longBowTestCase_IsFailed(testCase)) {
        longBowReportRuntime_RedPrintf("%s", string);
    } else if (longBowTestCase_IsWarning(testCase)) {
        longBowReportRuntime_YellowPrintf("%s", string);
    } else if (longBowTestCase_IsIncomplete(testCase)) {
        longBowReportRuntime_YellowPrintf("%s", string);
    } else if (longBowTestCase_IsSuccessful(testCase)) {
        longBowReportRuntime_GreenPrintf("%s", string);
    } else {
        longBowReportRuntime_RedPrintf("%s", string);
    }

    free(string);
    free(testCaseString);
    free(statusString);
    free(elapsedTimeString);
    free(rusageString);

    return testCase;
}

void
longBowReportTesting_DisplayTestCaseResult(const LongBowTestCase *testCase __attribute__((unused)))
{
    return;
}

void
longBowReportTesting_Trace(const char *restrict format, ...)
{
    va_list ap;
    va_start(ap, format);
    char *message;
    if (vasprintf(&message, format, ap) == -1) {
        va_end(ap);
        return;
    }
    va_end(ap);

    longBowReportRuntime_MagentaPrintf("%s\n", message);
    fflush(stdout);
    free(message);
}
