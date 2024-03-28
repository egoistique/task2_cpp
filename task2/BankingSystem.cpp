#pragma once

#include "BankingSystem.h"

BankingSystem::BankingSystem() {
}


BankingSystem::~BankingSystem() {
    for (auto bank : banks) {
        delete bank;
    }
}

void BankingSystem::createBank(const std::string& bank_name) {
    banks.push_back(new Bank(bank_name));
}

bool BankingSystem::removeBank(const std::string& bank_name) {
    for (auto it = banks.begin(); it != banks.end(); ++it) {
        if ((*it)->getName() == bank_name) {
            delete* it;
            banks.erase(it);
            return true;
        }
    }
    return false;
}

double BankingSystem::getBankBalance(const std::string& bank_name) const {
    for (const auto& bank : banks) {
        if (bank->getName() == bank_name) {
            return bank->getBankBalance();
        }
    }
    return 0.0; 
}

const std::vector<Client*>& BankingSystem::getBankClients(const std::string& bank_name) const {
    static std::vector<Client*> emptyClients; 
    for (const auto& bank : banks) {
        if (bank->getName() == bank_name) {
            return bank->getClients();
        }
    }
    return emptyClients;
}

size_t BankingSystem::getBankCount() const {
    return banks.size();
}

void BankingSystem::addIndividualClient(const std::string& bank_name, const std::string& client_name, const std::string& account_id, double initial_balance) {
    for (auto& bank : banks) {
        if (bank->getName() == bank_name) {
            bank->addIndividualClient(client_name, account_id, initial_balance);
            return;
        }
    }
}

void BankingSystem::addLegalClient(const std::string& bank_name, const std::string& client_name, const std::string& account_id, double initial_balance) {
    for (auto& bank : banks) {
        if (bank->getName() == bank_name) {
            bank->addLegalClient(client_name, account_id, initial_balance);
            return;
        }
    }
}

bool BankingSystem::removeClient(const std::string& bank_name, const std::string& client_name) {
    for (auto& bank : banks) {
        if (bank->getName() == bank_name) {
            return bank->removeClient(client_name);
        }
    }
    return false;
}

double BankingSystem::transferMoney(const std::string& sender_bank_name, Client* sender, const std::string& recipient_bank_name, Client* recipient, double amount) {
    for (auto& bank : banks) {
        if (bank->getName() == sender_bank_name) {
            double commission = amount * COMMISSION_RATE;
            double totalAmount = amount + commission;
            if (sender->transferMoney(recipient, totalAmount)) {
                sender->withdraw(totalAmount);
                recipient->deposit(amount);

                bank->increaseBankBalance(commission);

                return commission;
                
            }
            else  return 0.0;
        }
    }
    return 0.0;
}

std::vector<Bank*> BankingSystem::getBanks() const {
    return banks;
}

std::string BankingSystem::getBankName(int index) const {
    if (index >= 0 && index < banks.size()) {
        return banks[index]->getName();
    }
    else {
        return "Invalid index";
    }
}
