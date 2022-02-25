#pragma once
#include<string>
#include"TNodeStackAndList.h"
using namespace std;
class TCalculator
{
	T_stack_list<double> st_a;
	T_stack_list<char> st_char;
	string expr;
	string postfix; // строчка постфиксной записи выражения
	int prior(char op) {
		switch (op)
		{
		case'(': return 0;
		case'+': return 1;
		case'-': return 1;
		case'*': return 2;
		case'/': return 2;
		case'^': return 3;
		}
		return 0;
	}

public:
	TCalculator() {}
	TCalculator(TCalculator& TC) {
		expr = TC.expr;
		postfix = TC.postfix;
	}
	~TCalculator() {}

	TCalculator& operator=(TCalculator& TC) {
		expr = TC.expr;
		postfix = TC.postfix;
		return *this;
	}
	void SetExpr(string _expr) {
		expr = _expr;
	}
	string GetExpr() {
		return expr;
	}
	string GetPostfix() {
		return postfix;
	}
	bool CheckExpr()
	{
		for (int i = 0; i < expr.length(); i++) {
			if (expr[i] == '(')
				st_char.push(expr[i]);
			else if (expr[i] == ')')
				if (st_char.is_empty()) return false;
				else st_char.pop();
		}
		if (st_char.is_empty())
			return true;
		else return false;
	}

	void ToPostfix() {
		// где-то раньше очищаем expr от лишних скобок или добавляем их
		string infix = "(" + expr + ")";
		postfix = ""; // чистим строчку
		st_char.clear();
		string a_dig = ""; // накопительная строка для числа с >= 1 знаков

		for (int i = 0; i < infix.size(); i++) {
			if (infix[i] == ' ') continue; // избавились от пробелов на итерации
			if (isdigit(infix[i])) {
				a_dig += infix[i];
			}
			else {
				if (a_dig != "") {
					postfix += a_dig;
					a_dig = "";
					postfix += " ";
				}

				if (infix[i] == '(')
				{
					st_char.push(infix[i]);
				}
				else if (infix[i] == ')') // Если закрывающая скобка - вытаскиваем из стека в результат всё до первой (
				{
					while (st_char.top() != '(')
					{
						postfix += st_char.pop();
						postfix += " ";
					}
					st_char.pop(); // Удалим открывающую скобку
				}
				else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/') || (infix[i] == '^'))
				{
					while (prior(infix[i]) <= prior(st_char.top()))
					{
						postfix += st_char.pop();
						postfix += " ";
					}
					st_char.push(infix[i]);
				}
			}
		}
		if (!postfix.empty())
			postfix.pop_back(); // Удалим пробел после выражений
	}

	double CalcPostfix() {
		double tmp;
		st_a.clear();
		string a_dig = "";
		if (postfix.empty()) throw"empty";
		for (int i = 0; i < postfix.length(); i++) {
			if (isdigit(postfix[i])) {
				a_dig += postfix[i];
			}
			else if (postfix[i] == ' ' && isdigit(postfix[i - 1])) {
				double a = stod(a_dig);
				st_a.push(a);
				a_dig = "";
			}

			else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^')
			{
				if (st_a.is_empty()) throw("No more digits");
				double second = st_a.pop();
				if (st_a.is_empty()) throw("No more digits");
				double first = st_a.pop();
				switch (postfix[i])
				{
				case '+':
					tmp = first + second;
					st_a.push(tmp);
					break;
				case '-':
					tmp = first - second;
					st_a.push(tmp);
					break;
				case '*':
					tmp = first * second;
					st_a.push(tmp);
					break;
				case '/':
					tmp = first / second;
					st_a.push(tmp);
					break;
				case '^':
					tmp = 1;
					for (int j = 0; j < second; j++)
						tmp *= first;
					st_a.push(tmp);
					break;
				}
			}
		}
		if (st_a.is_empty()) throw("No more digits");
		else {
			double a = st_a.pop();
			if (st_a.is_empty()) return a;
			else throw("Too much digits");
		}
	}
};

