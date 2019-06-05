#include "eval.hpp"
/**
 * \brief check wether a Symbol is a primitive operator
 * \throw exception when c is not a SymbolCell
 * \param c a SymbolCell to be checked
 * \return true if and only if the symbol is a primitive operator
 */
bool operatorp(Cell* const c);
/** 
* \brief To check any mismatch in operand type and operand number for special operator ( quote, if, eval, print, define, lambda, apply)
* \param op the string indicating an operator
* \param operands_list a list of operands
*/
void Special_Form_type_check(string op, Cell* const operands_list, int operands_num);
/**
 * \brief eval a list and return the evaluated list as result
 * \param c the root of a binary tree storing a pased list expression
 * \return a new root of a binary tree storing the evaluated list expression
 */
Cell* eval(Cell* const c);
/**
 * \brief evaluate all the operands
 * \param operands_list
 * \return a new list contains all the evaluated operands
 */
Cell* eval_each(Cell* const operands_list);
/**
 * \brief apply the user-defined operator to a list of operands
 * \param procedure a ProcedureCell contain the definintion of user-defined operator
 * \param arg the list of operands
 * \return the result of the user-defined operation
 */
Cell* apply(Cell* const procedure, Cell* const arg);

///This function will only return true, if operator found, otherwise exception will be throw 
///Also, it is used to output the error message telling us which sup-expression is not an valid operator
bool operatorp(Cell* const c)
{
	if(symbolp(c)){
		string op=get_symbol(c);
		if(op=="+"||op=="-"||op=="*"||op=="/"||op=="quote"||op=="if"||op=="ceiling"||op=="floor"
			||op=="cons"||op=="car"||op=="cdr"||op=="nullp"||op=="intp"||op=="doublep"||op=="symbolp"||op=="listp"||op=="define"
			||op=="<"||op=="not"||op=="print"||op=="eval" ||op=="lambda"||op=="apply") 
		{ return true;
		} else {
			return false;
		}
	}
	else
	{
		throw runtime_error("There is no function and oeprators for expressions");
		/*
		stringstream op;
		op<<*c;
		string op_string=op.str();
		throw runtime_error(op_string+" can not be an valid operator");
		*/
	}
}

Cell* eval_each(Cell* const c)
{
	if (nullp(c)) {
		return nil;
	} 
	else if (atom(c)) {
		return tree_copy(c);
	} 
	//ConsCell
	else {
		Cell* eval_car=eval(car(c));
		return cons(eval_car , eval_each(cdr(c)));
		//return cons(eval(car(c)), eval_each(cdr(c)));
	}
}

//\class is_symbol function object
//\brief to check if all the oeprands are symbol
//\brief used in type checking of lambda first operand , which is a list of formals and they should be all symbol
class is_symbol{
public:
	bool all_symbol;
	is_symbol() : all_symbol(1) {}
	void operator() (Cell* operand) {
		if(!symbolp(operand)) { all_symbol=0; }
	}
};

///type check for operator "quote", "eval", "if", "define"
void Special_Form_type_check(string op, Cell* const operands_list, int operands_num)
{
	if(op=="quote" ||op=="eval") {
		if(operands_num!=1) {
			throw runtime_error(op+" operator requires exactly one operand.");
		}
	}
	else if(op== "if") {
		if(!(operands_num==2 || operands_num==3)) {
			throw runtime_error("if operator requires either two or three operands.");
		}
	}
	else if(op=="define") {
		if(operands_num!=2) {
			throw runtime_error("define operator requires exactly two operands."); 
		} else {
			if(!symbolp(car(operands_list))) {
				throw runtime_error("define operator need a symbol as the first operand."); }
		}
	}
	else if(op=="lambda") {
		if(operands_num<1) {
			throw runtime_error("lambda operator requires at least one operand.");
		}
		//The two operands of lambda should be list
		if(!listp(car(operands_list))) {
			throw runtime_error("the first operand of lambda operator must be a list of symbols."); 
		}
		if(!listp(cdr(operands_list))) {
			throw runtime_error("The rest of the operands of lambda operator must be a lsit of expressions.");
		}
		//check if all formals are symbol, if there is any
		if(!nullp(car(operands_list))) {
		is_symbol symbol_list_checker;
		for_each(car(operands_list),symbol_list_checker);
		if(!symbol_list_checker.all_symbol) {
				throw runtime_error("formals must be a symbol");
		}
		}
	}
}

//\class Define_symbol function object
//\brief used in apply() to bond all the arg to the formals
class Define_symbol{
private:
	Cell* arg_list;
	int arg_counter;
public:
	Define_symbol(Cell* const arg) : arg_list(arg), arg_counter(1) {}
	void operator() (Cell* operand) {
		if(!nullp(operand)) {
		Cell* nth_arg=nth_operand(arg_list,arg_counter);
		define(get_symbol(operand),nth_arg);
		++arg_counter;
		}
	}
};

