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
 * @file longBow_Status.h
 * @ingroup testing
 * @brief A simple status representation for a LongBow Test Case.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Status_h
#define LongBow_longBow_Status_h

#include <stdbool.h>
#include <stdint.h>

/**
 * @typedef LongBowStatus
 * @brief The status of an individual Test Case, and aggregate Test Fixture, or Test Runner.
 *
 * Status is either successful or not and each has a subset of qualifiers.
 *
 * A successful status is an outright success, or a qualified success.
 *
 * Qualified success is a test that issued an explicit warning (via <code>testWarn(...)</code>),
 * was purposefully skipped (via <code>testSkip(...)</code>),
 * or is unimplemented (via <code>testUnimplemented(...)</code>).
 *
 * Correspondingly, an unsuccessful test is outright failure,
 * or a qualified failure.
 * Qualified values indicate that the test process received a signal during the test,
 * or either the Test Fixture set-up or tear-down steps signaled failure.
 *
 */
enum LongBowStatus {
    /**
     * Used for expressing the expected status.
     */
    LongBowStatus_DONTCARE        = -2,

    /**
     * The test was not run (initial state).
     */
    LongBowStatus_UNTESTED        = -1,

    /* successful */
    /**
     * The test was successful.
     */
    LONGBOW_STATUS_SUCCEEDED       =  0,
    /**
     * The test was successful, but with a warning.
     */

    LongBowStatus_WARNED          = 10,
    /**
     * The test was successful, but the tear down issued a warning.
     */

    LongBowStatus_TEARDOWN_WARNED = 11,

    /**
     * The test was purposefully skipped by the test implementor.
     */
    LONGBOW_STATUS_SKIPPED         = 21,

    /**
     * The test was incomplete because it signals that it is not implemented.
     */
    LongBowStatus_UNIMPLEMENTED   = 22,

    /**
     * The test ran but evaluated nothing.
     */
    LongBowStatus_IMPOTENT        = 23,

    /**
     * The setup function signals that all of the subordinate test cases must be skipped.
     */
    LONGBOW_STATUS_SETUP_SKIPTESTS = 24,

    /* failures */
    /**
     * The tests failed.
     */
    LONGBOW_STATUS_FAILED          = 1,

    /**
     * The test failed because it was stopped by a signal.
     */
    LongBowStatus_STOPPED         = 3,

    /**
     * The tear down of the test failed.
     *
     * This doesn't imply that the test failed.
     */
    LONGBOW_STATUS_TEARDOWN_FAILED = 4,

    /**
     * The test was incomplete because the setup for the test failed.
     */
    LONGBOW_STATUS_SETUP_FAILED    = 5,

    /**
     * The test was incomplete because a memory leak was detected.
     */
    LONGBOW_STATUS_MEMORYLEAK      = 6,

    /**
     * The test failed due to an uncaught signal.
     */
    LongBowStatus_SIGNALLED       = 100,

    /**
     * The limit of LongBowStatus values
     */
    LongBowStatus_LIMIT           = 200,
};
typedef enum LongBowStatus LongBowStatus;

/**
 * Compose a LongBowStatus from the given signalNumber.
 */
#define LongBowStatus_SIGNAL(signalNumber) (LongBowStatus_SIGNALLED + signalNumber)

/**
 * Generate a human readable, nul-terminated C string representation of the `LongBowStatus` value.
 *
 * @param [in] status A `LongBowStatus` value
 *
 * @return A pointer to an allocated C string that must be freed via stdlib.h free(3).
 *
 * Example:
 * @code
 * {
 *     LongBowStatus status = LONGBOW_STATUS_SUCCEEDED;
 *     printf("Status = %s\n", longBowStatus_ToString(status));
 * }
 * @endcode
 */
char *longBowStatus_ToString(LongBowStatus status);

/**
 * Return `true` if the given status indicates an outright or qualified success.
 *
 * Success, outright or qualified, encompasses `LONGBOW_STATUS_SUCCEEDED`,
 *  longBowStatus_IsWarning(status), or
 * longBowStatus_IsIncomplete(status)
 *
 * @param [in] status A `LongBowStatus` value.
 *
 * @return `true` if the given status indicated an outright or qualified success.
 *
 * Example:
 * @code
 * {
 *     LongBowStatus status = LONGBOW_STATUS_SUCCEEDED;
 *     printf("Is success? = %d\n", longBowStatus_IsSuccessful(status));
 * }
 * @endcode
 */
bool longBowStatus_IsSuccessful(LongBowStatus status);

/**
 * Return <code>true</code> if the given status indicates a failure.
 *
 * @param [in] status A `LongBowStatus` value.
 *
 * @return `true` if the given status indicated a failure.
 *
 * Example:
 * @code
 * {
 *     LongBowStatus status = LONGBOW_STATUS_FAILED;
 *     printf("Is warned? = %d\n", longBowStatus_IsFailed(status));
 * }
 * @endcode
 */
bool longBowStatus_IsFailed(LongBowStatus status);

/**
 * Return <code>true</code> if the given status indicates a warning.
 *
 * @param [in] status A `LongBowStatus` value.
 *
 * @return Return `true` if the given status indicate a warning.
 */
bool longBowStatus_IsWarning(LongBowStatus status);

/**
 * Return <code>true</code> if the given status indicates a test was incomplete.
 *
 * @param [in] status A `LongBowStatus` value.
 *
 * @return `true` if the given status indicated it was incomplete.
 *
 * Example:
 * @code
 * {
 *     LongBowStatus status = LONGBOW_STATUS_SKIPPED;
 *     printf("Is incomplete? = %d\n", longBowStatus_IsIncomplete(status));
 * }
 * @endcode
 */
bool longBowStatus_IsIncomplete(LongBowStatus status);

/**
 * Return <code>true</code> if the given status indicated a test induced a signal.
 *
 * @param [in] status A `LongBowStatus` value.
 *
 * @return `true` if the given status indicated a test induced a signal.
 *
 * Example:
 * @code
 * {
 *     LongBowStatus status = LongBowStatus_SIGNALLED;
 *     printf("Is signalled? = %d\n", longBowStatus_IsSignalled(status));
 * }
 * @endcode
 */
bool longBowStatus_IsSignalled(LongBowStatus status);
#endif // LONGBOWSTATUS_H_
