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

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include <LongBow/longBow_Debug.h>
#include <LongBow/Reporting/longBowReport_Runtime.h>

/** @cond */
struct longbow_debug_criteria {
    bool enabled;
};
/** @endcond */

static struct longbow_debug_criteria LongBowDebug_StaticCriteria = {
    .enabled = true
};

static LongBowDebugCriteria *LongBowDebug_CurrentCriteria = &LongBowDebug_StaticCriteria;

LongBowDebugCriteria *
longBowDebug_CurrentCriteria(void)
{
    return LongBowDebug_CurrentCriteria;
}

static void
_longBowDebug_MemoryDumpLine(const char *memory, size_t offset, size_t length)
{
    int bytesPerLine = 16;
    char accumulator[bytesPerLine + 1];
    memset(accumulator, ' ', bytesPerLine);
    accumulator[bytesPerLine] = 0;

    printf("%5zd: ", offset);

    for (size_t i = 0; i < bytesPerLine; i++) {
        if (offset + i >= length) {
            printf("   ");
            accumulator[i] = ' ';
        } else {
            char c = memory[offset + i];
            printf("%02x ", c & 0xFF);
            if (isprint(c)) {
                accumulator[i] = c;
            } else {
                accumulator[i] = '.';
            }
        }
    }
    printf("   %s\n", accumulator);
}

void
longBowDebug_MemoryDump(const char *memory, size_t length)
{
    size_t bytesPerLine = 16;

    for (size_t offset = 0; offset < length; offset += bytesPerLine) {
        _longBowDebug_MemoryDumpLine(memory, offset, length);
    }
}

void
longBowDebug_Message(LongBowDebugCriteria *criteria, const LongBowLocation *location, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    char *message;
    int status = vasprintf(&message, format, ap);
    va_end(ap);
    if (status != -1) {
#if 1
        char *locationString = longBowLocation_ToString(location);
        longBowReportRuntime_Message("%s %s\r\n", locationString, message);
        
        free(locationString);
#else
        longBowReportRuntime_Message(location, message);
#endif
        free(message);
    }
}

ssize_t
longBowDebug_WriteFile(const char *fileName, const char *data, size_t length)
{
    ssize_t result = 0;

    int fd = open(fileName, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd == -1) {
        perror(fileName);
    } else {
        result = write(fd, data, length);
    }
    close(fd);
    return result;
}

ssize_t
longBowDebug_ReadFile(const char *fileName, char **data)
{
    ssize_t result = -1;
    struct stat statbuf;
    char *buffer;

    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        perror(fileName);
    } else {
        if (fstat(fd, &statbuf) != -1) {
            buffer = malloc((unsigned long) statbuf.st_size + 1);
            result = read(fd, buffer, (unsigned long) statbuf.st_size);
            buffer[statbuf.st_size] = 0;
            *data = buffer;
        }
    }
    return result;
}
