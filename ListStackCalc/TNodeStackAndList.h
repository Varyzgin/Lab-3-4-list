#pragma once
#include <iostream>
#include"../TNodeStruct.h"
// стек на списке 

/* когда были стеки мы хранили его вершину
	  |
0 1 2 3 4 5 6 - индексы
6 3 7 1       - элементы
в стеке на списках начало списка будет в конце стека (p_first = Top)
будет:
nullptr <- 6 <- 3 <- 7 <- 1 <- p_first     - элементы + указатели
при удалении мы должны лишь удалить p_first и для этого есть функция Pop ниже
*/
template <class T>
class T_stack_list
{
private:
	T_node<T>* p_first;
	void copy_nodes(const T_stack_list<T>& other);
public:
	T_stack_list();
	T_stack_list(const T_stack_list<T>& other);
	~T_stack_list();
	T_stack_list<T>& operator=(const T_stack_list<T>& other);
	bool is_empty() const;
	bool is_not_empty() const;
	bool operator==(const T_stack_list<T>& other) const;
	bool operator!=(const T_stack_list<T>& other) const;
	void push(T value);
	T pop();
	T top() const;
	void clear();
	friend std::ostream& operator<<(std::ostream& out, const T_stack_list<T>& s) {
		T_node<T>* node = s.p_first;
		while (node != nullptr) {
			out << node->value << ' ';
			node = node->p_next;
		}
		return out;
	}
};

template <class T>
T_stack_list<T>::T_stack_list() : p_first(nullptr) {} // стек не зависит от размеров массива, ибо массива нет, и стек должен быть

template <class T>
T_stack_list<T>::T_stack_list(const T_stack_list& other) {
	p_first = nullptr; // на всякий: если копировать надо пустой
	copy_nodes(other);
}

template <class T>
T_stack_list<T>::~T_stack_list() {
	clear();
}

template <class T>
T_stack_list<T>& T_stack_list<T>::operator=(const T_stack_list<T>& other) {
	if (this == &other) return *this;
	clear();
	copy_nodes(other);
}

template <class T>
bool T_stack_list<T>::is_empty() const {
	return p_first == nullptr;
}

template <class T>
bool T_stack_list<T>::is_not_empty() const {
	return p_first != nullptr;
}

template <class T>
bool T_stack_list<T>::operator==(const T_stack_list<T>& other) const {
	T_node<T>* node = p_first;
	T_node<T>* other_node = other.p_first;
	while (node != nullptr && other_node != nullptr) {
		if (node->value != other_node->value) return false;
		node = node->p_next;
		other_node = other_node->p_next;
	}
	if (node != nullptr || other_node != nullptr) return false;
	return true;
}

template <class T>
bool T_stack_list<T>::operator!=(const T_stack_list<T>& other) const {
	return !operator==(other);
}

template <class T>
void T_stack_list<T>::push(T _value) { // добавление в начало списка и в конец стека
	T_node<T>* new_node = new T_node<T>(); // создаем новый модуль
	new_node->value = _value; // даем нужное значение
	new_node->p_next = p_first; // следущим будет тот, кто после первого
	p_first = new_node; // новый становится первым
}

template <class T>
T T_stack_list<T>::pop() { // смотрим верхний элемент в стеке, первый в списке
	if (p_first == nullptr) throw ("Can't pop");
	T_node<T>* del_node = p_first;  // создали звено, которое потом удалим
	T val = del_node->value; // сохранили то,что в конце возвратим
	p_first = del_node->p_next; // первый элемент теперь второй
	delete del_node; // удаляем первый
	return val; // возвращаем сохраненное значение бывшего первенца
}

template <class T>
T T_stack_list<T>::top() const {
	if (p_first == nullptr) throw ("Can't get top");
	return p_first->value;
}

template <class T>
void T_stack_list<T>::clear() {
	T_node<T>* node;
	while (p_first != nullptr) {
		node = p_first;
		p_first = p_first->p_next;
		delete node;
	}
}

template <class T>
void T_stack_list<T>::copy_nodes(const T_stack_list<T>& other) {
	if (other.is_not_empty()) {
		T_node<T>* new_node; 
		T_node<T>* this_node;
		T_node<T>* other_node = other.p_first;
		new_node = new T_node<T>; // делаем первый модуль
		new_node->value = other.p_first->value; 
		new_node->p_next = nullptr;
		p_first = new_node; // присваиваем новый модуль, скопированнный с other списка this списку
		this_node = p_first;
		other_node = other_node->p_next; // скопировали 1 раз - сдвинули
		while (other_node != nullptr) { // для остальных модулей
			new_node = new T_node<T>; // делаем новый модуль
			new_node->value = other_node->value;
			new_node->p_next = nullptr;
			this_node->p_next = new_node; // в отличие от того, что над whilом тут не меняется pfirst, а простраивается список далее(строЕМый список указывает на новый, уже построенный, модуль)
			this_node = new_node; // привязываем модуль
			other_node = other_node->p_next; // далее делаем сдвиг
		}
	}
}