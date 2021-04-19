#pragma once
#include <unordered_map>
#include <vector>
using namespace std;
//�Զ����˫��������
class DLinkedNode {
public:
	int key, val;
	DLinkedNode* pre, *next;
	DLinkedNode() :key(0), val(0), pre(nullptr), next(nullptr) {}
	DLinkedNode(int _key, int _value) :key(_key), val(_value), pre(nullptr), next(nullptr) {}
};
//least recent used
//��һ���µ�put�����Ƿ��Ѵ��ڣ��Ѿ����ھ��ƶ���˫������ͷ�������ھ��½�һ�������ڱ�ͷ�����size������capacity���Ͱѱ�β��ɾ��
//��ΪҪƵ���ض�ͷβ��������������˫������
class LRUCache {
public:
	//����key�ҽ��
	unordered_map<int, DLinkedNode*>m;
	int m_capacity;
	int m_size;
	//˫������ͷβ���
	DLinkedNode* head, *tail;
	LRUCache(int capacity) :m_capacity(capacity), m_size(0) {
		head = new DLinkedNode();
		tail = new DLinkedNode();
		head->next = tail;
		tail->pre = head;
	}

	int get(int key) {
		if (m.count(key) == 0)
			return -1;
		auto *node = m[key];
		moveToHead(node);
		return node->val;
	}

	void put(int key, int value) {
		if (m.count(key) == 0) {
			DLinkedNode* node = new DLinkedNode(key, value);
			addToHead(node);
			m[key] = node;
			++m_size;
			if (m_size > m_capacity) {
				removeTail();
				--m_size;
			}
		}
		else {
			auto *node = m[key];
			moveToHead(node);
			node->val = value;
		}
	}
	void moveToHead(DLinkedNode *node) {
		node->pre->next = node->next;
		node->next->pre = node->pre;
		addToHead(node);
	}

	void addToHead(DLinkedNode *node) {
		node->next = head->next;
		node->pre = head;
		head->next->pre = node;
		head->next = node;
	}

	void removeTail() {
		auto *node = tail->pre;
		m.erase(node->key);
		tail->pre = node->pre;
		tail->pre->next = tail;
		delete node;
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
