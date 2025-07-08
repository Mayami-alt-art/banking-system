#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h> // For password masking with _getch()

using namespace std;

void Administrator_Menu();
void userMenu(string username);
bool Administrator_Login();
bool userLogin(string &username);
void registerUser();
void depositToUser();
void withdrawCash(string username);
void checkBalance(string username);
void changePassword(string username, string userType);
bool validateUser(string username, string password, string &lineData);
string getMaskedPassword();
bool usernameExists(const string &username);

int main() {
    int choice;
    while (true) {
        cout << "\n****WELCOME TO      E-CASH SERVICES****\n";
        cout << "1. Administrator Login\n2. Normal User Login\n3. Exit\nChoose an option to proceed: ";
        cin >> choice;
        cout << "--------------------------------------------\n";

        if (choice == 1) {
            if (Administrator_Login()) Administrator_Menu();
        } else if (choice == 2) {
            string username;
            if (userLogin(username)) userMenu(username);
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}

string getMaskedPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

bool Administrator_Login() {
    string user, pass, storedUser, storedPass;
    cout << "Enter Admin Username: ";
    cin >> user;
    cout << "Enter Admin Password: ";
    pass = getMaskedPassword();

    ifstream file("admin.txt");
    file >> storedUser >> storedPass;
    file.close();

    if (user == storedUser && pass == storedPass) return true;

    cout << "Invalid admin credentials.\n";
    return false;
}

void Administrator_Menu() {
    int choice;
    while (true) {
        cout << "\n Welcome Admin \n";
        cout << "1. Register new Client \n2. Deposit money for client \n3. Reset your Password\n4. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) registerUser();
        else if (choice == 2) depositToUser();
        else if (choice == 3) changePassword("admin", "admin");
        else if (choice == 4) break;
        else cout << "Invalid choice.\n";
    }
}

bool usernameExists(const string &username) {
    string line, uname, pass;
    float bal;
    ifstream file("usersDB.txt");
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> uname >> pass >> bal;
        if (uname == username) return true;
    }
    return false;
}

void registerUser() {
    string user, pass;
    float balance = 0;
    cout << "New Username: ";
    cin >> user;

    if (usernameExists(user)) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    cout << "New Password: ";
    pass = getMaskedPassword();

    ofstream file("usersDB.txt", ios::app);
    file << user << " " << pass << " " << balance << endl;
    file.close();
    cout << "User registered successfully.\n";
}

bool userLogin(string &username) {
    string password, lineData;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    password = getMaskedPassword();

    if (validateUser(username, password, lineData)) return true;

    cout << "Invalid login.\n";
    return false;
}

void userMenu(string username) {
    int choice;
    while (true) {
        cout << "\n Welcome newUser \n";
        cout << "1. Withdraw Cash\n2. Check Balance\n3. Reset your Password\n4. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) withdrawCash(username);
        else if (choice == 2) checkBalance(username);
        else if (choice == 3) changePassword(username, "user");
        else if (choice == 4) break;
        else cout << "Invalid choice.\n";
    }
}

void depositToUser() {
    string user, line;
    float deposit;
    cout << "Enter username to deposit to: ";
    cin >> user;
    cout << "Enter deposit amount: ";
    cin >> deposit;

    ifstream inFile("usersDB.txt");
    ofstream outFile("temp.txt");

    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string uname, pass;
        float bal;
        ss >> uname >> pass >> bal;

        if (uname == user) {
            bal += deposit;
            outFile << uname << " " << pass << " " << bal << endl;
            found = true;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();
    remove("usersDB.txt");
    rename("temp.txt", "usersDB.txt");

    if (found) cout << "Deposit successful.\n";
    else cout << "User not found.\n";
}

void withdrawCash(string username) {
    string line, uname, pass;
    float amount, bal;
    cout << "Amount to withdraw: ";
    cin >> amount;

    ifstream inFile("usersDB.txt");
    ofstream outFile("temp.txt");

    bool success = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        ss >> uname >> pass >> bal;
        if (uname == username) {
            if (bal >= amount) {
                bal -= amount;
                cout << "Withdrawal successful.\n";
                success = true;
            } else {
                cout << "Insufficient balance.\n";
            }
            outFile << uname << " " << pass << " " << bal << endl;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();
    remove("usersDB.txt");
    rename("temp.txt", "usersDB.txt");
}

void checkBalance(string username) {
    string line, uname, pass;
    float bal;
    ifstream file("usersDB.txt");
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> uname >> pass >> bal;
        if (uname == username) {
            cout << "Your balance is: " << bal << endl;
            return;
        }
    }
    file.close();
}

void changePassword(string username, string userType) {
    string newPass, line, uname, pass;
    float bal;

    cout << "Enter new password: ";
    newPass = getMaskedPassword();

    if (userType == "admin") {
        ofstream file("admin.txt");
        file << username << " " << newPass;
        file.close();
        cout << "Admin password changed.\n";
        return;
    }

    ifstream inFile("usersDB.txt");
    ofstream outFile("temp.txt");

    while (getline(inFile, line)) {
        stringstream ss(line);
        ss >> uname >> pass >> bal;
        if (uname == username) {
            outFile << uname << " " << newPass << " " << bal << endl;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();
    remove("usersDB.txt");
    rename("temp.txt", "usersDB.txt");

    cout << "Password updated.\n";
}

bool validateUser(string username, string password, string &lineData) {
    string line;
    ifstream file("usersDB.txt");
    while (getline(file, line)) {
        stringstream ss(line);
        string uname, pass;
        float bal;
        ss >> uname >> pass >> bal;
        if (uname == username && pass == password) {
            lineData = line;
            return true;
        }
    }
    return false;
}
