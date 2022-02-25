#pragma once
#include"../TNodeStruct.h"

template <class T>
class T_queue_list {
	T_node<T>* p_first, * p_last; //первый в списке - хвост очереди    новый элемент в хвосте очереди    извлечение из головы   добавляем в начало списка, вынимаем из конца
	void copy_nodes(const T_queue_list<T>& other) {
		if (other.p_first->p_next != nullptr) {
			T_node<T>* this_node;
			T_node<T>* other_node = other.p_first->p_next;
			T_node<T>* new_node = new T_node<T>;
			new_node->value = other.p_first->value;
			new_node->p_next = nullptr;
			p_first = new_node;
			this_node = p_first;
			while (other_node != nullptr) {
				new_node = new T_node<T>;
				new_node->value = other_node->value;
				new_node->p_next = nullptr;
				this_node->p_next = new_node;
				this_node = new_node;
				other_node = other_node->p_next;
			}
			p_last = this_node;
		}
	}
public:
	T_queue_list() {
		p_first = p_last = nullptr;
	}
	T_queue_list(T_queue_list<T>& other) {
		p_first = p_last = nullptr;
		copy_nodes(other);
	}
	~T_queue_list() {
		clear();
	}
	void clear() {
		T_node<T>* del_node;
		while (p_first != nullptr) {
			del_node = p_first;
			p_first = p_first->p_next;
			delete del_node;
		}
		p_last = nullptr;
	}
	void push(T _value) { //тут работа с p_last
		T_node<T>* new_node = new T_node<T>; // создаем модуль
		new_node->value = _value;
		new_node->p_next = nullptr; // он последний
		if (p_last != nullptr) // если очередь не пуста
			p_last->p_next = new_node; // просто припаиваем новый модуль как последний
		else  // если же очередь пустая, то первый-новый модуль в ней просто становится последним
			p_first = new_node; // создали 1, считай элемент - он первый и последний одновременно
		p_last = new_node; // зациклили
	}
	T pop() { // работа с p_first
		if (p_first == nullptr) throw("Nothing to pop");
		T value = p_first->value; // сохранили значение
		T_node<T>* del_node = p_first;
		p_first = p_first->p_next;
		if (p_first == nullptr) p_last = nullptr; // если удалился первый элемент, то последний не должен существовать
		delete del_node;
		return value;
	}
	T get_first() {
		if (p_first == nullptr) throw("Element doesn't exist");
		return p_first->value;
	}
	T get_last() {
		if (p_last == nullptr) throw("Element doesn't exist");
		return p_last->value;
	}
	int get_size() {
		int size = 0;
		T_node<T>* node = p_first;
		while (node != p_last) size++;
		return size;
	}
	friend ostream& operator<<(ostream& out, const T_queue_list& other)
	{
		T_node<T>* node = other.p_first;
		while (node != nullptr) {
			out << node->value << ' ';
			node = node->p_next;
		}
		return out;
	}
	T_queue_list<T>& operator=(const T_queue_list<T>& other) {
		if (this == &other)
			return *this;
		clear();
		copy_nodes(other);
	}

	bool is_empty() {
		return p_first == nullptr;
	}
	bool is_not_empty() {
		return p_first != nullptr;
	}

	bool operator==(const T_queue_list<T>& other) {
		T_node<T>* this_node = p_first;
		T_node<T>* other_node = other.p_first;
		while (this_node != nullptr && other_node != nullptr) {
			if (this_node->value != other_node->value) return false;
			this_node = this_node->p_next;
			other_node = other_node->p_next;
		}
		if (this_node != nullptr || other_node != nullptr) return false;
		return true;
	}
	bool operator!=(const T_queue_list<T>& other) {
		return !operator==(other);
	}
};