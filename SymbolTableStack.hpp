/**
 * \file SymbolTableStack.hpp
 *
 * Encapsulates an interface for accessing symbol table(s).
 * Gobal symbol table created here.
 */

#ifndef SYMBOLTABLESTACK_HPP
#define SYMBOLTABLESTACK_HPP

#include "cons.hpp"
#include <map>
#include <algorithm>    // std::transform
#include <vector>       // std::vector
#include <utility>


typedef map<string, Cell*> SymbolTable;
typedef map<string, Cell*>::iterator Row_iter;
typedef vector<SymbolTable> sbTableStack;
typedef vector<SymbolTable>::iterator Table_iter;
/**
 * \brief create a new local table.
 * \param the new local symbol table.(optional)
 */
void create_a_local_table(SymbolTable& t);
void create_a_local_table();
/**
 * \brief delete a local table.
 */
void destroy_a_local_table();
/**
 * \brief bound a symbol to a cell typed value
 * \param symbol the symbol that you want it to be bounded/defined
 * \param value the cell that you want the symbol to be bounded to
 */
void define(string symbol, Cell* value);
/**
 * \brief find the bounded(defined) value to the symbol top-down table stack
 * \exception throw when symbol is undefined in any table
 * \param symbol the symbol that was defined
 * \return the cell bounded
 */
Cell* const symbol_translate(string symbol);
#endif // SYMBOLTABLE_HPP