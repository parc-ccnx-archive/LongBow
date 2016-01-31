/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @file longBow_Location.h
 * @ingroup internals
 * @brief LongBow Source File Location
 *
 * LongBow records events during execution and insofar that it's possible,
 * it records the source code location information for reporting.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Location_h
#define LongBow_longBow_Location_h

#include <stdint.h>

struct longbow_location;
/**
 * @typedef LongBowLocation
 */
typedef struct longbow_location LongBowLocation;

/**
 * Create a new LongBow location within a source code file.
 *
 * @param [in] fileName The file target of the location.
 * @param [in] functionName The function target of the location.
 * @param [in] lineNumber The exact line number within the target file.
 *
 * @return A pointer to an allocated LongBowLocation instance that must be deallocated via `longBowLocation_Destroy()`.
 *
 * Example:
 * @code
 * {
 *     LongBowLocation *location = longBowLocation_Create("test.c", "main", 101);
 * }
 * @endcode
 */
LongBowLocation *longBowLocation_Create(const char *fileName, const char *functionName, uint32_t lineNumber);

/**
 * Destroy the `LongBowLocation` instance.
 *
 * @param [in,out] locationPtr A pointer to the `LongBowLocation` instance to be destroyed.
 *
 * Example:
 * @code
 * {
 *     LongBowLocation *location = longBowLocation_Create("test.c", "main", 101);
 *     ...
 *     longBowLocation_Destroy(&location);
 * }
 * @endcode
 */
void longBowLocation_Destroy(LongBowLocation **locationPtr);

/**
 * Create a human readable representation of the `LongBowLocation` instance.
 *
 * @param [in] location The `LongBowLocation` instance from which to generate the string representation.
 *
 * @return An allocated, null-terminated C string that must be freed via free().
 *
 * Example:
 * @code
 * {
 *     LongBowLocation *location = longBowLocation_Create("test.c", "main", 101);
 *     char *stringRep = longBowLocation_ToString(location);
 *     ...
 *     longBowLocation_Destroy(&location);
 * }
 * @endcode
 */
char *longBowLocation_ToString(const LongBowLocation *location);
#endif // LongBow_longBow_Location_h
