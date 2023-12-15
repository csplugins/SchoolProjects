/*
	Cody Skala cws26 Project1 Part1
	Algorithms Spring 2016
	02/10/2016 13:25
	Dr. Duan
	This program will generate all the necessary numbers for rsa encryption
*/

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "BigIntegerLibrary.hh"

using namespace std;

BigInteger modOp(BigInteger base, BigInteger exponent, BigInteger mod){
	BigInteger x = BigInteger(1);
	while (exponent > 0){
		if (exponent % 2 == 1)
			x = (x * base) % mod;
		base = (base * base) % mod;
		exponent = exponent / 2;
	}
	return x % mod;
}
bool Fermat(BigInteger p){
	if (p == 1){
		return false;
	}
	for (int i = 0; i < 3; i++){
		BigInteger temp = BigInteger(rand());
		BigInteger a = temp % (p - BigInteger(1)) + BigInteger(1); 
		if (modOp(a, p - 1, p) != 1){ 
			return false;
		}
	}
	return true;
}

pair<BigInteger, BigInteger> extendedEuclid(BigInteger a, BigInteger b) {
    if(a == 0) return make_pair(0, 1);
    pair<BigInteger, BigInteger> p;
    p = extendedEuclid(b % a, a);
    return make_pair(p.second - p.first*(b/a), p.first);
}
 
BigInteger modInverse(BigInteger a, BigInteger m) {
    return (extendedEuclid(a,m).first + m) % m;
}

BigInteger gcdFunc(BigInteger a, BigInteger b) {
	while(b != 0){
		BigInteger temp;
		temp = a;
		a = b;
		b = temp % b;
	}
	return a;
}

int main() {
	srand(time(NULL));
	ofstream pqText("p_q.txt");
	ofstream enText("e_n.txt");
	ofstream dnText("d_n.txt");
	
	try {
		cout << "Generating necessary files...\nThis may take a while...\n";
		BigInteger p, q, n, e, d, phin;
		p = BigInteger(1);
		for (int i=0;i<155;i++) {
			p = p*10 +rand();
		}
		q = BigInteger(1);
		for (int i=0;i<155;i++) {
			q = q*10 +rand();
		}

		if(p % 2 == 0)
			p = p + 1;
		while(!Fermat(p))
			p = p + 2;
		if(q % 2 == 0)
			q = q + 1;
		while(!Fermat(q))
			q = q + 2;
		cout << "\np:" << p << "\n";
		cout << "\nq:" << q << "\n";
		pqText << p << "\n" << q;
		n = BigInteger(p * q);
		cout << "\nn:" << n << "\n";
		phin = BigInteger((p-BigInteger(1))*(q-BigInteger(1)));
		e = BigInteger(rand());
		if(e % 2 == 0)
				e = e + 1;
		while(!Fermat(e)){
			e = e + 2;
			if(gcdFunc(e,phin) != 1)
				e = e + 2;
		}
		enText << e << "\n" << n;
		BigInteger one = BigInteger(1);
		d= modInverse(e, phin);
		cout << "\n(p-1)(q-1):" << phin << "\n";
		cout << "\ne:" << e << "\n";
		cout << "\nd:" << d << "\n";
		dnText << d << "\n" << n;
	} catch(char const* err) {
		cout << "The library threw an exception:\n" << err << endl;
		pqText.close();
		enText.close();
		dnText.close();
	}
	pqText.close();
	enText.close();
	dnText.close();
	cout << "\nFiles saved successfully.\n";
	return 0;
}