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
 * @file longBow_Main.h
 * @ingroup testing
 * @brief A main() function to run one or more LongBow Test Runners.
 *
 * The functions in this file provide execution time support for running LongBow Tests.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LONGBOWMAIN_H_
#define LONGBOWMAIN_H_

/**
 * Run one or more LongBow Test Runners.
 *
 * The encapsulating function creates one or more `LongBowTestRunner` instances and supplies
 * these as a NULL terminated variable argument list to the longBowMain function.
 * The return value from longBowMain is suitable as an exit status from an executable as zero is success.
 *
 * @param [in] argc  The number of elements in argv.
 * @param [in] argv  An array of C string arguments.
 *
 * @return 0 All tests for all LongBowTestRunners were successful. Otherwise one of `LongBowStatus`.
 *
 * Example Usage:
 * @code
 * int
 * main(int argc, char *argv[argc])
 * {
 *   LongBowTestRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(MyTestRunner);
 *   int exitStatus = longBowMain(argc, argv, testRunner, NULL);
 *   longBowTestRunner_Destroy(&testRunner);
 *   exit(exitStatus);
 * }
 * @endcode
 */
int longBowMain_Impl(int argc, char *argv[], ...);
#endif /* LONGBOWMAIN_H_ */
