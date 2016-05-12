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
 * @file longBow_Event.h
 * @ingroup internals
 * @brief LongBow Event Support.
 *
 * LongBow assertions, traps and tests induce "events" which are experienced by the programme runtime as signals or long-jumps.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Event_h
#define LongBow_longBow_Event_h

#include <stdlib.h>
#include <stdbool.h>

#include <LongBow/longBow_EventType.h>
#include <LongBow/longBow_Location.h>
#include <LongBow/longBow_Backtrace.h>

struct longbow_event;

/**
 * @typedef LongBowEvent
 */
typedef struct longbow_event LongBowEvent;

/**
 * Get the `LongBowEventType` of a LongBowEvent.
 *
 * @param [in] event A `LongBowEvent` instance.
 *
 * @return A pointer to the LongBowEventType of the event.
 *
 * Example:
 * @code
 * {
 *     LongBowEvent *event = ...
 *     LongBowEventType type = longBowEvent_GetEventType(event);
 * }
 * @endcode
 */
const LongBowEventType *longBowEvent_GetEventType(const LongBowEvent *event);

/**
 * Create a `LongBowEvent`.
 *
 * Creating a `LongBowEvent` records runtime data and used by report facilities.
 * This does not actually cause the process to assert the assertion.
 *
 * @param [in] eventType The LongBowEventType for this event.
 * @param [in] location A LongBowLocation instance recording the location of the event.
 * @param [in] kind A string representing the kind of event.
 * @param [in] message A message to display. This will be freed via free(3).
 * @param [in] backtrace A pointer to a valid LongBowBacktrace instance.
 *
 * @return An allocated LongBowEvent which must be destroyed via `longBowEvent_Destroy()`.
 */
LongBowEvent *longBowEvent_Create(const LongBowEventType *eventType, const LongBowLocation *location, const char *kind, const char *message, const LongBowBacktrace *backtrace);

/**
 * Destroy a `LongBowEvent`.
 *
 * The value pointed to by `eventPtr`, is set to `NULL.
 *
 * @param [in,out] eventPtr The `LongBowEvent` instance to destroy and NULLify.
 */
void longBowEvent_Destroy(LongBowEvent **eventPtr);

/**
 * Get the `LongBowLocation` associated with this `LongBowEvent` instance.
 *
 * @param [in] event A `LongBowEvent` instance.
 *
 * @return A pointer to the `LongBowLocation` instance for the given `LongBowEvent`.
 */
const LongBowLocation *longBowEvent_GetLocation(const LongBowEvent *event);

/**
 * Get the name.
 *
 * @param [in] event A `LongBowEvent` instance.
 *
 * @return The name of the given LongBowEvent.
 */
const char *longBowEvent_GetName(const LongBowEvent *event);

/**
 * Get a pointer to the string representing the kind of this event.
 *
 * Currently the kind is only a static string set when creating a `LongBowEvent`.
 *
 * @param [in] event A pointer to a `LongBowEvent` instance.
 *
 * @return non-NULL The pointer to the string representing the kind of this event.
 * @return NULL The kind was not set.
 *
 * @see longBowEvent_Create
 */
const char *longBowEvent_GetKind(const LongBowEvent *event);

/**
 * Retrieve the message associated with this `LongBowEvent` instance.
 *
 * @param [in] event A `LongBowEvent` instance.
 *
 * @return The message associated with the given `LongBowEvent`.
 */
const char *longBowEvent_GetMessage(const LongBowEvent *event);

/**
 * Get the `LongBowBacktrace` instance for the given `LongBowEvent` instance.
 *
 * @param [in] event A pointer to a valid LongBowEvent instance.
 *
 * @return A pointer to a LongBowBacktrace instance.
 */
const LongBowBacktrace *longBowEvent_GetBacktrace(const LongBowEvent *event);

/**
 * Get an array of nul-terminated C strings containing the symbolic representation of the given `LongBowEvent` stack backtrace.
 * The length of the array is provided by `longBowEvent_GetCallStackLength`
 *
 * @param [in] event A pointer to a valid `LongBowEvent` instance.
 *
 * @return non-NULL An array of nul-terminated C strings
 * @see longBowEvent_GetCallStackLength
 */
char **longBowEvent_CreateSymbolicCallstack(const LongBowEvent *event);

/**
 * Retrieve the call stack length associated with this `LongBowEvent` instance.
 *
 * @param [in] event A `LongBowEvent` instance.
 *
 * @return The length of the call stack.
 */
size_t longBowEvent_GetCallStackLength(const LongBowEvent *event);
#endif // LongBow_longBow_Event_h
