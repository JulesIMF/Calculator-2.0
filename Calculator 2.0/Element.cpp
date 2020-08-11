#include "Element.h"
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

//Цифра в число
int aaoi(char c) {
	return static_cast<int>(c - '0');
}

Element::~Element()
{
}
ElementType Element::elementType(void) { return _element; }
ElementType Symbol ::elementType(void) { return _symbol;  }
ElementType Number ::elementType(void) { return _number;  }

Number::Number(long double d) 
{
	value = d;
}

void Number::find_num(std::string& s, int& i) 
{
	bool dot = false;
	int p = 1;
	long double v = 0;

	for (; (i != s.size()); i++) 
	{
		if (isdigit(s[i])) 
		{
			//Часть до точки
			if (!dot) 
			{
				v *= 10;
				v += aaoi(s[i]);
			}
			//Часть после точки
			else 
			{
				v += pow(0.1, p++) * aaoi(s[i]);
			}
			continue;
		}

		//Точка
		if (s[i] == '.') 
		{
			if (!dot) 
				dot = true;
			else throw 7; //Невозможно определить принадлежность этой точки
			continue;
		}
		i--;
		value = v;
		return;
	}
	i--;
	value = v;
	return;
}

Number::Number() = default;

Symbol::Symbol(OperatorType o, int p)
{
	priority = 0;
	otype = o;
	switch (o) 
	{
	case _div:
		priority += 0.1;
	case _pow:
	case _root:
		priority += 0.1;
	case _mlp:
		priority += 0.1;
	case _mod:
		priority += 0.1;
	case _add:
	case _sub:
		priority += 0.1;
	case _and:
		priority += 0.1;
	case _xor:
		priority += 0.1;
	case _or:
		priority += static_cast<float>(p);
	}

}