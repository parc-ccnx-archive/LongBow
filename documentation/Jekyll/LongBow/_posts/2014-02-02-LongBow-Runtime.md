---
layout: responsive
title: Runtime
categories: toplevel
---
Use LongBow assertions and traps to enforce program invariants during runtime execution.

For example:
{% highlight c %}
#include <LongBow/assertions>
#include <unistd.h>
#include <string.h>

void
function(char *pointer)
{
    assertNotNull(pointer, "The pointer cannot be NULL.");

    write(1, pointer, strlen(pointer));
}

int
main(int argc, char *argv[])
{
    function(0);
}
{% endhighlight %}

In this case the `assertNotNull` will trigger and the program will immediately terminate with the following output:
{% highlight c %}
Assert pointer.c:8 function() pointer != NULL The pointer cannot be NULL.
0   pointer                             0x0000000107840d4c function + 188
1   pointer                             0x0000000107840dd1 main + 33
2   libdyld.dylib                       0x00007fff887595fd start + 1
{% endhighlight %}


The example is very simple, and might imply that assertions are a type of error handling.
But unless catastrophic termination of your programme is your error handling strategy,
assertions are not a substitute for error handling.
Use assertions to explicitly test for conditions that must be true in order for an operation to work.
Test for NULL pointers, out-of-bounds array indices, incorrect dependent relationships.
Ultimately your code should work every time under all input conditions without ever triggering an assertion.

Be strategic about where the assertions are located and what they test for.

A failed assertion should be considered a bug and you should use them, and treat them, in that way.
For example a failure to open a file is likely not a bug in your programme, per se,
but indicative of some other problem and programmatic error handling would probably
be the best approach to handling the missing file.

Assertions can be included or excluded at compile-time.
In many cases, itt is reasonable to keep the assertions in production releases as an aid to future bug reporting.

<ul id="blog-posts" class="posts">
    {% for post in site.categories.runtime %}
      <li>
        <!-- span>{{ post.date | date_to_string }} &raquo;</span><a href="{{ post.url }}">{{ post.title }}</a -->
        <h3><a href="{{ site.baseurl }}{{ post.url }}">&raquo; {{ post.title }}</a></h3>
        <p>{{ post.excerpt }}</p>
      </li>
    {% endfor %}
</ul>