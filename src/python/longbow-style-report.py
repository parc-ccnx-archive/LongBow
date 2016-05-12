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
import StyleReport

if __name__ == '__main__':
    '''
@(#) longbow-code @VERSION@ @DATE@
	@(#)   Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).
	@(#)   All Rights Reserved. Use is subject to license terms.
'''
    desc = '''
Report on style conformance for one or more C source or header files.

Input is either from a list of files supplied as command line parameters,
or as a list of newline separated file names read from standard input.
Reports are:
--summary A one line per file report of the file name, number of lines, number of non-compliant lines, and a score.
--average A single line output of the average of all scores.
--total A single line of output of the percentage of all compliant lines to the total number of lines in all files.
--visual A visual representation of the style check.

For each of these reports, the output format is specified by:
--output text  Display text on standard output
--output csv Display a list of comma-separated values on standard output.
--output gui Use a graphical user interface if possible.

The visual report displays either a colorized, line by line output of
the differences between the original source file it's exemplar (-o text),
or displays a file-merge application for interactive use ()-o gui)

Example:

% longbow-style-report *.[ch]

Report conformance of the .c and .h files specified as command line parameters.

% longbow-style-report -
Report conformance of the .c and .h files read from standard input, one line per file.

$ longbow-style-report parc_JSON.c
parc_JSON.c   239     0 100.00$
$
$ echo parc_JSON.c | longbow-style-report -
parc_JSON.c,239,0,100.00
$
'''

    parser = argparse.ArgumentParser(prog='longbow-style-report', formatter_class=argparse.RawDescriptionHelpFormatter, description=desc)
    parser.add_argument('-', '--stdin', default=False, action="store_true", required=False, help="read the list of files from standard input only.")
    parser.add_argument('-s', '--summary', default=False, action="store_true", required=False, help="Display the score for each file.")
    parser.add_argument('-a', '--average', default=False, action="store_true", required=False, help="Display the simple average of all scores.")
    parser.add_argument('-t', '--total', default=False, action="store_true", required=False, help="Display the percentage of all compliant lines to the total number of lines in all files.")
    parser.add_argument('-d', '--distribution', default="[95, 90]", action="store", required=False, type=str, help="a list containing the score distributions for pretty-printing. Default '[95, 90]' (green >= 95, yellow >= 90, red < 90).")
    parser.add_argument('-o', '--output', default="text", action="store", required=False, type=str, help="the output format: 'text', 'csv', or 'gui'.")
    parser.add_argument('-v', '--visual', default=False, action="store_true", required=False, help="Display a visual representation of the style check.")
    parser.add_argument('-k', '--key', default="name", action="store", required=False, type=str, help="The sort key: Type '--key help' for the list.")
    parser.add_argument('-e', '--exclude', default="", action="store", required=False, type=str, help="Exclude a comma separated set of one or more of: 'red', 'yellow', 'green'.")

    parser.add_argument("files", help="Files to check", nargs="*")

    args = parser.parse_args()

    if args.summary == False and args.average == False and args.total == False and args.visual == False:
        args.summary = True

    targets = []

    if args.stdin:
        for line in sys.stdin:
            t = line.strip()
            if len(t) > 0:
                targets.append(t)
    else:
        targets = args.files

    UNCRUSTIFY = "@UNCRUSTIFY_BIN@"
    UNCRUSTIFY_CONFIG = "@UNCRUSTIFY_CONFIG@"

    StyleReport.commandLineMain(args, targets, UNCRUSTIFY, UNCRUSTIFY_CONFIG)
