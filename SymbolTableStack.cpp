/**
 * \file SymbolTable.cpp
 *
 * Implementation the interface for accessing symbol table(s).
 */

#include "SymbolTableStack.hpp"
///gobal variable to be used across all the files
//\var gobal symbol table
SymbolTable gTable;
//\var stack of local symbol table
sbTableStack local_table_stack;

void create_a_local_table(SymbolTable& t)
{
	local_table_stack.push_back(t);
}

void create_a_local_table()
{
	SymbolTable t;
	local_table_stack.push_back(t);
}

void destroy_a_local_table()
{
	if(!local_table_stack.empty()) {
		local_table_stack.pop_back();
	}
}

//operation inside a table
void define_to_table(string symbol, Cell* cell, SymbolTable& t)
{
	
	Row_iter record=t.find(symbol);
	if(record == t.end())
	{
		t[symbol]=cell;
	} else {
		throw runtime_error("symbol "+symbol+" can not be redefined");
	}
}

Cell* const  symbol_translate_from_table(string symbol, SymbolTable& t, bool& found)
{
	
	Row_iter record=t.find(symbol);
	if(record != t.end())
	{
		found=true;
		return t[symbol];
	} else {
		found=false;
		return nil;
	}
}

//operation on stack of table
void define(string symbol, Cell* cell)
{
	if(local_table_stack.empty()) {
		define_to_table(symbol, cell, gTable);
	}
	else {
		define_to_table(symbol, cell, local_table_stack.back());
	}
}

Cell* const symbol_translate(string symbol) {
	bool found;
	Cell* value;
	//find in local tables
	if(!local_table_stack.empty()) {
		Table_iter temp_table_ptr=local_table_stack.end();
		while (temp_table_ptr != local_table_stack.begin())
		{
			--temp_table_ptr;
			value=symbol_translate_from_table(symbol, *temp_table_ptr, found);
			if(found) {
				return value;
			}
		}
	}
	//find in gobla table
	value=symbol_translate_from_table(symbol, gTable, found);
	if(found) {
		return value;
	}
	//fround=false, no record found even in the gobal table
	throw runtime_error("symbol "+symbol+" is undefined");
}