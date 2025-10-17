#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
// TODO: Implement this function

class KCipher : public Cipher {

private:
	// book pages for cipher
	vector<string> book;
	string key_stream;

public:
	KCipher(const vector<string>& pages);

	// overriding enc and dec functions
	virtual string encrypt(string raw) override;
	virtual string decrypt(string enc) override;
};

#endif

