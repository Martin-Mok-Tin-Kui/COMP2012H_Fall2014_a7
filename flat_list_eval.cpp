/**
 * \file flat_list_eval.hpp
 *
 * Implementation of the abstract interface layer for operator functions applicable to flat list only
 */

#include "flat_list_eval.hpp"
//\class add function object to add a number to the result
class add {
public:
	//\var result of addition
	double result;
	//\var is_double true when the operand is a DoubleCell
	bool is_double;
	/** 
	* \brief result should be first initialize to 0 as it is the identity of +
	* \brief assume the numerical operand is an integer, so is_double=0 to signal a casting needed for integer result
	*/
	add () : result(0), is_double(0) {}
	/**
	* \brief add(Cell* operand) functor 
	* \param operand a numerical operand to be added to the result data field
	*/
	void operator() (Cell* const operand) {
		if(nullp(operand)) {
			result=0;
		}
		else {
			result+=get_number(operand,is_double);
		}
	}
};
//\class multiply function object to multiply a number to the result
class multiply {
public:
	//\var result of mutiplication
	double result;
	//\var is_double true when the operand is a DoubleCell
	bool is_double;
	/** 
	* \brief result should be first initialize to 1 as it is the identity of *
	* \brief assume the numerical operand is an integer, so is_double=0 to signal a casting needed for integer result
	*/
	multiply () : result(1), is_double(0) {}
	/**
	* \brief multiply(Cell* operand) functor 
	* \param operand a numerical operand to be mutipled to the result data field
	*/
	void operator() (Cell* const operand) {
		if(nullp(operand)) {
			result=1;
		}
		else {
			result*=get_number(operand,is_double);
		}
	}
};
//\class subtract function object to subtract the result by a number
class subtract {
public:
	//\var result of subtraction
	double result;
	//\var is_double true when the operand is a DoubleCell
	bool is_double;
	/** 
	* \brief subtract constructor
	* \brief assume the numerical operand is an integer, so is_double=0 to signal a casting needed for integer result
	* \param first_operand result is first initialized to the first_operand
	*/
	subtract (double first_operand,bool first_double=0) :result(first_operand) , is_double(first_double) {}
	/**
	* \brief subtract(Cell* operand) functor 
	* \param operand a numerical operand to be subtracted from the result data field
	*/
	void operator() (Cell* const operand) {
		result-=get_number(operand,is_double);
	}
};
//\class divide function object to divide the result by a number
class divide {
public:
	//\var result of division
	double result;
	//\var is_double true when the operand is a DoubleCell
	bool is_double;
	/** 
	* \brief divide constructor
	* \brief assume the numerical operand is an integer, so is_double=0 to signal a casting needed for integer result
	* \param first_operand result is first initialized to the first_operand
	*/
	divide (double first_operand,bool first_double=0) :result(first_operand) , is_double(first_double) {}
	/**
	* \brief divide(Cell* operand) functor 
	* \param operand a numerical operand to be divided from the result data field
	*/
	void operator() (Cell* const operand) {
		double x=get_number(operand,is_double);
		if(x) {
		result/=x;
		} else {
			throw runtime_error("Divided by zero!");
		}
	}
};
//\class LessThan function object to compare the two number, it return false once the left operand >= the right operand
class LessThan {
public:
	//\var result of < operator
	bool result;
	//\var the last right_operand compared
	double left_operand;
	//\var the last right_operand compared
	string left_string;
	/** 
	* \brief LeeThan Constructor
	* \brief assume the numerical operand is an integer, so is_double=0 to signal a casting needed for integer result
	* \param first_operand result is first initialized to the first_operand
	*/
	LessThan (double first_operand) : result(1), left_operand(first_operand) {}
	LessThan (string first_string) : result(1), left_string(first_string) {}
	/**
	* \brief multiply(Cell* operand) functor 
	* \param operand a IntCell or DoubleCell to be compared to the left_operand
	*/
	void operator() (Cell* const operand) {
		if(symbolp(operand)){
			if(left_string>=get_symbol(operand)) {
				result=0;
			}
			left_string=get_symbol(operand);
		}
		else {
			if(left_operand>=get_number(operand)) {
				result=0;
			}
			left_operand=get_number(operand);
		}
	}
};
//\class is_numeric function object 
//\brief to change the a bool flag which is true if and only if all the oeprands passed in is a number
class is_numeric{
public:
	bool is_number;
	is_numeric() : is_number(1) {}
	void operator() (Cell* operand) {
		if(!numberp(operand)) {
			is_number=0;
		}
	}
};
/** 
* \brief To check any mismatch in operand type and operand number for 
* \brief operator "nullp", "print", "not" "cons", "car", "cdr", "+", "-", "*", "/", "ceiling", "floor", "<"
* \param op the string indicating an operator
* \param operands_list a list of operands
*/
void operands_type_check(string op, Cell* const operands_list, int operands_num)
{
	if(op=="nullp" || op=="intp"|| op=="doublep"|| op=="symbolp" || op=="print" || op=="not") {
		if(operands_num!=1) {
			throw runtime_error(op+" operator requires exactly one operand."); 
		}
	}
	if(op=="car" || op=="cdr") {
		if(operands_num!=1) {
			throw runtime_error(op+" operator requires exactly one list operand."); 
		} else {
			if(!listp(car(operands_list))) {
				throw runtime_error(op+" operator requires exactly one list operand."); } 
		}
	}
	if(op=="cons") {
		if(operands_num!=2) {
			throw runtime_error(op+" operator requires exactly two operand."); 
		} else {
			if(!listp(car(cdr(operands_list)))) {
				throw runtime_error(op+" operator requires the second operand to be a list."); } 
		}
	}
	if(op=="ceiling" || op=="floor") {
		if(operands_num!=1) {
			throw runtime_error(op+" operator requires exactly one double operand."); 
		} else {
			if(!doublep(car(operands_list))) {
				throw runtime_error(op+" operator requires exactly one double operand."); } 
		}
	}
	if(op=="<") {
	}
	if(op=="+" || op=="-" || op=="*" || op=="/") {
		if(operands_num==0) {
			if(op=="-" || op=="/"){
				throw runtime_error(op+" operator requires at least one operand.");
			}
		} else {
			is_numeric Numeric_checker;
			for_each(operands_list,Numeric_checker);
			if(!Numeric_checker.is_number){
				throw runtime_error("operand of "+op+" operator should be number.");
			}
		}
	}
}

