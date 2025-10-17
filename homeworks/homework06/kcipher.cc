#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

KCipher::KCipher(const vector<string>& pages) {
	book = pages;

	// Compress book pages into key
	for (const auto& page : book) {
		for (char c : page) {
			if (c >= 'a' && c <= 'z') {
				key_stream += c;
			}
		}
	}
}

string KCipher::encrypt(string raw) {
	cout << "Encrypting (Running Key)...";

	string retStr;
	size_t key_index = 0;

	for (char c : raw) {
		if (c == ' ') {
			retStr += ' ';
		} else if (isalpha(c)) {
			if (key_index >= key_stream.size()) {
				cerr << "Error key stream exhausted" << endl;
				break;
			}
			char key_char = key_stream[key_index++];
			unsigned int shift = key_char - 'a';

			if (isupper(c)) {
				retStr += 'A' + (c - 'A' + shift) % ALPHABET_SIZE;
			} else if (islower(c)) {
				retStr += 'a' + (c - 'a' + shift) % ALPHABET_SIZE;
			}
		}
	}
	
	cout << "Encryption done" << endl;
	return retStr;
}

string KCipher::decrypt(string enc) {
	cout << "Decrypting (Running key)...";
	string retStr;
	size_t key_index = 0;

	for (char c : enc) {
		if (c == ' ') {
			retStr += ' ';
		} else if (isalpha(c)) {
			if (key_index > key_stream.size()) {
				cerr << "Error: key stream exhausted" << endl;
				break;
			}

			char key_char = key_stream[key_index++];
			unsigned int shift = key_char - 'a';

			if (isupper(c)) {
				retStr += 'A' + (c - 'A' + ALPHABET_SIZE - shift) % ALPHABET_SIZE;
			} else if (islower(c)) {
				retStr += 'a' + (c - 'a' + ALPHABET_SIZE - shift) % ALPHABET_SIZE;
			}
		}
	}
	cout << "Done" << endl;
	return retStr;
}

