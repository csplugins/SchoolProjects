/*
	Cody Skala cws26 Project1 Part2
	Algorithms Spring 2016
	02/11/2016 14:33
	Dr. Duan
	This program will sign or verify the the content of an original file using rsa
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "sha256.h"
#include "../Project1Part1/BigIntegerLibrary.hh"

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

int main(int argc, char *argv[]){
	if(argc != 3 || (string(argv[1])!="s"&&string(argv[1])!="v")){
		cout << "ERROR, Usage:\n\t" << argv[0] << " s someFile.txt\n\t" << argv[0] << " v someFile.txt.signed";
		return 0;
	}
	ifstream key;
	ifstream file;
	fstream signedFile;
	char keyChar;
	if(string(argv[1]) == "s"){
		key.open("../Project1Part1/d_n.txt");
		file.open(argv[2]);
		signedFile.open((string(argv[2])+".signed").c_str(), ios::out);
	}else{
		key.open("../Project1Part1/e_n.txt");
		signedFile.open(argv[2], ios::in);
	}
	string fileContent = "";//((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	if(string(argv[1]) == "v"){
		signedFile.get(keyChar);
		while(keyChar != '\n')
			signedFile.get(keyChar);
		signedFile.get(keyChar);
		while(!signedFile.eof()){
			fileContent += keyChar;
			signedFile.get(keyChar);
		}
	}else{
		file.get(keyChar);
		while(!file.eof()){
			fileContent += keyChar;
			file.get(keyChar);
		}
	}
	signedFile.clear();
	signedFile.seekg(0, ios::beg);
	string sha = sha256(fileContent);
	cout << "SHA: " << sha << endl << endl;
	BigInteger htoi = BigInteger(0);
	BigInteger converter = BigInteger(16);
	if(sha[sha.size()-1] > 57)
		htoi = sha[sha.size()-1] - 87;
	else htoi = sha[sha.size()-1] - 48;
	for(int i = 1; i < sha.size(); i++){
		if(sha[sha.size()-i-1] > 57)
			htoi = htoi + converter*(sha[sha.size()-i-1] - 87);
		else htoi = htoi + converter*(sha[sha.size()-i-1] - 48);
		converter = converter * 16;
	}
	if(string(argv[1]) == "s")
		cout << "Original file has the hash:\n" << htoi << endl << endl;
	else cout << "Message in signed file has the hash:\n" << htoi << endl << endl;
	vector<BigInteger> htoiVec;
	BigInteger eORd = BigInteger(0);
	BigInteger n = BigInteger(0);
	int nLength = 0;
	if(string(argv[1]) == "s"){
		BigInteger htoiCopy = htoi;
		while(htoiCopy != 0){
			htoiVec.push_back(htoiCopy%10);
			htoiCopy = htoiCopy / 10;
		}
	}
	key.get(keyChar);
	while(keyChar>='0' && keyChar<='9'){
		eORd = eORd*10 + keyChar-48;
		key.get(keyChar);
	}
	while(keyChar < '0' || keyChar > '9')
		key.get(keyChar);
	while(!key.eof()){
		n = n*10 + keyChar-48;
		key.get(keyChar);
		nLength++;
	}
	if(string(argv[1]) == "s"){
		vector<BigInteger> vec;
		int vecIndex = htoiVec.size()-1;
		while(vecIndex > -1){
			BigInteger temp = BigInteger(0);
			for(int i = 0; i < nLength-1; i++){
				temp = temp*10 + htoiVec[vecIndex];
				vecIndex--;
				if(vecIndex < 0) break;
			}
			vec.push_back(temp);
		}
		cout << "Original hashed message has encryption:\n";
		for(int i = 0; i < vec.size(); i++){
			BigInteger temp = modOp(vec[i], eORd, n);
			BigInteger tempCopy = temp;
			int digits = 0;
			while(tempCopy!=0){
				digits++;
				tempCopy = tempCopy/10;
			}
			for(int i = nLength; i > digits; i--){
				cout << "0";
				signedFile << "0";
			}
			cout << temp << "\n";
			signedFile << temp << "\n";
			file.clear();
			file.seekg(0, ios::beg);
			file.get(keyChar);
			while(!file.eof()){
				signedFile << keyChar;
				file.get(keyChar);
			}
		}
	}else{
		cout << "Encrypted hash found in signed file:\n";
		BigInteger verify = BigInteger(0);
		signedFile.get(keyChar);
		while(keyChar != '\n'){
			BigInteger temp = BigInteger(0);
			for(int i = 0; i < nLength; i++){
				temp = temp*10 + keyChar-48;
				signedFile.get(keyChar);
				if(keyChar == '\n') break;
			}
			htoiVec.push_back(temp);
		}
		for(int i = 0; i < htoiVec.size();i++)
			cout << htoiVec[i];
		cout << "\nEncryption after being decrypted gives hash:\n";
		for(int i = 0; i < htoiVec.size(); i++){
			BigInteger temp = modOp(htoiVec[i], eORd, n);
			BigInteger tempCopy = temp;
			while(tempCopy != 0){
				verify = verify*10 + tempCopy%10;
				tempCopy = tempCopy / 10;
			}
			cout << temp;
		}
		BigInteger verifyCopy = verify;
		verify = 0;
		while(verifyCopy != 0){
				verify = verify*10 + verifyCopy%10;
				verifyCopy = verifyCopy / 10;
			}
		if(verify == htoi)
			cout << "\n\nThere is a high chance that this file is authentic and it is original.\n";
		else cout << "\n\nThe contents of the original file have been modified!\n";
	}
	key.close();
	if(file.is_open())
		file.close();
	signedFile.close();
	return 0;
}