/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @file longBow_RuntimeResult.h
 * @ingroup internals
 * @brief LongBow Test Case Results
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 *
 * LongBow Test Cases have expected and actual results.
 * The expected results are typically a statically created instance of {@link LongBowRuntimeResult}
 * which is used when the Test Case is executed to compare with the actual results.
 * This permits, for example, a Test Case to indicate that it is expected to induce a specific LongBowEvent.
 * In which case, the actual LongBowEvent must equal the expected event for the Test Case to be considered a success.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_CaseResult_h
#define LongBow_longBow_CaseResult_h

#include <stdlib.h>
#include <stdint.h>
#include <sys/resource.h>

#include <LongBow/longBow_Status.h>
#include <LongBow/longBow_Event.h>

struct longbow_testcase_result;

/**
 * @typedef LongBowRuntimeResult
 * @brief The expected and actual result of a LongBow Test.
 */
typedef struct longbow_testcase_result LongBowRuntimeResult;

/**
 * @struct longbow_testcase_result
 * @brief The expected and actual result of a LongBow Test.
 */
struct longbow_testcase_result {
    /**
     * The number of event evaluations performed.
     * These asserts and traps with conditions that were evaluated.
     */
    size_t eventEvaluationCount;
    LongBowStatus status;           /**< The resulting status of the test case. */
    struct timeval elapsedTime;     /**< The elapsed time of the test case. */
    struct rusage resources;        /**< The resulting resource usage of the test case. */
    LongBowEventType *event;        /**< The expected or actual event. */
};

/**
 * Return the event evaluation count associated with the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 *
 * @return The number of Event evaluations.
 */
size_t longBowRuntimeResult_GetEventEvaluationCount(const LongBowRuntimeResult *testCaseResult);

/**
 * Retrieve the event type associated with the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 *
 * @return The LongBowEventType for the given LongBowRuntimeResult.
 */
LongBowEventType *longBowRuntimeResult_GetEvent(const LongBowRuntimeResult *testCaseResult);

/**
 * Set the event type associated with the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 * @param [in] eventType A new `LongBowEventType` instance.
 */
void longBowRuntimeResult_SetEvent(LongBowRuntimeResult *testCaseResult, LongBowEventType *eventType);

/**
 * Get the LongBowStatus type from the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 *
 * @return The LongBowStatus of the given LongBowRuntimeResult.
 */
LongBowStatus longBowRuntimeResult_GetStatus(const LongBowRuntimeResult *testCaseResult);

/**
 * Set the LongBowStatus type for the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 * @param [in] status A `LongBowStatus` value.
 */
void longBowRuntimeResult_SetStatus(LongBowRuntimeResult *testCaseResult, LongBowStatus status);

/**
 * Set the elapsed time for the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 * @param [in] elapsedTime A `struct timeval` instance.
 */
void longBowRuntimeResult_SetElapsedTime(LongBowRuntimeResult *testCaseResult, struct timeval *elapsedTime);

/**
 * Get the elapsed time associated with the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 *
 * @return A copy of the timeval of the given LongBowRuntimeResult.
 */
struct timeval longBowRuntimeResult_GetElapsedTime(const LongBowRuntimeResult *testCaseResult);

/**
 * Retrieve the RUsage struct from the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 *
 * @return A pointer to the struct rusage instance in the given LongBowRuntimeResult.
 */
struct rusage *longBowRuntimeResult_GetRUsage(LongBowRuntimeResult *testCaseResult);

/**
 * Set the RUsage struct for the given `LongBowRuntimeResult` instance.
 *
 * @param [in] testCaseResult A `LongBowRuntimeResult` instance.
 * @param [in] rusage A `struct rusage` instance.
 */
void longBowRuntimeResult_SetRUsage(LongBowRuntimeResult *testCaseResult, struct rusage *rusage);
#endif
