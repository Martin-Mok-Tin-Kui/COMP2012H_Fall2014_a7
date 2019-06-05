#include "Cell.hpp"

// Reminder: cons.hpp expects nil to be defined somewhere.  For this
// implementation, this is the logical place to define it.
Cell* const nil = 0;
//all Cell have two common methods:
//one is to check the type of the Cell, which is is_type()
//another is to print the content of the Cell, which is print()
//
//and also, based on the type different constructors 
//with different types of value(s) to be stored will be passed in.
//accessor(s) to member(s) in the Cell will also be defined
//a destructor may needed to release the dynamic resourse(s) used by the Cell
///////////////////////////////////
//implementation of IntCell
std::string IntCell::get_type()  const
{
	return "int";
}

Cell* IntCell::copy() const
{
	return new IntCell(this->int_m);
}

void IntCell::print(std::ostream& os) const
{
	os<<get_int();
}

IntCell::IntCell(const int i)
{
	int_m = i;
}

int IntCell::get_int() const
{
	return int_m;
}

bool IntCell::is_zero() const
{
	return int_m==0? true : false;
}
///////////////////////////////////
//implementation of DoubleCell
std::string DoubleCell::get_type() const
{
	return "double";
}

Cell* DoubleCell::copy() const
{
	return new DoubleCell(this->double_m);
}

void DoubleCell::print(std::ostream& os) const
{
	//os.precision(10);
	os.setf(ios::showpoint);
	os<<get_double();
}

DoubleCell::DoubleCell(const double d)
{
	double_m = d;
}

double DoubleCell::get_double() const
{
	return double_m;
}

bool DoubleCell::is_zero() const
{
	return double_m==0? true : false;
}
///////////////////////////////////
//implementation of SymbolCell
std::string SymbolCell::get_type() const
{
	return "symbol";
}

Cell* SymbolCell::copy() const
{
	return new SymbolCell(this->symbol_m);
}

void SymbolCell::print(std::ostream& os) const
{
	os<<get_symbol();
}

SymbolCell::SymbolCell(string s)
{
	symbol_m =s;
}

string SymbolCell::get_symbol() const
{
	return symbol_m;
}

bool SymbolCell::is_zero() const
{
	return symbol_m=="0" ? true : false;
}
///////////////////////////////////
//implementation of ConsCell
std::string ConsCell::get_type() const
{
	return "cons";
}

Cell* ConsCell::copy() const
{
	Cell* car_temp;
	if(this->car_m==nil) {
		car_temp=nil;
	} else {
		car_temp=this->car_m->copy();
	}
	Cell* cdr_temp;
	if(this->cdr_m==nil) {
		cdr_temp=nil;
	} else {
		cdr_temp=this->cdr_m->copy();
	}
	return new ConsCell(car_temp, cdr_temp);
}

void ConsCell::print(std::ostream& os) const
{
	os<<"(";
	if(get_car()==nil) {
		os<<"() ";
	} else {
		get_car()->print();
	}
	Cell* temp = get_cdr();
	while(temp != nil) 
	{
		os<<" ";
		if(temp->get_car()==nil) {
			os<<"() ";
		} else {
			temp->get_car()->print();
		}
		temp=temp->get_cdr(); 
	}
	os<<")";
}

ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr)
{
	car_m = my_car;
	cdr_m = my_cdr;
}

Cell* ConsCell::get_car() const
{
	return car_m;
}

Cell* ConsCell::get_cdr() const
{
	return cdr_m;
}

ConsCell::~ConsCell()
{
	delete car_m;
	delete cdr_m;
}
///////////////////////////////////
//implementation of ProcedureCell
std::string ProcedureCell::get_type() const
{
	return "procedure";
}

Cell* ProcedureCell::copy() const
{
	Cell* formals_temp;
	if(this->formals_m==nil) {
		formals_temp=nil;
	} else {
		formals_temp=this->formals_m->copy();
	}
	Cell* body_temp;
	if(this->body_m==nil) {
		body_temp=nil;
	} else {
		body_temp=this->body_m->copy();
	}
	return new ProcedureCell(formals_temp, body_temp);
}

/*
Cell* ProcedureCell::apply(Cell* const args) const
{
	return new ConsCell(ConsCell(this->formals_m, args));
}
*/
void ProcedureCell::print(std::ostream& os) const
{
	os<<"#<function>";
}

ProcedureCell::ProcedureCell(Cell* const my_formals, Cell* const my_body)
{
	formals_m = my_formals;
	body_m = my_body;
}

Cell* ProcedureCell::get_formals() const
{
	return formals_m;
}

Cell* ProcedureCell::get_body() const
{
	return body_m;
}

ProcedureCell::~ProcedureCell()
{
	delete formals_m;
	delete body_m;
}