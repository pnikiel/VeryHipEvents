About
-----

This module, previously known as EventRecorder, has been born out of necessity
to optimize some massive data-processing applications at CERN. 

The whole idea about it is that it should pose as small load to the application under investigation
as possible, while still being able to log events from numerous threads. Any sort of blocking or waiting
is excluded, by requirement.

Author
------
Piotr Nikiel <piotr.nikiel@gmail.com>