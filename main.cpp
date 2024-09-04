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



int main() {
    int length;
    char symbols;
    cout << "Enter the length of the password: ";
    cin >> length;
    cout << "Can it include different symbols as !@#$%^&*()_+{} etc? (y/n): ";
    cin >> symbols;

    if (cin.fail() || length <= 0) {
        cout << "Invalid input. Please enter a positive integer for the password length." << endl;
        return 1;  
    }

    if (symbols == 'y') {
	    cout << "haha" << endl;
	    string password = getPasswordAdvanced(length);
	    cout << "Generated Password: " << password << endl;
    } else {
	    cout << "hoho" << endl;
	    string password = getPassword(length);
	    cout << "Generated Password: " << password << endl;
    }

    return 0;
}
