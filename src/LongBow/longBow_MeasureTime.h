/*
 * Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @file longBow_MeasureTime.h
 *
 * Measure elapsed time, providing various fetching and reporting mechanisms.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef __LongBow__longBow_Measure__
#define __LongBow__longBow_Measure__
#include <stdint.h>
#include <stdbool.h>

#ifdef LongBow_DISABLE_MEASUREMENTS
#  define longBowMeasureTime(_iterations_)
#else
#  define longBowMeasureTime(_iterations_) for (LongBowMeasureTime *_measure = longBowMeasureTime_Start(_iterations_); \
     longBowMeasureTime_CountDown(_measure) ? true : (longBowMeasureTime_Report(_measure, __FILE__, __func__, __LINE__), longBowMeasureTime_Destroy(&_measure), false); )

#endif

struct longBowMeasureTime;
typedef struct longBowMeasureTime LongBowMeasureTime;

/**
 * Create and start a `LongBowMeasureTime` instance.
 *
 * @param [in] iterations The number of iterations to perform when used with `longBowMeasureTime_CountDown`
 *
 * @return non-NULL A pointer to a valid LongBowMeasureTime instance that must be destroyed by `longBowMeasureTime_Destroy`
 */
LongBowMeasureTime *longBowMeasureTime_Start(unsigned int iterations);

/**
 * Report on the `LongBowMeasureTime` instance.
 *
 * @param [in] measure A pointer to a valid LongBowMeasureTime instance.
 * @param [in] file A pointer to a nul-terminated C string representing the file name causing the report.
 * @param [in] function A pointer to a nul-terminated C string representing the function name causing the report.
 * @param [in] line An unsigned integer representing the line number of the file causing the report.
 *
 * @return true The report was successful.
 */
bool longBowMeasureTime_Report(LongBowMeasureTime *measure, const char *file, const char *function, unsigned int line);

/**
 * A simple count-down supporting measurement iterations.
 *
 * See {@link longBowMeasureTime} for an example.
 *
 * @param [in] measure A pointer to a valid LongBowMeasureTime instance.
 *
 * @return The current value of the counter.
 */
unsigned int longBowMeasureTime_CountDown(LongBowMeasureTime *measure);

/**
 * Get the total number of microseconds represented by the `LongBowMeasureTime` instance.
 *
 * @param [in] measure A pointer to a valid LongBowMeasureTime instance.
 *
 * @return The number of microseconds represented by the `LongBowMeasureTime` instance.
 */
uint64_t longBowMeasureTime_GetMicroseconds(const LongBowMeasureTime *measure);

/**
 * Get the total number of nanoseconds represented by the `LongBowMeasureTime` instance.
 *
 * @param [in] measure A pointer to a valid LongBowMeasureTime instance.
 *
 * @return The number of nanoseconds represented by the `LongBowMeasureTime` instance.
 */
uint64_t longBowMeasureTime_GetNanoseconds(const LongBowMeasureTime *measure);

/**
 * Destroy a valid `LongBowMeasureTime` instance.
 *
 * @param [in,out] instancePtr A pointer to a pointer to a valid LongBowMeasureTime instance, that will be set to zero.
 */
void longBowMeasureTime_Destroy(LongBowMeasureTime **instancePtr);

#endif /* defined(__LongBow__longBow_Measure__) */
