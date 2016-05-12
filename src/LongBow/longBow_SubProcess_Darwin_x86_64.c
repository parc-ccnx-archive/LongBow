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
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <LongBow/longBow_SubProcess.h>
#include <LongBow/private/longBow_Memory.h>

struct longbow_subprocess {
    const char *path;
    char **arguments;
    pid_t pid;
    int exitStatus;
    struct rusage rusage;
};

static void
_resetAllSignals(void)
{
    struct sigaction signalAction;
    signalAction.sa_handler = SIG_DFL;
    signalAction.sa_flags = SA_SIGINFO;
    sigemptyset(&signalAction.sa_mask);

    for (int i = 1; i < NSIG; i++) {
        sigaction(i, &signalAction, NULL);
    }
}

LongBowSubProcess *
longBowSubProcess_Exec(const char *path, ... /*, (char *)0 */)
{
    va_list ap;
    va_start(ap, path);

    size_t count = 0;
    for (char *arg = va_arg(ap, char *); arg != NULL; arg = va_arg(ap, char *)) {
        count++;
    }

    LongBowSubProcess *result = longBowMemory_Allocate(sizeof(LongBowSubProcess));

    result->path = path;
    longBowMemory_Allocate(sizeof(char *) * count + 1);
    va_end(ap);
    // This relies on the last element being all zeros.
    va_start(ap, path);

    for (size_t i = 0; i < count; i++) {
        result->arguments[i] = va_arg(ap, char *);
    }
    va_end(ap);

    result->pid = fork();
    if (result->pid == 0) {
        _resetAllSignals();
        printf("Exec %s\n", result->path);
        int error = execv(result->path, result->arguments);
        printf("Error %d\n", error);
        perror(path);
        exit(1);
    }

    printf("Process group child=%d, parent=%d\n", getpgid(result->pid), getpgrp());
    return result;
}

void
longBowSubProcess_Destroy(LongBowSubProcess **processPtr)
{
    LongBowSubProcess *process = *processPtr;

    if (process->pid) {
        longBowSubProcess_Signal(process, SIGKILL);
    }

    longBowMemory_Deallocate((void **) process->arguments);
    longBowMemory_Deallocate((void **) processPtr);
}

bool
longBowSubProcess_Terminate(LongBowSubProcess *subProcess)
{
    return longBowSubProcess_Signal(subProcess, SIGTERM);
}

bool
longBowSubProcess_Signal(LongBowSubProcess *subProcess, int signalNumber)
{
    return kill(subProcess->pid, signalNumber) == 0;
}

void
longBowSubProcess_Wait(LongBowSubProcess *subProcess)
{
    wait4(subProcess->pid, &subProcess->exitStatus, 0, &subProcess->rusage);
    subProcess->pid = 0;
}

void
longBowSubProcess_Display(const LongBowSubProcess *subprocess, int indentation)
{
    printf("%*s%s: ", indentation, "", subprocess->path);
    if (subprocess->pid == 0) {
        printf("not running .exitStatus=%d ", subprocess->exitStatus);
    } else {
        printf(".pid=%d", subprocess->pid);
    }

    printf("\n");
}
