#pragma once
using namespace std;

template<class Key, class Value>
class Table
{
protected:
	struct Row {
		Key key;
		Value value;
	};
	int size = 0;
	int maxsize = 10000;
public:
	virtual bool IsFull() const;
	bool IsEmpty() const;
	int GetSize() const;


	virtual Value* Find(Key _key) = 0;
	virtual int Insert(Key _key, Value _val) = 0;
	virtual int Delete(Key _key) = 0;

	virtual void Reset(void) = 0;
	virtual bool IsTabEnded(void) const = 0;
	virtual int GoNext(void) = 0;

	virtual Key GetKey(void) const = 0;
	virtual Value* GetValuePtr(void) const = 0;	//	(=1 first el, if called on last cell of table)				

	friend ostream& operator<<(ostream& os, Table& tab)
	{
		cout << "Table printing" << endl;
		if (!tab.IsEmpty()) {
			for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
			{
				os << " Key: " << tab.GetKey() << " Val: " << tab.GetValuePtr() << endl;
			}
			return os;
		}
		else {
			os << " Key: " << "NONE" << " Val: " << "NONE" << endl;
		}
	}
};

template<class Key, class Value>
bool Table<Key, Value>::IsFull() const
{
	return size == maxsize;
}
template<class Key, class Value>
bool Table<Key, Value>::IsEmpty() const
{
	return size == 0;
}
template<class Key, class Value>
int Table<Key, Value>::GetSize() const
{
	return size;
}
template<class Key, class Value>
class SearchTreeTable : public Table<Key, Value> {
public:
	struct TTableRec {
		Key key;
		Value value;
	};
	struct Node
	{
		TTableRec data;
		Node* left;
		Node* right;
		Node* parent;
	};
	Node* root;
	SearchTreeTable() { root->parent = nullptr;  root->data = { 2,  8 }; }
	SearchTreeTable(Node* p, int key, int value) { root = new Node(); root->parent = p; root->data.key = key; root->data.value = value; }
	void print(Node* p) {
		if (p == nullptr) return;
		print(p->left); 
		print(p->right);
	}
	Node* findNode(Key key, Node* node) {
		if (node == nullptr) { return nullptr; }
		if (key < node->data.key) { node = FindNode(key, node->left); }
		if (key >node->data.key) { node = FindNode(key, node->right); }
		return node;
	}
	Value* Find(Key key) {
		Node* node = findNode(key, root);
		if (node == nullptr) { return nullptr; }
		return &node->data.value;
	}
	int Insert(Key _key, Value _val) {
		if (this->Find(_key) != nullptr) {
			// Узел с таким ключом уже существует, вставка не требуется
			return 0;
		}
		else {
			// Создаем новый узел
			Node* new_node = new Node(_key, _val);
			if (root == nullptr) {
				root = new_node; // Если дерево пустое, новый узел становится корнем
			}
			else {
				Node* current = root;
				while (true) {
					if (_key < current->data.key) {
						if (current->left == nullptr) {
							current->left = new_node; // Вставляем новый узел влево
							break;
						}
						else {
							current = current->left;
						}
					}
					else if (_key > current->data.key) {
						if (current->right == nullptr) {
							current->right = new_node; // Вставляем новый узел вправо
							break;
						}
						else {
							current = current->right;
						}
					}
				}
			}
			return 1; // Успешная вставка нового узла
		}
	}
	int Delete(Key _key) {
		if (this->Find(_key) == nullptr) {
			// Узел с таким ключом не существует, удаление не требуется
			return 0;
		}
		else {
			deleteNode(root, _key);
			return 1; // Успешное удаление узла
		}
	}
	Node* deleteNode(Node* currentNode, Key _key) {
		if (_key < currentNode->data.key) {
			currentNode->left = deleteNode(currentNode->left, _key);
		}
		else if (_key > currentNode->data.key) {
			currentNode->right = deleteNode(currentNode->right, _key);
		}
		else {
			// Узел для удаления найден

			// Case 1: Узел без детей или с одним ребенком
			if (currentNode->left == nullptr) {
				Node* temp = currentNode->right;
				delete currentNode;
				return temp;
			}
			else if (currentNode->right == nullptr) {
				Node* temp = currentNode->left;
				delete currentNode;
				return temp;
			}

			// Case 2: Узел с двумя детьми
			Node* temp = minValueNode(currentNode->left);
			currentNode->data = temp->data;
			currentNode->right = deleteNode(currentNode->right, temp->data.key);
		}
		return currentNode;
	}
	Node* minValueNode(Node* node) {
		Node* current = node;
		while (current->right != nullptr) {
			current = current->right;
		}
		return current;
	}
	void Reset(void) {}
	bool IsTabEnded(void) const { return false; }
	int GoNext(void) { return 0; }
	Key GetKey(void) const { return this->GetKey(); }
	Value* GetValuePtr(void) const { this->GetValuePtr(); }
	 
	 
};
template<class Key, class Value>
class AWLTreeTable : public SearchTreeTable<Key, Value> {
private:
	byte balance;
public:
	Value* Find(Key key) {
		Node* node = findNode(key, root);
		if (node == nullptr) { return nullptr; }
		return &node->data.value;
	}
	int Delete(Key _key) {
		if (this->Find(_key) == nullptr) {
			// Узел с таким ключом не существует, удаление не требуется
			return 0;
		}
		else {
			deleteNode(root, _key);
			balancir();
			return 1; // Успешное удаление узла
		}
	}
	int Insert(Key _key, Value _val) {
		if (this->Find(_key) != nullptr) {
			// Узел с таким ключом уже существует, вставка не требуется
			return 0;
		}
		else {
			// Создаем новый узел
			Node* new_node = new Node(_key, _val);
			if (root == nullptr) {
				root = new_node; // Если дерево пустое, новый узел становится корнем
			}
			else {
				Node* current = root;
				while (true) {
					if (_key < current->data.key) {
						if (current->left == nullptr) {
							current->left = new_node; // Вставляем новый узел влево
							break;
						}
						else {
							current = current->left;
						}
					}
					else if (_key > current->data.key) {
						if (current->right == nullptr) {
							current->right = new_node; // Вставляем новый узел вправо
							break;
						}
						else {
							current = current->right;
						}
					}
				}
			}
			balancir();
			return 1; // Успешная вставка нового узла
		}
	}
	void balancir() {}

};
enum class Color { RED, BLACK };
template<class Key, class Value>
class RBTable: public SearchTreeTable<Key,Value> {
private:
	
	

