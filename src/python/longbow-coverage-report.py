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
import argparse

sys.path.append("@INSTALL_PYTHON_DIR@")
sys.path.append("@DEPENDENCY_PYTHON_DIR@")
sys.path.append("../site-packages/longbow/")
import CoverageReport


if __name__ == '__main__':
    '''
@(#) longbow-coverage-report @VERSION@ @DATE@
@(#)   Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).
@(#)   All Rights Reserved. Use is subject to license terms.
'''
    description = '''
longbow-coverage-report @VERSION@ @DATE@
Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).
All Rights Reserved. Use is subject to license terms.

Report on the code coverage of tests.

The source files or executables to analyse are supplied as command line parameters,
or as a list of newline separated file names read from standard input.

Output is plain-text (default --output text) or a CSV file (--output csv)
reporting the results.

Results are:
  An average of all files specified (--average)
  A one line summary of all files specified (--summary)
  A listing of the original source file, colorized showing tested and non-tested lines.
    '''
    parser = argparse.ArgumentParser(prog='longbow-coverage-report',
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     description=description)
    parser.add_argument('-', '--stdin', default=False, action="store_true", required=False,
                        help="Read the list of files from standard input.")
    parser.add_argument('-s', '--summary', default=False, action="store_true", required=False,
                        help="Display the score for each file (excluding test source files).")
    parser.add_argument('-a', '--average', default=False, action="store_true", required=False,
                        help="Display the average score for all C source files (excluding test source files).")
    parser.add_argument('-o', '--output', default="text", action="store", required=False, type=str,
                        help="Set the output format: \"text\" or \"csv\"")
    parser.add_argument('-v', '--visual', default=False, action="store_true", required=False,
                        help="Colorize the original source code showing coverage")
    parser.add_argument('-x', '--explain', default=False, action="store_true", required=False,
                        help="Display information about the collection of coverage information (guru mode).")
    parser.add_argument('-d', '--distribution', default="[95, 90]", action="store", required=False, type=str,
                        help="A list containing the score distributions for pretty-printing. Default [95, 90]")
    parser.add_argument('-T', '--includeTestSources', default=False, action="store_true", required=False,
                        help="Include analysis of the test sources. Default False")
    parser.add_argument('-t', '--testDir', default="", action="store", required=False, type=str,
                        help="Directory hint for locating test files.")

    parser.add_argument("files", help="Files to check", nargs="*")

    args = parser.parse_args()

    if not args.summary and not args.average and not args.visual and not args.explain:
        args.summary = True

    fileNames = []

    if args.stdin:
        for line in sys.stdin:
            t = line.strip()
            if len(t) > 0:
                fileNames.append(t)
    else:
        fileNames = args.files

    CoverageReport.commandLineMain(args, fileNames, args.testDir)
