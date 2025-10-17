#ifndef VCIPHER_H_
#define VCIPHER_H_
//#include "cipher.h"
#include "kcipher.h"

using namespace std;

/* A class that implements a
   Vigenere cipher class. It 
   inherts KCipher */
// TODO: Implement this class

class VCipher : public KCipher {

private:
	string keyword;

public:
	VCipher(const string& key);

	virtual string encrypt(string raw) override;
	virtual string decrypt(string enc) override;
};

#endif
