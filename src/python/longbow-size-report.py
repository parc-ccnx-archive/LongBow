#! /usr/bin/env python
# Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# ################################################################################
# #
# # PATENT NOTICE
# #
# # This software is distributed under the BSD 2-clause License (see LICENSE
# # file).  This BSD License does not make any patent claims and as such, does
# # not act as a patent grant.  The purpose of this section is for each contributor
# # to define their intentions with respect to intellectual property.
# #
# # Each contributor to this source code is encouraged to state their patent
# # claims and licensing mechanisms for any contributions made. At the end of
# # this section contributors may each make their own statements.  Contributor's
# # claims and grants only apply to the pieces (source code, programs, text,
# # media, etc) that they have contributed directly to this software.
# #
# # There is no guarantee that this section is complete, up to date or accurate. It
# # is up to the contributors to maintain their portion of this section and up to
# # the user of the software to verify any claims herein.
# #
# # Do not remove this header notification.  The contents of this section must be
# # present in all distributions of the software.  You may only modify your own
# # intellectual property statements.  Please provide contact information.
# 
# - Palo Alto Research Center, Inc
# This software distribution does not grant any rights to patents owned by Palo
# Alto Research Center, Inc (PARC). Rights to these patents are available via
# various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
# intellectual property used by its contributions to this software. You may
# contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
#
# @author Glenn Scott, Palo Alto Research Center (PARC)
# @copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.

import sys
import os
import subprocess
import difflib
import csv
import argparse
sys.path.append("@INSTALL_PYTHON_DIR@")
import LongBow
from pprint import pprint

def textOutputFile(file, maximumFileNameLength):
    format = "%-" + str(maximumFileNameLength) + "s %6d"
    print format % (file[0], file[1])
    return

def textSummary(files):
    maximumFileNameLength = max(map(lambda file: len(file[0]), files))
    map(lambda file: textOutputFile(file, maximumFileNameLength), files)
    return

def csvOutputFile(file):
    format = "size,%s,%d"
    print format % (file[0], file[1])
    return

def csvSummary(files):
    map(lambda file: csvOutputFile(file), files)
    return

def textTotal(files):
    total = sum(map(lambda file: file[1], files))
    print total
    return

def csvTotal(files):
    total = sum(map(lambda file: file[1], files))
    print total
    return

def main():
    desc = '''
Report on number of lines of one or more C source or header files.

Input is either from a list of files supplied as command line parameters,
or as a list of newline separated file names read from standard input.
Output is a plain text (default) or a CSV file reporting
the file name and the total number of lines in the file.

Usage:

% longbow-size-report *.[ch]

Report the number of lines in .c and .h files specified as command line parameters.

% longbow-size-report -
Read the lists of files from standard input, one file per line.

$ longbow-size-report parc_JSON.c
parc_JSON.c    239
$
$
$ echo parc_JSON.c | longbow-size-report -o csv -
parc_JSON.c,239
$
'''

    parser = argparse.ArgumentParser(prog='longbow-size-report', formatter_class=argparse.RawDescriptionHelpFormatter, description=desc)
    parser.add_argument('-', '--stdin', default=False, action="store_true", required=False, help="read the list of files from standard input.")
    parser.add_argument('-s', '--summary', default=False, action="store_true", required=False, help="display the number of lines for each file")
    parser.add_argument('-t', '--total', default=False, action="store_true", required=False, help="display the total number of lines for all files")
    parser.add_argument('-o', '--output', default="text", action="store", required=False, type=str, help="the output format: \"text\" or \"csv\"")

    parser.add_argument("files", help="Files to check", nargs="*")

    args = parser.parse_args()

    if args.summary == False and args.total == False:
        args.summary = True

    targets = []

    if args.stdin:
        for line in sys.stdin:
            t = line.strip()
            if len(t) > 0:
                targets.append(t)
    else:
        targets = args.files

    if len(targets) == 0:
        parser.print_usage()
        sys.exit(1)

    files = map(lambda fileName: [ fileName, LongBow.countLines(fileName)], targets)
    total = sum(map(lambda element: element[1], files))

    if args.summary:
        if args.output == "text":
            textSummary(files)
        else:
            csvSummary(files)

    if args.total:
        if args.output == "text":
            textTotal(files)
        else:
            csvTotal(files)

if __name__ == '__main__':
    '''
    @(#) longbow-size-report @VERSION@ @DATE@
    @(#)   Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).
    @(#)   All Rights Reserved. Use is subject to license terms.
    '''
    main()
