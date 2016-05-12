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
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <string.h>

#include <LongBow/private/longBow_OpenFile.h>
#include <LongBow/private/longBow_Memory.h>
#include <LongBow/private/longBow_String.h>

struct longbow_openfile {
    char *fullPathName;
    struct stat statbuf;
    int fd;
};

#if defined(_WIN64)
static char *
_getFullPathNameFromFd(int fd)
{
    return strdup("./");
}
#elif defined(_WIN32)
static char *
_getFullPathNameFromFd(int fd)
{
    return strdup("./");
}
#elif defined(__APPLE__)
static char *
_getFullPathNameFromFd(int fd)
{
    char filePath[PATH_MAX];

    if (fcntl(fd, F_GETPATH, filePath) != -1) {
        return strdup(filePath);
    }
    return NULL;
}
#elif defined(__linux)
static char *
_getFullPathNameFromFd(int fd)
{
    return strdup("./");
}
#elif defined(__unix) // all unices not caught above
static char *
_getFullPathNameFromFd(int fd)
{
    return strdup("./");
}
#elif defined(__posix)
static char *
_getFullPathNameFromFd(int fd)
{
    return strdup("./");
}
#endif

LongBowOpenFile *
longBowOpenFile_Create(int fd)
{
    LongBowOpenFile *result = longBowMemory_Allocate(sizeof(LongBowOpenFile));
    if (result != NULL) {
        result->fd = fd;

        if (fstat(fd, &result->statbuf) == 0) {
            result->fullPathName = _getFullPathNameFromFd(fd);
        }
    }
    return result;
}

void
longBowOpenFile_Destroy(LongBowOpenFile **openFilePtr)
{
    longBowMemory_Deallocate((void **) openFilePtr);
}

char *
longBowOpenFile_StructStatToString(const struct stat *statbuf)
{
    LongBowString *string = longBowString_CreateFormat("0x%" PRIx16 " %3ld %10d %10d %6lld",
                                                       statbuf->st_mode,
                                                       (long) statbuf->st_nlink,
                                                       statbuf->st_uid,
                                                       statbuf->st_gid,
                                                       (long long) statbuf->st_size);
    char *result = longBowString_ToString(string);

    return result;
}

char *
longBowOpenFile_ToString(LongBowOpenFile *openFile)
{
    char *statString = longBowOpenFile_StructStatToString(&(openFile->statbuf));
    LongBowString *string = longBowString_CreateFormat("%d %s %s", openFile->fd, statString, openFile->fullPathName);
    free(statString);
    char *result = longBowString_ToString(string);
    
    return result;
}

LongBowArrayList *
longBowOpenFile_CurrentlyOpen(void)
{
    struct rlimit rlimit;

    bool success = getrlimit(RLIMIT_NOFILE, &rlimit) == 0;
    if (!success) {
        return NULL;
    }
    // Here is a potential problem:  struct rlimit specifies rlim_cur as a 64 bit value (rlim_t), but poll only takes an
    // unsigned int's worth of file descriptors.

    LongBowArrayList *list = longBowArrayList_Create(longBowArrayList_StdlibFreeFunction);

    for (nfds_t i = 0; i < (nfds_t) rlimit.rlim_cur; i++) {
        int flags = fcntl((int) i, F_GETFD);
        if (flags != -1) {
            LongBowOpenFile *openFile = longBowOpenFile_Create((int) i);
            longBowArrayList_Add(list, openFile);
        }
    }

    return list;
}
