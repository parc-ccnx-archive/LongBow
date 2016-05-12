#! /usr/bin/env python
# Copyright (c) 2014-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
# @copyright (c) 2014-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
import os
import sys
import re
import pprint
import subprocess
import argparse
import json

class TokenParser:
    def __init__(self, tokens=[]):
        self.index = 0
        self.tokens = tokens

    def nextToken(self):
        result = self.tokens[self.index]
        self.index = self.index + 1
        return result

    def previousToken(self):
        self.index = self.index - 1
        result = self.tokens[self.index - 1]
        return result

    def expectedToken(self, expected):
        token = self.nextToken()
        if token == expected:
            return True
        self.index = self.index - 1
        print "expectedToken(%s) is not the actual %s" % (expected, token)
        return False

    def end(self):
        if self.index == len(self.tokens):
            return True
        return False

class LongBowCodeCoverage:
    def __init__(self):
        return

    def run(self, executableFile):
        lines = subprocess.check_output([ "gcov", "-f", executableFile ])
        token =  map(lambda x : x.strip("'"), re.split("[ :\n]+", lines))
        return self.parse(token)

    def parseFunction(self, parser):
        functionName = parser.nextToken()
        parser.expectedToken("Lines")
        parser.expectedToken("executed")
        coverage = parser.nextToken()
        return { "function" : functionName, "coverage" : coverage }
    
    def parseFile(self, parser):
        fileName = parser.nextToken()
        parser.expectedToken("Lines")
        parser.expectedToken("executed")
        coverage = parser.nextToken()
        return { "file" : fileName, "coverage" : coverage }
    
    def parse(self, tokens):
        parser = TokenParser(tokens)
        functions = [ ]
        
        while not parser.end():
            token = parser.nextToken()
            if (token == "Function"):
                function = self.parseFunction(parser)
                functions.append(function)
            elif (token == "File"):
                file = self.parseFile(parser)
            pass

        self.detailCoverage = { "file" : file, "functions" : functions }
        return self.detailCoverage

    def getCoverage(self):
        result["file"]["coverage"]

    def getDetailCoverage(self):
        return self.detailCoverage


class LongBowTestRun:
    def __init__(self, options=[]):
        self.options = options
        self.mainFileName = None
        self.exitStatus = 0
        return
    
    def setOptions(self, options=[]):
        self.options = options
        return
    
    def getMainFileName(self):
        return self.mainFileName
    
    def run(self, testRunner):
        self.mainFileName = testRunner
        self.exitStatus = 0

        try:
            try:
                os.remove(testRunner + ".gcda")
            except:
                pass
            lines = subprocess.check_output([ testRunner ])
            lines = re.split("[ :]+", lines)
            self.exitStatus = 0
        except subprocess.CalledProcessError, e:
            self.exitStatus = e.returncode
        
        return self.exitStatus

    def report(self, detailedOutput=False, jsonOutput=False):
        result = ""
        if self.exitStatus == 0:
            coverage = LongBowCodeCoverage()
            result = coverage.run(testRunner.getMainFileName())
    
            if detailedOutput:
                if jsonOutput:
                    result = json.dumps(result, sort_keys=False, indent=4, separators=(',', ': '))
                else:
                    pp = str(result)
                    pass
            else:
                if jsonOutput:
                    result = json.dumps(result["file"], sort_keys=False, indent=4, separators=(',', ': '))
                else:
                    result = "PASS " + result["file"]["file"] + " " + result["file"]["coverage"]
        else:
            result = "FAIL " + args.testRunner
            pass

        return result


if __name__ == '__main__':
    testRunners = []
    if len(sys.argv) < 2:
        print "Usage: longbow-test-run.py testExecutable"
        print "Run a LongBow test"
        sys.exit(1)
    
    parser = argparse.ArgumentParser(description='Run a LongBow Test')
    parser.add_argument("--json", help="Produce JSON output instead of a Python dictionary.",  action="store_true")
    parser.add_argument("--detailed", help="Produce detailed output.",  action="store_true")
    parser.add_argument("testRunner", help="The name of the test executable.", nargs='+')
    args = parser.parse_args()

    testRunner = LongBowTestRun([ "--run-nonforked" ])

    for test in args.testRunner:
        exitStatus = testRunner.run(test)
        print testRunner.report(args.detailed, args.json)

