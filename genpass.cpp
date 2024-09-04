#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <cctype>
#include <vector>
#include <fstream>

using namespace std;

vector<string> passwordHistory;

string generatePassword(int length, const string& characters) {
    if (length <= 0 || characters.empty()) {
        return "";
    }

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

string generatePronounceablePassword(int length) {
    if (length <= 0) {
        return "";
    }

    static const string vowels = "aeiou";
    static const string consonants = "bcdfghjklmnpqrstvwxyz";

    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> vowelDist(0, vowels.size() - 1);
    uniform_int_distribution<> consonantDist(0, consonants.size() - 1);

    string password;
    password.reserve(length);

    bool useVowel = true;

    for (int i = 0; i < length; ++i) {
        if (useVowel) {
            password += vowels[vowelDist(generator)];
        } else {
            password += consonants[consonantDist(generator)];
        }
        useVowel = !useVowel;
    }

    return password;
}

int calculatePasswordStrength(const string& password) {
    int score = 0;
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSymbol = false;

    for (char c : password) {
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSymbol = true;
    }

    if (hasLower) score += 1;
    if (hasUpper) score += 1;
    if (hasDigit) score += 1;
    if (hasSymbol) score += 1;
    if (password.size() >= 8) score += 1;
    if (password.size() >= 12) score += 1;

    return score;
}

void displayPasswordStrength(int strength) {
    const int maxStrength = 6;
    string bar = "[";

    for (int i = 0; i < maxStrength; ++i) {
        if (i < strength) {
            bar += "#";
        } else {
            bar += " ";
        }
    }
    bar += "] ";

    string color;
    if (strength <= 2) {
        color = "\033[31m"; // Red for weak
        bar += "Weak";
    } else if (strength <= 4) {
        color = "\033[33m"; // Yellow for moderate
        bar += "Moderate";
    } else {
        color = "\033[32m"; // Green for strong
        bar += "Strong";
    }

    string reset = "\033[0m";
    cout << "Password Strength: " << color << bar << reset << endl;
}

string getPassword(int length, bool excludeSimilar) {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

    if (excludeSimilar) {
        string similarChars = "O0l1I";
        characters.erase(remove_if(characters.begin(), characters.end(),
                                   [&](char c) { return similarChars.find(c) != string::npos; }),
                         characters.end());
    }

    return generatePassword(length, characters);
}

string getPasswordAdvanced(int length, bool excludeSimilar) {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+{}[]',.";

    if (excludeSimilar) {
        string similarChars = "O0l1I";
        characters.erase(remove_if(characters.begin(), characters.end(),
                                   [&](char c) { return similarChars.find(c) != string::npos; }),
                         characters.end());
    }

    return generatePassword(length, characters);
}

string getPasswordCustom(int length, bool excludeSimilar) {
    string characters;
    cout << "Enter symbols which your password can include (e.g., abcABC123): ";
    cin >> characters;

    if (excludeSimilar) {
        string similarChars = "O0l1I";
        characters.erase(remove_if(characters.begin(), characters.end(),
                                   [&](char c) { return similarChars.find(c) != string::npos; }),
                         characters.end());
    }

    return generatePassword(length, characters);
}

void addToHistory(const string& password, const string& filename) {
    ofstream file(filename, ios::app);  // Open in append mode
    if (!file) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    file << password << endl;
}

void viewHistory(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file for reading: " << filename << endl;
        return;
    }

    string password;
    cout << "Password History:" << endl;
    while (getline(file, password)) {
        cout << password << endl;
    }
}

void clearHistory(const string& filename) {
    ofstream file(filename, ios::trunc);  // Open in truncate mode to clear contents
    if (!file) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    cout << "Password history cleared." << endl;
}

int main() {
    const string historyFilename = "password_history.txt";

    // Ensure the history file exists or create it
    ofstream file(historyFilename, ios::app);  // Open in append mode to create if it doesn't exist
    file.close();

    while (true) {
        int length;
        char choice;
        char excludeChoice;

        cout << "Enter the length of the password (0 to exit): ";
        cin >> length;

        if (length == 0) {
            // Save password history to file before exiting
            return 0;
        }

        if (cin.fail() || length <= 0) {
            cout << "Invalid input. Please enter a positive integer for the password length." << endl;
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }

        cout << "Choose a type of password:\n"
             << "1. Random letters and numbers\n"
             << "2. Random letters, numbers, and symbols\n"
             << "3. Custom symbols only\n"
             << "4. Pronounceable password\n"
             << "5. View password history\n"
             << "6. Clear password history\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice != '4' && choice != '5' && choice != '6') {
            cout << "Do you want to exclude similar characters like 'O', '0', 'l', '1', etc.? (y/n): ";
            cin >> excludeChoice;
        }

        bool excludeSimilar = (excludeChoice == 'y' || excludeChoice == 'Y');
        string password;

        switch (choice) {
            case '1':
                password = getPassword(length, excludeSimilar);
                break;
            case '2':
                password = getPasswordAdvanced(length, excludeSimilar);
                break;
            case '3':
                password = getPasswordCustom(length, excludeSimilar);
                break;
            case '4':
                password = generatePronounceablePassword(length);
                break;
            case '5':
                viewHistory(historyFilename);
                continue;
            case '6':
                clearHistory(historyFilename);
                continue;
            default:
                cout << "Invalid choice. Please enter 1, 2, 3, 4, 5, or 6." << endl;
                continue;
        }

        cout << "Generated Password: " << password << endl;

        // Add to history
        addToHistory(password, historyFilename);

        // Evaluate and display password strength
        int strength = calculatePasswordStrength(password);
        displayPasswordStrength(strength);

        // Ask if the user wants to generate a new password
        char generateNewPassword;
        cout << "Do you want to generate a new password? (y/n): ";
        cin >> generateNewPassword;

        if (generateNewPassword != 'y' && generateNewPassword != 'Y') {
            // Save password history to file before exiting
            return 0;
        }
    }

    // Save password history to file before exiting
    return 0;
}
