#pragma once

#include <string>
#include "Account.h"

class Client {
protected:
    std::string name;
    std::string bankName; 
    Account account;

public:
    Client(const std::string& client_name, const std::string& account_id, double initial_balance, const std::string& bank_name);
    std::string getName() const;
    double getBalance() const;
    bool deposit(double amount);
    bool withdraw(double amount);
    virtual bool  transferMoney(Client* recipient, double amount);
    std::string getBankName() const; 
};
