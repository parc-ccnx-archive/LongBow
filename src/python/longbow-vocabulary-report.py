#! /usr/bin/env python
# Copyright (c) 2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
# @copyright (c) 2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.

import sys
import argparse

sys.path.append("@INSTALL_PYTHON_DIR@")
sys.path.append("@DEPENDENCY_PYTHON_DIR@")
sys.path.append("../site-packages/longbow/")
import VocabularyReport
import hfcca

def main(argv):
	desc = '''
Print the vocabulary (number of tokens) of functions and files.

The option --function displays the file name, function name,
line number of the function, the number of tokens

The default option --summary displays the file name, the average vocabulary
of all functions in the file and a score ranging from 0 to 100.

Usage:
$ longbow-vocabulary-report parc_JSON.c
parc_JSON.c  51.00 100.00
$
$ echo parc_JSON.c | longbow-vocabulary-report --function -o csv -
vocabulary,parc_JSON.c,_destroyPARCJSON,39,15,100.00
vocabulary,parc_JSON.c,parcJSON_Create,49,50,100.00
...
$

'''

	parser = argparse.ArgumentParser(prog='longbow-vocabulary-report', formatter_class=argparse.RawDescriptionHelpFormatter, description=desc)
	parser.add_argument('-s', '--summary', default=False, action="store_true", help="print the average vocabulary of each target file.")
	parser.add_argument('-f', '--function', default=False, action="store_true", help="print the vocabulary of each function in each target file.")
	parser.add_argument('-', '--stdin', default=False, action="store_true", required=False, help="read the list of files from standard input rather than the command line.")
	parser.add_argument('-a', '--average', default=False, action="store_true", required=False, help="display only the simple average of the average vocabulary of each target file.")
	parser.add_argument('-o', '--output', default="text", action="store", required=False, type=str, help="the output format: \"text\" or \"csv\"")
	parser.add_argument("files", help="Files to check", nargs="*")

	args = parser.parse_args()

        VocabularyReport.commandLineMain(args, hfcca)


if __name__ == "__main__":
	'''
@(#) longbow-vocabulary-report @VERSION@ @DATE@
@(#)   Copyright (c) 2014, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).
@(#)   All Rights Reserved. Use is subject to license terms.
	'''
	main(sys.argv)
