#pragma once

#include <string>

class Account {
private:
    std::string accountId; 
    double balance;
public:
    Account(const std::string& id, double initial_balance);
    std::string getAccountId() const;
    double getBalance() const;
    bool deposit(double amount);
    bool withdraw(double amount);
};