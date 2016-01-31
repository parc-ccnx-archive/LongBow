/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
 * @file ANSITerm/longBowReport_Runtime.h
 * @ingroup reporting
 * @brief ANSI Terminal Reporting
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef LongBow_longBowReport_ANSITerm_Runtime_h
#define LongBow_longBowReport_ANSITerm_Runtime_h

#include <stdio.h>
#include <stdarg.h>

#include <LongBow/Reporting/longBowReport_Runtime.h>

/**
 * Begin printing in red.
 *
 */
void longBowReportRuntime_PrintRed(void);

/**
 * Print the formatted string in red.
 *
 */
void longBowReportRuntime_RedPrintf(const char *format, ...);

/**
 * Print the formatted string in green.
 *
 */
void longBowReportRuntime_GreenPrintf(const char *format, ...);

/**
 * Print the formatted string in yellow.
 *
 */
void longBowReportRuntime_YellowPrintf(const char *format, ...);

/**
 * Print the formatted string in magenta.
 *
 */
void longBowReportRuntime_MagentaPrintf(const char *format, ...);

/**
 * Parse the given key and set the corresponding LongBowReportConfig to suppress reports.
 *
 * @param [in] config A valid LongBowReportConfig instance.
 * @param [in] key A nul-terminated C string consisting of one or more of the characters, X.SWstwFTU
 */
void longBowReportRuntime_ParseSuppress(LongBowReportConfig *config, const char *key);
#endif // LongBow_longBowReport_ANSITerm_Runtime_h