/*считаем 2 + 3 * 4 ^ (1 + 2)

	 was A + B
	 bacame A B +

	 was 2 + 3* 4
	 became 2 3 4 * +

	 was 2 + 3* 4 - 5
	 became 2 3 4 * + 5 -

	 was 2 + 3* 4^2 - 5
	 became 2 3 4 2 ^ * + 5 -
	 was (2 + 3)* 4^2 - 5
	 became 2 3 + 4 2 ^ * 5 -
	 was (2 + 3)* 4^(2 - 5)
	 became 2 3 + 4 2 5 - ^ *
	 was 1/(2 + 3)* 4^(2 - 5)
	 became 1 2 3 + 4 2 5 - ^ * /

	 такие переводы на слудующем занятии
	 рассчеты:
	 кладем цифры в стек
	 встречаем знак - вынимаем два значения из стека
		  - делаем операцию - удаляем из стека -
		  - результат в стеке на вершине





	 нужна еще проверка корректности
	 если 4 - , то не можем изъять жлемент стека
	 если 4 5 - +, операций слишком много
	 если 4 3 2 -, осталось лишнее количество чисел
	 ну и скобки
	   с помощью стека можно указать конкретное место, где произошла ошибка





	 проверить правильность расстановки скобок в выражении
 при помощи стека(1 + 2) * 4
 пустые скобки() - нормально
 (1 + 2)) * 4
 ((((((1 + 2) * 4
	 ))((1 + )2 * 4()
		 Алгоритм:
 Создадим стек - встречаем(-кладем, встречаем) - убираем
	 просматтриваем слевонаправо
 если устанавливается скобка - кладем в стек,
 если закрывающую извлекаем из стека
 Если изымаем из пустого, то не правильно
 Если стек в итоге не пустой - тоже не правильно
 Тип данных - string
 юхаем
 str.size
 str.lengh
 для cin и cout  строчка считывается до первого пробела
 надо использовать getline(cin, str) читает все до enter





  УРОК 9 числа!


	 Работа с арифметическими выражениями
	 2 + 3 * 4 ^ 5
	 2 3 4 5 ^ * +
	 2ка - в строчку
	 + встретили ->  в стек ее
	 3ка - в строчку
	 * встретили -> сравниваем приоритеты, если больше у нее,
	 то она попадает в стек -> в стек ее
	 4ка - в строчку
	 ^ встретили -> сравниваем приоритеты, если больше у нее,
	 то она попадает в стек -> в стек ее
	 5ка - в строчку

	 обратно идем ибо конец строки

	 операция - выталкиваем из стека и тд

	 2 + 3 - 4 ^ 5
	 2 3 + 4 5 ^ -

	 22 + (3-2*2) ^ 5
	 22 3 2 2 * - 5 ^ +
	 если видим ( скобку - записываем ее в стек
	 если видим ) скобку - выпихиваем все операции

	 2ка - в строчку
	 + встретили ->  в стек ее
	 ( скобкку - записываем ее в стек
	 3ка - в строчку
	 - встретили ->  в стек ее
	 * встретили -> сравниваем приоритеты, если больше у нее,
	 то она попадает в стек -> в стек ее
	 2ка - в строчку
	 ) скобку -> удаляем из стека все (* и -), вполоть до (.,
	 параллельно записывая в строку


	 ^ встретили -> сравниваем приоритеты, если больше у нее,
	 то она попадает в стек -> в стек ее
	 5ка - в строчку
	 вычислили

	 !! приоритет ( = 0 !!
	 (заносится в стек без сравнения)

	 //искуственно добавим скобки в начале и в конце, тогда не надо
	 //писать отдельные исключения

	 приоритеты операций:
	 ( = 0
	 +- = 1
	 * / = 2
	 ^    = 3

	 2 + (2 * 2 - 1) ^ 5

	 2ка - в строчку
	 + встретили ->  в стек ее
	 ( скобкку - записываем ее в стек
	 2ка - в строчку
	 * встретили -> сравниваем приоритеты, если больше у нее,
	 то она попадает в стек -> в стек ее
	 2ка - в строчку
	 - встретили -> сравниваем приоритеты, меньше, выталкиваем *, пишем в стек
	 1ка - в строчку
	 ) скобку -> удаляем из стека *, и (, записываем * в строку
	 и тд

	 */