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
 * @file longBow_String.h
 * @brief <#Brief Description#>
 *
 * <#Detailed Description#>
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef __LongBow__longBow_String__
#define __LongBow__longBow_String__

#include <stdbool.h>
#include <stdio.h>

#include <LongBow/private/longBow_ArrayList.h>

struct longbow_String;
typedef struct longbow_string LongBowString;

/**
 * Create a LongBowString
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in] initialSize The initial buffer size to allocate for the string.
 *
 * @return non-NULL A pointer to a valid LongBowString instance.
 * @return NULL Memory could not be allocated.
 *
 */
LongBowString *longBowString_Create(const size_t initialSize);

/**
 * Create a `LongBowString` instance containing the formatted result of the given format string and parameters.
 *
 * @param [in] format A pointer to a valid LongBowString instance.
 *
 * @return The a LongBowString instance that must be deallocated via longBowString_Deallocate.
 */
LongBowString *longBowString_CreateFormat(const char *format, ...) __attribute__((format(printf, 1, 2)));

/**
 * Destroy a LongBowString instance.
 *
 * The pointer will be set to zero on return.
 *
 * @param [in,out] stringPtr A pointer to a valid LongBowString instance.
 */
void longBowString_Destroy(LongBowString **stringPtr);

/**
 * Append to the given LongBowString instance the formatted result of the given format string and parameters.
 *
 * @param [in] string A pointer to a valid LongBowString instance.
 *
 * @return The value of @p string
 */
LongBowString *longBowString_Format(LongBowString *string, const char *format, ...) __attribute__((format(printf, 2, 3)));

/**
 * Determine if a string begins with a specific prefix.
 *
 * @param [in] string A nul-terminated C string.
 * @param [in] prefix A nul-terminated C string.
 *
 * @return true The value of @p string starts with @p prefix.
 * @return false The value of @p string does not start with @p prefix.
 *
 * Example:
 * @code
 * {
 *     bool result = longBowString_StartsWith("Hello World", "Hello");
 * }
 * @endcode
 */
bool longBowString_StartsWith(const char *string, const char *prefix);

/**
 * Determine if a nul-terminated C string is equal to another.
 *
 * @param [in] string A nul-terminated C string.
 * @param [in] other A nul-terminated C string.
 *
 * @return true The value of @p string starts with @p prefix.
 * @return false The value of @p string does not start with @p prefix.
 *
 * Example:
 * @code
 * {
 *     bool result = longBowString_StartsWith("Hello World", "Hello");
 * }
 * @endcode
 */
bool longBowString_Equals(const char *string, const char *other);

/**
 * Produce a LongBowArrayList containing the tokens for the given @p string
 * where each token is separated by characters in the string @p separators.
 *
 * @param [in] string A nul-terminated C string.
 * @param [in] separators A nul-terminated C string containing the characters that separate the tokens.
 *
 * @return non-NULL A valid LongBowArrayList containing the tokens of the string.
 * @return NULL Memory could not be allocated.
 *
 * Example:
 * @code
 * {
 *     LongBowArrayList *result = longBowString_Tokenise("Hello World", " ");
 *         ....
 *     longBowArrayList_Destroy(&result);
 * }
 * @endcode
 */
LongBowArrayList *longBowString_Tokenise(const char *string, const char *separators);

/**
 * Produce a nul-terminated C string from the given LongBowString instance.
 *
 * @param [in] string A pointer to a valid LongBowString instance.
 *
 * @return non-NULL A pointer to a nul-terminated C string that must be deallocated via free(3).
 */
char *longBowString_ToString(const LongBowString *string);

/**
 * Write the contents of the given LongBowString instance to the specified FILE output stream.
 *
 * @param [in] string A pointer to a valid LongBowString instance.
 * @param [in] fp A pointer to a valid FILE instance.
 *
 * @return true All of the string was successfully written.
 * @return false All of the string was not successfully written.
 */
bool longBowString_Write(const LongBowString *string, FILE *fp);

#endif /* defined(__LongBow__longBow_String__) */
