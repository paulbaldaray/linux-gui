reorganizetags
==============

Description
-----------

Shifts all clients per tag to leftmost unoccupied tags.

For example, if clients A, B, C are tagged on tags 1, 5, 9 respectively, when
this function is called, they will now be on 1, 2, and 3. The focused client
will also remain focused.

Clients on multiple tags will be treated as if they only were only on their
leftmost tag, and will be reduced to one tag after the operation is complete.

Download
--------
* [dwm-reorganizetags-6.2.diff]([dwm-reorganizetags-6.2.diff)

Authors
-------
* Paul Baldaray - <paulbaldaray@gmail.com>
