
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

class scheme_symm {
protected:
	string plaintext;
	string cipher_text;
	string key;

public:
	static scheme_symm *run_CBC(string cipher_text, string key);
	virtual void print() = 0;
	virtual void encrypt() = 0;
	virtual void decrypt(string cipher_text = "") = 0;
	virtual string return_cipher_text() = 0;
	virtual string return_plaintext() = 0;

};

class scheme_block {
protected:
	string plaintext;
	string cipher_text;
	string key;

public:
	static scheme_block *make_Block_Cipher(int S_N, int P_N, string key);
	virtual void print() = 0;
	virtual void encrypt(string input) = 0;
	virtual void decrypt(string input = "") = 0;
	virtual string return_cipher_text() = 0;
	virtual string return_plaintext() = 0;

};

int binary_to_decimal(string str) {
	int result = 0;
	for(int i = 0; i < str.length(); i++) {
		result += (str[str.length() - i - 1] == '0' ? 0 : 1) * pow(2, i);
	}
	return result;
}

string decimal_to_binary(int n) {
	string result = "";
	while(n != 0) {
		result = (n % 2 == 0 ? "0" : "1") + result;
		n /= 2;
	}
	return result;
}

string xor_strings(string mask, string input) {
	string output = "";

	for(int i = 0; i < input.length(); i++) {
		output += input[i] == mask[i] ? "0" : "1";
	}

	return output;
}


class Block_Cipher : public scheme_block {
protected:
	string plaintext;
	string cipher_text;
	string key;
	string key_chain[2];
	int S_N;
	int P_N;
public:
	Block_Cipher(int S_N, int P_N, string key) {
		this->S_N = S_N;
		this->P_N = P_N;
		this->key = key;
		this->key_chain[0] = this->key.substr(0, this->key.length()/2);
		this->key_chain[1] = this->key.substr(this->key.length()/2, this->key.length());
	}
	~Block_Cipher();

	void encrypt(string input) {
		substitute(input);
		permutate();
		this->cipher_text = key_step(key_step(this->cipher_text, this->key_chain[0]), this->key_chain[1]);
	}

	void decrypt(string input = "") {
		if(input != "") {
			this->cipher_text = input;
		}
		this->plaintext = key_step(key_step(this->cipher_text, key_chain[1]), key_chain[0]);
		decrypt_permutate();
		decrypt_substitute();
	}

	void substitute(string input) {
		this->plaintext = input;
		cipher_text = "";
		for(int i = 0; i < this->plaintext.length(); i++) {
			string chunk = "";
			for(int j = 0; j < this->S_N; j++) {
				if(i + j > this->plaintext.length()) {
					chunk += "0";
				} else {
					chunk += this->plaintext[i + j];
				}
			}
			int x = binary_to_decimal(chunk);

			x = ((x + 1) * 7) % 17 - 1;

			string dec_chunk = decimal_to_binary(x);

			while(dec_chunk.length() < this->S_N) {
				string tmp = "0" + dec_chunk;
				dec_chunk = tmp;
			}

			cipher_text += dec_chunk;
			chunk.clear();
			i += this->S_N - 1;
		}
		this->cipher_text = cipher_text;

	}

	void decrypt_substitute() {
		string result = "";
		for(int i = 0; i < this->plaintext.length(); i++) {
			string chunk = "";
			for(int j = 0; j < this->S_N; j++) {
				if(i + j > this->plaintext.length()) {
					chunk += "0";
				} else {
					chunk += this->plaintext[i + j];
				}
			}
			int x = binary_to_decimal(chunk);
			int inv_x = 18; // unreachable
			int works;

			for(int j = 0; j < 17 && inv_x != x; j++) {
				inv_x = ((j + 1) * 7) % 17 - 1;
				works = j;
			}

			string bin_chunk = decimal_to_binary(works);

			while(bin_chunk.length() < this->S_N) {
				string tmp = "0" + bin_chunk;
				bin_chunk = tmp;
			}

			result += bin_chunk;
			i += this->S_N - 1;
		}
		this->plaintext = result;
	}

