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
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <LongBow/runtime.h>
#include <LongBow/private/longBow_ArrayList.h>
#include <LongBow/private/longBow_Memory.h>

struct longbow_array_list {
    void **array;
    size_t numberOfElements;
    size_t limit;
    void (*destroyElement)(void **elementAddress);
};

static LongBowArrayList *_longBowArrayList_EnsureRemaining(LongBowArrayList *array, size_t remnant);
static LongBowArrayList *_longBowArrayList_EnsureCapacity(LongBowArrayList *array, size_t newCapacity);

void
longBowArrayList_AssertValid(const LongBowArrayList *array)
{
    if (array == NULL) {
        printf("Parameter must be a non-null pointer to a LongBowArrayList instance\n");
        abort();
    }
}

LongBowArrayList *
longBowArrayList_Add(LongBowArrayList *array, const void *pointer)
{
    longBowArrayList_AssertValid(array);

    if (_longBowArrayList_EnsureRemaining(array, 1) == NULL) {
        return NULL;
    }
    array->array[array->numberOfElements++] = (void *) pointer;

    return array;
}

static size_t
_longBowArrayList_Remaining(const LongBowArrayList *array)
{
    longBowArrayList_AssertValid(array);

    return array->limit - array->numberOfElements;
}

static LongBowArrayList *
_longBowArrayList_EnsureCapacity(LongBowArrayList *array, size_t newCapacity)
{
    longBowArrayList_AssertValid(array);

    void *newArray = longBowMemory_Reallocate(array->array, newCapacity * sizeof(void *));

    if (newArray == NULL) {
        return NULL;
    }
    array->array = newArray;
    array->limit = newCapacity;

    return array;
}

static LongBowArrayList *
_longBowArrayList_EnsureRemaining(LongBowArrayList *array, size_t remnant)
{
    longBowArrayList_AssertValid(array);

    if (_longBowArrayList_Remaining(array) < remnant) {
        size_t newCapacity = longBowArrayList_Length(array) + remnant;
        return _longBowArrayList_EnsureCapacity(array, newCapacity);
    }
    return array;
}

bool
longBowArrayList_Equals(const LongBowArrayList *a, const LongBowArrayList *b)
{
    if (a != b) {
        if (a == NULL || b == NULL) {
            return false;
        }
        if (a->numberOfElements == b->numberOfElements) {
            for (size_t i = 0; i < a->numberOfElements; i++) {
                if (a->array[i] != b->array[i]) {
                    return false;
                }
            }
        }
    }

    return true;
}

void *
longBowArrayList_Get(const LongBowArrayList *array, size_t index)
{
    longBowArrayList_AssertValid(array);

    assert(index < array->numberOfElements);

    return array->array[index];
}

size_t
longBowArrayList_Length(const LongBowArrayList *array)
{
    longBowArrayList_AssertValid(array);

    return array->numberOfElements;
}

LongBowArrayList *
longBowArrayList_Create(void (*destroyElement)(void **elementAddress))
{
    LongBowArrayList *result = longBowMemory_Allocate(sizeof(LongBowArrayList));

    if (result != NULL) {
        result->numberOfElements = 0;
        result->limit = 0;
        result->array = NULL;
        result->destroyElement = destroyElement;
    }

    return result;
}

LongBowArrayList *
longBowArrayList_Create_Capacity(void (*destroyElement)(void **elementAddress), size_t size)
{
    LongBowArrayList *result = longBowArrayList_Create(destroyElement);
    if (result != NULL) {
        _longBowArrayList_EnsureRemaining(result, size);
    }

    return result;
}

void
longBowArrayList_Destroy(LongBowArrayList **arrayPtr)
{
    assertNotNull(arrayPtr, "Parameter must be a non-null pointer to a LongBow_ArrayList pointer.");

    LongBowArrayList *array = *arrayPtr;

    longBowArrayList_AssertValid(array);

    assertTrue(array->numberOfElements == 0 ? true : array->array != NULL, "LongBow_ArrayList is inconsistent.");

    if (array->destroyElement != NULL) {
        for (size_t i = 0; i < array->numberOfElements; i++) {
            array->destroyElement(&array->array[i]);
            array->array[i] = NULL;
        }
    }

    if (array->array != NULL) {
        longBowMemory_Deallocate((void **) &array->array);
    }

    longBowMemory_Deallocate((void **) arrayPtr);
}

void **
longBowArrayList_GetArray(const LongBowArrayList *array)
{
    longBowArrayList_AssertValid(array);
    return array->array;
}

LongBowArrayList *
longBowArrayList_Copy(const LongBowArrayList *original)
{
    longBowArrayList_AssertValid(original);

    LongBowArrayList *result = longBowMemory_Allocate(sizeof(LongBowArrayList));

    if (result != NULL) {
        for (size_t i = 0; i < original->numberOfElements; i++) {
            longBowArrayList_Add(result, original->array[i]);
        }
    }

    return result;
}

void
longBowArrayList_StdlibFreeFunction(void **elementPtr)
{
    if (elementPtr != NULL) {
        free(*elementPtr);
        *elementPtr = 0;
    }
}

LongBowArrayList *
longBowArrayList_RemoveAtIndex(LongBowArrayList *array, size_t index)
{
    longBowArrayList_AssertValid(array);

    size_t length = longBowArrayList_Length(array);
    assertTrue(index < length, "Index must be ( 0 <= index < %zd). Actual=%zd", length, index);

    if (index < length) {
        // Destroy the element at the given index.
        if (array->destroyElement != NULL) {
            array->destroyElement(&array->array[index]);
        }

        // Adjust the list to elide the element.
        for (size_t i = index; i < length; i++) {
            array->array[i] = array->array[i + 1];
        }
        array->numberOfElements--;
    }

    return array;
}

LongBowArrayList *
longBowArrayList_Add_AtIndex(LongBowArrayList *array, const void *pointer, size_t index)
{
    longBowArrayList_AssertValid(array);
    size_t length = longBowArrayList_Length(array);

    if (index > array->limit) {
        // We need to grow the array to fit this element.
        _longBowArrayList_EnsureCapacity(array, index + 1);
        array->numberOfElements = index + 1;
    } else {
        // Create space and grow the array if needed
        _longBowArrayList_EnsureRemaining(array, length + 1);
        for (size_t i = index; i < length; i++) {
            array->array[i + 1] = array->array[i];
        }
        array->numberOfElements++;
    }

    array->array[index] = (void *) pointer;


    return array;
}

bool
longBowArrayList_Replace(LongBowArrayList *array, const void *old, void *new)
{
    for (size_t i = 0; i < longBowArrayList_Length(array); i++) {
        if (array->array[i] == old) {
            array->array[i] = new;
            return true;
        }
    }
    return false;
}
