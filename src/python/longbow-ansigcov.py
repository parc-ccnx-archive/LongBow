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
import os
import subprocess
'''
This programme takes a previously generated LongBow production (see longbow-preprocess.py) as input
and generates corresponding C code as a template for a complete test runner for that production.
'''

ansiRed = "\x1b[31m";
ansiGreen = "\x1b[32m";
ansiYellow = "\x1b[33;1m";
ansiOrange = "\x1b[33m";
ansiReset = "\x1b[0m";


def ANSITerminal_printchars(color, chars):
    if color == "red":
        return ansiRed + chars + ansiReset
    if color == "green":
        return ansiGreen + chars + ansiReset
    if color == "yellow":
        return ansiYellow + chars + ansiReset
    if color == "orange":
        return ansiOrange + chars + ansiReset
    return chars


class LongBowAnsi:
    def __init__(self, input=sys.stdin):
        self.input = input
        return

    def tokenise(self, line):
        fields = line.split(":", 2)
        fields[0] = fields[0].strip()
        return fields

    def colourise(self):
        lines = self.input.read().splitlines()
        for line in lines:
            fields = self.tokenise(line)
            if len(fields) == 3:
                if fields[0] == "#####":
                    print ANSITerminal_printchars("red", fields[1]), ANSITerminal_printchars("red", fields[2])
                    pass
                elif fields[0] == "$$$$$":
                    print ANSITerminal_printchars("yellow", fields[1]), ANSITerminal_printchars("yellow", fields[2])
                    pass
                else:
                    print ANSITerminal_printchars("green", fields[1]), ANSITerminal_printchars("green", fields[2])
                    pass
                pass
            pass
        return


if __name__ == '__main__':
    outputFileName = None
    
    if len(sys.argv) != 2:
        print "Usage: longbow-ansigov.py file.gcov"
        sys.exit(1)

    with open(sys.argv[1], 'r') as f:
        longBowAnsi = LongBowAnsi(f)
        longBowAnsi.colourise()
    f.close()

    pass
