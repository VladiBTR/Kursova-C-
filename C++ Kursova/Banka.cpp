#include <iostream>
#include <string>
#include <list>  
#include <unordered_map>
#include <limits>  

using namespace std;

class Account {
private:
    int accountNumber;
    string bankName;
    string accountType; 

public:
    // konstruktor 
    Account(int accNo, string bank, string type) : accountNumber(accNo), bankName(bank), accountType(type) {}

    int getAccountNumber() const { return accountNumber; }
    string getBankName() const { return bankName; }
    string getAccountType() const { return accountType; }

    // za sortirane i printirane
    virtual string toString() const {
        return "Account Number: " + to_string(accountNumber) + "\nBank Name: " + bankName + "\nAccount Type: " + accountType;
    }
};

class PersonalAccount : public Account {
private:
    string accountHolder;
    double balance;

public:
    PersonalAccount(int accNo, string bank, string type, string holder, double bal) 
        : Account(accNo, bank, type), accountHolder(holder), balance(bal) {}

    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }

    string toString() const override {
        return Account::toString() + "\nAccount Holder: " + accountHolder + "\nBalance: " + to_string(balance);
    }
};

class Bank {
public:
    static void main() {
        list<PersonalAccount> accounts;
        int accountCount = 5;
        int currentCount = 0, savingsCount = 0;

        for (int i = 0; i < accountCount; ++i) {
            int accNo;
            string bank, type, holder;
            double balance;

            while (true) {
                cout << "Enter account number: ";
                cin >> accNo;

                if (cin.fail()) {
                    cout << "Invalid. Please enter a valid integer for account number." << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                } else {
                    break;  
                }
            }

            cout << "Enter bank name: ";
            cin.ignore();  
            getline(cin, bank);

            
            while (true) {
                cout << "Enter account type (Current/Savings): ";
                getline(cin, type);
                if (type == "Current" || type == "Savings") {
                    break;  
                }
                cout << "Invalid. Please enter 'Current' or 'Savings'." << endl;
            }

            cout << "Enter account holder name: ";
            getline(cin, holder);

            cout << "Enter balance: ";
            cin >> balance;

       
            PersonalAccount account(accNo, bank, type, holder, balance);
            accounts.push_back(account);

            
            if (type == "Current") {
                ++currentCount;
            } else if (type == "Savings") {
                ++savingsCount;
            }
        }

        
        cout << "\n=== Account Information ===\n";
        for (const auto &account : accounts) {
            cout << account.toString() << endl << "------------------" << endl;
        }

        
        unordered_map<string, double> accountHolderBalanceMap;
        unordered_map<string, int> accountHolderCountMap;

        for (const auto &account : accounts) {
            string holder = account.getAccountHolder();
            accountHolderBalanceMap[holder] += account.getBalance();
            accountHolderCountMap[holder]++;
        }

        cout << "\n=== Total Balance for Account Holders with Multiple Accounts ===\n";
        for (const auto &entry : accountHolderCountMap) {
            if (entry.second >= 2) {  
                cout << "Account Holder: " << entry.first
                     << " | Total Balance: " << accountHolderBalanceMap[entry.first] << endl;
            }
        }

        cout << "\nNumber of Current Accounts: " << currentCount << endl;
        cout << "Number of Savings Accounts: " << savingsCount << endl;
    }
};

int main() {
    Bank::main();
    return 0;
}
