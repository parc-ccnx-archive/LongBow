/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @file Reporting/longBowReport_Runtime.h
 * @ingroup reporting
 * @brief The LongBow Runtime Report Generator.
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 *
 * This header specifies the interface for an implementation of a LongBow Test Report generator.
 * Different implementations of a Test Report generator are used to connect to external environments to hook in
 * LongBow unit tests within a larger framework like an IDE or continuous integration system.
 *
 * There may be many different ways to report the summary of a LongBow Unit Test,
 * and the different ways implement the functions prescribed here.
 * The resulting object files are then linked with the unit-test according to the kind of report needed.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LONGBOW_REPORT_RUNTIME_H_
#define LONGBOW_REPORT_RUNTIME_H_

#include <LongBow/longBow_Event.h>

#include <LongBow/runtime.h>
#include <LongBow/unit-test.h>

struct longbow_report_config;
/**
 * @brief Configuration for a LongBow Test.
 */
typedef struct longbow_report_config LongBowReportConfig;

/**
 * @struct longbow_report_config
 * @brief The configuration information for a LongBow Test Report.
 */
struct longbow_report_config {
    struct {
        unsigned int untested : 1;
        unsigned int succeeded : 1;
        unsigned int warned : 1;
        unsigned int teardown_warned : 1;
        unsigned int skipped : 1;
        unsigned int unimplemented : 1;
        unsigned int failed : 1;
        unsigned int stopped : 1;
        unsigned int teardown_failed : 1;
        unsigned int setup_failed : 1;
        unsigned int signalled : 1;
    } suppress_report;  /**< Bit fields representing which report to suppress. */
};

/**
 * Create a LongBowReportConfiguration from a set of parameters.
 *
 * @param [in] argc The number of parameters in the argv array.
 * @param [in] argv An array of C strings.
 *
 * @return An allocated LongBowReportConfiguration instance that must be dellocted via longBowReport_Destroy.
 *
 * Example:
 * @code
 * {
 *     char *argv[2] = { "arg1", "arg2" };
 *     LongBowReportConfig *report = longBowReport_Create(2, argv);
 * }
 * @endcode
 */
LongBowReportConfig *longBowReportRuntime_Create(int argc, char *argv[]);

/**
 * Destroy a LongBowReportConfig instance.
 *
 * @param [in,out] configPtr A pointer to a LongBowReportConfig pointer. The value of configPtr will be set to zero.
 *
 * Example:
 * @code
 * {
 *     char *argv[2] = { "arg1", "arg2" };
 *     LongBowReportConfig *report = longBowReport_Create(2, argv);
 *     LongBowReport_Destroy(&report);
 * }
 * @endcode
 */
void longBowReportRuntime_Destroy(LongBowReportConfig **configPtr);

/**
 * Report a LongBowEvent.
 *
 * @param [in] event A pointer to a valid LongBowEvent instance.
 */
void longBowReportRuntime_Event(const LongBowEvent *event);

/**
 * Report a message.
 *
 * @param [in] message A pointer to a nul-terminated C string.
 */
void longBowReportRuntime_Message(const char *message, ...);

/**
 * Report an error message.
 *
 * An error message reports an unrecoverable error.
 *
 * @param [in] message A pointer to a nul-terminated C string.
 */
void longBowReportRuntime_Error(const char *message, ...);

/**
 * Report an error message.
 *
 * An error message reports an recoverable warning.
 *
 * @param [in] message A pointer to a nul-terminated C string.
 */
void longBowReportRuntime_Warning(const char *message, ...);

/**
 * Format a struct timeval structure.
 *
 * @param [in] time A struct timeval value.
 *
 * @return An allocated nul-terminated C string that must be freed via stdlib free(3).
 */
char *longBowReportRuntime_TimevalToString(const struct timeval time);

/**
 * Format a struct rusage struture.
 *
 * @param [in] rusage A pointer to a valid `struct rusage` instance.
 * @return An allocated nul-terminated C string that must be freed via stdlib free(3).
 */
char *longBowReportRuntime_RUsageToString(const struct rusage *rusage);
#endif // LONGBOW_REPORT_RUNTIME_H_
