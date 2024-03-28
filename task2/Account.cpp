#include "Account.h"
#include <iostream>

Account::Account(const std::string& id, double initial_balance) : accountId(id), balance(initial_balance) {}

std::string Account::getAccountId() const {
    return accountId;
}

double Account::getBalance() const {
    return balance;
}

bool Account::deposit(double amount) {
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    else {
        std::cout << "Insufficient funds for withdrawal." << std::endl;
        return false;
    }
}