Cell* apply_to_flat_list(string op, Cell* const operands_list)
{
	int operands_num=number_of_operands(operands_list);
	operands_type_check(op, operands_list, operands_num);

	if(op=="nullp") {
		return nullp(car(operands_list)) ? make_int(1):make_int(0);
	}
	if(op=="intp") {
		return intp(car(operands_list)) ? make_int(1):make_int(0);
	}
	if(op=="doublep") {
		return doublep(car(operands_list)) ? make_int(1):make_int(0);
	}
	if(op=="symbolp") {
		return symbolp(car(operands_list)) ? make_int(1):make_int(0);
	}
	if(op=="listp") {
		return listp(car(operands_list)) ? make_int(1):make_int(0);
	}
	if(op=="print") {
		nullp(car(operands_list)) ? cout<<"()\n" : cout<<*car(operands_list)<<endl;
		return nil;
	}
	if(op=="car") {
		return list_copy(car(car(operands_list)));
	}
	if(op=="cdr") {
		return list_copy(cdr(car(operands_list)));
	}
	if(op=="ceiling") {
		return make_int(std::ceil(get_double(car(operands_list))));
	} 
	if(op=="floor") {
		return make_int(std::floor(get_double(car(operands_list))));
	}
	if(op=="not") {
		return zerop(car(operands_list)) ? make_int(1) : make_int(0);
	}
	if(op=="cons") {
		Cell* operand1 = car(operands_list);
		Cell* operand2 = car(cdr(operands_list));
		return cons(list_copy(operand1),list_copy(operand2));
	}
	///arithmetic operators
	if(op=="+") {
		///calculation
		add adder;
		for_each(operands_list,adder);
		///return result
		if(adder.is_double) {
			return make_double(adder.result);
		} else {
			return make_int((int)adder.result);
		}
	}

	if(op=="*") {
		///calculation
		multiply multiplier;
		for_each(operands_list,multiplier);
		///return result
		if(multiplier.is_double) {
			return make_double(multiplier.result);
		} else {
			return make_int((int)multiplier.result);
		}
	}

	if(op=="<") {
		if(operands_num==0 || operands_num==1) {
			return make_int(1);
		} else {
			if(symbolp(car(operands_list))) {
				string first_string=get_symbol(car(operands_list));
				///calculation
				LessThan comparator(first_string);
				for_each(cdr(operands_list),comparator);
				///return result
				return make_int(comparator.result);
			}
			else {
				///get the first number since the left operand can not initilize to -infinity.
				double first_number=get_number(car(operands_list));
				///calculation
				LessThan comparator(first_number);
				for_each(cdr(operands_list),comparator);
				///return result
				return make_int(comparator.result);
			}
		}
	}

	///get the first operand since the operator behave differently with only one operand and more than one operands
	bool first_double=0;
	Cell* first_operand=car(operands_list);
	double first_number=get_number(first_operand,first_double);

	if(op=="-") {
		///calculation
		subtract subtracter(0);
		if(operands_num==1) {
			subtracter(first_operand);
		} else {
			subtracter.result=first_number;
			subtracter.is_double=first_double;
			for_each(cdr(operands_list),subtracter);
		}
		///return result
		if(subtracter.is_double) {
			return make_double(subtracter.result); 
		} else {
			return make_int((int)subtracter.result);
		}
	}

	if(op=="/") {
		///calculation
		divide divider(1);
		if(operands_num==1) {
			if(first_number==0) {
				divider.result=0;
			} else {
				divider(first_operand);
			}
		} else {
			divider.result=first_number;
			divider.is_double=first_double;
			for_each(cdr(operands_list),divider);
		}
		///return result
		if(divider.is_double) {
			return make_double(divider.result);
		} else {
			return make_int((int)divider.result);
		}	
	}
}