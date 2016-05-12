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
 * @file traps.h
 * @ingroup runtime
 * @brief Runtime and Test Traps
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_traps_h
#define LongBow_traps_h

/**
 * @def trapUnrecoverableState
 * @brief Lay a trap to report an unrecoverable state in program execution.
 *
 * @param ... A printf(3) format string of explanitory text and values
 */
#define trapUnrecoverableState(...) \
    longBowTrap(&LongBowTrapUnrecoverableState, "Unrecoverable State: " __VA_ARGS__)

/**
 * @def trapNotImplemented
 * @brief Lay a trap to report and abort an unimplemented capability.
 *
 * @param ... A printf(3) format string of explanitory text and values
 */
#define trapNotImplemented(...) \
    longBowTrap(&LongBowTrapNotImplemented, "Feature not implemented: " __VA_ARGS__)

/**
 * @def trapIllegalValue
 * @brief Trap an illegal value.
 *
 * To used for capturing parameter validation, for example.
 *
 * @param [in] argumentName A name that is displayed in the report message.
 * @param [in] ... A printf format string and associated parameters.
 */
#define trapIllegalValue(argumentName, ...) \
    longBowTrap(&LongBowTrapIllegalValue, "Illegal value for '" #argumentName "': " __VA_ARGS__)

/**
 * @def trapIllegalValueIf
 * @brief Trap an illegal value if a condition is met.
 *
 * To used for the case where the value is valid
 * (eg. it is the correct type) but is an illegal value to be used in the context in which it was attempted to be applied.
 *
 * @param [in] condition A logical expression that if true, induces this trap.
 * @param [in] ... A printf format string and associated parameters.
 */
#define trapIllegalValueIf(condition, ...) \
    longBowTrapIf(&LongBowTrapIllegalValue, condition, "Illegal value: " __VA_ARGS__)

/**
 * @def trapInvalidValueIf
 * @brief Trap an invalid value if a condition is met.
 *
 * Used for capturing parameter validation.
 * For example, a composite value (C struct) has an internally invalid state for example.
 *
 * @param [in] condition A logical expression that if true, induces this trap.
 * @param [in] ... A printf format string and associated parameters.
 */
#define trapInvalidValueIf(condition, ...) \
    longBowTrapIf(&LongBowTrapInvalidValue, condition, "Invalid value: " __VA_ARGS__)

/**
 * @def trapOutOfBounds
 * @brief Trap an out-of-bounds condition on an index.
 *
 * @param [in] index The index that is out of bounds.
 * @param [in] ... A printf format string and associated parameters.
 */
#define trapOutOfBounds(index, ...) \
    longBowTrap(&LongBowTrapOutOfBounds, "Element out of bounds, " #index ": " __VA_ARGS__)

/**
 * @def trapOutOfBoundsIf
 * @brief Trap an out-of-bounds condition for a specific value.
 *
 * @param [in] condition A logical expression that if true, induces this trap.
 * @param [in] ... A printf format string and associated parameters.
 */
#define trapOutOfBoundsIf(condition, ...) \
    longBowTrapIf(&LongBowTrapOutOfBounds, condition, "Out of bounds: " __VA_ARGS__)

/**
 * @def trapOutOfMemory
 * @brief Signal that no more memory could be allocated.
 *
 * @param ... A printf format string and accompanying parameters.
 */
#define trapOutOfMemory(...) \
    longBowTrap(&LongBowTrapOutOfMemoryEvent, "Out of memory. " __VA_ARGS__)

/**
 * @def trapOutOfMemoryIf
 * @brief  Signal that no more memory could be allocated.
 *
 * @param [in] condition A logical expression that if true, induces this trap.
 * @param [in] ... A printf format string and associated parameters.
 */
#define trapOutOfMemoryIf(condition, ...) \
    longBowTrapIf(&LongBowTrapOutOfMemoryEvent, condition, "Out of memory. " __VA_ARGS__)

/**
 * @def trapUnexpectedState
 * @brief Signal that an unexpected or inconsistent state was encountered.
 *
 * @param ... A printf format string and accompanying parameters.
 */
#define trapUnexpectedState(...) \
    longBowTrap(&LongBowTrapUnexpectedStateEvent, "Unexpected state. " __VA_ARGS__)

/**
 * @def trapUnexpectedStateIf
 * @brief If the given condition is true, signal that an unexpected state was encountered .
 *
 * @param [in] condition A logical expression that if true, induces this trap.
 * @param [in] ... A printf format string and associated parameters.
 */
#define trapUnexpectedStateIf(condition, ...) \
    longBowTrapIf(&LongBowTrapUnexpectedStateEvent, condition, "Unexpected state: " __VA_ARGS__)

/**
 * @def trapCoreDump
 * @brief Send a SIGTRAP to the current process.
 */
#define trapCoreDump() \
    kill(0, SIGTRAP);

/**
 * @def trapCannotObtainLock
 * @brief Signal that a lock could not be obtained.
 *
 * @param ... A printf format string and accompanying parameters.
 */
#define trapCannotObtainLock(...) \
    longBowTrap(&LongBowTrapCannotObtainLockEvent, "Cannot obtain lock " __VA_ARGS__)

/**
 * @def trapCannotObtainLock
 * @brief Signal that a lock could not be obtained.
 *
 * @param ... A printf format string and accompanying parameters.
 */
#define trapCannotObtainLockIf(condition, ...) \
    longBowTrapIf(&LongBowTrapCannotObtainLockEvent, condition, "Cannot obtain lock " __VA_ARGS__)

#endif
