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
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz == 0 || sz > MAX_VECTOR_SIZE)
			throw out_of_range("Vector size should be greater than zero");

		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		if (arr == nullptr) throw "TDynamicVector ctor requires non-nullptr arg";
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		swap(*this, v);
	}
	~TDynamicVector()
	{
		delete[]pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v) return *this;
		if (sz != v.sz) {
			T* p = new T[v.sz];
			delete[]pMem;
			sz = v.sz;
			pMem = p;
		}

		std::copy(v.pMem, v.pMem + sz, pMem);
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		if (ind < 0 || ind >= sz) throw invalid_argument("error");
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind < 0 || ind >= sz) throw invalid_argument("error");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind < 0 || ind >= sz) throw invalid_argument("error");
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return false;
		for (size_t i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i])
				return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + val;
		}
		return tmp;
	}
	TDynamicVector operator-(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - val;
		}
		return tmp;
	}
	TDynamicVector operator*(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] * val;
		}
		return tmp;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz) throw "Length not equal";

		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + v.pMem[i];
		}
		return tmp;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz) throw "Length not equal";
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - v.pMem[i];
		}
		return tmp;
	}
	T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
	{
		if (sz != v.sz) throw "Length not equal";
		T tmp = T();
		for (int i = 0; i < sz; i++) {
			tmp += pMem[i] * v.pMem[i];
		}

		return tmp;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};
class TMonom
{
private:
	double coef;
	int degX, degY, degZ;
public:
	TMonom() {
		coef = 1;
		degX = degY = degZ = 1;
	}
	TMonom(double _coef, int _degX, int _degY, int _degZ) {
		coef = _coef;
		degX = _degX;
		degY = _degY;
		degZ = _degZ;

	}
	void SetCoef(double cval) { coef = cval; }
	double GetCoef(void) { return coef; }
	int GetDegreeX(void) { return degX; }
	int GetDegreeY(void) { return degY; }
	int GetDegreeZ(void) { return degZ; }
	bool compare(const TMonom& other) {
		if ((degX != other.degX) ||
			(degY != other.degY) ||
			(degZ != other.degZ))
			return false;
		return true;
	}
	int* GetDegree(void) {
		int* d = new int[3];
		d[0] = degX;
		d[1] = degY;
		d[2] = degZ;
		return d;
	}
	void SetDegree(int xval, int yval, int zval) {
		degX = xval;
		degY = yval;
		degZ = zval;
	}
	bool operator==(const TMonom& other) {
		if ((coef == other.coef) &&
			(degX == other.degX) &&
			(degY == other.degY) &&
			(degZ == other.degZ))
			return false;
		return true;
	}
	void operator=(const TMonom& other) {
		coef = other.coef;
		degX = other.degX;
		degY = other.degY;
		degZ = other.degZ;
	}
	TMonom operator+(const TMonom& other) {
		TMonom t(*this);
		t.coef += other.coef;
		return t;
	}
	TMonom operator*(const TMonom& other) {
		TMonom t(*this);
		t.coef *= other.coef;
		t.degX += other.degX;
		t.degY += other.degY;
		t.degZ += other.degZ;
		return t;
	}
	bool operator!=(const TMonom& other) {
		if ((coef != other.coef) ||
			(degX != other.degX) ||
			(degY != other.degY) ||
			(degZ != other.degZ))
			return true;
		return false;
	}
	int operator [] (const TMonom& t) {}
	bool operator>(const TMonom& other) {
		if ((coef > other.coef) &&
			(degX > other.degX) &&
			(degY > other.degY) &&
			(degZ > other.degZ))
			return true;
		return false;
	}
	bool operator<(const TMonom& other) {
		if ((coef > other.coef) &&
			(degX > other.degX) &&
			(degY > other.degY) &&
			(degZ > other.degZ))
			return false;
		return true;
	}
};
class TPolinom
{
	list<TMonom> list;
public:
	TPolinom();
	TPolinom(TMonom t);
	TPolinom(TPolinom& other);
	TPolinom(TDynamicVector<TMonom> vec);//
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other);
	TPolinom operator+(TPolinom& q);


	TPolinom AddMonom(TMonom newMonom); //
	TPolinom MultMonom(TMonom monom);
	TPolinom Div(int variable, int order);
	TPolinom Integral(int variable, int order);
	TPolinom AddPolinom(TPolinom& other);
	TPolinom operator*(double coef);
	TPolinom operator* (TPolinom& other);
	bool operator==(TPolinom& other);
	bool operator!=(TPolinom& other);
	string ToString(); //
};

