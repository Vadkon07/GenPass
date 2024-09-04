#include <iostream>
#include <string>
#include <random>

using namespace std;

string getPassword(int length) {
    if (length <= 0) {
        return "";
    }

    static const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

    int charSize = characters.size();

    static random_device rd;  
    static mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, charSize - 1);

    string password;
    password.reserve(length);

    for (int i = 0; i < length; ++i) {
        int randomIndex = distribution(generator);
	password += characters[randomIndex];
    }

    return password;
}

string getPasswordAdvanced(int length) {
    if (length <= 0) {
        return "";
    }

    static const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+{}[]',.";

    int charSize = characters.size();

    static random_device rd;  
    static mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, charSize - 1);

    string password;
    password.reserve(length);

    for (int i = 0; i < length; ++i) {
        int randomIndex = distribution(generator);
	password += characters[randomIndex];
    }

    return password;
}

string getPasswordCustom(int length) {
	if (length <= 0) {
		return "";
	}

	static string characters;

	cout << "Enter symbols which your password can include (abcABC123): " << endl;
	cin >> characters;

	int charSize = characters.size();
	static random_device rd;  
   	static mt19937 generator(rd());
    	uniform_int_distribution<> distribution(0, charSize - 1);

    	string password;
    	password.reserve(length);

    	for (int i = 0; i < length; ++i) {
        	int randomIndex = distribution(generator);
		password += characters[randomIndex];
    	}

    	return password;
	}


int main() {
    int length;
    char symbols;


    cout << "Enter the length of the password: ";
    cin >> length;
    cout << "Choose a type of password:\n\n 1. Random letters and numbers\n 2. Random letters, numbers, and symbols\n 3. Custom symbols only\n\nEnter your choice: ";
    cin >> symbols;

    if (cin.fail() || length <= 0) {
        cout << "Invalid input. Please enter a positive integer for the password length." << endl;
        return 1;  
    }

    if (symbols <= 0) {
        cout << "Invalid input." << endl;
        return 1;  
    }

    if (symbols == '1') {
	    string password = getPassword(length);
	    cout << "Generated Password: " << password << endl;
    }
    if (symbols == '2') {
	    string password = getPasswordAdvanced(length);
	    cout << "Generated Password: " << password << endl;
    }
    if (symbols == '3') {
	    string password = getPasswordCustom(length);
	    cout << "Generated Passsord: " << password << endl;
    }

    return 0;
}
