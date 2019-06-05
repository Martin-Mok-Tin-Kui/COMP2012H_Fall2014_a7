/**
 * \file list_utility.hpp
 *
 * An abstract interface layer for operations on list such as copy list , destroy list, count number of elements and get element specified by integer index
 * also include a class for creating a cell list for easy of operation
 */

#ifndef LIST_UTILITY_HPP
#define LIST_UTILITY_HPP

#include "cons.hpp"

typedef Cell element;
typedef Cell list;

/**
 * \brief deep copy a list
 * \param list to be copied
 * \return a copy of the list
 */
inline list* list_copy(Cell* const list){
	return cell_copy(list);
}
///synonym function names
inline Cell* tree_copy(Cell* const tree){
	return cell_copy(tree);
}
/**
 * \brief deeply destroy a tree
 * \param c the tree to be destroyed
 */
inline void tree_destroy(Cell* tree){
	cell_destroy(tree);
}
inline void list_destroy(Cell* list){
	cell_destroy(list);
}
/**
 * \brief count the number of cell
 * \param CellList a list of Cell
 * \return number of Cells inside the list
 */
int len(list* const CellList);
inline int number_of_operands(Cell* const operands_list) {
	return len(operands_list);
}
/**
 * \brief get the nth element of the newCellList
 * \param n the index of the element(counted from 1)
 * \return the nth element
 */
element* const nth_operand(list* const operands_list, int n);
/**
 * \brief apply an operator on a list of operands
 * \param operands_list a list of operands
 * \param op a unary functor to be applied on all operands
 * \return data field of the unary functor after applying it to all operands
 */
template <class FuncType>
void for_each(list* const operands_list, FuncType& op)
{
	if(nullp(operands_list)) {
		op(nil);//<no operand, return the result specified when op get zero operand
	}
	else if(atom(operands_list)) {
		op(operands_list);
	}
	else if(consp(operands_list)) {
		int n=number_of_operands(operands_list);
		for(int i=1;i <= n;++i)
		{
			op(nth_operand(operands_list,i)); 
		}
	}
}

#endif //LIST_UTILITY_HPP