TPolinom::TPolinom() //не проверял
{
	TMonom m(1, 2, 3, 4);
	list.push_back(m);
}
TPolinom::TPolinom(TMonom t) //не проверял
{
	list.push_back(t);
}

TPolinom::TPolinom(TPolinom& other)//работает
{
	list = other.list;
}

TPolinom::TPolinom(TDynamicVector<TMonom> vec)//работает
{
	for (int i = 0; i <= vec.size() - 1; i++)
	{
		TMonom d(vec[i].GetCoef(), vec[i].GetDegreeX(), vec[i].GetDegreeY(), vec[i].GetDegreeZ());
		list.push_back(d);
	}
}

TPolinom::TPolinom(string str)//не трогал
{
	/*size_t pos = 0;
	while (pos < str.length()) {
		double coef = 0.0;
		int degX = 0, degY = 0, degZ = 0;
		char var;
		if (isdigit(str[pos]) || str[pos] == '-' || str[pos] == '+') {
			size_t nextPos;
			coef = stod(str.substr(pos), &nextPos);
			pos += nextPos;
		}
		while (pos < str.length() && (str[pos] == 'x' || str[pos] == 'X' ||
			str[pos] == 'y' || str[pos] == 'Y' ||
			str[pos] == 'z' || str[pos] == 'Z')) {
			var = tolower(str[pos]);
			pos++;
			if (pos < str.length() && str[pos] == '^') {
				pos++;
				size_t nextPos;
				int deg = stoi(str.substr(pos), &nextPos);
				pos += nextPos;
				switch (var) {
				case 'x': degX = deg; break;
				case 'y': degY = deg; break;
				case 'z': degZ = deg; break;
				}
			}
			else {
				switch (var) {
				case 'x': degX = 1; break;
				case 'y': degY = 1; break;
				case 'z': degZ = 1; break;
				}
			}
		}
		this->AddMonom(TMonom(coef, degX, degY, degZ));
	}*/
}

TPolinom& TPolinom::operator=(TPolinom& other)//работает
{
	this->list = other.list;
	return *this;
}

TPolinom TPolinom::AddMonom(TMonom otherMon)//работает
{
	bool i = false;
	for (TMonom& var : this->list) {
		if (var.compare(otherMon) == true) {
			var = var + otherMon;
			i = true;
			break;
		}
	}
	if (i == false) list.push_back(otherMon);
	return *this;
}
TPolinom TPolinom::AddPolinom(TPolinom& other)//работает
{
	for (TMonom var : other.list) { this->AddMonom(var); }

	return *this;
}

TPolinom TPolinom::MultMonom(TMonom monom)// работает
{
	for (TMonom& var : list) { var* monom; }
	return *this;
}

TPolinom TPolinom::operator+(TPolinom& other)//работает
{
	/*for (TMonom var : other.list) { this->AddMonom(var); }
	return *this;*/
	TPolinom res(*this);
	for (TMonom& var : other.list) { res.AddMonom(var); }

	return res;
}
TPolinom TPolinom::Div(int variable, int order) {
	TPolinom res(*this);
	for (int i = 0; i < order; i++) {
		switch (variable) {
		case 1:
			for (TMonom& var : res.list) {
				var.SetCoef(var.GetCoef() * var.GetDegreeX());
				var.SetDegree(var.GetDegreeX() - 1, var.GetDegreeY(), var.GetDegreeZ());

			} break;
		case 2: for (TMonom& var : res.list) {
			var.SetCoef(var.GetCoef() * var.GetDegreeY());
			var.SetDegree(var.GetDegreeX(), var.GetDegreeY() - 1, var.GetDegreeZ());

		} break;
		case 3: for (TMonom& var : res.list) {
			var.SetCoef(var.GetCoef() * var.GetDegreeZ());
			var.SetDegree(var.GetDegreeX(), var.GetDegreeY(), var.GetDegreeZ() - 1);

		} break;
		default: break;
		}
	}
	return res;
}
TPolinom TPolinom::Integral(int variable, int order) {
	TPolinom res(*this);
	for (int i = 0; i < order; i++) {
		switch (variable) {
		case 1:
			for (TMonom& var : res.list) {
				var.SetDegree(var.GetDegreeX() + 1, var.GetDegreeY(), var.GetDegreeZ());
				var.SetCoef(var.GetCoef() / var.GetDegreeX());
			} break;
		case 2: for (TMonom& var : res.list) {
			var.SetDegree(var.GetDegreeX(), var.GetDegreeY() + 1, var.GetDegreeZ());
			var.SetCoef(var.GetCoef() / var.GetDegreeY());
		} break;
		case 3: for (TMonom& var : res.list) {
			var.SetDegree(var.GetDegreeX(), var.GetDegreeY(), var.GetDegreeZ() + 1);
			var.SetCoef(var.GetCoef() / var.GetDegreeZ());
		} break;
		default: break;
		}
	}
	return res;
}


