/**
 * \file cons.hpp
 *
 * Encapsulates an abstract interface layer for a cons list ADT,
 * without using member functions. Makes no assumptions about what
 * kind of concrete type Cell will be defined to be.
 */

#ifndef CONS_HPP
#define CONS_HPP

#include "Cell.hpp"

#include <fstream>
#include <sstream>

#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include <stdexcept>

using namespace std;
/**
 * \var nil a gobal variable
 * defined in Cell.cpp to be null cell.
 */
extern Cell* const nil;
///group of functions to make different cells:
inline Cell* cell_copy(Cell* const c);
inline void cell_destroy(Cell* c);
inline IntCell* make_int(const int i);
inline DoubleCell* make_double(const double d);
inline SymbolCell* make_symbol(const char* const s);
inline ConsCell* cons(Cell* const my_car, Cell* const my_cdr);
inline ProcedureCell* lambda(Cell* const my_formals, Cell* const my_body);
///group of functions to get the contents of the cell:
inline int get_int(Cell* const c);
inline double get_double(Cell* const c);
inline double get_number(Cell* const c,bool& is_double);
inline double get_number(Cell* const c);
inline std::string get_symbol(Cell* const c);
inline Cell* car(Cell* const c);
inline Cell* cdr(Cell* const c);
inline Cell* get_formals(Cell* const c);
inline Cell* get_body(Cell* const c);
///group of functions to check the cell type:
inline bool procedurep(Cell* const c);
inline bool nullp(Cell* const c);
inline bool consp(Cell* const c);
inline bool listp(Cell* const c);
inline bool atom(Cell* const c);
inline bool intp(Cell* const c);
inline bool doublep(Cell* const c);
inline bool symbolp(Cell* const c);
inline bool zerop(Cell* const c);
inline bool numberp(Cell* const c);

////////////////////////////////////////////////////////////////////
///group of functions to make different cells:
///make_int, make_double, make_symbol, cons, lambda
////////////////////////////////////////////////////////////////////
/**
 * \brief Copy the Cell deeply
 * \param a cell pointer
 * \return a new cell pointer with the same cell content
 */
Cell* cell_copy(Cell* const c)
{
	if(c==nil) {
		return nil;
	} else {
		return c->copy();
	}
}
/**
 * \brief Destroy the Cell deeply
 * \param a cell pointer
 */
void cell_destroy(Cell* c)
{
	if(c) {
		delete c;
		c=nil;
	}
}
/**
 * \brief Make an int cell.
 * \param i The integer to be stored
 */
IntCell* make_int(const int i)
{
  return new IntCell(i);
}

/**
 * \brief Make a double cell.
 * \param d The double to be stored
 */
DoubleCell* make_double(const double d)
{
  return new DoubleCell(d);
}

/**
 * \brief Make a symbol cell.
 * \param s The symbol to be stored
 */
SymbolCell* make_symbol(const char* const s)
{
  return new SymbolCell(string(s));
}

/**
 * \brief Make a conspair cell.
 * \param my_car The car part
 * \param my_cdr The cdr part
 */
ConsCell* cons(Cell* const my_car, Cell* const my_cdr)
{
  return new ConsCell(my_car, my_cdr);
}
/**
 * \brief Make a procedure cell.
 * \param my_formals (the list of arguments).
 * \param my_body (the list of expressions).
 */
ProcedureCell* lambda(Cell* const my_formals, Cell* const my_body)
{
  return new ProcedureCell(my_formals, my_body);
}
//endgroup

////////////////////////////////////////////////////////////////////
///group of functions to get the contents of the cell
///get_int, get_double, get_symbol, car, cdr
////////////////////////////////////////////////////////////////////
/**
 * \brief get the integer field of a IntCell.
 * \brief throw runtime error if c is not a IntCell.
 * \return The integer  field in the IntCell.
 */
int get_int(Cell* const c)
{
	if (intp(c))
		return c->get_int();
	else
	{
		throw runtime_error("try to get an integer from non integer Cell.");
	}
}

/**
 * \brief get the double field of a DoubleCell.
 * \brief throw runtime error if c is not a DoubleCell.
 * \return The double field in the DoubleCell.
 */
double get_double(Cell* const c)
{
	if (doublep(c))
		return c->get_double();
	else
	{
		throw runtime_error("try to get a double from non double Cell.");
	}
}

/**
 * \brief get a double value which is double field of a DoubleCell or a casted double from the integer field of IntCell
 * \brief throw runtime error if c is not a IntCell or DoubleCell.
 * \return The double value
 */
double get_number(Cell* const c,bool& is_double) {
	if(numberp){
		if(doublep(c)) {
			is_double=1;
			return get_double(c);
		} else {
			return get_int(c);
		}
	} else {
		throw runtime_error("try to get a number from a cell that can not do");
	}
}

