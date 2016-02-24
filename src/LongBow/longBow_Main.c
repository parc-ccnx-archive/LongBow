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
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>
#include <stdarg.h>

#include <LongBow/longBow_Main.h>

#include <LongBow/unit-test.h>
#include <LongBow/Reporting/longBowReport_Testing.h>
#include <LongBow/longBow_Config.h>

int
longBowMain_Impl(int argc, char *argv[argc], ...)
{
    LongBowStatus exitStatus = LONGBOW_STATUS_SUCCEEDED;

    // Perform some processing on the input parameters.

    LongBowConfig *config = longBowConfig_Create(argc, argv, NULL);
    if (config == NULL) {
        return LONGBOW_STATUS_FAILED;
    }
    va_list ap;
    va_start(ap, argv);

    for (LongBowTestRunner *testRunner = va_arg(ap, LongBowTestRunner *); testRunner != NULL; testRunner = va_arg(ap, LongBowTestRunner *)) {
        if (testRunner != NULL) {
            longBowTestRunner_SetConfiguration(testRunner, config);
            longBowTestRunner_Run(testRunner);
            longBowReportTesting_TestRunner(testRunner);

            if (!longBowTestRunner_IsSuccessful(testRunner)) {
                exitStatus = longBowTestRunner_GetStatus(testRunner);
            }
        }
    }
    va_end(ap);

    longBowConfig_Destroy(&config);

    return (int) exitStatus;
}
