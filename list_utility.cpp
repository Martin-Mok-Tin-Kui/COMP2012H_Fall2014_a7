/**
 * \file list_utility.cpp
 *
 * Implementation of operations on list such as copy list , destroy list, count number of elements and get element specified by integer index
 * also include a class for creating a cell list for easy of operation
 */

#include "list_utility.hpp"

///general algorithm on list
int len(list* const CellList)
{
	element* temp=CellList;
	int num=0;
	while(!nullp(temp))
	{
		++num;
		temp=cdr(temp);
	}
	return num;
}

element* const nth_operand(list* const operands_list, int n)
{
	if(nullp(operands_list) || atom(operands_list)) {
		return operands_list;
	} else {
		if(n <= len(operands_list)) {
			Cell* temp=operands_list;
			for(int i=1;i<n;++i) {
				temp=cdr(temp);
			}
			return car(temp);
		} else {
			return nil;
		}
	}
}