double get_number(Cell* const c) {
	if(numberp){
		 return doublep(c) ?  get_double(c) : (double)get_int(c);
	} else {
		throw runtime_error("try to get a number from a cell that can not do");
	}
}
/**
 * \brief get the symbol field of a SymbolCell.
 * \brief throw runtime error if c is not a SymbolCell.
 * \return The symbol in the SymbolCell.
 */
std::string get_symbol(Cell* const c)
{
  if (symbolp(c))
		return c->get_symbol();
	else
	{
		throw runtime_error("try to get a symbol from non symbol Cell.");
	}
}
/**
 * \brief get the car pointer
 * \brief throw runtime error if c is not a ConsCell.
 * \return The car part in the ConsCell.
 */
Cell* car(Cell* const c)
{
	if (listp(c)) {
		if(!nullp(c)) {
		return c->get_car();
		} else {
			throw runtime_error("try to get a car of a null Cell.");
		}
	} else {
		throw runtime_error("try to get a car from non-ConsCell.");
	}
}

/**
 * \brief get the cdr pointer
 * \return The cdr part in the ConsCell.
 * \return nil if it is null cell or atom cell
 */
Cell* cdr(Cell* const c)
{
	if(nullp(c)) {
		return nil;
	} else if(atom(c)) {
		return nil;
	} else {
		return c->get_cdr();
	}
}

/**
 * \brief get formals_m (the list of arguments)
 * \brief throw runtime error if c is not a ProcedureCell.
 * \return The formals_m field (stored the list of arguments)
 */
Cell* get_formals(Cell* const c)
{
  if (procedurep(c)) {
		if(!nullp(c)) {
			return c->get_formals();
		} else {
			throw runtime_error("try to get a list of arguments from a null Cell.");
		}
	} else {
		throw runtime_error("try to a list of arguments from non-ProcedureCell.");
	}
}

/**
 * \brief get body_m (the list of expressions)
 * \brief throw runtime error if c is not a ProcedureCell.
 * \return The body_m field (stored the list of expressions)
 */
Cell* get_body(Cell* const c)
{
  if (procedurep(c)) {
		if(!nullp(c)) {
			return c->get_body();
		} else {
			throw runtime_error("try to get a list of arguments from a null Cell.");
		}
	} else {
		throw runtime_error("try to a list of arguments from non-ProcedureCell.");
	}
}
//endgroup

////////////////////////////////////////////////////////////////////
///group of functions to check the cell type
///procedurep, nullp, consp, listp, atom, intp, doublep, symbolp, zerop
////////////////////////////////////////////////////////////////////
/**
 * \brief Check if c is a procedure cell.
 * \return True iff c is a procedure cell.
 */
bool procedurep(Cell* const c)
{
  return !nullp(c) && c->get_type()=="procedure";
}
/**
 * \brief Check if c points to an empty list, i.e., is a null pointer.
 * \return True iff c points to an empty list, i.e., is a null pointer.
 */
bool nullp(Cell* const c)
{
  return c == nil;
}
/**
 * \brief Check if c points to an cons cell.
 * \return True iff c points to an cons cell.
 */
bool consp(Cell* const c)
{
	return !nullp(c) && c->get_type()=="cons";
}
/**
 * \brief Check if c points to a list (i.e., nil or a cons cell).
 * \return True iff c points to a list (i.e., nil or a cons cell).
 */
bool listp(Cell* const c)
{
  return nullp(c) || consp(c);
}
/**
 * \brief Check if c is an atom (i.e. int,double or symbol)
 * \return True iff c is an atom (i.e. int,double or symbol)
 */
bool atom(Cell* const c)
{
	return !listp(c) && !procedurep(c);
}
/**
 * \brief Check if c points to an int cell.
 * \return True iff c points to an int cell.
 */
bool intp(Cell* const c)
{
	return !nullp(c) && c->get_type()=="int";
}
/**
 * \brief Check if c points to a double cell.
 * \return True iff c points to a double cell.
 */
bool doublep(Cell* const c)
{
	return !nullp(c) && c->get_type()=="double";
}
/**
 * \brief Check if c points to a symbol cell.
 * \return True iff c points to a symbol cell.
 */
bool symbolp(Cell* const c)
{
	return !nullp(c) && c->get_type()=="symbol";
}
/**
 * \brief check if the cell c stored a zero.
 * \return true if the stored value is zero.
 */
bool zerop(Cell* const c)
{
	if(c==nil) return false;
	return c->is_zero();
}

bool numberp(Cell* const c){
	return !nullp(c) && (c->get_type()=="int" || c->get_type()=="double");
}
//endgroup

/**
 * \brief Print the tree rooted at c, in s-expression notation.
 * \param os The output stream to print to.
 * \param c The root cell of the subtree to be printed.
 */
inline std::ostream& operator<<(std::ostream& os, const Cell& c)
{
		c.print(os);
		return os;
}

#endif // CONS_HPP
