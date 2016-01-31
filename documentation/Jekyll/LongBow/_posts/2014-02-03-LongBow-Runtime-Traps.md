---
layout: responsive
title: LongBow Traps
categories: runtime
---
LongBow traps are subsets of assertions and are intended for simple error reporting.
There is no functional difference between a trap and an assertion,
although traps do not perform tests while assertions do.

{% highlight c %}
if (impossibleState) {
    trapUnexpectedState("Things are in an impossible state");
}
{% endhighlight %}

This is functionally equivalent to:

{% highlight c %}
    assertNotTrue(impossibleState, "Things are in an impossible state");
{% endhighlight %}




