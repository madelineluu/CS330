#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation

CCipher::CCipher(unsigned int r) {
	rotation = r % ALPHABET_SIZE;

	string alpha = "abcdefghijklmnopqrstuvwxyz";
	rotate_string(alpha, rotation);
	set_cipher_alpha(alpha);
}	

CCipher::~CCipher() {
}
// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.

	unsigned int n = in_str.size();
	if (n == 0) return;

	rot = rot % ALPHABET_SIZE;

	// Rotate with in-clasa algorithm
	reverse(in_str.begin(), in_str.begin() + n - rot);
	reverse(in_str.begin() + n - rot, in_str.end());
	reverse(in_str.begin(), in_str.end());

}
