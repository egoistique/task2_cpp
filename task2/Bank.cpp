#include "Bank.h"
#include "LegalClient.cpp"
#include "IndividualClient.cpp"

Bank::Bank(const std::string& bank_name) : name(bank_name), bank_balance(0) {}

void Bank::addLegalClient(const std::string& client_name, const std::string& account_id, double initial_balance) {
    LegalClient* client = new LegalClient(client_name, account_id, initial_balance, this->getName());
    clients.push_back(client);
}

void Bank::addIndividualClient(const std::string& client_name, const std::string& account_id, double initial_balance) {
    IndividualClient* client = new IndividualClient(client_name, account_id, initial_balance, this->getName());
    clients.push_back(client);
}

std::string Bank::getName() const {
    return name;
}

bool Bank::removeClient(const std::string& client_name) {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->getName() == client_name) {
            delete* it;
            clients.erase(it);
            return true;
        }
    }
    return false;
}

double Bank::getBankBalance() const {
    return bank_balance;
}

const std::vector<Client*>& Bank::getClients() const {
    return clients;
}

void Bank::increaseBankBalance(double amount) {
    bank_balance += amount;
}

double Bank::transferMoney(Client* sender, Client* recipient, double amount) {
    if (!sender || !recipient)
        return 0.0;

    double commission = sender->transferMoney(recipient, amount);

    return commission;
}
