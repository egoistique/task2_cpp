#include <iostream>
#include <vector>
#include "Client.h"

class IndividualClient : public Client {
public:
    IndividualClient(const std::string& client_name, const std::string& account_id, double initial_balance, const std::string& bank_name)
        : Client(client_name, account_id, initial_balance, bank_name) {}

    bool transferMoney(Client* recipient, double totalAmount) override {
        if (recipient->getBankName() == getBankName()) {
            std::cout << "Transfer $" << totalAmount << " from " << getName() << " to " << recipient->getName() << std::endl;
            return (getBalance() >= totalAmount) ? true : false;
        }
        else {
            std::cout << "Cannot transfer money to a client in a different bank." << std::endl;
            return false;
        }
    }

};
