/*
 * Copyright (c) 2013-2014,2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @copyright 2013-2014,2015, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdlib.h>

#include <LongBow/longBow_TestCaseClipBoard.h>
#include <LongBow/private/longBow_Memory.h>

struct longbow_testcase_clipboard {
    /**
     * A pointer to arbitrary data shared between the setup, test case, and teardown.
     */
    void *shared;
};

LongBowTestCaseClipBoard *
longBowTestCaseClipBoard_Create(void *shared)
{
    LongBowTestCaseClipBoard *result = longBowMemory_Allocate(sizeof(LongBowTestCaseClipBoard));
    longBowTestCaseClipBoard_Set(result, shared);
    return result;
}

void
longBowTestCaseClipBoard_Destroy(LongBowTestCaseClipBoard **clipBoardPtr)
{
    longBowMemory_Deallocate((void **) clipBoardPtr);
}

void *
longBowTestCaseClipBoard_Get(const LongBowTestCaseClipBoard *clipBoard)
{
    return clipBoard->shared;
}

LongBowTestCaseClipBoard *
longBowTestCaseClipBoard_Set(LongBowTestCaseClipBoard *clipBoard, void *shared)
{
    void *previousValue = clipBoard->shared;
    clipBoard->shared = shared;
    return previousValue;
}
