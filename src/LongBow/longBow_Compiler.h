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
 * @file longBow_Compiler.h
 * @ingroup compiling
 * @brief LongBow compile time functionality.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_compiling_h
#define LongBow_compiling_h

/**
 * @def LONGBOW_GNUC_EXACTLY
 *
 * Compile-time test to determine if the compiler is the GNU C compiler with the specfied
 * version, revision and patch levels.
 *
 * @param [in] major The required major version number of the compiler.
 * @param [in] minor The required minor version number of the compiler.
 * @param [in] patch The required patch number of the compiler.
 *
 * @return true If the current compiler matches the requirements.
 *
 * Example:
 * @code
 * #if LONGBOW_GNUC_EXACTLY(4,2,1)
 *   printf("Hello GNU compiler 4.2.1\n");
 * #endif
 * @endcode
 *
 * @see LONGBOW_GNUC_ATLEAST
 */
#ifdef __GNUC__
#  define LONGBOW_GNUC_EXACTLY(major, minor, patch) \
    (__GNUC__ == major) && (__GNUC_MINOR__ = minor) && (__GNUC_PATCHLEVEL__ == patch)
#else
#  define LONGBOW_GNUC_EXACTLY(major, minor, patch) \
    (0)
#endif

/**
 * @def LONGBOW_GNUC_ATLEAST
 *
 * Compile-time test to determine if the compiler is the GNU C compiler with at least the specfied
 * version, revision and patch levels.
 *
 * @param [in] major The minimum required major version number of the compiler.
 * @param [in] minor The minimum required minor version number of the compiler.
 * @param [in] patch The minimum required patch number of the compiler.
 *
 * @return true If the current compiler matches the requirements.
 * @return false If the current compiler fails to match the requirements.
 *
 * Example:
 * @code
 * #if LONGBOW_GNUC_ATLEAST(4,0,0)
 *   printf("Hello GNU compiler 4.x\n");
 * #endif
 * @endcode
 *
 * @see LONGBOW_GNUC_EXACTLY
 */
#ifdef __GNUC__
#  define LONGBOW_GNUC_ATLEAST(major, minor, patch) \
    (__GNUC__ >= major) && (__GNUC_MINOR__ > minor) && (__GNUC_PATCHLEVEL__ >= patch)
#else
#  define LONGBOW_GNUC_ATLEAST(major, minor, patch) \
    (0)
#endif

/**
 * @def LONGBOW_CLANG_EXACTLY
 *
 * Compile-time test to determine if the compiler is the Clang C compiler with the specfied
 * version, revision and patch levels.
 *
 * @param [in] major The required major version number of the compiler.
 * @param [in] minor The required minor version number of the compiler.
 * @param [in] patch The required patch number of the compiler.
 *
 * @return true If the current compiler matches the requirements.
 *
 * Example:
 * @code
 * #if LONGBOW_CLANG_EXACTLY(5,0,0)
 *   printf("Hello Clang 5.0.0\n");
 * #endif
 * @endcode
 *
 * @see LONGBOW_CLANG_ATLEAST
 */
#ifdef __clang__
#  define LONGBOW_CLANG_EXACTLY(major, minor, patch) \
    (__clang_major__ == major) && (__clang_major__ = minor) && (__clang_patchlevel__ == patch)
#else
#  define LONGBOW_CLANG_EXACTLY(major, minor, patch) \
    (0)
#endif

/**
 * @def LONGBOW_CLANG_ATLEAST
 *
 * Compile-time test to determine if the compiler is the GNU C compiler with at least the specfied
 * version, revision and patch levels.
 *
 * @param [in] major The minimum required major version number of the compiler.
 * @param [in] minor The minimum required minor version number of the compiler.
 * @param [in] patch The minimum required patch number of the compiler.
 *
 * @return true If the current compiler matches the requirements.
 * @return false If the current compiler fails to match the requirements.
 *
 * Example:
 * @code
 * #if LONGBOW_CLANG_ATLEAST(5,0,0)
 *   printf("Hello Clang compiler 5.x\n");
 * #endif
 * @endcode
 *
 * @see LONGBOW_CLANG_EXACTLY
 */
#ifdef __clang__
#  define LONGBOW_CLANG_ATLEAST(major, minor, patch) \
    (__clang_major__ >= major) && (__clang_major__ > minor) && (__clang_patchlevel__ >= patch)
#else
#  define LONGBOW_CLANG_ATLEAST(major, minor, patch) \
    (0)
#endif

/**
 * @def LONGBOW_START_DEPRECATED_WARNINGS
 *
 * Compile-time preprocessing to signal the compiler to not report the use of deprecated functions.
 *
 * Example:
 * @code
 * LONGBOW_STOP_DEPRECATED_WARNINGS
 *  someDeprecatedFunction();
 * @endcode
 *
 * @see LONBOW_STOP_DEPRECATED_WARNINGS
 */

