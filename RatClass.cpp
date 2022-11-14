#include <iostream>
using namespace std;

class Rat {
private:
	int n;                  // declaring private numerator variable
	int d;                  // declaring private denominator variable
public:
	// constructors

	// default constructor
	Rat() {
		n = 0;              // no paramater, so makes the numerator 0
		d = 1;              // no paramater, so must make the denominator 1 because it would be undefined with 0
	}

	// 2 paramater constructor 
	Rat(int i, int j) {
		n = i;                 // takes i for the numerator
		d = j;                 // takes j for the denominator 
	}

	// conversion constructor
	Rat(int i) {
		n = i;                // if the paramater is just one paramater
		d = 1;                // this constructor makes the numerator i and denominator is 1 (5 = 5/1)
	}

	// accessor functions (usually called get() and set())
	void setN(int i) {
		n = i;                       // numerator is equal to what is in the paramater
	}
	void setD(int i) {
		d = i;                       // denominator is equal to what is in the paramater
	}
	int getN() {
		return n;                    // to get numerator, simply return n
	}
	int getD() {
		return d;                    // to get denominator, simply return d
	}

	// arithmetic operators
	Rat operator+(Rat r) {       // teaches the compiler operator addition
		Rat t;                   // Rat t will have the sum of both rats
		t.n = n * r.d + d * r.n; // numerator of rat t = (numerator (left rat) * r.denominator) + (denominator * r.numerator)
		t.d = d * r.d;           // denominator of rat t = (denominator (left rat) * r.denominator)
		t.simplify();
		return t;                // return rat t which now has the sum
	}

	Rat operator-(Rat r) {       // teaches the compiler operator subtraction
		Rat t;                   // Rat t will have the difference of both rats
		t.n = n * r.d - d * r.n; // numerator of rat t = (numerator (left rat) * r.denominator) - (denominator * r.numerator)
		t.d = d * r.d;           // denominator of rat t = (denominator (left rat) * r.denominator)
		t.simplify();
		return t;                // return rat t which now has the difference
	}

	Rat operator*(Rat r) {       // teaches the compiler operator multiplication
		Rat t;                   // Rat t will have the product of both rats
		t.n = n * r.n;           // numerator of rat t = (numerator (left rat) * r.numerator)
		t.d = d * r.d;           // denominator of rat t = (denominator (left rat) * r.denominator)
		t.simplify();
		return t;                // return rat t which now has the product
	}

	Rat operator/(Rat r) {       // teaches the compiler operator division
		Rat t;                   // Rat t will have the quotient of both rats
		t.n = n * r.d;           // numerator of rat t = (numerator (left rat) * r.denominator) opposite of * bc reciprocal 
		t.d = d * r.n;           // denominator of rat t = (denominator (left rat) * r.numerator) oppositie of * bc reciprocal
		t.simplify();
		return t;                // return rat t which now has the quotient
	}

	void simplify() {
		for (int i = 2; i < d; i++) {           // for loop from 2 to the denominator which would be the max possible divisor
			if (n % i == 0 && d % i == 0) {     // if both the numerator and denominator are divisible by current i value
				n = n / i;                      // then divide numerator by i, keeps looping until its fully simplified
				d = d / i;                      // then divide denominator by i, keeps looping until its fully simplified
			}                                   // could have also made a int gcd variable and set gcd = i in the loop and if statement
		}                                       // when the loop was done, it would have found the greatest common divisor
	}                                           // then divide n and d by gcd, but this would have required more code

	// 2 overloaded i/o operators
	friend ostream& operator<<(ostream& os, Rat r);  // declaring friend function operator<< (cout), this means it has access to private info
	friend istream& operator>>(istream& is, Rat& r); // declaring friend function operator>> (cin), this means it has access to private info
}; // end Rat

// operator<<() is NOT a member function but since it was declared a friend of Rat
// it has access to its private parts

ostream& operator<<(ostream& os, Rat r) {                 // teaches compiler how to output a rat
	r.simplify();                                         // firstly, simplify the number (lowest terms), Ex. 14/6 becomes 7/3
	// in this if statement below, I added r.n % r.d != 0 because if I put 4 for example, it would return 4 0/1, I want it to just return 4/1
	if (r.n > r.d && r.n % r.d != 0) {  // if it is an improper function (bigger numerator / smaller denominator) and the remainder is not 0
		int remainder = r.n % r.d;                        // remainder = numerator % denominator (if 7/3, 7 % 3 = 1, remainder is 1)
		int wholeNum = (r.n - remainder) / r.d;           // the whole num is numerator - remainder / denominator (if 7/3, (7-1)/6 = 6/3 = 2)
		os << wholeNum << " " << remainder << "/" << r.d; // output the whole number and the remainder fraction (if 7/3, returns 2 1/3) 
	}
	else {                                             // else if it's not an improper fraction
		os << r.n << "/" << r.d;                       // simply output the numerator / denominator which have been simplified already 
	}
	return os;                                         // finally, return os
}

// operator>>() is NOT a member function but since it was declared a friend of Rat
// it has access to its private parts

istream& operator>>(istream& is, Rat& r) {      // teaches compiler how to input a rat
	is >> r.n >> r.d;                           // input first number as numerator, second number as denominator
	return is;                                  // return is
}                                               // after input is done, you can then cout << the rat because it now knows the n and d

int main() {
	Rat x(14, 8);  // initialize rat x to 14/8,
	Rat y(6, 10);  // initialize rat y to 6/10

	cout << "Rat 1: " << x << endl; // print rat x, operator<< simplifies 14,8 to 7,4, then prints whole num and remainder fraction 1 3/4
	cout << "Rat 2: " << y << endl << endl; // print rat y, operator<< simplifies 6,10 to 3,5, then prints 3/5
	
	// for these operations, x is left side, y is the Rat r paramater in the operator functions which is the right side
	cout << "Rat 1 + Rat 2 = " << x.operator+(y) << endl; // add: rat x + rat y, (operator+ adds them, then simplifies and returns)
	cout << "Rat 1 - Rat 2 = " << x.operator-(y) << endl; // subtract: rat x - rat y, (operator- subtracts them, then simplifies and returns)
	cout << "Rat 1 * Rat 2 = " << x.operator*(y) << endl; // multiply: rat x * rat y, (operator* multiplies them, then simplifies and returns)
	cout << "Rat 1 / Rat 2 = " << x.operator/(y) << endl; // divide: rat x / rat y, (operator/ divides them, then simplifies and returns)
	// the way it works is the operators simplify the result, then the operator<< changes the improper fractions to mixed fraction form
	return 0;
	
}