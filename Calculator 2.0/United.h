#define _CRT_SECURE_NO_WARNINGS
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
#include <time.h>
//<Element.h>
enum ElementType { _symbol, _number, _element }; //��� ��������
enum OperatorType { _add, _sub, _mlp, _div, _pow, _root }; //��� ���������


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
//</Element.h>

//<Element.cpp>
//����� � �����
int aaoi(char c) {
	return static_cast<int>(c - '0');
}

Element::~Element()
{
}
ElementType Element::elementType(void) { return _element; }
ElementType Symbol::elementType(void) { return _symbol; }
ElementType Number::elementType(void) { return _number; }

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
			//����� �� �����
			if (!dot)
			{
				v *= 10;
				v += aaoi(s[i]);
			}
			//����� ����� �����
			else
			{
				v += pow(0.1, p++) * aaoi(s[i]);
			}
			continue;
		}

		//�����
		if (s[i] == '.')
		{
			if (!dot)
				dot = true;
			else throw 7; //���������� ���������� �������������� ���� �����
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
	case _pow:
	case _root:
		priority += 0.25;
	case _mlp:
	case _div:
		priority += 0.25;
	case _add:
	case _sub:
		priority += static_cast<float>(p);
	}

}
//</Element.cpp>


//������ ����������
const char* ExceptionMessages[] =
{
	/*1*/  "�� ������� ����������.\n",
	/*2*/  "��������� ������������������ � ������� �� �������� ����������.\n",
	/*3*/  "����������� ������.\n",
	/*4*/  "���������� ��������� ���� �� ����������.\n",
	/*5*/  "����������� ����� �� �������������� � ���� ������: ���������� ����������� ����� �� �������������� ����� ����������.\n",
	/*6*/  "������������� ������������ �������� (����������� �������� \"NaN\").\n",
	/*7*/  "���������� ���������� �������������� ����� �� �����.\n",
	/*8*/  "����������� �������.\n",
	/*9*/  "���������� \"ans\" ��� �� ������ ��������.\n",
	/*10*/ "���������� \"ans\" ���������� ������ �������� �������.\n",
	/*11*/ "���������� ���������������� �������.\n",
	/*12*/ "������������ ���������.\n",
};

//char -> int
extern int aaoi(char c);

//������� ������ ����� "�����" � ��������������� CurrentYear �����
std::string age(int CurrentYear)
{
	if (CurrentYear % 100 >= 10 && CurrentYear % 100 <= 20)
		return "�������";
	if (CurrentYear % 10 == 0 || CurrentYear % 10 >= 5)
		return "�������";
	if (CurrentYear % 10 == 1)
		return "�����";

	return "������";
}

//������� ���������� ��� ������� �� ������ ������� ���������
int julesAge()
{
	time_t tCurrentTime;
	time(&tCurrentTime);
	tm* tk = localtime(&tCurrentTime);

	if (tk->tm_mon < 1)
		return tk->tm_year - 103;
	if (tk->tm_mon == 1 && tk->tm_mday < 22)
		return tk->tm_year - 103;

	return tk->tm_year - 102;
}

//������� ������� ��������� �����
void infoOut()
{
	std::cout << "Calculator v. 2.2" << std::endl << "�����, " << julesAge();
	std::cout << ((julesAge() != 16) ? (" (�� ������ �������� 16)") : ("")) << " ";
	std::cout << age(julesAge()) << ", 2018 ���." << std::endl;
	std::cout << "������, ��� ������������� ������� �� ��������������." << std::endl;
	std::cout << "��� ������ ������ �������� \"#help\"." << std::endl << std::endl;
}

//�����
//����

class MomentChange
{
public:
	bool yChanged, mChanged;
	MomentChange(bool y, bool m)
	{
		yChanged = y;
		mChanged = m;
	}
};

class Moment
{
public:
	Moment(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}



