dailylearn
==========

record the learning process in daily life, such as how to post a file, how to get url by proxy .... 



if you can't push your code, encounter the following error:

error: The requested URL returned error: 503 while accessing https://github.com/honglianglv/lib.git/info/refs
fatal: HTTP request failed

you can solve the problem by the following two ways:

1. git remote set-url origin ssh://git@github.com/your-user-name/your-project-name.git

or

2. git remote set-url origin https://your-user-name@github.com/your-user-name/your-project-name.git