	void permutate() {
		string result = "";

		for(int i = 0; i < this->cipher_text.length(); i++) {
			string chunk = "";
			for(int j = 0; j < this->P_N; j++) {
				if(i + j > this->cipher_text.length()) {
					chunk += "0";
				} else {
					chunk += this->cipher_text[i + j];
				}
			}
			for(int j = 2; j < chunk.length(); j++) {
				result += chunk[j];
			}
			result += chunk[1];
			result += chunk[0];

			i += this->P_N - 1;
		}
		this->cipher_text = result;
	}

	void decrypt_permutate() {
		string result = "";
		for(int i = 0; i < this->plaintext.length(); i++) {
			string chunk = "";
			for(int j = 0; j < this->P_N; j++) {
				if(i + j > this->plaintext.length()) {
					chunk += "0";
				} else {
					chunk += this->plaintext[i + j];
				}
			}
			result += chunk[chunk.length() - 1];
			result += chunk[chunk.length() - 2];
			for(int j = 0; j < chunk.length() - 2; j++) {
				result += chunk[j];
			}
			i += this->P_N - 1;
		}
		this->plaintext = result;
	}

	string key_step(string cipher_text, string key) {
		string result = "";
		for(int i = 0; i < cipher_text.length(); i++) {
			string chunk = "";
			for(int j = 0; j < key.length()/2; j++) {
				if(i + j > cipher_text.length()) {
					chunk += "0";
				} else {
					chunk += cipher_text[i + j];
				}
			}
			result += xor_strings(key, chunk);
			i += key.length()/2 - 1;
		}
		return result;
	}

	void print() {
		cout << this->cipher_text << endl;
	}

	string return_cipher_text() {
		return this->cipher_text;
	}

	string return_plaintext() {
		return this->plaintext;
	}

};

class Symmetric_encryption : public scheme_symm {
protected:
	string plaintext;
	string IV;
	string cipher_text;

public:
	Symmetric_encryption(string cipher_text, string IV) {
		this->cipher_text = cipher_text;
		this->IV = IV;
	}
	~Symmetric_encryption(){};

	void encrypt() {
		string result = "";
		string key_step_IV = this->IV;
		for(int i = 0; i < this->cipher_text.length(); i++) {
			string chunk = "";
			for(int j = 0; j < key_step_IV.length(); j++) {
				if(i + j > this->cipher_text.length()) {
					chunk += "0";
				} else {
					chunk += this->cipher_text[i + j];
				}
			}
			string xor_result = xor_strings(key_step_IV, chunk);
			result += xor_result;

			key_step_IV = xor_result;

			i += key_step_IV.length() - 1;
		}

		this->cipher_text = result;
	}

	void decrypt(string cipher_text = "") {
		if(cipher_text != "") {
			this->cipher_text = cipher_text;
		}
		string result = "";
		string key_step_IV = this->IV;
		for(int i = 0; i < this->cipher_text.length(); i++) {
			string chunk = "";
			for(int j = 0; j < this->IV.length(); j++) {
				if(i + j > this->cipher_text.length()) {
					chunk += "0";
				} else {
					chunk += this->cipher_text[i + j];
				}
			}

			string xor_result = xor_strings(key_step_IV, chunk);
			result += xor_result;

			key_step_IV.clear();
			for(int j = 0; j < this->IV.length(); j++) {
				key_step_IV += this->cipher_text[i + j];
			}

			i += this->IV.length() - 1;
		}
		this->plaintext = result;
	}

	void print() {
		cout << plaintext << endl;
	}

	string return_plaintext() {
		return this->plaintext;
	}

	string return_cipher_text() {
		return this->cipher_text;
	}
};

scheme_block *scheme_block::make_Block_Cipher(int S_N, int P_N, string key) {
	return new Block_Cipher(S_N, P_N, key);
}
scheme_symm * scheme_symm::run_CBC(string cipher_text, string IV) {
	return new Symmetric_encryption(cipher_text, IV);
}

