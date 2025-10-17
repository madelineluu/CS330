#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
// TODO: Implement this class

class CCipher : public Cipher {

private:
	unsigned int rotation;

public:
	CCipher(unsigned int r = 0);
	~CCipher();
};

/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif

