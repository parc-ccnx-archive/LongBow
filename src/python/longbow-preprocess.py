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
import os
import subprocess
import pprint

def sourceFileNameToName(sourceFileName):
    '''
    Given the path to a source file, return the name without any path components or trailing suffix.
    '''
    name = os.path.basename(sourceFileName)
    return name.split(".")[0]

def canonicalizeFunctionName(functionName):
    '''
    Given a function name that contains the initial '_' character,
    strip it and return a canonicalised form of the same name suitable for a source file.
    '''
    if functionName[0] == "_":
        functionName = functionName[1:]
    return functionName

def isReservedName(functionName):
    '''
    Given a canonicalized name, determine if it is a reserved name according to ISO/IEC 9899:2011 and  ANSI Sec. 4.1.2.1,
    identifiers that begin with an underscore and either an uppercase letter or another underscore are always reserved for any use.
    '''
    if functionName[0] == '_' and functionName[1] == '_':
        return True
    elif functionName[0] == '_' and functionName[1].isupper():
        return True

    return False


def getDarwinTestableFunctions(sourceFileName, objectFileName):
    '''
    '''
    command = [ "/usr/bin/nm", "-Um", objectFileName ]

    output = subprocess.check_output(command)
    lines = output.splitlines()

    external = []
    internal = []
    for line in lines:
        fields = line.split(" ")
        if fields[1] == "(__TEXT,__text)":
            functionName = canonicalizeFunctionName(fields[3])

            if isReservedName(functionName):
                print "Ignoring function with a ISO/IEC 9899:2011 and ANSI Sec. 4.1.2.1 reserved name: ", functionName
            else:
                if fields[2] == "external":
                    external.append( ( functionName ) )
                else:
                    internal.append( ( functionName ) )
                    pass
            pass
    pass

    external.sort()
    internal.sort()
    return { "Static": internal, "Global" : external }

def testCases(functionList):
    '''
    '''
    return { "testCases" : functionList }

def testSuite(testCases):
    '''
    A Test Suite is comprised of one or more Test Cases
    '''
    if testCases == None or len(testCases) == 0:
        return None
    return [ testCases ]

def testFixture(testFixtureName, testSuites):
    '''
    A Test Fixture contains an initial setup function, one or more Test Suites, and a final tear-down function.
    '''
    if testSuites == None:
        return None
    return { "name" : testFixtureName, "testSuites" : testSuites }

def testRunner(testRunnerName, files, testFixtures):
    '''
    A Test Runner contains one or more Test Fixtures.
    '''
    testFixtures = [x for x in testFixtures if x is not None]
    return { "name" : testRunnerName, "files" : files, "testFixtures" : testFixtures }

def computeFileNames(argv):
    """ Given an argument list, compute the file names to use for code generation.


    """
    if (argv[1].endswith(".c")):
        return (argv[1], argv[2], sourceFileNameToName(argv[1]) + ".longbow")

    return (argv[1]+".c", argv[1]+".o", sourceFileNameToName(argv[1]) + ".longbow")

if __name__ == '__main__':
    '''
    @(#) longbow-preprocess @VERSION@ @DATE@
	@(#)   Copyright 2015 Palo Alto Research Center (PARC), a Xerox company.
	@(#)   All Rights Reserved. Use is subject to license terms.
'''
    if len(sys.argv) <= 1:
        print "Usage: longbow-preprocess (sourceFileName objectFileName) | (fileNamePrefix)"
        print
        print "Generate a plain-text intermediate form for a LongBow test case generated from"
        print "a specified source and object file.  Use longbow-code to produce a LongBow"
        print "test runner based upon the intermediate form."
        sys.exit(1)

    fileNames = computeFileNames(sys.argv)

    sourceFileName = fileNames[0]
    objectFileName = fileNames[1]
    outputFileName = fileNames[2]

    functionDictionary = getDarwinTestableFunctions(sourceFileName, objectFileName)

    testRunnerName = sourceFileNameToName(sourceFileName)

    testFixtures = map(lambda(fixtureType):
                       testFixture(fixtureType, testSuite(testCases(functionDictionary[fixtureType]))), functionDictionary)

    files = { "sourceFile" : sourceFileName, "objectFile" : objectFileName }
    result = testRunner(testRunnerName, files, testFixtures)

    out = open(outputFileName, "w")
    pp = pprint.PrettyPrinter(indent=4, width=132, depth=None, stream=out)
    pp.pprint(result)
    out.close()
    pass
