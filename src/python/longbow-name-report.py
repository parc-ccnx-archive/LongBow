#! /usr/bin/env python
# Copyright (c) 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
# All rights reserved.
#  
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#  
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution. 
#     * Patent rights are not granted under this agreement. Patent rights are
#       available under FRAND terms.
#  
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# @author Glenn Scott, Palo Alto Research Center (PARC)
# @copyright 2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.

import os
import sys
import argparse

sys.path.append("../site-packages/longbow/")
sys.path.append("@INSTALL_PYTHON_DIR@")
import NameReport

if __name__ == '__main__':
    '''
    @(#) name-report @VERSION@ @DATE@
    @(#)   Copyright 2015 Palo Alto Research Center (PARC), a Xerox company.
    @(#)   All Rights Reserved. Use is subject to license terms.
    '''
    desc = '''
Print a score representing the percentage of compliance with the naming conventions for one or more C source and object files.

$ ./longbow-name-report parc_Object.c
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-names 100.00 enum-names 100.0 typedef-names 100.0
$
$ echo parc_Object.c | ./parc-name-grade -
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-names 100.00 enum-names 100.0 typedef-names 100.0
$

Default Output (--summary):
namespace, module-name[, topic, score]

namespace: Namespace of the file, like `parc`
module-name: The name of the file, like `parc_ArrayList.c`
topic: The name of the topic: valid-name, function-name-conformance, or enum-name-conformance
score: A context-sensitive value related to the topic (valid-name: True/False, function/enum-name-conformance: 0-100)

Finegrain Output (--finegrain):
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-names 100.00 enum-names 100.0 typedef-names 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_Acquire 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_AssertValid 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_Compare 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_Copy 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_Create 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_Display 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_Equals 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_GetReferenceCount 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_HashCode 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_Release 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_TestAcquireContractRaw 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object function-name parcObject_ToJSON 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/LibpgetEnumerationsFromFilesarc/parc/algol parc_Object function-name parcObject_ToString 100.0
/Users/cwood/Projects/DistilleryBranches/Case1073/Libparc/parc/algol parc_Object typedef-name _ObjectHeader 100.0
'''

    parser = argparse.ArgumentParser(prog='longbow-name-report', formatter_class=argparse.RawDescriptionHelpFormatter, description=desc)
    parser.add_argument('-a', '--average', default=False, action="store_true", help="Print an average summary of the naming conformance results for all modules")
    parser.add_argument('-s', '--summary', default=False, action="store_true", help="Print a summary of the naming conformance results for each module")
    parser.add_argument('-f', '--finegrain', default=False, action="store_true", help="Print the individual results for each function, typedef, and enumeration in each module.")
    parser.add_argument('-o', '--output', default="text", action="store", required=False, type=str, help="the output format: \"text\" or \"csv\"")
    parser.add_argument('-d', '--distribution', default="[99, 90]", action="store", required=False, type=str, help="a list containing the score distributions for pretty-printing. Default [99, 90]")
    parser.add_argument('-t', '--trace', default=False, action="store_true", help="Turn on exception tracing to debug an issue with the tool.")
    parser.add_argument('-', '--stdin', default=False, action="store_true", required=False, help="Read the list of files from standard input.")
    parser.add_argument('-p', '--opath', default="", action="store", required=False, type=str, help="Specify the path for object files.")
    parser.add_argument("files", help="Files to check", nargs="*")

    args = parser.parse_args()

    targets = []
    if args.stdin:
        for line in sys.stdin:
            targets.append(line.strip())
    else:
        targets = args.files

    if (len(targets) == 0):
        parser.print_usage()
        sys.exit(1)

    NameReport.commandLineMain(args, targets, args.opath)
