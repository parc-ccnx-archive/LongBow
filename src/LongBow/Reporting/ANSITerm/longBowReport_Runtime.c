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
#include <stdarg.h>
#include <assert.h>

#include <LongBow/Reporting/ANSITerm/longBowReport_Runtime.h>
#include <LongBow/private/longBow_Memory.h>

static const char *ansiRed = "\x1b[31m";
static const char *ansiGreen = "\x1b[32m";
static const char *ansiYellow = "\x1b[33m";
static const char *ansiMagenta = "\x1b[35m";
static const char *ansiReset = "\x1b[0m";

static void
_printGreen(void)
{
    printf("%s", ansiGreen);
}

static void
_printYellow(void)
{
    printf("%s", ansiYellow);
}

static void
_printMagenta(void)
{
    printf("%s", ansiMagenta);
}

static void
_printReset(void)
{
    printf("%s", ansiReset);
    fflush(stdout);
}

static void
_longBowReportRuntime_RedPrintf(const char *format, va_list args)
{
    longBowReportRuntime_PrintRed();
    vprintf(format, args);
    _printReset();
}

static void
_longBowReportRuntime_YellowPrintf(const char *format, va_list args)
{
    _printYellow();
    vprintf(format, args);
    _printReset();
}

void
longBowReportRuntime_PrintRed(void)
{
    printf("%s", ansiRed);
}

void
longBowReportRuntime_RedPrintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _longBowReportRuntime_RedPrintf(format, args);
    va_end(args);
}

void
longBowReportRuntime_GreenPrintf(const char *format, ...)
{
    _printGreen();
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    _printReset();
}

void
longBowReportRuntime_MagentaPrintf(const char *format, ...)
{
    _printMagenta();
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    _printReset();
}

void
longBowReportRuntime_YellowPrintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    _longBowReportRuntime_YellowPrintf(format, args);

    va_end(args);
}

void
longBowReportRuntime_ParseSuppress(LongBowReportConfig *result, const char *key)
{
    for (size_t i = 0; i < strlen(key); i++) {
        if (*key == 'X') {
            result->suppress_report.untested = 1;
        } else if (*key == '.') {
            result->suppress_report.succeeded = 1;
        } else if (*key == 'S') {
            result->suppress_report.skipped = 1;
        } else if (*key == 'W') {
            result->suppress_report.warned = 1;
        } else if (*key == 's') {
            result->suppress_report.setup_failed = 1;
        } else if (*key == 't') {
            result->suppress_report.teardown_failed = 1;
        } else if (*key == 'w') {
            result->suppress_report.teardown_warned = 1;
        } else if (*key == 'F') {
            result->suppress_report.failed = 1;
        } else if (*key == 'T') {
            result->suppress_report.stopped = 1;
        } else if (*key == 'U') {
            result->suppress_report.unimplemented = 1;
        } else {
            printf("Unknown suppression key '%c'\n", *key);
        }
    }
}

LongBowReportConfig *
longBowReportRuntime_Create(int argc, char *argv[])
{
    static const char *prefix = "--report";
    size_t prefixLength = strlen(prefix);

    LongBowReportConfig *result = longBowMemory_Allocate(sizeof(LongBowReportConfig));

    for (int i = 0; i < argc; i++) {
        if (strncmp(prefix, argv[i], prefixLength) == 0) {
            if (strcmp("--report-suppress", argv[i]) == 0) {
                longBowReportRuntime_ParseSuppress(result, argv[i + 1]);
                i++;
            }
        } else if (strcmp("--help", argv[i]) == 0) {
            printf("Options for LongBow Report ANSI Terminal\n");
            printf("  --report-suppress [STFU.XWstw] Suppress the display of specific reports.\n");
            printf("     S - suppress the report of a skipped test.\n");
            printf("     T - suppress the report of a stopped test.\n");
            printf("     F - suppress the report of a failed test.\n");
            printf("     U - suppress the report of an unimplemented test.\n");
            printf("     . - suppress the report of a successful test.\n");
            printf("     X - suppress the report of an untested test.\n");
            printf("     W - suppress the report of a warned test.\n");
            printf("     s - suppress the report of a setup failure.\n");
            printf("     t - suppress the report of a tear-down failure.\n");
            printf("     w - suppress the report of a tear-down warning.\n");
            free(result);
            return NULL;
        }
    }

    return result;
}

void
longBowReportRuntime_Destroy(LongBowReportConfig **reportPtr)
{
    longBowMemory_Deallocate((void **) reportPtr);
}

static void
_EventPrint(const LongBowEvent *event)
{
    if (longBowEventType_IsSuppressAlert(longBowEvent_GetEventType(event)) == false) {
        char *location = longBowLocation_ToString(longBowEvent_GetLocation(event));
        printf("%s %s %s %s\r\n",
               longBowEvent_GetName(event), location, longBowEvent_GetKind(event), longBowEvent_GetMessage(event));

        if (longBowEventType_IsSuppressBacktrace(longBowEvent_GetEventType(event)) == false) {
            char **strs = longBowEvent_CreateSymbolicCallstack(event);
            if (strs != NULL) {
                for (size_t i = 0; i < longBowEvent_GetCallStackLength(event); ++i) {
                    printf("%s\r\n", strs[i]);
                }
                free(strs);
            }

        }
        fflush(stdout);
        free(location);
    }
}

void
longBowReportRuntime_Event(const LongBowEvent *event)
{
    LongBowStatus status = longBowEventType_GetStatus(longBowEvent_GetEventType(event));
    switch (status) {
        case LongBowStatus_DONTCARE:
        case LongBowStatus_UNTESTED:
            break;

        /* successful */
        case LONGBOW_STATUS_SUCCEEDED:
            // If this happens, there is an error in the encoding of the LongBowEventType.
            longBowReportRuntime_PrintRed();
            _EventPrint(event);
            _printReset();
            break;

        case LongBowStatus_WARNED:
        case LongBowStatus_TEARDOWN_WARNED:
        case LONGBOW_STATUS_SKIPPED:
        case LongBowStatus_UNIMPLEMENTED:
        case LongBowStatus_IMPOTENT:
        case LONGBOW_STATUS_MEMORYLEAK:
        case LONGBOW_STATUS_SETUP_SKIPTESTS:
            _printYellow();
            _EventPrint(event);
            _printReset();
            break;

        /* failure */
        case LONGBOW_STATUS_FAILED:
        case LongBowStatus_STOPPED:
        case LONGBOW_STATUS_TEARDOWN_FAILED:
        case LONGBOW_STATUS_SETUP_FAILED:
        case LongBowStatus_SIGNALLED:
            longBowReportRuntime_PrintRed();
            _EventPrint(event);
            _printReset();
            break;
            
        case LongBowStatus_LIMIT: // fall through
        default:
            _printYellow();
            _EventPrint(event);
            _printReset();
            break;
    }
}

void
longBowReportRuntime_Message(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void
longBowReportRuntime_Warning(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    longBowReportRuntime_YellowPrintf("WARNING ");
    _longBowReportRuntime_YellowPrintf(format, args);
    va_end(args);
}

void
longBowReportRuntime_Error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    longBowReportRuntime_RedPrintf("FAILURE ");
    _longBowReportRuntime_RedPrintf(format, args);
    va_end(args);
}