	MomentChange increment()
	{
		bool monthChanged = false, yearChanged = false;

		if (day == 31 && (month == 1 || month == 3 || month == 5 ||
			month == 7 || month == 8 || month == 10 || month == 12))

		{
			day = 1;
			month++;
			monthChanged = true;
		}



		if (day == 30 && (month == 4 || month == 6 ||
			month == 9 || month == 11))
		{
			day = 1;
			month++;
			monthChanged = true;
		}


		if (day == 28 && (month == 2) &&
			(year % 4 != 0 || (year % 400 != 0 && year % 100 == 0)))

		{
			day = 1;
			month++;
			monthChanged = true;
		}



		if (day == 29 && (month == 2) &&
			((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))

		{
			day = 1;
			month++;
			monthChanged = true;
		}
		if (month == 13)
		{
			year++;
			month = 1;
			yearChanged = true;
		}

		if (!monthChanged) day++;
		return MomentChange(monthChanged, yearChanged);
	}



	void increment_nl()
	{
		bool monthChanged = false, yearChanged = false;
		if (day == 30 && (month == 0 || month == 2 || month == 4 ||
			month == 6 || month == 7 || month == 9 || month == 11))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (day == 29 && (month == 3 || month == 5 ||
			month == 8 || month == 10))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (day == 27 && (month == 1) &&
			((year + 1) % 4 != 0 ||
				((year + 1) % 400 != 0 && (year + 1) % 100 == 0)))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (day == 28 && (month == 1) &&
			(((year + 1) % 4 == 0 && (year + 1) % 100 != 0) ||
				(year + 1) % 400 == 0))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (month == 12)
		{
			year++;
			month = 0;
			yearChanged = true;
		}
		if (!monthChanged) day++;
	}




	bool operator==(Moment& moment)
	{
		if (year == moment.getYear() &&
			month == moment.getMonth() &&
			day == moment.getDay())   return true;

		else
			return false;
	}

	bool operator!=(Moment& moment)
	{
		return !(*this == moment);
	}



	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

protected:
	int day, month, year;
};


//��������� ��� ������� ��������� �����
//"���", "�����" � "����" � ���������������
//������������� �����

std::string y_case(int numeral)
{
	if (numeral == 0)
		return "";

	if (numeral % 100 >= 10 && numeral % 100 <= 20)
		return "���";

	if (numeral % 10 == 0 || numeral % 10 >= 5)
		return "���";

	if (numeral % 10 == 1)
		return "���";

	return "����";
}

std::string m_case(int numeral)
{
	if (numeral == 0)
		return "";

	if (numeral % 100 >= 10 && numeral % 100 <= 20)
		return "�������";

	if (numeral % 10 == 0 || numeral % 10 >= 5)
		return "�������";

	if (numeral % 10 == 1)
		return "�����";

	return "������";
}

std::string d_case(int numeral)
{
	if (numeral % 100 >= 10 && numeral % 100 <= 20)
		return "����";

	if (numeral % 10 == 0 || numeral % 10 >= 5)
		return "����";

	if (numeral % 10 == 1)
		return "����";

	return "���";
}

bool parseDate(Moment * *moment)
{
	std::string s;
	std::cin >> s;
	int d, m, y;

	//��������� ������ ����� ��� "dd.mm.yyyy"
	if (s.length() != (2 + 2 + 4 + 2))
	{
		std::cout << "���� ������� �������" << std::endl;
		return false;
	}

	if (!isdigit(s[0]) || !isdigit(s[1]) ||
		!isdigit(s[3]) || !isdigit(s[4]) ||
		!isdigit(s[6]) || !isdigit(s[7]) ||
		!isdigit(s[8]) || !isdigit(s[9]) ||
		isdigit(s[2]) || isdigit(s[5]))
	{
		std::cout << "���� ������� �������" << std::endl;
		return false;
	}

	//���� ��������� ���������,
	//������������� ����

	d = aaoi(s[0]);
	d *= 10;
	d += aaoi(s[1]);

	m = aaoi(s[3]);
	m *= 10;
	m += aaoi(s[4]);

	y = aaoi(s[6]);
	y *= 10;
	y += aaoi(s[7]);
	y *= 10;
	y += aaoi(s[8]);
	y *= 10;
	y += aaoi(s[9]);

	//�������� �� ���������� ��� � 29 �������
	if (d == 29 && m == 2 &&
		(y % 4 != 0 || (y % 100 == 0 && y % 400 != 0)))

	{
		std::cout << "���� �� ����������" << std::endl;
		return false;
	}

	//�������� �� ������� ��� � �������
	if (d > 29 && m == 2)
	{
		std::cout << "���� �� ����������" << std::endl;
		return false;
	}

	//�������� �� ������� ��� �
	//������, ����, ��������, ������
	if (d > 30 && (m == 4 || m == 6 ||
		m == 9 || m == 11))

	{
		std::cout << "���� �� ����������" << std::endl;
		return false;
	}

	//�������� �� ������� ��� �
	//������, �����, ���, ����, 
	//�������, �������, �������
	if (d > 31 && (m == 1 || m == 3 || m == 5 ||
		m == 7 || m == 8 || m == 10 || m == 12))

	{
		std::cout << "���� �� ����������" << std::endl;
		return false;
	}

	//� ���������� �� ������ ����� �����?
	if (m > 12)
	{
		std::cout << "���� �� ����������" << std::endl;
		return false;
	}

	//���� ���� ���������,
	//������������� ��
	*moment = new Moment(d, m, y);
	return true;
}

bool isGreater(Moment m1, Moment m2)
{
	if (m1.getYear() > m2.getYear())
		return true;
	if (m1.getYear() < m2.getYear())
		return false;
	if (m1.getMonth() > m2.getMonth())
		return true;
	if (m1.getMonth() < m2.getMonth())
		return false;
	if (m1.getDay() > m2.getDay())
		return true;

	return false;
}


void calculateDataDifference(Moment m1, Moment m2)
{

	//���� m1 ��� ����� m2,
	//���������� �������� ��
	if (isGreater(m1, m2)) std::swap(m1, m2);

	//������� �������� ���,
	//������������� ������� counter
	Moment counter(0, 0, 0);

	int d = 0, m = 0, y = 0;

	while (m1 != m2 && (isGreater(m2, m1)))
	{
		d++;
		m1.increment();
		counter.increment_nl();
		if (d % 30 == 0) m++;
		if (d % 365 == 0) y++;
	}

	if (d == 0)
	{
		std::cout << "���� �����" << std::endl;
		return;
	}

	std::cout << "����� ����� ������� � ";

	if (counter.getYear() != 0)
	{
		std::cout << counter.getYear() << " " << y_case(counter.getYear());

		if (counter.getMonth() != 0 && counter.getDay() != 0) std::cout << ", ";

		else
		{
			if (counter.getMonth() != 0 || counter.getDay() != 0) std::cout << " � ";
		}
	}

	if (counter.getMonth() != 0)
	{
		std::cout << counter.getMonth() << " " << m_case(counter.getMonth());
		if (counter.getDay() != 0) std::cout << " � ";
	}

	if (counter.getDay() != 0)
	{
		std::cout << counter.getDay() << " " << d_case(counter.getDay());
	}

	std::cout << "." << std::endl;

	if (counter.getDay() != d)
		std::cout << "����� ������� ���������� ����� " << d
				  << " " << d_case(d) << "." << std::endl;
}


void helpOut() {
	std::cout << "��������� ��������:" << std::endl;
	std::cout << "��������\t\t\t\t������" << std::endl << std::endl;
	std::cout << "��������\t\t\t\t2+2" << std::endl;
	std::cout << "���������\t\t\t\t3-8.5" << std::endl;
	std::cout << "���������\t\t\t\t8*9" << std::endl;
	std::cout << "�������\t\t\t\t\t91/13" << std::endl;
	std::cout << "���������� � �������\t\t\t2^10" << std::endl;
	std::cout << "������ ����������� �����\t\t_2" << std::endl << std::endl;
	std::cout << "��� ��������� ������ ���������� ������ �����-���� ���������. ������:" << std::endl;
	std::cout << "(2+2)*2" << std::endl << "  =8" << std::endl;
	std::cout << "��������, ��� ��������� ������������������ ������ �������� ����������. \n"
				 "����������� ���������� ��������� ����������� ������.\n";
	std::cout << "��������� ������������ �������������� ���������� ���������� "
				 "(����� ������).\n� ������ �� ��� ����� �������� ��������� �����.\n";
	std::cout << "������ \"ans\" ��������������� � ������ ������ ��������� �����.\n";
	std::cout << "������ �������������:" << std::endl;
	std::cout << "afd+5*(6+7/3.5)" << std::endl << "=  43\n����� ������ \"afd\" ������� �������� 3.\n" << std::endl;
	std::cout << "��������� ������������ �������. ����� ������� ���������� � ������� \"#\"."
			  << std::endl << "������ ������:" << std::endl << std::endl;
	std::cout << "#set <name>\t\t������������� �������� ������ <name> ������ ���������� ������" << std::endl;
	std::cout << "#list\t\t\t���������� ��� ������, ��������� �� ����� ������ ���������" << std::endl;
	std::cout << "#date\t\t\t������� ������� ����� �����" << std::endl;
	std::cout << "#cls\t\t\t������� �� � ������, �������� ������ ��������� �����" << std::endl;
	std::cout << "#vacant\t\t\t������� ��������� �� � ������" << std::endl;
	std::cout << "#restart\t\t������������� ���������" << std::endl;
	std::cout << "#init\t\t\t�� ��, ��� � #restart" << std::endl;
	std::cout << "#void\t\t\t�� ��, ��� � #restart + #vacant" << std::endl;
	std::cout << "#help\t\t\t������� ������ �� ���������" << std::endl;
	std::cout << "#quit\t\t\t��������� ���������" << std::endl;
	std::cout << "#exit\t\t\t�� ��, ��� � #quit" << std::endl;
	std::cout << "#terminate\t\t�� ��, ��� � #quit" << std::endl;

}



//������� �������� ������� ���� ���� � ������
inline std::string smaller(std::string s)
{
	std::string s_;
	for (int i = 0; i < s.size(); i++)
	{
		if ((int)s[i] <= 90 && (int)s[i] >= 65) s_ += (char)(int(s[i]) + 32);
		else s_ += s[i];
	}
	return s_;
}



//������� ���������� ������,
//��������� �� ������ �������
std::string ctos(char c)
{
	std::string s_;
	s_ += c;
	return s_;
}

//������� �������� ��� ����������
//�� �������, ����������� �������� i
inline std::string sub_name(std::string & s, int& i)
{
	std::string ans;
	for (; i < s.size(); i++)
	{
		if (isalpha(s[i]))
		{
			ans += s[i];
			continue;
		}

		else break;
	}
	i--;
	return ans;
}



//������� ���������, �������� ��
//��� ���������� �����������������
//���������� "ans"
inline bool subname_is_ans(std::string & s, int& i)
{
	return (s.substr(i, 3) == "ans") ? true : false;
}



//������� ������� ��������� �� ������
inline void err_out(std::string s)
{
	std::cout << "������! " << s;
}



//������� ���������, �������� ��
//�������� ������ �������� � ������
bool isQuit(std::string s)
{
	if (smaller(s).substr(0, 5) == "#quit" ||
		smaller(s).substr(0, 10) == "#terminate" ||
		smaller(s).substr(0, 5) == "#exit") return true;

	else return false;
}



//����� ����� � ����������
int main()
{
	//wchar_t applicationTitle[] = L"Calculator 2.2\0";
	//SetConsoleTitle(applicationTitle);
	bool julesEnabled = true;
	bool julesOnceDisabled = false;
	setlocale(LC_ALL, "RUS");
	//	SetConsoleCP(1251);
	std::string input;
	int CBS;
	long double ans = 0.0;
	int counter = 0;

	std::map<std::string, long double> memory; //����� �������� ����������


	std::vector<Element*> v;
	std::vector<long double> listOfAnswers;
	Symbol* sp; //��������� �� ������ (��������)
	Number* np; //��������� �� �����
	infoOut();

	do
	{
		np = nullptr;
		sp = nullptr;
		v.clear();
		std::getline(std::cin, input);

		//������ ����� ���������,
		//�������� �� ��������� ������
		//�������� ������?

		if (isQuit(input))
			break;

		//�������� �� ������������
		CBS = 0;
		try
		{

			//���������, ���� �� ����������� �������
			for (auto& t : input)
			{
				if ((int)t < 0) throw 11;
			}


			if (smaller(input) == "jules" && julesEnabled)
			{
				std::cout << "Podliva" << std::endl;
				continue;
			}



			//<��������� ������>

						//���������, �������� �� intput ��������
			if (input[0] == '#')
			{
				if (input.size() < 4) throw 8; //��� ������� ������ 3 ��������

				//������� ��������� ����������
				if (smaller(input.substr(1, 3)) == "set")
				{
					//���������� i �� 4 ������� ������ 
					//� ���������, ��� �� ���������
					int i = 4;
					for (; i < input.size(); i++)
					{
						if (isalpha(input[i])) break;

						if (input[i] != ' ')
							throw 3; //����������� ������
					}

					//������������� ���������� �����, ������
					//���� ���� ��� ����������� ����������
					if (counter)
					{
						std::string variableName = sub_name(input, i);
						if (variableName == "")
							throw 1; //��� �� ���������� "" ?

						if (variableName == "ans")
							throw 10; //����������������� ���

						memory[variableName] = ans;
						std::cout << "�������� ���������� \"" << variableName
							<< "\" �����������." << std::endl;

					}
					else throw 9; //���������� "ans" ��� �� ������ ��������
					continue;
				}

				//������� ������������
				if (smaller(input.substr(1, 4)) == "fact")
				{
					//���������� i �� 4 ������� ������ 
					//� ���������, ��� �� ���������
					int i = 4;
					for (; i < input.size(); i++)
					{
						if (isalpha(input[i])) break;

						if (input[i] != ' ')
							throw 3; //����������� ������
					}

					//������������� ���������� �����, ������
					//���� ���� ��� ����������� ����������
					if (counter)
					{
						std::string variableName = sub_name(input, i);
						if (variableName == "")
							throw 1; //��� �� ���������� "" ?

						if (variableName == "ans")
							throw 10; //����������������� ���

						memory[variableName] = ans;
						std::cout << "�������� ���������� \"" << variableName
							<< "\" �����������." << std::endl;

					}
					else throw 9; //���������� "ans" ��� �� ������ ��������
					continue;
				}

				//��� ��������� �������
				else
				{

					//<��������>
					if (smaller(input.substr(1, 11)) == "enablejules")
					{
						if (julesEnabled) std::cout << "����� � ��� enabled" << std::endl;
						else std::cout << "�������" << std::endl;
						julesEnabled = true;
						continue;
					}
					if (smaller(input.substr(1, 12)) == "disablejules")
					{
						if (!julesEnabled) std::cout << "����� � ��� disabled (� ����� ����������)" << std::endl;
						else
						{
							if (!julesOnceDisabled) std::cout << "��� �� ����� �������� ����� ����, ����� disable ������??" << std::endl;
							else std::cout << "�� �� � ���� �������" << std::endl;
							julesOnceDisabled = true;
						}
						julesEnabled = false;
						continue;
					}
					//</��������>

					//������ �����
					if (smaller(input.substr(1, 6)) == "vacant")
					{
						system("cls");
						continue;
					}


					//������ �����, �� � ����������� � ���������
					if (smaller(input.substr(1, 3)) == "cls")
					{
						system("cls");
						infoOut();
						continue;
					}

					//������� ��� ����������, ������� ����
					//�������� � ���� ������ ���������
					if (smaller(input.substr(1, 4)) == "list" || smaller(input.substr(1, 4)) == "show")
					{
						for (int i = 0; i < listOfAnswers.size(); i++)
						{
							std::cout << i + 1 << ":\t" << listOfAnswers[i] << std::endl;
						}
						if (listOfAnswers.size() == 0)
							std::cout << "�� ��� ��� �� ���� �������� �� ������ ����������!\n";
						continue;
					}

					//������� ������ ������
					if (smaller(input.substr(1, 4)) == "help")
					{
						helpOut();
						continue;
					}

					//������������ ���������
					if (smaller(input.substr(1, 4)) == "init" ||
						smaller(input.substr(1, 7)) == "restart")

					{
						counter = 0;
						input = "";
						ans = 0;

						listOfAnswers.clear();
						memory.clear();
						np = nullptr;
						sp = nullptr;
						for (int i = 0; i < v.size(); i++)
						{
							delete v[i];
						}
						v.clear();
						CBS = 0;
						system("cls");
						infoOut();
						continue;
					}

					//������������ ��������� + system("cls")
					if (smaller(input.substr(1, 4)) == "void")
					{
						counter = 0;
						input = "";
						ans = 0;

						listOfAnswers.clear();
						memory.clear();
						np = nullptr;
						sp = nullptr;
						for (int i = 0; i < v.size(); i++)
						{
							delete v[i];
						}
						v.clear();
						CBS = 0;
						system("cls");
						continue;
					}

					//��������� ��������� ���
					if (smaller(input.substr(1, 4)) == "date" || smaller(input.substr(1, 4)) == "data") 
					{
						Moment* m1 = nullptr, * m2 = nullptr;
						do
						{
							std::cout << "������� ������ ���� � ������� ��.��.����: ";
						}
						while (parseDate(&m1) != true);
						do
						{
							std::cout << "������� ������ ���� � ������� ��.��.����: ";
						} while (parseDate(&m2) != true);

						calculateDataDifference((*m1), (*m2));
						continue;
					}
				}
				throw 8;
			}

			//</��������� ������>



			//<�������>

			for (int i = 0; i < input.size(); i++)
			{
				//������ ������ �� ������
				if (input[i] == ' ') 
					continue;

				//���� ��� �����, �� ��� ����������
				if (isalpha(input[i]))
				{
					try
					{
						if (subname_is_ans(input, i) && !counter)
							throw 9; //������ ���������� ans, ����� ��� ��� �� ������ ��������

						np = new Number(memory.at(sub_name(input, i)));
						v.insert(v.end(), np);
						np = nullptr;
						continue;
					}
					catch (std::out_of_range& e)
					{
						throw 1;
						//���� ��� ����� ����������, ���� �������� 
						//����� ���������� ��� ������� ����� �� � memory
					}
				}


				//���� �����, �� ��� �����
				if (isdigit(input[i]))
				{
					np = new Number;
					np->find_num(input, i);
					v.insert(v.end(), np);
					np = nullptr;
					continue;
				}


				//� ��������� ������� ��� ��������

				//���� ��������������� ��������
				switch (input[i])
				{

					//������:
				case '(':
					CBS++; //����������� ���-�� ������
					continue;


				case ')':
					if (--CBS < 0)
						throw 2; //��������� ����� ������,
								 //��������, � ����� �� ��� �������

					continue;

					//�������� ���������:
				case '+':
					sp = new Symbol(_add, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '-':
					sp = new Symbol(_sub, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '*':
					sp = new Symbol(_mlp, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '/':
					sp = new Symbol(_div, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '^':
					sp = new Symbol(_pow, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;

					//������� ��������:    
				case '_':
					sp = new Symbol(_root, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


					//��� ��������� �� ���������� ��� ��������        
				default:
					throw 3;
				}
			}

			//</�������>



			//<���������� ���������>
			while (v.size())
			{
				//����� ������� � ������������ �����������
				float maxPriority = -1; //����� �������� ������������ ���������
				int it = -1; //� ����� ��������� �� ������ � ������������ �����������
				for (int i = 0; i < v.size(); i++)
				{
					//���� ������� ������� - ������, �� ����� ��� ���������
					if (v[i]->elementType() == _symbol)
					{
						if (dynamic_cast<Symbol*>(v[i])->priority > maxPriority)
						{
							maxPriority = dynamic_cast<Symbol*>(v[i])->priority;
							it = i;
						}
					}
				}

				//������, ����� ������ ��� �� ������ ���������
				if (it == -1)
				{
					if (v.size() != 1)
						throw 12; //��-�����, ����� ����������, �� ��-����

					ans = dynamic_cast<Number*>(v[0])->value;
					break;
				}

				//������� ����� (��� ������������ � ���� ����������� � ��� �����������������)
				if (dynamic_cast<Symbol*>(v[it])->otype == _sub)
				{
					if (it + 1 == v.size())
						throw 4; //��� ������� ��������

					//it == 0:
					if (v[it + 1]->elementType() == _number && it == 0)
					{
						//��������� ������������������ ������� - ���, ������� ���� � ����������:
						//if (dynamic_cast<Number*>(v[it + 1])->value < 0) throw 4;

						np = new Number(0 - dynamic_cast<Number*>(v[it + 1])->value);
						delete v[it];
						delete v[it + 1];
						v[it] = np;
						np = nullptr;
						v.erase(v.begin() + it + 1);
						continue;
					}


					//it != 0:
					if (v[it + 1]->elementType() == _number && v[it - 1]->elementType() == _symbol)
					{
						//��������� ������������������ ������� - ���, ������� ���� � ����������:
						//if (dynamic_cast<Number*>(v[it + 1])->value < 0) throw 4;


						np = new Number(0 - dynamic_cast<Number*>(v[it + 1])->value);
						delete v[it];
						delete v[it + 1];
						v[it] = np;
						np = nullptr;
						v.erase(v.begin() + it + 1);
						continue;
					}
				}

				//���� �������� ����� �����/������ �������
				if (((it == 0) && (dynamic_cast<Symbol*>(v[it])->otype != _root))
					|| it + 1 == v.size()) throw 4;

				//���� ���������� ������ ������ ������������ ������
				if ((dynamic_cast<Symbol*>(v[it])->otype == _root) &&
					(v[it + 1]->elementType() != _number)) throw 4;

				//���� �������� �������� �� ������� ����� � ������ �� ��������
				if ((dynamic_cast<Symbol*>(v[it])->otype != _root))
				{
					if (v[it - 1]->elementType() != _number ||
						v[it + 1]->elementType() != _number)
						throw 4;
				}


				//���������� ������
				if ((dynamic_cast<Symbol*>(v[it])->otype == _root))
				{
					if (dynamic_cast<Number*>(v[it + 1])->value < 0)
						throw 5; //���������� sqrt �� �������������� �����

					np = new Number(sqrt(dynamic_cast<Number*>(v[it + 1])->value));


					delete v[it];
					delete v[it + 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					np = nullptr;
					continue;
				}

				switch (dynamic_cast<Symbol*>(v[it])->otype) {
					//��������
				case _add:
					np = new Number(dynamic_cast<Number*>(v[it - 1])->value
						+
						dynamic_cast<Number*>(v[it + 1])->value);


					if (isnan(np->value) || isinf(np->value))
						throw 6; //���� �� ����� ��������, �� ��� ��

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//���������
				case _sub:
					np = new Number(dynamic_cast<Number*>(v[it - 1])->value
						-
						dynamic_cast<Number*>(v[it + 1])->value);


					if (isnan(np->value) || isinf(np->value))
						throw 6; //����������

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//���������
				case _mlp:
					np = new Number((dynamic_cast<Number*>(v[it - 1])->value)
						*
						(dynamic_cast<Number*>(v[it + 1])->value));


					if (isnan(np->value) || isinf(np->value))
						throw 6; //����������

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//�������
				case _div:
					np = new Number((dynamic_cast<Number*>(v[it - 1])->value)
						/
						(dynamic_cast<Number*>(v[it + 1])->value));


					if (isnan(np->value) || isinf(np->value))
						throw 6; //� ��� ��� ����� ���� ������� �� ����!

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//���������� � �������
				case _pow:
					np = new Number(pow((dynamic_cast<Number*>(v[it - 1])->value),
						(dynamic_cast<Number*>(v[it + 1])->value)));


					if (isnan(np->value) || isinf(np->value))
						throw 6; //��� ���� ���-������ �� ����� ���������

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;
				}
			}
			//</���������� ���������>
		} //����� ���������� �������� ���� try


		//������������ ����������
		catch (int i)
		{
			err_out(ExceptionMessages[i - 1]);

			for (int i = 0; i < v.size(); i++)
			{
				delete v[i];
				v[i] = nullptr;
			}
			v.clear();
			continue;
		}

		//���� �� �������� ��������, �� ����� ��� ������� � �������� � ans
		if (v.size())
		{
			std::cout << "=  " << ans << std::endl;
			memory["ans"] = ans;
			listOfAnswers.insert(listOfAnswers.end(), ans);
			delete v[0];
			if (np != nullptr)
			{
				delete np;
			}
			if (sp != nullptr)
			{
				delete sp;
			}
			counter++;
		}


	} while (true);
}