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
//#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <LongBow/longBow_Backtrace.h>
#include <LongBow/private/longBow_Memory.h>

#if defined(_WIN64)
#  define backtrace(...) (0)
#  define backtrace_symbols(...) 0
#  define backtrace_symbols_fd(...) ((void) 0)
#elif defined(_WIN32)
#  define backtrace(...) (0)
#  define backtrace_symbols(...) 0
#  define backtrace_symbols_fd(...) ((void) 0)
#elif defined(__ANDROID__)
#  define backtrace(...) (0)
#  define backtrace_symbols(...) 0
#  define backtrace_symbols_fd(...) ((void) 0)
#elif defined(__APPLE__)
#  include <execinfo.h>
#elif defined(__linux)
#  include <execinfo.h>
#elif defined(__unix) // all unices not caught above
#  define backtrace(...) (0)
#  define backtrace_symbols(...) 0
#  define backtrace_symbols_fd(...) ((void) 0)
#elif defined(__posix)
#  include <execinfo.h>
#endif

struct longbow_backtrace {
    void *callstack;
    unsigned int frames;
    unsigned int offset;
};

LongBowBacktrace *
longBowBacktrace_Create(uint32_t maximumFrames, uint32_t offset)
{
    LongBowBacktrace *result = longBowMemory_Allocate(sizeof(LongBowBacktrace));

    if (maximumFrames > 0) {
        void **stackTrace = longBowMemory_Allocate(sizeof(stackTrace[0]) * ((size_t) maximumFrames + offset));

        unsigned int frames = (unsigned int) backtrace(stackTrace, (int) (maximumFrames + offset));
        if (frames > offset) {
            unsigned int actualFrames = frames - offset;

            if (actualFrames > maximumFrames) {
                actualFrames = maximumFrames;
            }

            // Shift out the first 'offset' number of frames in the stack trace.
            memmove(&stackTrace[0], &stackTrace[offset], actualFrames * sizeof(stackTrace[0]));

            result->callstack = stackTrace;
            result->frames = actualFrames;
            result->offset = 0;
        }
    }

    return result;
}

unsigned int
longBowBacktrace_GetFrameCount(const LongBowBacktrace *backtrace)
{
    return backtrace->frames;
}

void
longBowBacktrace_Destroy(LongBowBacktrace **backtracePtr)
{
    LongBowBacktrace *backtrace = *backtracePtr;
    longBowMemory_Deallocate(&backtrace->callstack);
    longBowMemory_Deallocate((void **) backtracePtr);
}

char **
longBowBacktrace_Symbols(const LongBowBacktrace *backtrace)
{
    char **result = NULL;
    if (backtrace != NULL) {
        result = backtrace_symbols(backtrace->callstack, (int) backtrace->frames);
    }

    return result;
}

char *
longBowBacktrace_ToString(const LongBowBacktrace *backtrace)
{
    char *result = NULL;

    char **lines = longBowBacktrace_Symbols(backtrace);

    if (lines == NULL) {
        result = longBowMemory_StringCopy("(backtrace symbols not supported)");
    } else {
        size_t sum = 0;
        for (int i = 0; i < backtrace->frames; i++) {
            sum += strlen(lines[i]) + 1;
        }
        result = longBowMemory_Allocate(sum + 1 * sizeof(char));

        char *offset = result;
        for (int i = 0; i < backtrace->frames; i++) {
            strcpy(offset, lines[i]);
            offset += strlen(lines[i]);
            *offset++ = '\n';
        }
        *offset = 0;
    }

    return result;
}
