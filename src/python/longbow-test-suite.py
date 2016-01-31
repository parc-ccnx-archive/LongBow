#! /usr/bin/env python
# Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
# @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
import sys
from subprocess import call

class LongBowTestSuite:
    def __init__(self):
        self.options = []
        return

    def setOptions(self, options=[]):
        self.options = options
        return

    def run(self, testRunners=[]):
        result = 0
        for test in testRunners:
            outputFileName = test + ".log"
            outputFile = open(outputFileName, 'w')
            command = [ test ] + self.options
            print command
            status = call(command, stdout=outputFile)
            if result == 0:
                result = status
                pass
            outputFile.close()
            pass
        return result


if __name__ == '__main__':
    testRunners = []
    if len(sys.argv) < 2:
        print "Usage: longbow-test-suite.py testExecutable ..."
        print "Run one or more LongBow test runners as indpendant processes"
        sys.exit(1)
    testRunners = testRunners + sys.argv[1:]

    testSuite = LongBowTestSuite()
    testSuite.setOptions([ "--run-nonforked" ])
    exitStatus = testSuite.run(testRunners)