/**
 * @def LONGBOW_STOP_DEPRECATED_WARNINGS
 *
 * Compile-time preprocessing to signal the compiler to report the use of deprecated functions.
 *
 * Example:
 * @code
 * LONGBOW_STOP_DEPRECATED_WARNINGS
 *  someDeprecatedFunction();
 * @endcode
 *
 * @see LONBOW_START_DEPRECATED_WARNINGS
 */
#if LONGBOW_CLANG_ATLEAST(5, 0, 0) || LONGBOW_GNUC_ATLEAST(4, 6, 0)
#  define LONGBOW_STOP_DEPRECATED_WARNINGS \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")

#  define LONGBOW_START_DEPRECATED_WARNINGS \
    _Pragma("GCC diagnostic pop")

#elif __clang__ || __GNUC__

#  define LONGBOW_STOP_DEPRECATED_WARNINGS \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")

#  define LONGBOW_START_DEPRECATED_WARNINGS \
    _Pragma("GCC diagnostic warning \"-Wdeprecated-declarations\"")

#else

#  define LONGBOW_STOP_DEPRECATED_WARNINGS /* nothing */

#  define LONGBOW_START_DEPRECATED_WARNINGS /* nothing */
#endif

/**
 * @def LongBowCompiler_IgnoreInitializerOverrides
 *
 * Compile-time preprocessing to signal the compiler to not report the use of structure initializer overrides.
 *
 * Example:
 * @code
 * LongBowCompiler_IgnoreInitializerOverrides
 *  struct foo {
 *     int a;
 *  } instance = {
 *      .a = 1,
 *      .a = 1
 *  };
 * LongBowCompiler_WarnInitializerOverrides
 * @endcode
 *
 * @see LongBowCompiler_WarnInitializerOverrides
 */
#if LONGBOW_CLANG_ATLEAST(5, 0, 0)
#  define LongBowCompiler_IgnoreInitializerOverrides \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Winitializer-overrides\"")

#  define LongBowCompiler_WarnInitializerOverrides \
    _Pragma("GCC diagnostic pop")

#elif LONGBOW_GNUC_ATLEAST(4, 6, 0)
#  define LongBowCompiler_IgnoreInitializerOverrides \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"")

#  define LongBowCompiler_WarnInitializerOverrides  \
    _Pragma("GCC diagnostic pop")

#elif __clang__ || __GNUC__
#  define LongBowCompiler_IgnoreInitializerOverrides \
    _Pragma("GCC diagnostic ignored \"-Woverride-init\"")

#  define LongBowCompiler_WarnInitializerOverrides \
    _Pragma("GCC diagnostic warning \"-Woverride-init\"")

#else

#  define LongBowCompiler_IgnoreInitializerOverrides /* nothing */

#  define LongBowCompiler_WarnInitializerOverrides /* nothing */
#endif

/**
 * @def LONGBOW_STOPWARNINGS_UnusedVariable
 *
 * Compile-time preprocessing to signal the compiler to report unused variables.
 *
 * Example:
 * @code
 * LONGBOW_STOPWARNINGS_UnusedVariable
 * void
 * foo(int unusedVariable)
 * {
 *    return;
 * }
 * LONGBOW_STARTWARNINGS_UnusedVariable
 * @endcode
 *
 * @see LONGBOW_STARTWARNINGS_UnusedVariable
 *
 * @def LONGBOW_STARTWARNINGS_UnusedVariable
 *
 * Compile-time preprocessing to signal the compiler to report unused variables.
 *
 * Example:
 * @code
 * LONGBOW_STOPWARNINGS_UnusedVariable
 * void
 * foo(int unusedVariable)
 * {
 *    return;
 * }
 * LONGBOW_STARTWARNINGS_UnusedVariable
 * @endcode
 *
 * @see LONGBOW_STARTWARNINGS_UnusedVariable
 */
#if LONGBOW_CLANG_ATLEAST(5, 0, 0)
#  define LONGBOW_STOPWARNINGS_UnusedVariable \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
#  define LONGBOW_STARTWARNINGS_UnusedVariable \
    _Pragma("GCC diagnostic pop")
#elif LONGBOW_GNUC_ATLEAST(4, 6, 0)
#  define LONGBOW_STOPWARNINGS_UnusedVariable \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
#  define LONGBOW_STARTWARNINGS_UnusedVariable  \
    _Pragma("GCC diagnostic pop")
#elif __clang__ || __GNUC__
#  define LONGBOW_STOPWARNINGS_UnusedVariable \
    _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
#  define LONGBOW_STARTWARNINGS_UnusedVariable \
    _Pragma("GCC diagnostic warning \"-Wunused-variable\"")
#else

#  define LONGBOW_STOPWARNINGS_UnusedVariable /* nothing */

#  define LONGBOW_STARTWARNINGS_UnusedVariable /* nothing */
#endif


#endif // LongBow_compiling_h
