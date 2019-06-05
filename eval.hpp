/**
 * \file eval.hpp
 *
 * Encapsulates the interface for the expression evaluator function.
 */

#ifndef EVAL_HPP
#define EVAL_HPP

#include "cons.hpp"
#include "SymbolTableStack.hpp"
#include "flat_list_eval.hpp"
#include "list_utility.hpp"

/**
 * \brief Evaluate the expression tree whose root is pointed to by c
 * (error if c does not hold a well-formed expression).
 *
 * \return The value resulting from evaluating the expression.
 */
Cell* eval(Cell* const c);
#endif // EVAL_HPP
