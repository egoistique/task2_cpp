#include "Client.h"
#include "Account.h"
#include <vector>

Client::Client(const std::string& client_name, const std::string& account_id, double initial_balance, const std::string& bank_name)
    : name(client_name), bankName(bank_name), account(account_id, initial_balance) {}

std::string Client::getName() const {
    return name;
}

double Client::getBalance() const {
    return account.getBalance();
}

bool Client::deposit(double amount) {
    return account.deposit(amount);
}

bool Client::withdraw(double amount) {
    return account.withdraw(amount);
}

bool Client::transferMoney(Client* recipient, double amount) {
    return 0;
}

std::string Client::getBankName() const {
    return bankName;
}