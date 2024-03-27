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
enum class Color { RED, BLACK };
template<class Key, class Value>
class RBTable: public Table<Key,Value> {
private:
	int height;
	Color color;
	RBTable* parent;
	RBTable* left;
	RBTable* right;
	public:
	// Унаследовано через Table
	RBTable(){this.}
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
	
}
template<class Key, class Value>
int RBTable<Key, Value>::Delete(Key _key)
{
	
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
	
}
template<class Key, class Value>
int RBTable<Key, Value>::GoNext(void)
{
	
}
template<class Key, class Value>
Key RBTable<Key, Value>::GetKey(void) const
{
	return this->GetKey();
}
template<class Key, class Value>
Value* RBTable<Key, Value>::GetValuePtr(void) const
{
	
}