	int height;
	Color color;
	RBTable* parent;
	RBTable* left;
	RBTable* right;
	public:
	// Унаследовано через Table
//	RBTable(){this.}
	Value* Find(Key _key) override;
	int Insert(Key _key, Value _val) override;
	int Delete(Key _key) override;
	void Reset(void) override;
	bool IsTabEnded(void) const override;
	int GoNext(void) override;
	Key GetKey(void) const override;
	Value* GetValuePtr(void) const override;

};
template<class Key, class Value>
Value* RBTable<Key, Value>::Find(Key _key)
{
	if (this->GetKey() < _key) { return left->Find(); }
	if (this->GetKey() > _key) { return right->Find(); }
	if (this->GetKey() == _key) { return this->GetValuePtr(); }
}
template<class Key, class Value>
int RBTable<Key, Value>::Insert(Key _key, Value _val)
{
	size++;
}
template<class Key, class Value>
int RBTable<Key, Value>::Delete(Key _key)
{
	size--;
}
template<class Key, class Value>
void RBTable<Key, Value>::Reset(void)
{
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}
template<class Key, class Value>
bool RBTable<Key, Value>::IsTabEnded(void) const
{
	return false;
}
template<class Key, class Value>
int RBTable<Key, Value>::GoNext(void)
{
	
}
template<class Key, class Value>
Key RBTable<Key, Value>::GetKey(void) const
{
	return this->key;
}
template<class Key, class Value>
Value* RBTable<Key, Value>::GetValuePtr(void) const
{
	return &this->value;
}
