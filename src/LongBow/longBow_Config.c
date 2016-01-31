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
#include <stdio.h>
#include <inttypes.h>

#include <LongBow/private/longBow_ArrayList.h>
#include <LongBow/private/longBow_Memory.h>
#include <LongBow/private/longBow_String.h>

#include <LongBow/longBow_Properties.h>

#include <LongBow/longBow_Config.h>
#include <LongBow/Reporting/longBowReport_Runtime.h>
#include <LongBow/longBow_About.h>

/** @cond private */
struct longbow_configuration {
    LongBowReportConfig *reportConfiguration;
    LongBowProperties *properties;
};
/** @endcond */

static void
_longBowConfig_SetupEnvironment(const LongBowConfig *config)
{
}

static void
_longBowConfig_Show(const LongBowConfig *configuration)
{
    char *string = longBowProperties_ToString(configuration->properties);
    ssize_t nwritten = write(1, string, strlen(string));
    if (nwritten != strlen(string)) {
        fprintf(stderr, "Failed to write to file descriptor 1.\n");
        exit(-1);
    }
    longBowMemory_Deallocate((void **) &string);
}

static bool
_longBowConfig_Set(LongBowConfig *configuration, const char *expression)
{
    bool result = false;

    LongBowArrayList *tokens = longBowString_Tokenise(expression, "=");
    if (tokens != NULL) {
        if (longBowArrayList_Length(tokens) == 2) {
            char *name = longBowArrayList_Get(tokens, 0);
            char *value = longBowArrayList_Get(tokens, 1);
            result = longBowConfig_SetProperty(configuration, name, value);
            longBowArrayList_Destroy(&tokens);
        }
    }

    return result;
}

LongBowConfig *
longBowConfig_Create(int argc, char *argv[], const char *mainFileName)
{
    LongBowConfig *result = longBowMemory_Allocate(sizeof(LongBowConfig));

    result->properties = longBowProperties_Create();
    longBowProperties_Set(result->properties, "trace", "false");
    longBowProperties_Set(result->properties, "silent", "false");
    longBowProperties_Set(result->properties, "run-forked", "false");

    for (int i = 1; i < argc; i++) {
        if (longBowString_Equals("--help", argv[i]) || longBowString_Equals("-h", argv[i])) {
            // If the option is "--help",
            // then let all of the sub-systems that also take arguments process that option also.
            printf("LongBow %s\n", longBowAbout_Version());
            printf("%s\n", longBowAbout_MiniNotice());
            printf("Options\n");
            //printf("  --main          Print the name of the main test runner source file.\n");
            printf("  --help           Print this help message.\n");
            printf("  --run-forked     Run the tests as forked processes.\n");
            printf("  --run-nonforked  Run the tests in the same process (default).\n");
            printf("  --version        Print the version of LongBow used for this test.\n");
            printf("  --core-dump      Produce a core file upon the first failed assertion.\n");
            printf("  --set name=value Set a configuration property name to the specified value\n");
            longBowTestRunner_ConfigHelp();
            longBowTestFixture_ConfigHelp();
            longBowTestCase_ConfigHelp();
            longBowReportRuntime_Create(argc, argv);
            longBowConfig_Destroy(&result);
            printf("\n");
            return NULL;
        } else if (longBowString_Equals("--main", argv[i])) {
            printf("%s\n", mainFileName);
            longBowConfig_Destroy(&result);
            return NULL;
        } else if (longBowString_Equals("--version", argv[i])) {
            printf("%s\n", longBowAbout_Version());
            longBowConfig_Destroy(&result);
            return NULL;
        } else if (longBowString_Equals("--run-nonforked", argv[i])) {
            longBowProperties_Set(result->properties, "run-forked", "false");
        } else if (longBowString_Equals("--run-forked", argv[i])) {
            printf("?\n");
            longBowProperties_Set(result->properties, "run-forked", "true");
        } else if (longBowString_Equals("--trace", argv[i])) {
            longBowProperties_Set(result->properties, "trace", "true");
        } else if (longBowString_Equals("--silent", argv[i])) {
            longBowProperties_Set(result->properties, "silent", "true");
        } else if (longBowString_Equals("--core-dump", argv[i])) {
            longBowProperties_Set(result->properties, "core-dump", "true");
        } else if (longBowString_StartsWith(argv[i], "--set")) {
            char *parameter = argv[++i];
            if (_longBowConfig_Set(result, parameter) == false) {
                printf("Could not set parameter: %s\n", parameter);
            }
        } else if (longBowString_StartsWith(argv[i], "--show")) {
            _longBowConfig_Show(result);
        } else {
            printf("Unknown option '%s'\n", argv[i]);
        }
    }

    LongBowReportConfig *reportConfiguration = longBowReportRuntime_Create(argc, argv);

    if (reportConfiguration == NULL) {
        longBowConfig_Destroy(&result);
        result = NULL;
    } else {
        if (result == NULL) {
            // nothing to do.
        } else {
            result->reportConfiguration = reportConfiguration;
        }
    }

    if (result != NULL) {
        _longBowConfig_SetupEnvironment(result);
    }
    return result;
}

void
longBowConfig_Destroy(LongBowConfig **configPtr)
{
    LongBowConfig *config = *configPtr;

    if (config != NULL) {
        if (config->reportConfiguration != NULL) {
            longBowReportRuntime_Destroy(&config->reportConfiguration);
        }
        longBowProperties_Destroy(&config->properties);
        longBowMemory_Deallocate((void **) configPtr);
    }
}

bool
longBowConfig_IsRunForked(const LongBowConfig *config)
{
    return longBowConfig_GetBoolean(config, false, "run-forked");
}

bool
longBowConfig_IsTrace(const LongBowConfig *config)
{
    return longBowConfig_GetBoolean(config, false, "trace");
}

static const char *
_longBowConfig_GetProperty(const LongBowConfig *config, const char *format, va_list ap)
{
    const char *result = NULL;

    char *propertyName;
    if (vasprintf(&propertyName, format, ap) != -1) {
        if (config != NULL && config->properties != NULL) {
            result = longBowProperties_Get(config->properties, propertyName);
        }
        free(propertyName);
    }

    return result;
}

const char *
longBowConfig_GetProperty(const LongBowConfig *config, const char *format, ...)
{
    const char *result = NULL;

    if (config != NULL && config->properties != NULL) {
        va_list ap;
        va_start(ap, format);
        result = _longBowConfig_GetProperty(config, format, ap);
        va_end(ap);
    }

    return result;
}

bool
longBowConfig_SetProperty(const LongBowConfig *config, const char *name, const char *value)
{
    bool result = false;

    if (config != NULL && config->properties != NULL) {
        result = longBowProperties_Set(config->properties, name, value);
    }

    return result;
}

bool
longBowConfig_GetBoolean(const LongBowConfig *config, bool defaultValue, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    const char *value = _longBowConfig_GetProperty(config, format, ap);
    va_end(ap);

    bool result = defaultValue;
    if (value != NULL) {
        result = (strcasecmp(value, "true") == 0);
    }
    return result;
}

uint32_t
longBowConfig_GetUint32(const LongBowConfig *config, uint32_t defaultValue, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    const char *value = _longBowConfig_GetProperty(config, format, ap);
    va_end(ap);

    uint32_t result = defaultValue;
    if (value != NULL) {
        result = (uint32_t) strtoul(value, NULL, 10);
    }
    return result;
}
