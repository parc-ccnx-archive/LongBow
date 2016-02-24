/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @file runtime.h
 * @ingroup runtime
 * @brief LongBow Runtime Support
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LongBow_runtime_h
#define LongBow_runtime_h

#include <signal.h>

#include <LongBow/longBow_Runtime.h>

/**
 * @def longBowIsFalse
 * @brief Indicate true if a condition is false.
 *
 * @param [in] condition The condition to test.
 */
#if __GNUC__
#    define longBowIsFalse(condition) __builtin_expect(!(condition), 0)
#else
#    define longBowIsFalse(condition) (!(condition))
#endif

#if __STDC_VERSION__ < 199901L
#    define __func__ ((const char *) 0)
#endif

/**
 * @def longBowEvent
 * @brief If the condition is true record the given event and abort the running programme.
 *
 * @param [in] eventPointer
 * @param [in] condition A boolean value that is expected to be true.
 * @param [in] location A pointer to a LongBowLocation instance.
 * @param [in] ... A printf format string following corresponding parameters.
 */
#ifdef LongBow_DISABLE_ASSERTIONS
#define longBowEvent(eventPointer, condition, location, ...) if (0 && condition) for (; false; )
#else
#define longBowEvent(eventPointer, condition, location, ...) \
     if (longBowRuntime_EventEvaluation(eventPointer) && longBowIsFalse(condition) && \
        longBowRuntime_EventTrigger(eventPointer, location, #condition, __VA_ARGS__)) \
        for (; true; longBowRuntime_Abort(), kill(0, SIGTRAP))
#endif

/**
 * @def longBowAssert
 * @brief Assert a condition, abort the running programme recording the given event if the condition is false.
 *
 * @param [in] eventPointer
 * @param [in] condition A boolean value that is expected to be true.
 * @param [in] ... A printf format string following corresponding parameters.
 */

#  define longBowAssert(eventPointer, condition, ...) \
    longBowEvent(eventPointer, condition, longBowLocation_Create(__FILE__, __func__, __LINE__), __VA_ARGS__)

/**
 * @def longBowTrap
 * @brief Abort the running programme recording the given trap.
 *
 * @param [in] eventPointer
 * @param [in] ... A printf format string following corresponding parameters.
 */
#define longBowTrap(eventPointer, ...) \
    longBowRuntime_EventEvaluation(eventPointer); \
    if (longBowRuntime_EventTrigger(eventPointer, \
                                    longBowLocation_Create(__FILE__, __func__, __LINE__), longBowEventType_GetName(eventPointer), __VA_ARGS__), true) \
        for (; true; abort())


#define longBowTrapIf(eventPointer, condition, ...) \
    longBowEvent(eventPointer, (!(condition)), longBowLocation_Create(__FILE__, __func__, __LINE__), __VA_ARGS__)

/**
 * @def longBowTest
 * @brief Terminate a LongBow Test Case signaling the given event if the condition is false.
 *
 * @param [in] testEventPointer
 * @param [in] ... A printf format string following corresponding parameters.
 */
# define longBowTest(testEventPointer, ...) do { \
        longBowRuntime_EventEvaluation(testEventPointer); \
        longBowRuntime_EventTrigger(testEventPointer, \
                                    longBowLocation_Create(__FILE__, __func__, __LINE__), \
                                    "Test", __VA_ARGS__); \
        longjmp(longBowTestCaseAbort, SIGABRT); \
} while (0)

#include <LongBow/assertions.h>
#include <LongBow/debugging.h>
#include <LongBow/traps.h>
#endif // LongBow_runtime_h
