/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @file longBow_Runtime.h
 * @ingroup runtime
 * @brief The LongBow Runtime support.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Runtime_h
#define LongBow_longBow_Runtime_h

#include <LongBow/longBow_Event.h>
#include <LongBow/longBow_RuntimeResult.h>
#include <LongBow/longBow_Config.h>

struct longbow_runtime;
typedef struct longbow_runtime LongBowRuntime;

/**
 * Create and return a new `LongBowRuntime` instance with the specified `LongBowRuntimeResult` instance.
 *
 * @param [in] expectedResultTemplate A `LongBowRuntimeResult` instance.
 *
 * @return A pointer to an allocated LongBowRuntime instance that must be deallocated via longBowRuntime_Destroy
 */
LongBowRuntime *longBowRuntime_Create(const LongBowRuntimeResult *expectedResultTemplate, LongBowConfig *config);

/**
 * Destroy the `LongBowRuntime` instance.
 *
 * @param [in,out] runtimePtr A pointer to a `LongBowRuntime` instance.
 */
void longBowRuntime_Destroy(LongBowRuntime **runtimePtr);

/**
 * Get the expected test case result from the `LongBowRuntime` instance.
 *
 * @param [in] runtime A `LongBowRuntime` instance.
 *
 * @return A pointer to the expected LongBowRuntimeResult.
 */
LongBowRuntimeResult *longBowRuntime_GetExpectedTestCaseResult(const LongBowRuntime *runtime);

/**
 * Get the actual test case result from the `LongBowRuntime` instance.
 *
 * @param [in] runtime A `LongBowRuntime` instance.
 *
 * @return A pointer to the actual LongBowRuntimeResult.
 */
LongBowRuntimeResult *longBowRuntime_GetActualTestCaseResult(const LongBowRuntime *runtime);

/**
 * Get the number of events that were evalutated.
 *
 * @param [in] runtime A `LongBowRuntime` instance.
 *
 * @return The number of events that were evalutated.
 */
size_t longBowRuntime_GetActualEventEvaluationCount(LongBowRuntime *runtime);

/**
 * Get the LongBowEventType of the given LongBowRuntime.
 *
 * @param [in] runtime A `LongBowRuntime` instance.
 *
 * @return The LongBowEventType of the given LongBowRuntime.
 */
LongBowEventType *longBowRuntime_GetActualEventType(const LongBowRuntime *runtime);

/**
 * Get the expected EventType from the given LongBowRuntime.
 *
 * When testing, a test may set a LongBowEventType that is expected to be triggered.
 * This function simply gets the expected LongBowEventType from the given LongBowRuntime instance.
 *
 * @param [in] runtime A pointer to a LongBowRuntime instance.
 *
 * @return The expected EventType in the LongBowRuntime.
 */
LongBowEventType *longBowRuntime_GetExpectedEventType(const LongBowRuntime *runtime);

/**
 * Set the "actual" LongBowEventType of the given LongBowRuntime.
 *
 * @param [in] runtime A `LongBowRuntime` instance.
 * @param [in] eventType A `LongBowEventType` instance.
 */
void longBowRuntime_SetActualEventType(LongBowRuntime *runtime, LongBowEventType *eventType);

/**
 * Set the current `LongBowRuntime`.
 *
 * @param [in] runtime A `LongBowRuntime` instance.
 *
 * @return The previous LongBowRuntime
 */
LongBowRuntime *longBowRuntime_SetCurrentRuntime(LongBowRuntime *runtime);

/**
 * Retrieve the current `LongBowRuntime`.
 *
 * @return The current global LongBowRuntime.
 */
LongBowRuntime *longBowRuntime_GetCurrentRuntime(void);

/**
 * Retrieve the `LongBowConfig` instance of the current global runtime.
 *
 * @return The `LongBowConfig` instance of the current global runtime.
 */
LongBowConfig *longBowRuntime_GetCurrentConfig(void);

/**
 * Set the `LongBowConfig` instance of the current global runtime.
 *
 * @param [in] config The new `LongBowConfig` instance of the current global runtime.
 */
void longBowRuntime_SetCurrentConfig(LongBowConfig *config);

/**
 * Trigger a LongBow event.
 *
 * The event will be reported via the longBowReport_Event.
 *
 * @param [in] eventType The type of event.
 * @param [in] location The LongBowLocation of the event (this will be destroyed).
 * @param [in] kind A string indicating the kind of event this is triggering.
 * @param [in] format A printf format string.
 * @param [in] ... Parameters associated with the printf format string.
 *
 * @return true Always return true.
 */
bool longBowRuntime_EventTrigger(LongBowEventType *eventType,
                                 LongBowLocation *location,
                                 const char *kind,
                                 const char *format, ...) __attribute__((__format__ (__printf__, 4, 5)));
/**
 * Record an event evaluation.
 *
 * This only records the fact of the evaluation, not the results of the evaluation.
 *
 * @param [in] type A pointer to the LongBowEventType being evaluated.
 *
 * @return true Always returns true.
 *
 * Example:
 * @code
 * {
 *     longBowRuntime_EventEvaluation(&LongBowAssertEvent);
 * }
 * @endcode
 */
bool longBowRuntime_EventEvaluation(const LongBowEventType *type);

/**
 * Set the current value for the depth of  printed stack trace.
 *
 *   If the depth is less than 1, no stack trace is displayed.
 *
 * @param [in] newDepth The new value to set.
 *
 * @return The previous value.
 */
unsigned int longBowRuntime_SetStackTraceDepth(unsigned int newDepth);

/**
 * Get the current value for the depth of printed stack trace.
 *
 * @return The current stack-trace depth.
 */
unsigned int longBowRuntime_GetStackTraceDepth(void);

/**
 * Print a formatted stack trace to the current output file descriptor.
 *
 * @param [in] fileDescriptor A valid file descriptor.
 */
void longBowRuntime_StackTrace(int fileDescriptor);

/**
 * Abort the running process using the current runtime environment.
 * If the configuration is set to produce a core dump, this function simply returns.
 * This permits the caller to use the form:
 * <code>
 * longBowRuntime_Abort(), kill(0, SIGTRACE)
 * </code>
 * To generate a core image.
 *
 * See the assertion macros for how this is used.
 */
void longBowRuntime_Abort(void);
#endif // LongBow_longBow_Runtime_h
