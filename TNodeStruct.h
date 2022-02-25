#pragma once
// чисто списки
#include<iostream>
using namespace std;

template<class T> // структура для классов стеки и очереди
struct T_node {
	T value;
	T_node* p_next;
};

struct TNode {
	int value;
	TNode* p_next;
};
int count_nodes(TNode* first_node) {
	TNode* node = first_node;
	int result = 0;
	while (node != nullptr) {
		node = node->p_next;
		result++;
	}
	return result;
}

//Добавить новый элемент в конец списка
void push_back(TNode* first_node, int _value) { // функция работает с указателями, поэтому ничего не возвращает, но проделанные операции сохранятся)
	TNode* node = first_node; //передали сам указатель (поэтому в конце можно сделать node->p_next = new_node; и все сохранится при выходе)
	while (node->p_next != nullptr) { //пробегаем по элементам до конца (node->p_next, а не просто node, как в предыдущем потому что операции проводим с последним элементом: в последней строчке и изменим)
		node = node->p_next;
	}
	TNode* new_node = new TNode; //создаем новый модуль списка через указатель, чтоб сохранилось после выхода из функции
	if (new_node == nullptr) throw("Memory allocation error");
	new_node->value = _value;
	new_node->p_next = nullptr; //указываем в 0
	node->p_next = new_node; //самое важное - прицепляем готовый элемент к списку (node - не копия, а указатель, значит, при выходе привязка сохранится)
}
bool del_one_node_by_value(TNode* first_node, int _val) { // удаляется НЕ последний модуль и только первое упоминание этого значения
	TNode* node = first_node; // текущий указатель
	TNode* prev = first_node; // предыдущий указатель
	while (node->value != _val || node->p_next != nullptr) {
		prev = node; // остается на предыдущем
		node = node->p_next; // дошли до указателя на нужный элемент
	}
	if (node->p_next != nullptr) { //если модуль найден, то true - модуль есть
		prev->p_next = node->p_next; // заменили указатель у предыдущего на следующий после удаляемого
		delete node;
		return true;
	}
	return false; // если модуль с таким значением не найден, то false - нет такого элемента типо
}