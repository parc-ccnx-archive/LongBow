/*
 * Copyright (c) 2013, 2014, 2015 2016, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @file longBowReport_Testing.h
 * @ingroup reporting
 * @brief The LongBow Test Report Generator.
 *
 *    This header specifies the interface for an implementation of a LongBow Test Report generator.
 *    Different implementations of a Test Report generator are used to connect to external environments to hook in
 *	  LongBow unit tests within a larger framework like an IDE or continuous integration system.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013, 2014, 2015 2016, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LONGBOW_REPORT_TESTING_H_
#define LONGBOW_REPORT_TESTING_H_

#include <LongBow/Reporting/longBowReport_Runtime.h>

#include <LongBow/runtime.h>
#include <LongBow/unit-test.h>

/**
 * Produce a summary report for the given LongBowTestRunner.
 *
 * @param [in] testRunner A pointer to a valid LongBowTestRunner instance.
 * @return The given LongBowTestRunner.
 */
const LongBowTestRunner *longBowReportTesting_TestRunner(const LongBowTestRunner *testRunner);

/**
 * Produce a summary report for the given LongBowTestFixture.
 *
 * @param [in] testFixture A pointer to a LongBowTestFixture instance.
 * @return The given LongBowTestFixture.
 */
const LongBowTestFixture *longBowReportTesting_TestFixture(const LongBowTestFixture *testFixture);

/**
 * Produce a summary report for the given LongBowTestCase.
 *
 * @param [in] testCase A pointer to a LongBowTestCase instance.
 * @return The pointer to the given LongBowTestCase.
 */
const LongBowTestCase *longBowReportTesting_TestCase(const LongBowTestCase *testCase);

/**
 * Produce a single character displaying the status of an individual test case.
 *
 * @param [in] testCase A pointer to a LongBowTestCase instance.
 */
void longBowReportTesting_DisplayTestCaseResult(const LongBowTestCase *testCase);

/**
 * Make a trace report.
 *
 * @param [in] format A printf-style format string.
 */
void longBowReportTesting_Trace(const char *restrict format, ...);
#endif // LONGBOW_REPORT_TESTING_H_