TPolinom TPolinom::operator*(double _coef)//работает
{
	TPolinom res(*this);
	for (TMonom& var : res.list) {
		var.SetCoef(var.GetCoef() * _coef);

	}
	return res;
}

TPolinom TPolinom::operator*(TPolinom& other)//пока не работает
{
	TPolinom res(*this);
	res.list.clear();
	for (TMonom var : list) {
		for (TMonom var2 : other.list) {
			TMonom var3 = var * var2;
			res.AddMonom(var3);
		}
	}

	return res;
}

bool TPolinom::operator==(TPolinom& other)//не работает
{
	TPolinom res(*this);
	bool k = false;
	if (list.size() != other.list.size()) return false;
	for (TMonom& var : res.list) {
		for (TMonom var2 : other.list) {
			if (var == var2) { res.list.pop_front(); k = true; break; }
		}
		if (k == false) { return false; }
	}
	if (res.list.size() == 0) return true;
	else return false;
}

bool TPolinom::operator!=(TPolinom& other)//обратно ==
{

	return !(*this == other);
}

string TPolinom::ToString()//работает
{
	string res;
	for (TMonom var : list)
	{
		var.GetCoef() < 0 ? res += "-" : res += "+";
		res += to_string(abs(var.GetCoef())) +
			"x^" + to_string(var.GetDegree()[0]) +
			"y^" + to_string(var.GetDegree()[1]) +
			"z^" + to_string(var.GetDegree()[2]) + " ";
	}
	cout << endl;

	return res;
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
		int nomer;
		Table data;
		Node* left;
		Node* right;
		Node* parent;
		Node(Key key, Value value) {
			left = nullptr;
			right = nullptr;
			data.key = key;
			data.value = value;
			number++; this->nomer = number;
			this->parent = nullptr;
		}
		Node(Node* l, Node* r, Key key, Value value) {
			left = l;    right = r;
			data.key = key;
			data.value = value;
			l->parent = r->parent = this;
			number++;   this->nomer = number;
		}
		void operator=(const Node& other) {
			parent = other.parent;
			left = other.left;
			right = other.right;
			data.key = other.data.key;
			data.value = other.data.value;
			nomer = other.nomer;
		}
	};
	Node* root;
	static int number;
	SearchTreeTable() { TPolinom p; root = new Node(2, p); root->parent = nullptr; }
	SearchTreeTable(int key, TPolinom value) { root = new Node(key, value); }
	SearchTreeTable(SearchTreeTable p1, SearchTreeTable p2, int key, TPolinom value) { root = new Node(p1.root, p2.root, key, value); root->parent = nullptr; }
	string toString() {
		string res;
		res += "(" + std::to_string(root->data.key) + ", " + std::to_string(root->data.value) + ")";
		return res;
	}
	void print(Node* node) {
		if (node == nullptr) return;
		print(node->left);
		//cout << "(Left potomok: ";
		if (node->parent == nullptr)
			cout << "Parent: null, ";
		else
			cout << "Parent: " << node->parent->data.key << ", ";
		cout << "Key:" << node->data.key << ", Value: " << node->data.value.ToString() << ", Left potomok: ";
		if (node->left == nullptr)
			cout << "null, ";
		else { cout << node->left->data.key << " Right Potomok: "; }
		if (node->right == nullptr)
			cout << "null " << ")" << endl;
		else { cout << node->right->data.key << " )" << endl; }
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
				return 1; // Успешная вставка нового узла
			}
			Node* current = root;
			Node* parent = nullptr;
			// Находим место для вставки новой вершины
			while (current != nullptr) {
				parent = current;
				if (_key < current->data.key) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
			// Вставляем новую вершину и устанавливаем ссылку на родителя
			if (_key < parent->data.key) {
				parent->left = new_node;
			}
			else {
				parent->right = new_node;
			}
			new_node->parent = parent;
			return 1; // Успешная вставка нового узла
		}
	}
	int Delete(Key _key) {
		if ((this->Find(_key) == nullptr) || (root == nullptr)) {
			// Узел с таким ключом не существует, удаление не требуется
			return 0;
		}
		else {
			root = deleteNode(root, _key);
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
			// случай для 0 потомков
			if ((currentNode->left == nullptr) && (currentNode->right == nullptr)) {
				if ((currentNode->parent)->left == currentNode) { (currentNode->parent)->left = nullptr; }
				else { (currentNode->parent)->right = nullptr; }
				delete currentNode;
				return nullptr;
			}
			else if (currentNode->left != nullptr && currentNode->right != nullptr) {
				Node* temp = maxValueNode(currentNode->left);
				currentNode->data = temp->data;
				deleteNode(currentNode->left, temp->data.key);
				return currentNode;
			}
			else {
				Node* temp = (currentNode->left != nullptr) ? currentNode->left : currentNode->right;
				if (currentNode->parent == nullptr) {
					currentNode = temp;
					delete temp;
					return currentNode;
				}
				else {
					if (currentNode == currentNode->parent->left) {
						currentNode->parent->left = temp;
					}
					else {
						currentNode->parent->right = temp;
					}
					temp->parent = currentNode->parent;
					delete currentNode;
					return temp;
				}
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
int SearchTreeTable<Key, Value>::number = 0;
template<class Key, class Value>
class AVLTreeTable : public SearchTreeTable<Key, Value> {
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
		int balance;
		Node(Key key, Value value) {
			left = nullptr;
			right = nullptr;
			data.key = key;
			data.value = value;
			this->parent = nullptr;
			balance = 0;
		}
		Node(Node* l, Node* r, Key key, Value value) {
			left = l;
			right = r;
			data.key = key;
			data.value = value;
			l->parent = r->parent = this;
			balance = this.update_balance();
		}

		void update_balance2() {
			Node* n = this->parent;
			if (n == nullptr) {
				if (n->left == this) { this->balance--; }
				else { this->balance++; }
				return;
			}
			if (n->left == this) { this->balance--; }
			else { this->balance++; }
			this->update_balance2();
		}
		Node* update_balance() {
			if (this != nullptr) {
				this->balance = get_height(this->right) - get_height(this->left);
				if ((this->balance == 2) || (this->balance == -2)) { this->balancir(); }
				if (this->parent != nullptr) { this->parent->update_balance(); }
			}
			else return this;
		}
		int get_height(Node* node) {
			if (node == nullptr) return -1;
			return 1 + max(get_height(node->left), get_height(node->right));
		}
		Node* balancir() {
			if (this->balance == -2)
			{
				if (this->left->balance < 0)
				{
					cout << "1" << endl; this->singleUpLeft();  return this;
				}
				if (this->left->balance > 0)
				{
					cout << "2" << endl; this->doubleUpLeft();  return this;
				}
			}
			if (this->balance == 2) {
				if (this->right->balance < 0)
				{
					cout << "3" << endl; this->singleUpRight(); return this;
				}
				if (this->right->balance > 0)
				{
					cout << "4" << endl; this->doubleUpRight(); return this;
				}
			}
			return this;
		}
		Node* singleUpLeft() {
			Node* B = this->left;

			if (this->parent != nullptr) {
				if (this == ((this->parent)->left)) {
					B->parent = this->parent;
					(B->parent)->left = B;
				}
				else {
					(B->parent)->right = B;
					B->parent = this->parent;
				}
			}
			else { B->parent = this->parent; }

			this->left = B->right;
			B->right = this;
			this->parent = B;
			this->update_balance();
			B->update_balance();
			return B;
		}
		Node* singleUpRight() {
			Node* B = this->right;

			if (this->parent != nullptr) {
				if (this == ((this->parent)->right)) {
					B->parent = this->parent;
					(B->parent)->left = B;
				}
				else {
					(B->parent)->left = B;
					B->parent = this->parent;
				}
			}
			else { B->parent = this->parent; }

			this->right = B->left;
			B->left = this;
			this->parent = B;
			this->update_balance();
			B->update_balance();
			return B;
		}
		Node* doubleUpLeft() {
			Node* B = this->left;
			Node* C = B->right;

			if (this->parent != nullptr) {
				if (this == ((this->parent)->left)) {
					C->parent = this->parent;
					(C->parent)->left = C;
				}
				else {
					(C->parent)->right = C;
					C->parent = this->parent;
				}
			}
			else { C->parent = this->parent; }

			B->right = C->left;
			C->left = B;
			this->left = C->right;
			C->right = this;
			B->parent = C;
			this->parent = C;
			this->update_balance();
			B->update_balance();
			C->update_balance();
			return C;
		}
		Node* doubleUpRight() {
			Node* B = this->right;
			Node* C = B->left;

			if (this->parent != nullptr) {
				if (this == ((this->parent)->left)) {
					C->parent = this->parent;
					(C->parent)->left = C;
				}
				else {
					(C->parent)->right = C;
					C->parent = this->parent;
				}
			}
			else { C->parent = this->parent; }

			B->left = C->right;
			C->right = B;
			this->right = C->left;
			C->left = this;
			B->parent = C;
			this->parent = C;
			this->update_balance();
			B->update_balance();
			C->update_balance();
			return C;
		}
		void print() {
			if (this == nullptr) return;
			this->left->print();
			if (this->parent == nullptr)
				cout << "Parent: null, ";
			else
				cout << "Parent: " << this->parent->data.key << ", ";
			cout << "Key:" << this->data.key  << ", Value: " << this->data.value.ToString() << ", Balance: " << this->balance << ", Left potomok: ";
			if (this->left == nullptr)
				cout << "null " << ", ";
			else { cout << this->left->data.key << " ,"; }
			if (this->right == nullptr)
				cout << "Right potomok: null " << " )" << endl;
			else { cout << "Right potomok: " << this->right->data.key << " )" << endl; }
			this->right->print();
		}
	};
	Node* root;
public:
	AVLTreeTable() {
		TPolinom p; root = new Node(2, p);
		root->balance = 0;
	}
	AVLTreeTable(int key, int value) {
		root = new Node(key, value);
		root->balance = 0;
	}
	AVLTreeTable(AVLTreeTable p1, AVLTreeTable p2, int key, int value) {
		root = new Node(p1.root, p2.root, key, value);
		root->balance = p2.root->balance - p1.root->balance;
	}
	string toString() {
		string res;
		res += "(" + std::to_string(root->data.key) + ", " + std::to_string(root->data.value) + ", " + std::to_string(root->balance) + ")";
		return res;
	}
	Value* Find(Key key)
	{
		Node* node = findNode(key, root);
		if (node == nullptr) { return nullptr; }
		return &node->data.value;
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
				return 1; // Успешная вставка нового узла
			}
			Node* current = root;
			Node* parent = nullptr;
			// Находим место для вставки новой вершины
			while (current != nullptr) {
				parent = current;
				if (_key < current->data.key) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
			// Вставляем новую вершину и устанавливаем ссылку на родителя
			if (_key < parent->data.key) {
				parent->left = new_node;
			}
			else {
				parent->right = new_node;
			}
			// Дополнительная проверка на листовую вершину
			if (parent->left == nullptr && parent->right == nullptr) {
				parent->update_balance(); // Обновляем баланс и структуру дерева
			}
			new_node->parent = parent;
			if (root->parent != nullptr) {
				root = root->parent; // Обновление корня дерева
			}
			new_node->update_balance();
			if (root->parent != nullptr) {
				root = root->parent; // Обновление корня дерева
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
			this->root = deleteNode(root, _key);
			this->root->update_balance();
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
			// случай для 0 потомков
			if ((currentNode->left == nullptr) && (currentNode->right == nullptr)) {
				if ((currentNode->parent)->left == currentNode) { (currentNode->parent)->left = nullptr; }
				else { (currentNode->parent)->right = nullptr; }
				delete currentNode;
				return nullptr;
			}
			else if (currentNode->left != nullptr && currentNode->right != nullptr) {
				Node* temp = maxValueNode(currentNode->left);
				currentNode->data = temp->data;
				deleteNode(currentNode->left, temp->data.key);
				return currentNode;
			}
			else {
				Node* temp = (currentNode->left != nullptr) ? currentNode->left : currentNode->right;
				if (currentNode->parent == nullptr) {
					currentNode = temp;
					delete temp;
					return currentNode;
				}
				else {
					if (currentNode == currentNode->parent->left) {
						currentNode->parent->left = temp;
					}
					else {
						currentNode->parent->right = temp;
					}
					temp->parent = currentNode->parent;
					delete currentNode;
					return temp;
				}
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



};
class MixTable {
private:
	SearchTreeTable <int, TPolinom>t;
	AVLTreeTable <int,TPolinom>a;
public:
	void Add(int key, TPolinom p){
		a.Insert(key, p);
		t.Insert(key, p);
	}

	void Delete(int key) {
		a.Delete(key);
		t.Delete(key);
	}
	void print() {
		t.print(t.root);
		a.root->print();
	}
	void Find(int id, int key){
		switch (id) {
		case 1: t.Find(key); break;
		case 2: a.Find(key); break;
		default: break;
		}
	}


};
enum class Color { RED, BLACK };
template<class Key, class Value>
class RBTable : public SearchTreeTable<Key, Value> {
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
	return 0;
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
