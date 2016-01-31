/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC)
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
 * @copyright 2013-2014, Xerox Corporation (Xerox) and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <stdio.h>

#include <LongBow/longBow_Status.h>
#include <LongBow/unit-test.h>

bool
longBowStatus_IsSuccessful(LongBowStatus status)
{
    if (status == LONGBOW_STATUS_SUCCEEDED || longBowStatus_IsWarning(status) || longBowStatus_IsIncomplete(status)) {
        return true;
    }
    return false;
}

bool
longBowStatus_IsFailed(LongBowStatus status)
{
    switch (status) {
        case LONGBOW_STATUS_FAILED:
        case LONGBOW_STATUS_MEMORYLEAK:
        case LongBowStatus_STOPPED:
        case LONGBOW_STATUS_TEARDOWN_FAILED:
        case LONGBOW_STATUS_SETUP_FAILED:
            return true;

        default:
            if (status >= LongBowStatus_SIGNALLED) {
                return true;
            }
            return false;
    }
}

bool
longBowStatus_IsWarning(LongBowStatus status)
{
    switch (status) {
        case LongBowStatus_WARNED:
        case LongBowStatus_TEARDOWN_WARNED:
            return true;

        default:
            return false;
    }
}

bool
longBowStatus_IsIncomplete(LongBowStatus status)
{
    switch (status) {
        case LONGBOW_STATUS_SKIPPED:
        case LongBowStatus_UNIMPLEMENTED:
        case LongBowStatus_IMPOTENT:
            return true;

        default:
            return false;
    }
}

bool
longBowStatus_IsSignalled(LongBowStatus status)
{
    return status >= LongBowStatus_SIGNALLED;
}

static struct toString {
    LongBowStatus status;
    char *string;
} toString[] = {
    { LONGBOW_STATUS_SUCCEEDED,       "Succeeded"         },
    { LongBowStatus_WARNED,          "Warning"           },
    { LongBowStatus_TEARDOWN_WARNED, "Tear Down Warning" },
    { LONGBOW_STATUS_SKIPPED,         "Skipped"           },
    { LongBowStatus_UNIMPLEMENTED,   "Unimplemented"     },
    { LongBowStatus_IMPOTENT,        "Impotent"          },
    { LONGBOW_STATUS_FAILED,          "Failed"            },
    { LongBowStatus_STOPPED,         "Stopped"           },
    { LONGBOW_STATUS_TEARDOWN_FAILED, "Tear Down Failed"  },
    { LONGBOW_STATUS_SETUP_FAILED,    "Setup Failed"      },
    { LONGBOW_STATUS_MEMORYLEAK,      "Memory Leak"       },
    { 0,                              NULL                },
};

static const char *
_longBowStatus_StatusToString(const LongBowStatus status)
{
    const char *result = NULL;
    for (const struct toString *element = &toString[0]; element->string != NULL; element++) {
        if (element->status == status) {
            result = element->string;
            break;
        }
    }
    return result;
}

char *
longBowStatus_ToString(const LongBowStatus status)
{
    char *result = (char *) _longBowStatus_StatusToString(status);

    if (result == NULL) {
        if (status >= LongBowStatus_SIGNALLED) {
            int signalNumber = status - LongBowStatus_SIGNALLED;
            char *signalName = strsignal(signalNumber);
            int check;
            if (signalName == NULL) {
                check = asprintf(&result, "Signaled %d.", signalNumber);
            } else {
                check = asprintf(&result, "Signaled %s.", signalName);
            }
            if (check == -1) {
                return NULL;
            }
        } else {
            int check = asprintf(&result, "Unknown status: %d.  This is a bug.", status);
            if (check == -1) {
                return NULL;
            }
        }
    } else {
        result = strdup(result);
    }

    return result;
}
