#pragma once
// ����� ������
#include<iostream>
using namespace std;

template<class T> // ��������� ��� ������� ����� � �������
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

//�������� ����� ������� � ����� ������
void push_back(TNode* first_node, int _value) { // ������� �������� � �����������, ������� ������ �� ����������, �� ����������� �������� ����������)
	TNode* node = first_node; //�������� ��� ��������� (������� � ����� ����� ������� node->p_next = new_node; � ��� ���������� ��� ������)
	while (node->p_next != nullptr) { //��������� �� ��������� �� ����� (node->p_next, � �� ������ node, ��� � ���������� ������ ��� �������� �������� � ��������� ���������: � ��������� ������� � �������)
		node = node->p_next;
	}
	TNode* new_node = new TNode; //������� ����� ������ ������ ����� ���������, ���� ����������� ����� ������ �� �������
	if (new_node == nullptr) throw("Memory allocation error");
	new_node->value = _value;
	new_node->p_next = nullptr; //��������� � 0
	node->p_next = new_node; //����� ������ - ���������� ������� ������� � ������ (node - �� �����, � ���������, ������, ��� ������ �������� ����������)
}
bool del_one_node_by_value(TNode* first_node, int _val) { // ��������� �� ��������� ������ � ������ ������ ���������� ����� ��������
	TNode* node = first_node; // ������� ���������
	TNode* prev = first_node; // ���������� ���������
	while (node->value != _val || node->p_next != nullptr) {
		prev = node; // �������� �� ����������
		node = node->p_next; // ����� �� ��������� �� ������ �������
	}
	if (node->p_next != nullptr) { //���� ������ ������, �� true - ������ ����
		prev->p_next = node->p_next; // �������� ��������� � ����������� �� ��������� ����� ����������
		delete node;
		return true;
	}
	return false; // ���� ������ � ����� ��������� �� ������, �� false - ��� ������ �������� ����
}