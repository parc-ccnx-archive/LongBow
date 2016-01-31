/*
 * Copyright (c) 2013-2014,2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @copyright 2013-2014,2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <LongBow/longBow_Location.h>

#include <LongBow/private/longBow_Memory.h>

/** @cond private */
struct longbow_location {
    char *fileName;
    char *functionName;
    uint32_t lineNumber;
};
/** @endcond */

LongBowLocation *
longBowLocation_Create(const char *fileName, const char *functionName, uint32_t lineNumber)
{
    LongBowLocation *result = longBowMemory_Allocate(sizeof(LongBowLocation));

    if (result != NULL) {
        result->fileName = (fileName == NULL) ? NULL : strdup(fileName);
        result->functionName = (functionName == NULL) ? NULL : strdup(functionName);
        result->lineNumber = lineNumber;
    }

    return result;
}

void
longBowLocation_Destroy(LongBowLocation **locationPtr)
{
    assert(locationPtr != NULL);

    LongBowLocation *location = *locationPtr;

    if (location->fileName != NULL) {
        free(location->fileName);
    }
    if (location->functionName != NULL) {
        free(location->functionName);
    }
    longBowMemory_Deallocate((void **) locationPtr);
}

char *
longBowLocation_ToString(const LongBowLocation *location)
{
    assert(location != NULL);

    char *result;

    if (location->functionName == 0) {
        int status = asprintf(&result, "%s:%u", location->fileName, location->lineNumber);
        if (status == -1) {
            return NULL;
        }
    } else {
        int status = asprintf(&result, "%s:%u %s()", location->fileName, location->lineNumber, location->functionName);
        if (status == -1) {
            return NULL;
        }
    }

    return result;
}
