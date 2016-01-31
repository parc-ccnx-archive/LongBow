/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
/*
 * test_LongBow.c
 *
 *  Created on: Aug 28, 2013
 *      Author: gscott
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/errno.h>

#include "../unit-test.h"


LONGBOW_TEST_RUNNER(LongBow)
{
    LONGBOW_RUN_TEST_FIXTURE(LongBowFixture);
}

LONGBOW_TEST_RUNNER_SETUP(LongBow)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_RUNNER_TEARDOWN(LongBow)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(LongBowFixture)
{
    LONGBOW_RUN_TEST_CASE(LongBowFixture, alwaysSucceed);
    LONGBOW_RUN_TEST_CASE(LongBowFixture, alwaysUnimplemented);
    LONGBOW_RUN_TEST_CASE(LongBowFixture, alwaysImpotent);
}

LONGBOW_TEST_FIXTURE_SETUP(LongBowFixture)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(LongBowFixture)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(LongBowFixture, testErrno)
{
    errno = ENOENT;
    assertTrue(0, "Errno test");
}

LONGBOW_TEST_CASE(LongBowFixture, alwaysSucceed)
{
    assertTrue(1, "alwaysSucceed");
}

LONGBOW_TEST_CASE(LongBowFixture, alwaysImpotent)
{
}

LONGBOW_TEST_CASE_EXPECTS(LongBowFixture, testEvent, .event = &LongBowAssertEvent)
{
    assertTrue(0, "testEvent");
}

LONGBOW_TEST_CASE_EXPECTS(LongBowFixture, alwaysFail, .status = LONGBOW_STATUS_FAILED, .event = &LongBowAssertEvent)
{
    assertTrue(0, "alwaysFail");
}

LONGBOW_TEST_CASE_EXPECTS(LongBowFixture, alwaysSigTERM, .status = LONGBOW_STATUS_SIGNAL(SIGTERM))
{
    kill(getpid(), SIGTERM);
}

LONGBOW_TEST_CASE_EXPECTS(LongBowFixture, alwaysSEGV, .event = &LongBowEventSIGSEGV)
{
    int *p = 0;
    int i = *p;
    printf("not used %d\n", i);
}

LONGBOW_TEST_CASE(LongBowFixture, alwaysUnimplemented)
{
    testUnimplemented("alwaysUnimplemented");
}

LONGBOW_TEST_CASE(LongBowFixture, alwaysWarn)
{
    testWarn("alwaysWarn");
}

LONGBOW_TEST_CASE_EXPECTS(LongBowFixture, alwaysSkip, .event = &LongBowTestSkippedEvent)
{
    testSkip("alwaysSkip");
}

LONGBOW_TEST_CASE_EXPECTS(LongBowFixture, alwaysTrap, .status = LONGBOW_STATUS_FAILED)
{
    trapNotImplemented("alwaysTrap");
}

LONGBOW_TEST_FIXTURE(TestTearDownWarning)
{
    LONGBOW_RUN_TEST_CASE(TestTearDownWarning, alwaysFail);
    LONGBOW_RUN_TEST_CASE(TestTearDownWarning, alwaysSucceed);
}

LONGBOW_TEST_FIXTURE_SETUP(TestTearDownWarning)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(TestTearDownWarning)
{
    return LONGBOW_STATUS_TEARDOWN_WARNED;
}

LONGBOW_TEST_CASE(TestTearDownWarning, alwaysFail)
{
    assertTrue(0, "alwaysFail");
}

LONGBOW_TEST_CASE(TestTearDownWarning, alwaysSucceed)
{
    assertTrue(1, "alwaysSucceed");
}

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(LongBow);
    int status = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);

    exit(status);
}
