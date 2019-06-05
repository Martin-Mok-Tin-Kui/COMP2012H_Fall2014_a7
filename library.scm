(define > (lambda (x y) (< y x)))
(define >= (lambda (x y) (not (< x y))))
(define <= (lambda (x y) (not (< y x))))
(define = (lambda (x y) (if (< x y) 0 (not (< y x)))))
(define abs (lambda (x) (if (< x 0) (- 0 x) x)))
(define factorial (lambda (x) (if (< x 2) 1 (* x (factorial (- x 1))))))

(print (quote "eval each expression in an expression list and return the result of the last evaluation"))
(define eval-exp-list (lambda (exp-list)
(if (not (listp exp-list)) (quote error)
	(if(nullp exp-list) (quote ())
		(if(nullp (car exp-list)) (quote ())
			(eval (car exp-list)))))
(if (not (listp exp-list)) (quote error)
	(if(nullp exp-list) (quote ())
		(eval-exp-list (cdr exp-list))))))

(print (quote "for-each apply function f to each element in list t."))
(define for-each (lambda (f t) 
(if (not (listp t)) (quote error)
	(if (nullp t)
		(quote ())
		(eval-exp-list (cons
			(f (eval(car t)))
			(for-each f (cdr t))))))))

(print (quote "count the number of element of a list t."))
(define count (lambda (t)
(if (not (listp t)) (quote error)
	(if (nullp t)
	0
	(+ 1 (count (cdr t)))))))

(print (quote "list-tail return the sublist of <list> obtained by omitting the first <k> elements."))
(define list-tail (lambda (list k)
(if (not (listp list)) (quote error)
(if (not (intp k)) (quote error)
(if (< k 0) (quote error)
(if (< (count list) k) (quote error)
	(if (= k 0)
	list
	(list-tail (cdr list) (- k 1)))))))))

(print (quote "list-ref return the kth element of list."))
(define list-ref (lambda (list k)
		(car (list-tail list k))))

(define equal? (lambda (x y)
(if (nullp x) 
	(if (nullp y) 1 0) 
	(if (nullp y) 0 
		(if (listp x) 
			(if (listp y) 
				(if (equal? (car x) (car y)) 
					(if (equal? (cdr x) (cdr y)) 1 0) 
					0) 
			0) 
			(if (listp y) 
				0 
				(if (= x y) 1 0)))))))

(print (quote "assoc finds the first pair in <alist> whose car field is <key>, and returns that pair. If no pair in <alist> has <key> as its car, then 0 (not the empty list) is returned."))
(define assoc (lambda (key alist) 
(if (nullp alist) 
	0 
	(if (nullp (car alist)) 
		(quote error) 
		(if (equal? key (car (car alist))) 
			(car alist) 
			(assoc key (cdr alist)))))))
 
(define list-partition (lambda (partitioner list) 
(define true-part (lambda (list1) 
	(if (nullp list1) 
		(quote ()) 
		(if (partitioner (car list1)) 
			(cons (car list1) (true-part (cdr list1)))
			(true-part (cdr list1)))))) 
(define false-part (lambda (list2) 
	(if (nullp list2) 
		(quote ()) 
		(if (partitioner (car list2)) 
			(false-part (cdr list2)) 
			(cons (car list2) (false-part (cdr list2))))))) 
(cons (true-part list) (cons (false-part list) (quote ())))))

(define append (lambda (list1 list2)
(if (nullp list1)
	list2
	(cons (car list1) (append (cdr list1) list2)))))

(define list-sort (lambda (lessThan? list)
(if (nullp list) (define pivot (quote ())) (define pivot (car list)))
(define partitioner (lambda (first_arg) (if (lessThan? first_arg pivot) 1 0)))
(define partitioned-list (list-partition partitioner (cdr list)))
(if (nullp list) (quote ())
	(append
	(append
	(list-sort lessThan? (car partitioned-list))
	(cons pivot (quote ())))
	(list-sort lessThan? (car (cdr partitioned-list)))))))

(define even? (lambda (x) (if (= x 0) 1 (if (= x 1) 0 (even? (- x 2))))))