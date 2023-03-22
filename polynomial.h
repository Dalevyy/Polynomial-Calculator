#include <iostream>
using namespace std;

class polynomial
{

	struct node
	{
		int coefficient;
		node * link;
	};

public:
	polynomial();
	polynomial(const polynomial&);
	polynomial(int*, int);
	polynomial(int);
	~polynomial();

	polynomial operator*(const polynomial&) const;
	polynomial operator*(int) const;
	polynomial operator+(const polynomial&) const;
	polynomial operator+(int) const;
	const polynomial& operator=(const polynomial&);
	const polynomial& operator=(int);
	polynomial operator-() const;
	polynomial operator-(const polynomial&) const;
	polynomial operator-(int) const;

	friend ostream& operator<<(ostream& outfile, const polynomial&);
	friend polynomial operator+(int, const polynomial&);
	friend polynomial operator*(int, const polynomial&);
	friend polynomial operator-(int, const polynomial&);
private:
	node * head;
	int degree;
};