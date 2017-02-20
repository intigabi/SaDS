// Secure and Dependable Systems HW 1
// Inti Mendoza

#include <iostream>

using namespace std;

static int value1, value2, value3;

int getValue1() {
	return value1;
}

int getValue2() {
	return value2;
}

int getValue3() {
	return value3;
}

int lmao() {
	int err;
	if((err = getValue1()) != 0)
		goto fail;
	if((err = getValue2()) != 0)
		goto fail;
		goto fail;
	if((err = getValue3()) != 0)
		goto fail;

	return -1;
fail:
	return err;
}

void unit_tests() {
	int errors = 0;
	cout << "Unit Test 1 - value1 = 0, value2 = 0, value3 = 0" << endl;
	value1 = value2 = value3 = 0;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << " -- error!" << endl;
	}

	cout << "Unit Test 2 - value1 = 0, value2 = 0, value3 = 1" << endl;
	value1 = 0; value2 = 0; value3 = 1;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << "-- error!" << endl;
	}

	cout << "Unit Test 3 - value1 = 0, value2 = 1, value3 = 0" << endl;
	value1 = 0; value2 = 1; value3 = 0;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << "-- error!" << endl;
	}

	cout << "Unit Test 4 - value1 = 0, value2 = 1, value3 = 2" << endl;
	value1 = 0; value2 = 1; value3 = 2;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << "-- error!" << endl;
	}

	cout << "Unit Test 5 - value1 = 1, value2 = 0, value3 = 0" << endl;
	value1 = 1; value2 = 0; value3 = 0;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << "-- error!" << endl;
	}

	cout << "Unit Test 6 - value1 = 1, value2 = 0, value3 = 2" << endl;
	value1 = 1; value2 = 0; value3 = 2;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << "-- error!" << endl;
	}

	cout << "Unit Test 7 - value1 = 1, value2 = 2, value3 = 0" << endl;
	value1 = 1; value2 = 2; value3 = 0;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << "-- error!" << endl;
	}

	cout << "Unit Test 8 - value1 = 1, value2 = 2, value3 = 3" << endl;
	value1 = 1; value2 = 2; value3 = 3;
	cout << "err = " << lmao();
	if(lmao() != -1) {
		errors++;
		cout << "-- error!" << endl;
	}

	cout << endl << "--------" << endl << "Total errors: " << errors << endl;

}

int main() {
	unit_tests();
	return 0;
}