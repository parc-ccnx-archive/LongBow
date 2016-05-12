/*
 * Copyright (c) 2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @author Glenn Scott, Computing Science Laboratory, PARC
 * @copyright (c) 2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <LongBow/longBow_ClipBoard.h>

#include <LongBow/private/longBow_Memory.h>
#include <LongBow/private/longBow_ArrayList.h>

struct LongBowClipBoard {
    LongBowArrayList *list;
};

typedef struct Property {
    const char *name;
    char *value;
} _Property;

static void
_property_Destroy(_Property **pointer)
{
    _Property *property = *pointer;
    longBowMemory_Deallocate((void **) &property->name);
    longBowMemory_Deallocate((void **) property);
}

void
longBowClipBoard_Destroy(LongBowClipBoard **pointer)
{
    LongBowClipBoard *clipboard = *pointer;

    longBowArrayList_Destroy(&clipboard->list);
    longBowMemory_Deallocate((void **) pointer);
}

LongBowClipBoard *
longBowClipBoard_Create(void)
{
    LongBowClipBoard *result = longBowMemory_Allocate(sizeof(LongBowClipBoard));

    if (result != NULL) {
        result->list = longBowArrayList_Create((void (*)(void **))_property_Destroy);
    }

    return result;
}

static _Property *
_longBowClipBoard_Get(const LongBowClipBoard *clipBoard, const char *name)
{
    _Property *result = NULL;

    for (size_t index = 0; index < longBowArrayList_Length(clipBoard->list); index++) {
        _Property *property = longBowArrayList_Get(clipBoard->list, index);
        if (strcmp(property->name, name) == 0) {
            result = property;
            break;
        }
    }
    return result;
}

void *
longBowClipBoard_Get(const LongBowClipBoard *clipBoard, const char *name)
{
    _Property *property = _longBowClipBoard_Get(clipBoard, name);

    if (property != NULL) {
        return property->value;
    }

    return NULL;
}

char *
longBowClipBoard_GetAsCString(const LongBowClipBoard *clipBoard, const char *name)
{
    return (char *) longBowClipBoard_Get(clipBoard, name);
}

uint64_t
longBowClipBoard_GetAsInt(const LongBowClipBoard *clipBoard, const char *name)
{
    return (uint64_t) longBowClipBoard_Get(clipBoard, name);
}

void *
longBowClipBoard_Set(LongBowClipBoard *clipBoard, const char *name, void *value)
{
    void *result = NULL;

    _Property *property = _longBowClipBoard_Get(clipBoard, name);
    if (property == NULL) {
        property = longBowMemory_Allocate(sizeof(_Property));
        property->name = longBowMemory_StringCopy(name);
        property->value = value;
        longBowArrayList_Add(clipBoard->list, property);
    } else {
        result = property->value;
        property->value = value;
    }
    return result;
}

void *
longBowClipBoard_SetInt(LongBowClipBoard *clipBoard, const char *name, uint64_t value)
{
    return longBowClipBoard_Set(clipBoard, name, (void*)(uintptr_t) value);
}

void *
longBowClipBoard_SetCString(LongBowClipBoard *clipBoard, const char *name, char *value)
{
    return longBowClipBoard_Set(clipBoard, name, (char *) value);
}

bool
longBowClipBoard_Exists(const LongBowClipBoard *clipBoard, const char *name)
{
    return (_longBowClipBoard_Get(clipBoard, name) != NULL);
}

bool
longBowClipBoard_Delete(LongBowClipBoard *clipBoard, const char *name)
{
    bool result = false;

    for (size_t index = 0; index < longBowArrayList_Length(clipBoard->list); index++) {
        _Property *property = longBowArrayList_Get(clipBoard->list, index);
        if (strcmp(property->name, name) == 0) {
            longBowArrayList_RemoveAtIndex(clipBoard->list, index);
            result = true;
        }
    }

    return result;
}
