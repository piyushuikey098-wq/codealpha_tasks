#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

const string FILE_NAME = "users.txt";

// Validate username
bool isValidUsername(const string& username) {
    if (username.length() < 3 || username.length() > 20) {
        return false;
    }

    for (char ch : username) {
        if (!isalnum(static_cast<unsigned char>(ch)) && ch != '_') {
            return false;
        }
    }

    return true;
}

// Validate password
bool isValidPassword(const string& password) {
    return password.length() >= 8;
}

// Check whether username already exists
bool usernameExists(const string& username) {
    ifstream file(FILE_NAME);

    string storedUsername, storedPassword;

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            return true;
        }
    }

    return false;
}

// Register a new user
void registerUser() {
    string username, password;

    cout << "\n========== REGISTRATION ==========\n";

    cout << "Enter username (3-20 characters, letters, digits, _): ";
    cin >> username;

    if (!isValidUsername(username)) {
        cout << "Error: Invalid username format.\n";
        return;
    }

    if (usernameExists(username)) {
        cout << "Error: Username already exists. Try another username.\n";
        return;
    }

    cout << "Enter password (minimum 8 characters): ";
    cin >> password;

    if (!isValidPassword(password)) {
        cout << "Error: Password must contain at least 8 characters.\n";
        return;
    }

    ofstream file(FILE_NAME, ios::app);

    if (!file) {
        cout << "Error: Unable to save user details.\n";
        return;
    }

    file << username << " " << password << "\n";
    file.close();

    cout << "Registration successful!\n";
}

// Login an existing user
void loginUser() {
    string username, password;

    cout << "\n========== LOGIN ==========\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "Error: No registered users found. Please register first.\n";
        return;
    }

    string storedUsername, storedPassword;
    bool loginSuccessful = false;

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username &&
            storedPassword == password) {
            loginSuccessful = true;
            break;
        }
    }

    file.close();

    if (loginSuccessful) {
        cout << "Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "Error: Invalid username or password.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "    LOGIN AND REGISTRATION SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }

    } while (choice != 3);

    return 0;
}