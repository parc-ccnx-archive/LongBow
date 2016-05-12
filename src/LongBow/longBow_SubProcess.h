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
 * @file longBow_SubProcess.h
 * @ingroup testing
 * @brief Facilities for running and managing subprocesses.
 *
 * @author Glenn Scott  , Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef LongBow_longBow_SubProcess_h
#define LongBow_longBow_SubProcess_h

#include <stdbool.h>

struct longbow_subprocess;
typedef struct longbow_subprocess LongBowSubProcess;

/**
 * Start a subprocess.
 *
 * @param [in] path The pathname, either absolute or relative to the current directory, of the program to execute.
 * @param [in] ... A NULL terminated parameter list consisting of the parameters of the executable starting at `argv[0]`.
 *
 * @return A pointer to a `LongBowSubProcess` instance.
 *
 * Example:
 * @code
 * {
 *     LongBowSubProcess *process = longBowSubProcess_Exec("/bin/pwd", "pwd", NULL);
 * }
 * @endcode
 *
 * @see longBowSubProcess_Wait
 * @see longBowSubProcess_Signal
 * @see longBowSubProcess_Terminate
 * @see longBowSubProcess_Wait
 */
LongBowSubProcess *longBowSubProcess_Exec(const char *path, ... /*, (char *)0 */);

/**
 * Destroy a `LongBowSubProcess`
 *
 * If the process is still running it is sent the SIGKILL signal.
 *
 * @param [in] subProcessPtr A pointer to a `LongBowSubProcess` instance.
 *
 * Example:
 * @code
 * {
 *     LongBowSubProcess *process = longBowSubProcess_Exec("/bin/pwd", "pwd", NULL);
 *
 *     longBowSubProcess_Destroy(&process);
 * }
 * @endcode
 *
 * @see longBowSubProcess_Exec
 */
void longBowSubProcess_Destroy(LongBowSubProcess **subProcessPtr);

/**
 * Send a signal to a LongBowSubProcess
 *
 * @param [in] subProcess The LongBowSubProcess to receive the signal.
 * @param [in] signalNumber The signal to send.
 *
 * @return true The signal was successfully sent.
 * @return false The signal was not successfully sent.
 *
 * Example:
 * @code
 * {
 *     longBowSubProcess_Signal(subProcess, SIGTERM);
 * }
 * @endcode
 *
 * @see longBowSubProcess_Terminate
 */
bool longBowSubProcess_Signal(LongBowSubProcess *subProcess, int signalNumber);

/**
 * Send a SIGTERM to a LongBowSubProcess
 *
 * @param [in] subProcess The LongBowSubProcess to receive the signal.
 *
 * @return true The signal was successfully sent.
 * @return false The signal was not successfully sent.
 *
 * Example:
 * @code
 * {
 *     longBowSubProcess_Signal(subProcess, SIGTERM);
 * }
 * @endcode
 *
 * @see longBowSubProcess_Terminate
 */
bool longBowSubProcess_Terminate(LongBowSubProcess *subProcess);

/**
 * Wait for a `LongBowSubProcess` to stop or terminate
 *
 * @param [in] subProcess The LongBowSubProcess to wait for.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 *
 */
void longBowSubProcess_Wait(LongBowSubProcess *subProcess);

/**
 * Print a human readable representation of the given `LongBowSubProcess`.
 *
 * @param [in] indentation The level of indentation to use to pretty-print the output.
 * @param [in] subprocess A pointer to the instance to display.
 *
 * Example:
 * @code
 * {
 *     LongBowSubProcess *process = longBowSubProcess_Exec("/bin/pwd", "pwd", NULL);
 *
 *     longBowSubProcess_Display(process, 0);
 *
 *     longBowSubProcess_Destroy(&process);
 * }
 * @endcode
 *
 */
void longBowSubProcess_Display(const LongBowSubProcess *subprocess, int indentation);
#endif
