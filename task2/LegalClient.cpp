#include <iostream>
#include <vector>
#include "Client.h"

class LegalClient : public Client {
public:
    LegalClient(const std::string& client_name, const std::string& account_id, double initial_balance, const std::string& bank_name)
        : Client(client_name, account_id, initial_balance, bank_name) {}

    bool transferMoney(Client* recipient, double totalAmount) override {
        std::cout << "Transfer $" << totalAmount << " from " << getName() << " to " << recipient->getName() << std::endl;

        return (getBalance() >= totalAmount) ? true : false;
    }
};

