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
	struct Table {
		Key key;
		Value value;
	};
	struct Node
	{
		Table data;
		Node* left;
		Node* right;
		Node* parent;
		Node(Key key, Value value) {
			left = nullptr;
			right = nullptr;
			data.key = key;
			data.value = value; }
		Node(Node* l, Node* r,Key key, Value value) {
			left = l;
			right = r;
			data.key = key;
			data.value = value;
		}
	};
	Node* root;
	SearchTreeTable() {root = new Node(2,8);}	
	SearchTreeTable(int key, int value) { root = new Node(key, value); }
	SearchTreeTable(SearchTreeTable p1,SearchTreeTable p2, int key, int value) {root = new Node(p1.root,p2.root,key,value);}
	string toString() {
		string res; 
		res += "(" + std::to_string(root->data.key) + ", " + std::to_string(root->data.value) + ")";
		return res;
	}
	void print(Node* node) {
		if (node == nullptr) return;
		print(node->left); 
		cout << "(" << node->data.key << ", " << node->data.value << ")" << endl;
		print(node->right);
	}
	Node* findNode(Key key, Node* node) {
		if (node == nullptr) {
			return nullptr;
		}

		if (key < node->data.key) {
			return findNode(key, node->left);
		}
		else if (key > node->data.key) {
			return findNode(key, node->right);
		}
		else {
			return node; // Возвращаем узел, если ключ совпадает
		}
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
		if ((this->Find(_key) == nullptr) || (root == nullptr)) {
			// Узел с таким ключом не существует, удаление не требуется
			return 0;
		}
		else {
			root=deleteNode(root, _key);
			return 1; // Успешное удаление узла
		}
	}
	Node* deleteNode(Node* currentNode, Key _key) {
		if (currentNode == nullptr) return nullptr;

		if (_key < currentNode->data.key) {
			currentNode->left = deleteNode(currentNode->left, _key);
		}
		else if (_key > currentNode->data.key) {
			currentNode->right = deleteNode(currentNode->right, _key);
		}
		else {
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
			else {
				Node* temp = maxValueNode(currentNode->left);
				currentNode->data = temp->data;
				currentNode->left = deleteNode(currentNode->left, temp->data.key);
			}
		}

		return currentNode;
	}

	Node* maxValueNode(Node* node) {
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
	Value* GetValuePtr(void) const {
		return this->GetValuePtr(); 
	}
	 
};
template<class Key, class Value>
class AVLTreeTable : public SearchTreeTable<Key, Value> {
private:
	int balance;
public:
	/*Value* Find(Key key) {
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
	}*/
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
