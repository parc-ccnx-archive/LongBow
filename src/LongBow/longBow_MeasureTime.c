/*
 * Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @copyright 2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>
#include <stdio.h>
#include <sys/time.h>

#include <LongBow/longBow_MeasureTime.h>
#include <LongBow/private/longBow_Memory.h>

struct longBowMeasureTime {
    struct timeval start;
    struct timeval stop;
    unsigned int iterations;
};

LongBowMeasureTime *
longBowMeasureTime_Start(unsigned int iterations)
{
    LongBowMeasureTime *result = longBowMemory_Allocate(sizeof(LongBowMeasureTime));

    if (result != NULL) {
        gettimeofday(&result->start, NULL);
        result->iterations = iterations;
        result->stop = (struct timeval) { .tv_sec = 0, .tv_usec = 0 };
    }

    return result;
}

LongBowMeasureTime *
longBowMeasureTime_Stop(LongBowMeasureTime *measure)
{
    if (measure != NULL) {
        gettimeofday(&measure->stop, NULL);
    }

    return measure;
}

uint64_t
longBowMeasureTime_GetMicroseconds(const LongBowMeasureTime *measure)
{
    struct timeval result;
    timersub(&(measure->stop), &(measure->start), &result);

    return ((uint64_t) result.tv_sec * 1000000ULL) + ((uint64_t) result.tv_usec);
}

uint64_t
longBowMeasureTime_GetNanoseconds(const LongBowMeasureTime *measure)
{
    struct timeval result;
    timersub(&(measure->stop), &(measure->start), &result);

    return ((uint64_t) result.tv_sec * 1000000000ULL) + ((uint64_t) result.tv_usec * 1000);
}

unsigned int
longBowMeasureTime_CountDown(LongBowMeasureTime *measure)
{
    return measure->iterations--;
}

bool
longBowMeasureTime_Report(LongBowMeasureTime *measure, const char *file, const char *function, unsigned int line)
{
    struct timeval result;
    if (measure->stop.tv_sec == 0 && measure->stop.tv_usec == 0) {
        longBowMeasureTime_Stop(measure);
    }

    timersub(&(measure->stop), &(measure->start), &result);
    printf("%s %s %d %ld.%06ld\n", file, function, line, result.tv_sec, (long) result.tv_usec);
    return true;
}

void
longBowMeasureTime_Destroy(LongBowMeasureTime **instancePtr)
{
    longBowMemory_Deallocate((void **) instancePtr);
}
