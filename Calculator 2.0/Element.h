#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <clocale>
#include <cstdlib>
#include <cctype>
#include <map>
#include <list>
enum ElementType { _symbol, _number, _element}; //Тип элемента
enum OperatorType { _add, _sub, _mlp, _div, _pow, _root, _and, _or, _xor, _mod }; //Тип оператора


class Element
{
public:
	virtual ~Element();
	virtual ElementType elementType(void);
protected:

};

class Symbol : virtual public Element 
{
public:
	float priority;
	ElementType elementType(void);
	Symbol(OperatorType o, int p);
	OperatorType otype;
};

class Number : public Element 
{
public:
	Number();
	ElementType elementType(void);
	Number(long double d);
	long double value = 0;
	void find_num(std::string& s, int& i);
};