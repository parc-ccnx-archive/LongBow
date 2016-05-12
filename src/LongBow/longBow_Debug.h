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
 * @file longBow_Debug.h
 * @ingroup internals
 * @brief Support for LongBow and Application Debugging.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Debug_h
#define LongBow_longBow_Debug_h

#include <stdint.h>
#include <string.h>
#include <sys/types.h>

#include <LongBow/longBow_Location.h>

typedef struct longbow_debug_criteria LongBowDebugCriteria;

/**
 * Pretty print memory on standard output.
 *
 * @param [in] memory A pointer to memory.
 * @param [in] length The number of bytes to display.
 */
void longBowDebug_MemoryDump(const char *memory, size_t length);

/**
 * Generate and send a message to the specified location.
 *
 * @param [in] criteria Debug criteria.
 * @param [in] location The location to which the message is sent.
 * @param [in] format The format string for the message.
 * @param [in] ... Remaining arguments for the message string.
 */
void longBowDebug_Message(LongBowDebugCriteria *criteria, const LongBowLocation *location, const char *format, ...);

/**
 * Write data in an array to a file.
 *
 * Data is written to the specified file from the supplied array.
 *
 * @param [in] fileName The name of the to write to.
 * @param [in] data A pointer to an array of bytes to write.
 * @param [in] length The number of bytes to write.
 *
 * @return The number of bytes written.
 *
 * Example:
 * @code
 * {
 *     size_t numBytesWritten = longBowDebug_WriteFile("log.out", "error", 6);
 * }
 * @endcode
 *
 * @see longBowDebug_ReadFile
 */
ssize_t longBowDebug_WriteFile(const char *fileName, const char *data, size_t length);

/**
 * Read data from a file into an allocated array.
 *
 * Data is read from the specified file into an allocated byte array which must be deallocated by the caller via {stdlib free()}.
 *
 * For convenience the allocate buffer exceeds the size of the file by one byte, which is set to zero.
 * This permits using the result directly as a nul-terminated C string.
 *
 * @param [in] fileName The name of the file to read from.
 * @param [in] data A pointer to a character pointer that will be updated with the address of the read data.
 *
 * @return The number of bytes read, or -1 if there was an error.
 *
 * Example:
 * @code
 * {
 *     char *buffer = NULL;
 *     size_t numBytesRead = longBowDebug_ReadFile("log.out", &buffer);
 *     // use buffer as needed
 * }
 * @endcode
 *
 * @see longBowDebug_WriteFile
 */
ssize_t longBowDebug_ReadFile(const char *fileName, char **data);
#endif
