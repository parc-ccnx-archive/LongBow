/*
 * Copyright (c) 2013-2014,2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @copyright (c) 2013-2014,2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>
#include <inttypes.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/param.h>

#include <LongBow/private/longBow_ArrayList.h>
#include <LongBow/unit-test.h>

#include <LongBow/longBow_UnitTesting.h>

bool
longBowUnitTesting_AssertEqualsContract(bool (*equalsFunction)(void *a, void *b), void *x, void *y, void *z, ...)
{
    va_list ap;
    va_start(ap, z);

    assertNotNull(x, "The value of x cannot be NULL.");
    assertNotNull(y, "The value of y cannot be NULL.");
    assertNotNull(z, "The value of z cannot be NULL.");

    assertFalse(x == y, "The value x cannot be the same as y");
    assertFalse(x == z, "The value x cannot be the same as z");
    assertFalse(y == z, "The value y cannot be the same as z");

    assertTrue(equalsFunction(NULL, NULL), "Equality failed: Equals(NULL, NULL) must be true");

    assertFalse(equalsFunction(x, NULL), "Equality failed: The value of x must not be Equal to NULL.");
    assertFalse(equalsFunction(NULL, x), "Equality failed: NULL must not be equal to the value of x.");

    assertTrue(equalsFunction(x, x),
               "Reflexive failed: for any non-null reference value x, equals(x, x) must return true.");

    assertTrue(equalsFunction(x, y),
               "Equality failed: The values of x and y must be Equal.");
    assertTrue(equalsFunction(x, z),
               "Equality failed: The values of x and z must be Equal.");

    assertTrue(equalsFunction(x, y) == equalsFunction(y, x),
               "Symmetric equality failed: equals(x, y) == equals(y, x) must true.");

    assertTrue((equalsFunction(x, y) == equalsFunction(y, z)) == equalsFunction(z, x),
               "Transitive equality failed: equals(x, y) == equals(y, z) == equals(z, x) must true.");

    int index = 0;
    for (void *value = va_arg(ap, void *); value != 0; value = va_arg(ap, void *)) {
        assertFalse(equalsFunction(x, value), "Value %d (@%p) must not be equal to x", index, value);
        assertTrue(equalsFunction(x, value) == equalsFunction(value, x),
                   "Symmetric equality failed: equals(x, value) == equals(value, x) must true.");
        index++;
    }

    va_end(ap);
    return true;
}

bool
longBowUnitTesting_AssertCompareToContract(int (*compareTo)(const void *a, const void *b),
                                           void *exemplar,
                                           void **equivalent,
                                           void **lesser,
                                           void **greater)
{
    assertNotNull(exemplar, "Parameter exemplar must not be NULL");
    assertNotNull(equivalent, "Parameter equivalent must not be NULL");
    assertNotNull(lesser, "Parameter less must not be NULL");
    assertNotNull(greater, "Parameter greater must not be NULL");

    assertTrue(compareTo(NULL, NULL) == 0,
               "Comparison of null values must be 0.");

    assertTrue(compareTo(exemplar, NULL) > 0,
               "Comparison of a non-null value to a null value must be > 0.");

    assertTrue(compareTo(NULL, exemplar) < 0,
               "Comparison of null value to a non-null value must be < 0.");

    assertTrue(compareTo(exemplar, exemplar) == 0,
               "Comparison of a value to itself must == 0");

    for (int i = 0; equivalent[i] != NULL; i++) {
        assertTrue(compareTo(exemplar, equivalent[i]) == 0,
                   "Comparison of the value to equivalent[%d] must == 0", i);
        assertTrue(compareTo(exemplar, equivalent[i]) == -compareTo(equivalent[i], exemplar),
                   "Requires sgn(compareTo(value, equivalent[%d])) == -sgn(equivalent[%d], value)", i, i);
    }
    for (int i = 0; lesser[i] != NULL; i++) {
        assertTrue(compareTo(exemplar, lesser[i]) > 0,
                   "Compare of value to lesser[%d] must be > 0", i);
        assertTrue(compareTo(exemplar, lesser[i]) == -compareTo(lesser[i], exemplar),
                   "Requires sgn(compareTo(value, lesser[%d])) == -sgn(lesser[%d], value)", i, i);
    }
    for (int i = 0; greater[i] != NULL; i++) {
        assertTrue(compareTo(exemplar, greater[i]) < 0,
                   "Compare to greater[%d] must be > 0", i);
        assertTrue(compareTo(exemplar, greater[i]) == -compareTo(greater[i], exemplar),
                   "Requires sgn(compareTo(value, greater[%d])) == -sgn(greater[%d], value)", i, i);
    }

    return true;
}
