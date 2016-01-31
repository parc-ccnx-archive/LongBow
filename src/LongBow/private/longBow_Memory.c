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
#include <stdlib.h>
#include <string.h>

#include <LongBow/private/longBow_Memory.h>

#if HAVE_REALLOC == 0
static void *
_LongBow_rplRealloc(void *oldAlloc, size_t newSize)
{
    if (newSize == 0) {
        newSize = 1;
    }
    
    char *newAlloc = malloc(newSize);
    
    if (oldAlloc != NULL) {
        memcpy(newAlloc, oldAlloc, newSize);
        free(oldAlloc);
    }
    return newAlloc;
}
#endif

static uint64_t _outstandingAllocations;

void *
longBowMemory_Allocate(const size_t size)
{
    _outstandingAllocations++;
    return calloc(1, size);
}

void *
longBowMemory_Reallocate(void *oldAllocation, const size_t newSize)
{
#if HAVE_REALLOC
    void *result = realloc(oldAllocation, newSize);
#else
    void *result = _LongBow_rplRealloc(oldAllocation, newSize);
#endif    
    
    if (oldAllocation == NULL) {
        _outstandingAllocations++;
    }
    
    return result;
}

void
longBowMemory_Deallocate(void **pointerPointer)
{
    free(*pointerPointer);
    _outstandingAllocations--;
    *pointerPointer = NULL;
}

uint64_t
longBowMemory_OutstandingAllocations(void)
{
    return _outstandingAllocations;
}

char *
longBowMemory_StringCopy(const char *string)
{
    char *result = NULL;
    
    if (string != NULL) {
        size_t length = strlen(string);
        result = longBowMemory_Allocate(length + 1);
        strcpy(result, string);
        result[length] = 0;
    }
    return result;
}
