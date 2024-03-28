#pragma once

#include <string>
#include <vector>
#include "Client.h"

#define COMMISSION_RATE 0.01

class Bank {
private:
    std::string name;
    double bank_balance; 
    std::vector<Client*> clients;

public:
    Bank(const std::string& bank_name);
    std::string getName() const;
    void addLegalClient(const std::string& client_name, const std::string& account_id, double initial_balance);
    void addIndividualClient(const std::string& client_name, const std::string& account_id, double initial_balance);
    bool removeClient(const std::string& client_name);
    double getBankBalance() const;
    const std::vector<Client*>& getClients() const; 
    void increaseBankBalance(double amount); 
    double transferMoney(Client* sender, Client* recipient, double amount);
};