// Inti Mendoza
// RSA implementation C++

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

bool is_prime(int x) {
	for(int i = 2; i <= x/2; i++) {
		if(x % i == 0) {
			return false;
		}
	}
	return true;
}

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

class Key {
private:
	int N;
	int k;
public:
	Key() {
	}

	int get_N() {
		return this->N;
	}

	int get_k() {
		return this->k;
	}

	void set_N(int N) {
		this->N = N;
	}

	void set_k(int k) {
		this->k = k;
	}

	~Key(){}
};

class RSA {
private:
	int n;
	int P;
	int Q;
	int N;
	int M;
	int E;
	int D;
	Key key_e;
	Key key_d;
	vector<string> ciphertext;
	vector<string> plaintext;
public:
	RSA() {
        cout << "Enter n: "; cin >> this->n;
        setPQ();
        setN();
		setM();
		setE();
		setD();
		this->key_e = Key();
		this->key_e.set_N(this->N);
		this->key_e.set_k(this->E);
		this->key_d = Key();
		this->key_d.set_N(this->N);
		this->key_d.set_k(this->D);
	}

	void encrypt(vector<string> plaintext) {
		if(plaintext.size() != 0) {
			this->plaintext = plaintext;
		}
		vector<string> ciphertext;
		for(int i = 0; i < this->plaintext.size(); i++) {
			int x = binary_to_decimal(this->plaintext[i]);
			int encr_x = pow(x, key_e.get_k());
			encr_x = encr_x % key_e.get_N();
			ciphertext.push_back(decimal_to_binary(encr_x));
		}
		this->ciphertext = ciphertext;
	}

	void decrypt(vector<string> ciphertext) {
        if(ciphertext.size() != 0) {
            this->ciphertext = ciphertext;
        }
        vector<string> plaintext;
        for(int i = 0; i < this->ciphertext.size(); i++) {
            int x = binary_to_decimal(this->ciphertext[i]);
            int decr_x = pow(x, key_d.get_k());
            decr_x = decr_x % key_d.get_N();
            plaintext.push_back(decimal_to_binary(decr_x));
        }
        this->plaintext = plaintext;
	}

	void setPQ() {
		this->P = rand() % 100;
		this->Q = rand() % 100;
		if(pow(2, this->n) > this->P * this->Q || (!is_prime(this->P)) || (!is_prime(this->Q))) {
			setPQ();
		}
	}

	void setN() {
		this->N = this->P * this->Q;
	}

	void setM() {
		this->M = (this->P - 1) * (this->Q - 1);
	}

	void setE() {
		do {
			this->E = rand() % (this->M - 2) + 2;
		} while(gcd(this->E, this->M) != 1);
	}

	void setD() {
		this->D = rand() % this->M + 1;
		if((this->D * this->E) % this->M != 0) {
			setD();
		}
	}

	void print() {
		cout << "P = " << this->P << endl << "Q = " << this->Q << endl;
		cout << "M = " << this->M << endl << "E = " << this->E << endl;
		cout << "D = " << D << endl;
	}

	vector<string> get_ciphertext() {
		return this->ciphertext;
	}

	vector<string> get_plaintext() {
		return this->plaintext;
	}

	~RSA(){}
};

class Unittest {
private:
	RSA rsa;
	vector<string> test;
public:
	Unittest() {
	    srand(time(NULL));
		this->rsa = RSA();
	}

	void test_simple_text() {
		this->test.push_back("1001");
		this->rsa.print();
		this->rsa.encrypt(test);
		cout << "input:\t" << this->test[0] << endl;
		this->rsa.decrypt(this->rsa.get_ciphertext());
		if(this->rsa.get_plaintext() == rsa.get_ciphertext()) {
            cout << "Test result: Passed";
		} else {
            cout << "Test result: Failed";
		}
	}
};

int main() {
    cout << "This will ask for n twice. Just comply, idk why this happens :/" << endl;
    Unittest test = Unittest();
    test.test_simple_text();
    /*
    vector<string> test;
    test.push_back("1001");
	srand(time(NULL));
	RSA rsa = RSA();
	rsa.print();
	rsa.encrypt(test);
	cout << "input:\t" << test[0] << endl;
	cout << "encryption:\t" << rsa.get_ciphertext()[0] << endl;
	rsa.decrypt(rsa.get_ciphertext());
	cout << "decryption:\t" << rsa.get_plaintext()[0] << endl;
	*/
	return 0;
}
