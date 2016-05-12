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
 * @file assertions.h
 * @ingroup runtime
 * @brief Runtime and Test Assertions
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_assertions_h
#define LongBow_assertions_h

#ifndef LongBow_runtime_h
#error "Do not include LongBow/assertions.h directly.  Include LongBow/runtime.h"
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <LongBow/traps.h>
#include <LongBow/tests.h>

#include <LongBow/longBow_Location.h>
#include <LongBow/longBow_Event.h>

/**
 * @def assertTrue
 * @brief Assert that a condition is true.
 *
 * @param condition If false, the assertion triggers.
 * @param ... A printf formatting string (required) and parameters (optional).
 *
 * Example:
 * @code
 * {
 *     assertTrue(2 + 2 == 4, "Adding 2 + 2 did not equal 4.");
 * }
 * @endcode
 */
#define assertTrue(condition, ...) longBowAssert(&LongBowAssertEvent, (condition), __VA_ARGS__)

/**
 * @def assertFalse
 * @brief Assert that a condition is false.
 *
 * @param condition If true, the assertion triggers.
 * @param ... A printf formatting string (required) and parameters (optional).
 * Example:
 * @code
 * {
 *     assertFalse(2 + 2 == 5, "Adding 2 + 2 must not equal 5.");
 * }
 * @endcode
 */
#define assertFalse(condition, ...) longBowAssert(&LongBowAssertEvent, !(condition), __VA_ARGS__)

/**
 * @def assertNotNull
 * @brief Assert that the given value is not NULL.
 *
 * @param x     If the value is NULL, the assertion triggers.
 * @param ...   A printf formatting string (required) and parameters (optional).
 * Example:
 * @code
 * void
 * function(char *p)
 * {
 *     assertNotNull(p, "Parameter must not be NULL");
 * }
 * @endcode
 */
#define assertNotNull(x, ...) longBowAssert(&LongBowAssertEvent, (x) != NULL, __VA_ARGS__)

/**
 * @def assertNull
 * @brief Assert that the given value is NULL.
 *
 * @param x The value to test.
 * @param ... A printf formatting string (required) and parameters (optional).
 * Example:
 * @code
 * void
 * function(char *p)
 * {
 *     assertNull(p, "Parameter must be NULL");
 * }
 * @endcode
 */
#define assertNull(x, ...) longBowAssert(&LongBowAssertEvent, (x) == NULL, __VA_ARGS__)

/**
 * @def assertAligned
 * @brief  Assert that the given address is aligned according to `alignment`.
 *
 * Return true of the given address is aligned according to alignment.
 * The value for alignment must be a power of 2.

 * @param address A pointer to memory
 * @param alignment A power of 2 representing the memory alignment of address.
 * @param ... A printf formatting string (required) and parameters (optional).
 *
 * Example:
 * @code
 * void
 * function(void *p)
 * {
 *     assertAligned(p, 4, "Parameter must be aligned on 4 byte boundaries");
 * }
 * @endcode
 */
#define assertAligned(address, alignment, ...) \
    longBowAssert(&LongBowAssertEvent, longBowRuntime_TestAddressIsAligned((address), (alignment)), __VA_ARGS__)

/**
 * @def assertEqualStrings
 * @brief Assert that two strings are equal.
 *
 * @param expected
 * @param actual
 * @param ... A printf formatting string (required) and parameters (optional).
 *
 * Example:
 * @code
 * {
 *     assertEqualStrings("hello", "world");
 * }
 * @endcode
 */
#define assertEqualStrings(expected, actual) \
    longBowAssert(&LongBowAssertEvent, strcmp((expected), (actual)) == 0, "Expected '%s' actual '%s'", (expected), (actual))

/**
 * @def assertEqual
 * @brief Assert that two values are equal, using a canonical string message.
 */
#define assertEqual(expected, actual, format) \
    assertTrue((expected) == (actual), "Expected=" format " actual=" format, (expected), (actual))
#endif /* ASSERTIONS_H_ */