class Criptographer{
protected:
	scheme_block* block;
	scheme_symm* cbc;
	string input;
	string block_cipher_text;
	string cbc_cipher_text;
	string cbc_plaintext;
	string block_plaintext;
	string key;
	string IV;
	int S_N;
	int P_N;

public:
	Criptographer(int S_N, int P_N, string key, string input, string IV) {
		this->S_N = S_N;
		this->P_N = P_N;
		this->key = key;
		this->input = input;
		this->IV = IV;
		this->block = scheme_block::make_Block_Cipher(this->S_N, this->P_N, this->key);
	}

	string encrypt() {
		this->block->encrypt(this->input);
		this->block_cipher_text = this->block->return_cipher_text();

		this->cbc = scheme_symm::run_CBC(this->block_cipher_text, this->IV);

		this->cbc->encrypt();
		this->cbc_cipher_text = this->cbc->return_cipher_text();

		return this->cbc_cipher_text;
	}

	string encrypt_simple() {
        this->block->encrypt(this->input);
        this->block_cipher_text = this->block->return_cipher_text();

        return this->block_cipher_text;
	}

	string decrypt() {
		this->cbc->decrypt();
		this->cbc_plaintext = this->cbc->return_plaintext();

		this->block->decrypt();
		this->block_plaintext = this->block->return_plaintext();

		return this->block_plaintext;
	}

	string decrypt_simple() {
        this->block->decrypt();
        this->block_plaintext = this->block->return_plaintext();

        return this->block_plaintext;
	}

	string get_input() {
		return this->input;
	}

	string return_block_cipher_text() {
		return this->block_cipher_text;
	}

	string return_cbc_cipher_text() {
		return this->cbc_cipher_text;
	}

	string return_block_plaintext() {
		return this->block_plaintext;
	}

	string return_cbc_plaintext() {
		return this->cbc_plaintext;
	}
};

class Unittest {
private:
	string IV 		= "10101010";
	string key 		= "1001100000100110";
	int S_N			= 4;
	int P_N			= 8;
	int size;

public:
	Unittest(int size) {
		this->size = size * 8;
	}

	void test_random_input() {
		srand(time(NULL));
		string input = "";
		for(int i = 0; i < size; i++) {
			input += rand()%2 == 0 ? "0" : "1";
		}
		Criptographer cripto = Criptographer(this->S_N, this->P_N,
									 this-> key, input, this->IV);
		string encryption = cripto.encrypt_simple();
		string decryption = cripto.decrypt_simple();
		bool pass = input.compare(decryption) ? false : true;
		string outcome = pass ? "passed" : "failed";

		cout << "Program has " << outcome << " the test!" << endl;
		cout << "Show results of unit test? [Y/N]" << endl;
		char show;
		cin >> show;
		if(show == 'Y') {
            cout << "Random input: " << input << endl;
            cout << "Encryption: " << encryption << endl;
            cout << "Decryption: " << decryption << endl;
		}
	}

};

int main() {
	string key = "1001100000100110";
	string IV = "10101010";

	ifstream fin("tux.txt", ifstream::binary);
	ofstream fout1("tux_encr.txt", ifstream::binary);
	ofstream fout2("tux_decr.txt", ifstream::binary);
	ofstream fout1_simple("tux_encr_simple.txt", ifstream::binary);
	ofstream fout2_simple("tux_decr_simple.txt", ifstream::binary);

	string image = "";

	char c;
	while(fin.get(c)) {
		image += string(1, c);
	}
	Criptographer crypto_img = Criptographer(4, 8, key, image, IV);
	Criptographer crypto_img_simple = Criptographer(4, 8, key, image, IV);

	string img_encr_simple = crypto_img_simple.encrypt_simple();
	string img_encr = crypto_img.encrypt();

	fout1 << img_encr;
    fout1_simple << img_encr_simple;

    string img_decr_simple = crypto_img_simple.decrypt_simple();
    string img_decr = crypto_img_simple.decrypt_simple();

    fout2 << img_decr;
    fout2_simple << img_decr_simple;

	fin.close();
	fout1.close();
	fout2.close();
	fout1_simple.close();
	fout2_simple.close();
	Unittest test = Unittest(20);
	test.test_random_input();


	return 0;
}
