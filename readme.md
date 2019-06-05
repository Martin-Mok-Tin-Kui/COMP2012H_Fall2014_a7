COMP2012H Lab Programming Assignment 7, Fall 2014  
https://home.cse.ust.hk/~dekai/2012H/assignments/a7/html/  
maintain and extend the micro-Scheme language you've built in Assignments 1, 2, 3, and 4, specifically to provide a bigger micro-Scheme Standard Library of general-purpose library functions for users of your programming language.  

Recall that your micro-Scheme interpreter has been Turing-equivalent since Assignment 4. We celebrated by beginning to implement the rest of your micro-Scheme programming language, using only micro-Scheme. We had successfully used C++ to bootstrap your implementation of the micro-Scheme programming language, so that the rest can be done in micro-Scheme itself.  

Back in Assignment 4, we got you started by giving you implementations of the micro-Scheme Standard Library function factorial and the binary versions of the >, <=, >=, =, and abs operators. You yourself contributed your own implementation of another Standard Library function, for-each. Purely for fun, some of you also wrote additional Standard Library functions, such as the general map and reduce functions and the list function (which required you to have implemented the optional bonus support for a variable number of formal parameters for lambda).  

Now, in your existing library.scm file you will add implementations of a larger set of extremely useful Standard Library functions: list-tail and list-ref, reverse, equal?, assoc, partition, and list-sort.  