/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * Copyright 2016 Palo Alto Research Center, Inc. (PARC), a Xerox company.  All Rights Reserved.
 * The content of this file, whole or in part, is subject to licensing terms.
 * If distributing this software, include this License Header Notice in each
 * file and provide the accompanying LICENSE file.
 */
/**
 * @file longBow_ClipBoard.h
 * @brief <#Brief Description#>
 *
 * <#Detailed Description#>
 *
 * @author Glenn Scott, Computing Science Laboratory, PARC
 * @copyright 2016 Palo Alto Research Center, Inc. (PARC), A Xerox Company.  All Rights Reserved.
 */
#ifndef longBow_ClipBoard_h
#define longBow_ClipBoard_h

#include <stdbool.h>
#include <stdint.h>

struct LongBowClipBoard;
typedef struct LongBowClipBoard LongBowClipBoard;

void longBowClipBoard_Destroy(LongBowClipBoard **pointer);

LongBowClipBoard *longBowClipBoard_Create(void);

void *longBowClipBoard_Get(const LongBowClipBoard *clipBoard, const char *name);

char *longBowClipBoard_GetAsCString(const LongBowClipBoard *clipBoard, const char *name);

uint64_t longBowClipBoard_GetAsInt(const LongBowClipBoard *clipBoard, const char *name);

void *longBowClipBoard_Set(LongBowClipBoard *clipBoard, const char *name, void *value);

void *longBowClipBoard_SetInt(LongBowClipBoard *clipBoard, const char *name, uint64_t value);

void *longBowClipBoard_SetCString(LongBowClipBoard *clipBoard, const char *name, char *value);

bool longBowClipBoard_Exists(const LongBowClipBoard *clipBoard, const char *name);

bool longBowClipBoard_Delete(LongBowClipBoard *clipBoard, const char *name);

#endif /* longBow_ClipBoard_h */
