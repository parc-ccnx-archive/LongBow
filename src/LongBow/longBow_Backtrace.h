/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @file longBow_Backtrace.h
 * @ingroup internals
 * @brief Support for Stack Traces
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Backtrace_h
#define LongBow_longBow_Backtrace_h
#include <stdint.h>

struct longbow_backtrace;
/**
 * @typedef LongBowBacktrace
 * @brief A Backtrace representation.
 */
typedef struct longbow_backtrace LongBowBacktrace;

/**
 * Create a `LongBowBacktrace`.
 *
 * The backtrace includes depth number of elements from the stack.
 *
 * @param [in] depth  The number of elements from the stack to include.
 * @param [in] offset The offset of the stack to start the Backtrace.
 * @return A pointer to an allocated LongBowBacktrace instance.
 */
LongBowBacktrace *longBowBacktrace_Create(uint32_t depth, uint32_t offset);

/**
 * Get the array of symbols from the given `LongBowBacktrace instance`.
 *
 * @param [in] backtrace A pointer to a valid LongBowBacktrace instance.
 *
 * @return An array of nul-terminated, C strings each containing a symbolic representatino of the corresponding stack frame.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
char **longBowBacktrace_Symbols(const LongBowBacktrace *backtrace);
/**
 * Get the number of frames in the given LongBowBacktrace instance.
 *
 * @param [in] backtrace A pointer to a valid LongBowBacktrace instance.
 *
 * @return The number of frames in the LongBowBacktrace.
 */
unsigned int longBowBacktrace_GetFrameCount(const LongBowBacktrace *backtrace);

/**
 *
 * @param [in,out] backtracePtr A pointer to a pointer to a valid LongBowBacktrace instance.
 */
void longBowBacktrace_Destroy(LongBowBacktrace **backtracePtr);

/**
 *
 * @param [in] backtrace A pointer to a valid LongBowBacktrace instance.
 * @return An allocated C string that must be deallocated via longBowMemory_Deallocate().
 */
char *longBowBacktrace_ToString(const LongBowBacktrace *backtrace);
#endif
