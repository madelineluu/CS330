#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------

VCipher::VCipher(const string& key) : KCipher(vector<string>{ key }) {
	keyword = key;
}

string VCipher::encrypt(string raw) {
	cout << "Encrypting (Vigenere)...";
	string retStr;
	size_t key_index = 0;
	size_t key_len = keyword.size();

	for (char c : raw) {
		if (c == ' ') {
			retStr += ' ';
		} else if (isalpha(c)) {
			unsigned int shift = keyword[key_index % key_len];
			if (isupper(c)) {
				retStr += 'A' + (c - 'A' + shift) % ALPHABET_SIZE;
			} else if (islower(c)) {
				retStr += 'a' + (c - 'a' + shift) % ALPHABET_SIZE;
			}

			key_index++;
		}
	}
	cout << "Done" << endl;
	return retStr;
}

string VCipher::decrypt(string enc) {
        cout << "Decrypting (Vigenere)...";
        string retStr;
        size_t key_index = 0;
        size_t key_len = keyword.size();

        for (char c : enc) {
                if (c == ' ') {
                        retStr += ' ';
                } else if (isalpha(c)) {
                        unsigned int shift = keyword[key_index % key_len];
                        if (isupper(c)) {
                                retStr += 'A' + (c - 'A' + ALPHABET_SIZE - shift) % ALPHABET_SIZE;
                        } else if (islower(c)) {
                                retStr += 'a' + (c - 'a' + ALPHABET_SIZE - shift) % ALPHABET_SIZE;
			}

			key_index++;
		}
	}

	cout << "Done" << endl;
	return retStr;
}



