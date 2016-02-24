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
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <LongBow/longBow_Event.h>
#include <LongBow/longBow_EventType.h>
#include <LongBow/longBow_Backtrace.h>
#include <LongBow/longBow_Location.h>
#include <LongBow/longBow_Status.h>
#include <LongBow/private/longBow_Memory.h>

/** @cond private */
struct longbow_event {
    const LongBowEventType *type;
    const LongBowLocation *location;
    const char *kind;
    const char *message;
    const LongBowBacktrace *backtrace;
};
/** @endcond */

const char *
longBowEvent_GetName(const LongBowEvent *event)
{
    return longBowEventType_GetName(event->type);
}

LongBowEvent *
longBowEvent_Create(const LongBowEventType *eventType, const LongBowLocation *location, const char *kind, const char *message, const LongBowBacktrace *backtrace)
{
    LongBowEvent *result = longBowMemory_Allocate(sizeof(LongBowEvent));
    if (result != NULL) {
        result->type = eventType;
        result->location = location;
        result->kind = kind;
        result->message = strndup(message, strlen(message));
        result->backtrace = backtrace;
    }

    return result;
}

void
longBowEvent_Destroy(LongBowEvent **assertionPtr)
{
    LongBowEvent *assertion = *assertionPtr;

    if (assertion->location != NULL) {
        longBowLocation_Destroy((LongBowLocation **) &assertion->location);
    }
    if (assertion->message != NULL) {
        free((void *) assertion->message);
    }

    if (assertion->backtrace != NULL) {
        longBowBacktrace_Destroy((LongBowBacktrace **) &assertion->backtrace);
    }
    longBowMemory_Deallocate((void **) assertionPtr);
}

const LongBowLocation *
longBowEvent_GetLocation(const LongBowEvent *event)
{
    return event->location;
}

const LongBowEventType *
longBowEvent_GetEventType(const LongBowEvent *event)
{
    return event->type;
}

const char *
longBowEvent_GetKind(const LongBowEvent *event)
{
    return event->kind;
}

const char *
longBowEvent_GetMessage(const LongBowEvent *event)
{
    return event->message;
}

const LongBowBacktrace *
longBowEvent_GetBacktrace(const LongBowEvent *event)
{
    return event->backtrace;
}

char **
longBowEvent_CreateSymbolicCallstack(const LongBowEvent *event)
{
    char **result = longBowBacktrace_Symbols(event->backtrace);

    return result;
}

size_t
longBowEvent_GetCallStackLength(const LongBowEvent *event)
{
    return longBowBacktrace_GetFrameCount(event->backtrace);
}
