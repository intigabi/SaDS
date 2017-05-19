
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

long long int binary_to_decimal(string str) {
	int result = 0;
	for(int i = 0; i < str.length(); i++) {
		result += (str[str.length() - i - 1] == '0' ? 0 : 1) * pow(2, i);
	}
	return result;
}

int hash(string input) {
	vector<string> chunking;
	while(input.length() % 32 != 0) {
		input += "0";
	}

	for(int i = 0; i < input.length(); i++) {
		string chunk = "";
		for(int j = 0; j < 32; i++) {
			chunk += input[j + i];
		}

		chunking.push_back(chunk);
		chunk.clear();
		i += 31;
	}

	long long int res = 0;
	for(int i = 0; i < chunking.size(); i++) {
		int tmp = binary_to_decimal(chunking[i]);
		res = (long long int)pow(res + 2 + tmp, 1234567) % (long long int) 9993201131;
	}

	return res;
}

int main () {
	string text = "1101001011101001011101010";

	cout << "Hashing '" << text << "': " <<  hash(text) << endl;
	return 0;
}
