/**
 * \mainpage COMP2012H Programming Assignment 3 and 4, Fall 2014
 *
 * \author Mok Tin Kui
 * \author 20152782
 * \author tkmok@connect.ust.hk
 * \author COMP2012H Fall 2014
 *
 * \date 2014-11-20
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * 
 * (1)	the evaluator support case like ((quote if) 1 2 3)
 *
 * (2)	a function template called for_each ,defined in list_utility.hpp file, which accept an operator functor was written,
 *		so that an operator functor can be applied on each operands in an operands list
 *		and hence Clean up the evaluator using function templates.
 *
 * (3)	basically, this evaluator main eval function divided the evaluation problem in to two cases by operator type. 
 *		The first case is that the operator can apply on a non-flattened list, 
 *		and the second case is that the operator can only apply on a flat list.
 *		In the second case, Any non-flattened operands list will be evaluated to a flat list with each operand evaluated by eval_each function defined in eval.cpp file.
 *		The operator then apply on that flat list.
 *
 * (4)	Two gobal objects will be created in this program. both are declared in SymbolTableStack.cpp:
 *		A gobal symbol table object and a stack of local symbol table object. 
 *		Any operation related to a tables and a stack of table are decleared sperately in SymbolTable.hpp
 *		which provide an interface for operation on table and stack of table, and sperate them from the evaluator.
 *		Such that the symbol table and stack of symbol table used in this evaluator program can be implemented generally 
 *		without knowing there is a evaluator client using the symbol table or a stack of symbol table.
 *
 * (5)	In a7, the intp, doublep, symbolp defined in cons.cpp were exposed to the user of the evaluator
 *		And the < operator also edited so that for string can also be compared to make the lisp evaluator to accept general type
 */

/**
 * \file Cell.hpp
 *
 * Encapsulates the abstract interface for a concrete class-based
 * implementation of cells for a cons list data structure.
 */


#ifndef CELL_HPP
#define CELL_HPP

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//\class Cell
class Cell {
public:
	/**
	* \brief return the type name of the cell
	* \return type name
	*/
	virtual std::string get_type() const =0;
	//\return a copy of the cell
	virtual Cell* copy() const =0;
	//\Support function application
	//virtual Cell* apply(Cell* const args) const {return nil;}
	/**
	* \brief Print the value of the Cell.
	* \brief assume the Cell is null, and print ()
	* \param os The output stream (Default is cout) to print to.
	*/
	virtual void print(std::ostream& os = std::cout) const { os<<"() "; }
	//\brief different accessors to different members
	virtual int get_int() const {return false;}
	virtual double get_double() const {return false;}
	virtual string get_symbol() const {return false;}
	virtual Cell* get_car() const {return false;}
	virtual Cell* get_cdr() const {return false;}
	virtual Cell* get_formals() const {return false;}
	virtual Cell* get_body() const {return false;}
	/**
	* \brief check if the number or string is zero
	* \return true if the content of the cell is zero
	*/
	virtual bool is_zero() const {return false;}
	//\brief release all the resourses owned by the Cell
	virtual ~Cell(){}
};

//\class IntCell
class IntCell : public Cell
{
public:
	//\return "int"
	virtual std::string get_type() const;
	//\return a copy of this cell
	virtual Cell* copy() const;
	/**
	* \brief Print the value of the Cell.
	* \param os The output stream (Default is cout) to print to.
	*/
	virtual void print(std::ostream& os = std::cout) const;
	/** 
	* \brief To make an IntCell.
	* \param i The value assigned to the int in IntCell.
	*/
	IntCell(const int i);
	//\brief get the integer.
	int get_int() const;
	//\brief return true if int_m is zero
	virtual bool is_zero() const;
private:
	int int_m;
};

//\class DoubleCell
class DoubleCell : public Cell
{
public:
	//\return "double"
	virtual std::string get_type() const;
	//\return a copy of this cell
	virtual Cell* copy() const;
	/**
	* \brief Print the value of the Cell.
	* \param os The output stream (Default is cout) to print to.
	*/
	virtual void print(std::ostream& os = std::cout) const;
	/** 
	* \brief To make a DoubleCell.
	* \param d The value assigned to the double in DoubleCell.
	*/
	DoubleCell(const double d);
	//\brief get the double.
	double get_double() const;
	//\brief return true if int_m is zero
	virtual bool is_zero() const;
private:
	double double_m;
};

//\class SymbolCell
class SymbolCell : public Cell
{
public:
	//\return "symbol"
	virtual std::string get_type() const;
	//\return a copy of this cell
	virtual Cell* copy() const;
	/**
	* \brief Print the value of the Cell.
	* \param os The output stream (Default is cout) to print to.
	*/
	virtual void print(std::ostream& os = std::cout) const;
	/** 
	* \brief To make a SymbolCell.
	* \param d The value assigned to the string in SymbolCell.
	*/
	SymbolCell(const string s);
	//\brief get the symbol.
	string get_symbol() const;
	//\brief return true if int_m is zero
	virtual bool is_zero() const;
private:
	string symbol_m;
};

//\class ConsCell
class ConsCell : public Cell
{
public:
	//\return "cons"
	virtual std::string get_type() const;
	//\return a copy of this cell
	virtual Cell* copy() const;
	/**
	* \brief Print the value of the Cell.
	* \param os The output stream (Default is cout) to print to.
	*/
	virtual void print(std::ostream& os = std::cout) const;
	/** 
	* \brief To make a ConsCell.
	* \param my_car The value assigned to the car part in ConsCell.
	* \param my_cdr The value assigned to the cdr part in ConsCell.
	*/
	ConsCell(Cell* const my_car=0, Cell* const my_cdr=0);
	//\brief get the car pointer.
	Cell* get_car() const;
	//\brief get the car pointer.
	Cell* get_cdr() const;
	//\To release the memory allocated to the two pointers in the heap.
	~ConsCell();
private:
	Cell* car_m;    //\var Cell pointer to the head of ConsCell
	Cell* cdr_m;    //\var Cell pointer to the tail of ConsCell
};

//\class ProcedureCell
class ProcedureCell : public Cell
{
public:
	//\return "procedure"
	virtual std::string get_type() const;
	//\return a copy of this cell
	virtual Cell* copy() const;
	//\Support function application
	//virtual Cell* apply(Cell* const args) const;
	/**
	* \brief Print "#<function>"
	* \param os The output stream (Default is cout) to print to.
	*/
	virtual void print(std::ostream& os = std::cout) const;
	/** 
	* \brief To make a ProcedureCell.
	* \param my_formals
	* \param my_body
	*/
	ProcedureCell(Cell* const my_formals=0, Cell* const my_body=0);
	//\brief get the formals of Procedure
	Cell* get_formals() const;
	//\brief get the body of Procedure
	Cell* get_body() const;
	//\To release the memory allocated to the two pointers in the heap.
	~ProcedureCell();
private:
	Cell* formals_m;    //!< to point to the list of arguments
	Cell* body_m;       //!< to point to the list of expressions
};
// Reminder: cons.hpp expects nil to be defined somewhere (for this
// implementation, Cell.cpp is the logical place to define it).
// Here we promise this again, just to be safe.
extern Cell* const nil;

#endif // CELL_HPP