#include <iostream>
#include <string>
#include <vector>
#include <list>
#include<algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
using namespace std;
#pragma once
class TMonom
{
private:
	double coef;
	int degX, degY, degZ;
public:
	TMonom() {
		coef =1;
		degX = degY = degZ = 1;
	}
	TMonom(double _coef, int _degX, int _degY, int _degZ) {
		coef = _coef;
		degX = _degX;
		degY = _degY;
		degZ = _degZ;

	}
	void SetCoef(int cval) { coef = cval; }
	int GetCoef(void) { return coef; }
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
	string ToString() {
		TMonom r(*this);
		return to_string(abs(r.GetCoef())) +
			"x^" + to_string(r.GetDegree()[0]) +
			"y^" + to_string(r.GetDegree()[1]) +
			"z^" + to_string(r.GetDegree()[2]) + " ";
	}
};

int main()
{
	/*TMonom t(2, 1, 1, 1);
	TMonom t2(7, 5, 1, 1);
	string res;*/
	std::list<TMonom>list,list2;/*
	if (t2.compare(t) == 1) { TMonom t3 = t + t2;  cout << t3.ToString();
	}
	else { TMonom t3 = t; cout << t3.ToString(); }
		//res.append("54");
	
	
	/*res += to_string(t.GetCoef()) +
		"x^" +to_string(t.GetDegree()[0]) +
		"y^" + to_string(t.GetDegree()[1]) +
		"z^" + to_string(t.GetDegree()[2]);
	cout << res;*/
	/*std::list<int>list = {3};
	list.pop_front();
	cout << list.size();*/
	TMonom t(4,3,2,1);
	TMonom t2(7, 5, 1, 1);
	list.push_back(t);
	list.push_back(t2);
	for (TMonom var : list) {
		for (TMonom var2 : list) {
			TMonom var3 = var * var2;
			list2.push_back(var3);
		}
	}
	for (TMonom var : list2) {
		cout << var.ToString()<<endl;
	}
	//cout << t.ToString();
}

