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
 * @file longBow_OpenFile.h
 * @ingroup testing
 * @brief LongBow support for files and file descriptors.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_Files_h
#define LongBow_longBow_Files_h

#include <sys/stat.h>

#include <LongBow/private/longBow_ArrayList.h>

struct longbow_openfile;
/**
 * @typedef LongBowOpenFile
 * @brief A representation of an open file.
 */
typedef struct longbow_openfile LongBowOpenFile;

/**
 * @param [in] fd The file descriptor.
 * @return An allocated LongBowOpenFile instance that must be destroyed via longBowOpenFile_Destroy().
 */
LongBowOpenFile *longBowOpenFile_Create(int fd);

/**
 *
 * @param [in,out] openFilePtr A pointer to a pointer to a valid LongBowOpenFile instance.
 */
void longBowOpenFile_Destroy(LongBowOpenFile **openFilePtr);

/**
 *
 * @param [in] openFile A pointer to a valid LongBowOpenFile instance.
 * @return A nul-terminate C string that must be freed via free(3).
 */
char *longBowOpenFile_ToString(LongBowOpenFile *openFile);

/**
 * Create a list of the currently open files.
 *
 * @return A list of LongBowOpenFile instances for each open file.
 */
LongBowArrayList *longBowOpenFile_CurrentlyOpen(void);

/**
 * Return a nul-terminated C string representing the given `struct stat` pointed to by @p statbuf.
 *
 * @param [in] statbuf A pointer to a valid `struct stat` instance.
 *
 * @return non-NULL A nul-terminated C string that must be deallocated via longBowMemory_Deallocate.
 */
char *longBowOpenFile_StructStatToString(const struct stat *statbuf);
#endif