Cell* apply(Cell* const procedure, Cell* const arg) {
	int arg_number=number_of_operands(arg);
	int formals_number=number_of_operands(get_formals(procedure));
	if(arg_number!=formals_number) {
		throw runtime_error("operand number of user-defined operator does not match with the formals.");
	}
	///create a new local table
	create_a_local_table();
	///bound the formals to the arguments
	/*if(nullp(arg)) {
	Define_symbol define_all_local_symbols(arg);
	for_each(get_formals(procedure), define_all_local_symbols);
	}*/
	Define_symbol define_all_local_symbols(arg);
	for_each(get_formals(procedure), define_all_local_symbols);
	///evaluate the function in the new scope
	Cell* result=eval_each(get_body(procedure));
	///delete the local table
	destroy_a_local_table();
	//return result;
	///only the last eval result is neeeded
	if(nullp(result)) {
		return nil;
	} else {
		return nth_operand(result, len(result));
	}
}

Cell* eval(Cell* const c) {
		///the tree is empty
		if(nullp(c)) {
			throw runtime_error("empty list cannot be evaluated");}
		///c is an atom
		else if(atom(c)) {
			///if c is a symbol, return its bounded value
			if(symbolp(c)) {
				if(operatorp(c)) {
					return tree_copy(c);
				}
				else {
					Cell* eval_symbol = symbol_translate(get_symbol(c));
					return tree_copy(eval_symbol);
				}
			} 
			//c is IntCell or DoubleCell
			else  { 
				return tree_copy(c); 
			}
		}
		///return c to parse_eval_print function in main to print the "#<function>"
		else if(procedurep(c)) {
			return tree_copy(c);
		}
		///c is a list
		else {
			Cell* eval_head=eval(car(c));
			
			if(procedurep(eval_head)) 
			{
				///user-defined operator
				return apply(eval_head,eval_each(cdr(c)));
			}
			else 
			{
			///check whether it is a primitive operator
			string op;
			if(operatorp(eval_head)) {
				op=get_symbol(eval_head);
			}
			else {
				Cell* symbol_to_op=symbol_translate(get_symbol(eval_head));
				if(operatorp(symbol_to_op)) {
					op=get_symbol(symbol_to_op);
				} else {
					op=get_symbol(symbol_to_op);
					tree_destroy(eval_head);
					throw runtime_error(op+" can not be an valid operator");
				}
			}
			tree_destroy(eval_head);
			///count the number of operands
			int operands_num=number_of_operands(cdr(c));
			///type check for the operands of operator "quote", "eval", "if", "define"
			///exception will be throw from here if not pass
			Special_Form_type_check(op, cdr(c), operands_num);
			///The operands of the operator will be assumed to be correctly matching the requirement of the operator,
			///since any error had been caught and throw by above Special_Form_type_check function.
			///So the operator can be savely assumed to apply on a list of operands without any runtime_error

			///quote return the one and only one operand without evaluating it
			if(op=="quote") {
				return tree_copy(car(cdr(c)));
			}
			else if(op=="eval") {
				Cell* eval_operand=eval(car(cdr(c)));
				Cell* result;
				try {
					result=eval(eval_operand);
				} catch(...) {
					tree_destroy(eval_operand);
					throw;
				}
				tree_destroy(eval_operand);
				return result;
			}
			else if(op=="if") {
				if(operands_num==2) {
					return eval(car(cdr(cdr(c))));
				} 
				//operands_num==3
				else {
					Cell* first_operand=eval(car(cdr(c)));
					try {
						if(!zerop(first_operand)) {
							///return the second operand for non-zero first operand
							return eval(car(cdr(cdr(c))));
						} else {
							return eval(car(cdr(cdr(cdr(c)))));
						} 
					} catch(...) {
						tree_destroy(first_operand);
						throw;
					}
				}
			}
			else if(op=="define") {
				string key=get_symbol(car(cdr(c)));
				Cell* value=eval(car(cdr(cdr(c))));
				define(key, value);
				return nil;
			}
			else if(op=="lambda") {
				///return a procedure cell
				Cell* list_of_arguments=list_copy(car(cdr(c)));
				Cell* list_of_expressions=list_copy((cdr(cdr(c))));
				return lambda(list_of_arguments,list_of_expressions);
			}
			else if(op=="apply") {
				Cell* procedure=eval(car(cdr(c)));
				if(!procedurep(procedure)) {
					tree_destroy(procedure);
					//throw runtime_error("No user-defined operator for the operands.");
					throw runtime_error("cannot apply a value that is not a function");
				}
				Cell* arg=eval(car(cdr(cdr(c))));
				return apply(procedure,arg);
			}
			///The operator is "nullp", "print", "not" "cons", "car", "cdr", "+", "-", "*", "/", "ceiling", "floor" or "<" 
			///recursively eval the operands list first
			///apply the operator on the operands list after that
			else {
				///evaluate all the operands
				Cell* eval_list=eval_each(cdr(c));
				Cell* result;
				///apply the operator op on the evaluated operands
				try{
					result=apply_to_flat_list(op,eval_list);
				}
				catch(...)
				{
					tree_destroy(eval_list);
					throw;
				}
				tree_destroy(eval_list);
				return result;
			}
			}
		}
}