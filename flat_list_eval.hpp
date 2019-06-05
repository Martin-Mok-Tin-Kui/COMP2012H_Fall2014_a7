/**
 * \file flat_list_eval.hpp
 *
 * Encapsulates an abstract interface layer for operator functions applicable to flat list only
 */

#ifndef Flat_LIST_EVAL_HPP
#define Flat_LIST_EVAL_HPP

#include "list_utility.hpp"
/**
 * \brief apply one of the operator "nullp", "print", "not" "cons", "car", "cdr", "+", "-", "*", "/", "ceiling", "floor", "<" 
 * \brief to an list of operands which had been eval recursively by eval_each function
 * \param op the name of the operator
 * \param eval_list a flat list containing atoms-only operands
 * \return result of operation
 */
Cell* apply_to_flat_list(string op, Cell* const eval_list);

#endif //Flat_LIST_EVAL_HPP