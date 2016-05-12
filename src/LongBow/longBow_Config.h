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
 * @file longBow_Config.h
 * @ingroup internals
 * @brief Support for LongBow Configuration
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LONGBOWCONFIGURATION_H_
#define LONGBOWCONFIGURATION_H_
#include <stdbool.h>
#include <stdint.h>

struct longbow_configuration;

/**
 * @typedef LongBowConfig
 * @brief The LongBow Configuration
 */
typedef struct longbow_configuration LongBowConfig;

/**
 * Destroy a LongBowConfig instance.
 *
 * @param [in,out] configPtr A pointer to a LongBowConfig instance pointer.
 */
void longBowConfig_Destroy(LongBowConfig **configPtr);

/**
 * Create a LongBowConfig structure instance from the given array of parameters.
 *
 * The function parses argv style arguments and composes a LongBowConfig structure.
 *
 * The argv-style arguments may include parameters not related to creating a LongBowConfig structure.
 *
 * For example, the arguments may only be `--help` and prints a help message but doesn't create a `LongBowConfig` structure.
 *
 * @param [in] argc The number of elements in the `argv` array.
 * @param [in] argv An array of nul-terminated C strings.
 * @param [in] mainFileName The string printed for the `--main` option.
 *
 * @return non-NULL A LongBowConfig structure instance suitable for running a test
 * @return NULL Nothing suitable for running a test (not an error).
 */
LongBowConfig *longBowConfig_Create(int argc, char *argv[], const char *mainFileName);

/**
 * Get a property stored in the configuration.
 * @param [in] config A pointer to a valid LongBowConfig instance.
 * @param [in] format A pointer to a valid, nul-terminated format string.
 *
 * @return non-NULL A pointer to nul-terminated, C string.
 */
const char *longBowConfig_GetProperty(const LongBowConfig *config, const char *format, ...);

/**
 * Set the property @p name to @p value
 *
 * @param [in] config A pointer to a valid LongBowConfig instance.
 *
 * @return true
 * @return true
 */
bool longBowConfig_SetProperty(const LongBowConfig *config, const char *name, const char *value);

/**
 * Get the property @p name interpreted as a 32-bit integer.
 *
 * @param [in] config A pointer to a valid LongBowConfig instance.
 *
 * @return The property @p name interpreted as a 32-bit integer.
 */
uint32_t longBowConfig_GetUint32(const LongBowConfig *config, uint32_t defaultValue, const char *format, ...);

/**
 * Get the value of the configuration property named by the formatted property name.
 * If the given LongBowConfig instance is not available, or the property is not present, the default value is returned.
 *
 * @param [in] config A pointer to a valid LongBowConfig instance.
 * @param [in] defaultValue Either true or false.
 * @param [in] format A printf format string followed by appropriate parameters used to construct the property name.
 *
 * @return true The property was present with the value true, or the property was not present and the default value is true.
 * @return false The property was present with the value false, or the property was not present and the default value is false.
 */
bool longBowConfig_GetBoolean(const LongBowConfig *config, bool defaultValue, const char *format, ...);

/**
 * Return `true` if the given `LongBowConfig` instance specifies that test cases are to be run in a sub-process.
 *
 * @param [in] config A pointer to a valid LongBowConfig instance.
 * @return true if the given specification stipulates tests are to run in a sub-process.
 */
bool longBowConfig_IsRunForked(const LongBowConfig *config);

/**
 * Indicate if the given configuration is specifying the 'trace' flag.
 *
 * @param [in] config A pointer to a valid LongBowConfig instance.
 *
 * @return true The given configuration is specifying the 'trace' flag.
 * @return false The given configuration is not specifying the 'trace' flag.
 *
 * Example:
 * @code
 * if (longBowConfig_IsTrace(longBowRunner_GetConfiguration(testRunner)) {
 *     longBowTrace_Report(testRunner->configuration);
 * }
 * @endcode
 */
bool longBowConfig_IsTrace(const LongBowConfig *config);

#endif // LONGBOWCONFIGURATION_H_
