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
 * @file longBow_TestCaseClipboard.h
 * @ingroup testing
 * @brief LongBow Clipboard shared between the setup, test case, and teardown.
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LongBow_longBowTestCaseClipBoard_h
#define LongBow_longBowTestCaseClipBoard_h

struct longbow_testcase_clipboard;

/**
 * @typedef LongBowTestCaseClipBoard
 */
typedef struct longbow_testcase_clipboard LongBowTestCaseClipBoard;

/**
 * Create a `LongBowTestCaseClipBoard` containing the shared data pointer.
 *
 * @param [in] shared A pointer to a value that is shared between the setup, test-case, and tear-down functions.
 * @return A pointer to a valid LongBowTestCaseClipBoard instance.
 *
 * @see longBowTestCaseClipBoard_Destroy
 */
LongBowTestCaseClipBoard *longBowTestCaseClipBoard_Create(void *shared);

/**
 *
 * @param [in,out] clipBoardPtr A pointer to a pointer to a LongBowTestCaseClipBoard instance.
 */
void longBowTestCaseClipBoard_Destroy(LongBowTestCaseClipBoard **clipBoardPtr);

/**
 *
 * @param [in] clipBoard A pointer to a valid LongBowTestCaseClipBoard instance.
 * @param [in] shared A pointer to a value that is shared between the setup, test-case, and tear-down functions.
 * @return The previous value of the "clipboard", or NULL if there was no previous value.
 */
LongBowTestCaseClipBoard *longBowTestCaseClipBoard_Set(LongBowTestCaseClipBoard *clipBoard, void *shared);

/**
 *
 * @param [in] clipBoard A pointer to a valid LongBowTestCaseClipBoard instance.
 * @return The value currently stored on the clipboard.
 */
void *longBowTestCaseClipBoard_Get(const LongBowTestCaseClipBoard *clipBoard);
#endif
