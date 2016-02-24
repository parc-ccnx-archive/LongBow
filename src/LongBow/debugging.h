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
 * @file debugging.h
 * @brief Debugging Utilities
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LongBow_debugging_h
#define LongBow_debugging_h

#include <LongBow/longBow_Debug.h>

#include <LongBow/longBow_MeasureTime.h>

/**
 * @def longBow_function
 * @brief The compile time function name.
 */
#if __STDC_VERSION__ >= 199901L
#    define longBow_function __func__
#else
#    define longBow_function ((const char *) 0)
#endif

/**
 * @def longBowDebug
 * @brief Print a debugging message.
 *
 * @param ... A printf-style format string followed by a variable number of parameters supplying values for the format string.
 */
#ifndef LONGBOW_DEBUG_DISABLED
#   define longBowDebug(...) \
    do { longBowDebug_Message(NULL, longBowLocation_Create(__FILE__, longBow_function, __LINE__), __VA_ARGS__); } while (0)
#else
#   define longBowDebug(...) \
    do { } while (0)
#endif
#endif
