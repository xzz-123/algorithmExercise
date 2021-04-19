#pragma once
#include <unordered_map>
#include <vector>
using namespace std;
//自定义的双向链表结点
class DLinkedNode {
public:
	int key, val;
	DLinkedNode* pre, *next;
	DLinkedNode() :key(0), val(0), pre(nullptr), next(nullptr) {}
	DLinkedNode(int _key, int _value) :key(_key), val(_value), pre(nullptr), next(nullptr) {}
};
//least recent used
//来一个新的put，看是否已存在，已经存在就移动到双向链表头，不存在就新建一个结点加在表头，如果size超过了capacity，就把表尾的删掉
//因为要频繁地对头尾结点操作，所以用双向链表
class LRUCache {
public:
	//根据key找结点
	unordered_map<int, DLinkedNode*>m;
	int m_capacity;
	int m_size;
	//双向链表头尾结点
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
