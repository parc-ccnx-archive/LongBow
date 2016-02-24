/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @copyright 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <sys/time.h>

#include <LongBow/longBow_RuntimeResult.h>

size_t
longBowRuntimeResult_GetEventEvaluationCount(const LongBowRuntimeResult *testCaseResult)
{
    return testCaseResult->eventEvaluationCount;
}

LongBowEventType *
longBowRuntimeResult_GetEvent(const LongBowRuntimeResult *testCaseResult)
{
    return testCaseResult->event;
}

void
longBowRuntimeResult_SetEvent(LongBowRuntimeResult *testCaseResult, LongBowEventType *eventType)
{
    testCaseResult->event = eventType;
}

void
longBowRuntimeResult_SetStatus(LongBowRuntimeResult *testCaseResult, LongBowStatus status)
{
    testCaseResult->status = status;
}
void
longBowRuntimeResult_SetElapsedTime(LongBowRuntimeResult *testCaseResult, struct timeval *elapsedTime)
{
    testCaseResult->elapsedTime = *elapsedTime;
}

struct rusage *
longBowRuntimeResult_GetRUsage(LongBowRuntimeResult *testCaseResult)
{
    return &testCaseResult->resources;
}

void
longBowRuntimeResult_SetRUsage(LongBowRuntimeResult *testCaseResult, struct rusage *resources)
{
    testCaseResult->resources = *resources;
}

LongBowStatus
longBowRuntimeResult_GetStatus(const LongBowRuntimeResult *testCaseResult)
{
    return testCaseResult->status;
}

struct timeval
longBowRuntimeResult_GetElapsedTime(const LongBowRuntimeResult *testCaseResult)
{
    return testCaseResult->elapsedTime;
}
