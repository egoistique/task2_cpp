#pragma once

#include "Bank.h"

class BankingSystem {
private:
    std::vector<Bank*> banks;

public:
    BankingSystem();
    ~BankingSystem();
    void createBank(const std::string& bank_name);
    bool removeBank(const std::string& bank_name);
    double getBankBalance(const std::string& bank_name) const;
    const std::vector<Client*>& getBankClients(const std::string& bank_name) const;
    size_t getBankCount() const;
    void addIndividualClient(const std::string& bank_name, const std::string& client_name, const std::string& account_id, double initial_balance);
    void addLegalClient(const std::string& bank_name, const std::string& client_name, const std::string& account_id, double initial_balance);
    bool removeClient(const std::string& bank_name, const std::string& client_name);
    void increaseBankBalance(const std::string& bank_name, double amount);
    double transferMoney(const std::string& sender_bank_name, Client* sender, const std::string& recipient_bank_name, Client* recipient, double amount);
    std::vector<Bank*> getBanks() const;
    std::string getBankName(int index) const;
};


