---
layout: responsive
title: LongBow Assertions
categories: runtime
---
LongBow provides a basic set of assertions that test a condition and if that condition fails to be true,
the assertion triggers.

When an assertion triggers:
  * An Event is created which records the kind of assertion that failed,
  * the location of the assertion's failure,
  * the formatted message of the failed assertion.
  * The event is reported via the LongBow report library.
  * The running program is sent a SIGABRT signal..
  



 