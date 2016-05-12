/*
 * Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @file longBow_UnitTest.h
 * @ingroup testing
 * @brief Unit Testing Support.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef __LongBow__longBow_UnitTest__
#define __LongBow__longBow_UnitTest__

/**
 * Compose the C function name prefix for a Test Runner.
 *
 * @param [in] _testRunnerName_ A valid identifier for the Test Runner.
 */
#define longBowUnitTest_RunnerName(_testRunnerName_) \
    LongBowTestRunner_ ## _testRunnerName_

/**
 * Compose the C function name for a Test Runner Setup function.
 *
 * @param [in] _testRunnerName_ A valid identifier for the Test Runner.
 */
#define longBowUnitTest_RunnerSetupName(_testRunnerName_) \
    LongBowTestRunner_ ## _testRunnerName_ ## _Setup

/**
 * @brief Compose the C function name for a Test Runner Tear-Down function.
 *
 * @param [in] _testRunnerName_ A valid identifier for the Test Runner.
 */
#define longBowUnitTest_RunnerTearDownName(_testRunnerName_) \
    LongBowTestRunner_ ## _testRunnerName_ ## _TearDown

/**
 * @brief Compose the C function name for a Test Runner function.
 *
 * @param [in] _testRunnerName_ A valid identifier for the Test Runner.
 */
#define longBowUnitTest_RunnerRunName(_testRunnerName_) \
    LongBowTestRunner_ ## _testRunnerName_ ## _Run

/**
 * @defined longBowUnitTest_FixtureName
 * @brief Compose a Test Fixture name.
 * @param [in] _testFixtureName_ A valid identifier fragment for the Test Fixture.
 */
#define longBowUnitTest_FixtureName(_testFixtureName_) \
    LongBowTestFixture_ ## _testFixtureName_

/**
 * @brief Compose the C function name for a Test Fixture function.
 *
 * @param [in] _testFixtureName_ A valid identifier for the Test Fixture.
 */
#define longBowUnitTest_FixtureRunName(_testFixtureName_) \
    LongBowTestFixture_ ## _testFixtureName_ ## _Run

/**
 * Compose the C function name for a Test Fixture Setup function.
 *
 * @param [in] _testFixtureName_ A valid identifier for the Test Fixture.
 */
#define longBowUnitTest_FixtureSetupName(_testFixtureName_) \
    LongBowTestFixture_ ## _testFixtureName_ ## _Setup

/**
 * @brief Compose the C function name for a Test Fixture Tear-Down function.
 *
 * @param [in] _testFixtureName_ A valid identifier for the Test Fixture.
 */
#define longBowUnitTest_FixtureTearDownName(_testFixtureName_) \
    LongBowTestFixture_ ## _testFixtureName_ ## _TearDown

/**
 * @brief Compose the C name for a Test Fixture Configuration structure.
 *
 * @param [in] _testFixtureName_ A valid identifier for the Test Fixture.
 */
#define longBowUnitTest_FixtureConfigName(_testFixtureName_) \
    LongBowTestFixture_ ## _testFixtureName_ ## _Config

/**
 *
 */
#define longBowUnitTest_CaseName(_testFixtureName_, _testCaseName_) \
    LongBowTestCase_ ## _testFixtureName_ ## _ ## _testCaseName_

#endif /* defined(__LongBow__longBow_UnitTest__) */
