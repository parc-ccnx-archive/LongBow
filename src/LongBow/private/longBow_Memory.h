/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
 * @file longBow_Memory.c
 * @ingroup internal
 * @brief Memory allocation and deallocation support.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Memory_h
#define LongBow_longBow_Memory_h

#include <stdint.h>

/**
 * Allocate `size` bytes of memory.
 *
 * @param [in] size The number of bytes to allocate
 *
 * @return non-NULL A pointer to allocated memory that must be deallocated via `longBowMemory_Deallocate`
 * @return NULL Memory could not be allocated.
 * @see longBowMemory_Deallocate
 */
void *longBowMemory_Allocate(const size_t size);

/**
 * Reallocate memory adjusting to a new size.
 *
 * @param [in] oldAllocation A pointer to memory previously allocated by `longBowMemory_Allocate` or `longBowMemory_Reallocate`
 * @param [in] newSize The number of bytes to allocate
 *
 * @return non-NULL A pointer to allocated memory that must be deallocated via `longBowMemory_Deallocate`
 * @return NULL Memory could not be allocated.
 * @see longBowMemory_Allocate
 */
void *longBowMemory_Reallocate(void *oldAllocation, const size_t newSize);

/**
 * Deallocate previously allocated memory.
 *
 * @param [in,out] pointerPointer A pointer to a pointer to allocated memory that will set to NULL.
 *
 * @see longBowMemory_Allocate
 */
void longBowMemory_Deallocate(void **pointerPointer);

/**
 * Duplicate a nul-terminated C string in allocated memory.
 *
 * @param [in] string The nul-terminated string to duplicate
 *
 * @return non-NULL A pointer to allocated memory that must be deallocated via `longBowMemory_Deallocate`
 * @return NULL Memory could not be allocated.
 *
 * Example:
 * @code
 * {
 *     char *copy = longBowMemory_StringCopy("Hello World");
 *
 *     longBowMemory_Deallocate((void **) &copy);
 * }
 * @endcode
 *
 * @see longBowMemory_Deallocate
 */
char *longBowMemory_StringCopy(const char *string);

/**
 * Get the count of outstanding memory allocations.
 *
 * @return The number of outstanding memory allocations.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
uint64_t longBowMemory_OutstandingAllocations(void);
#endif
