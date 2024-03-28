#include <iostream>
#include <cassert>

#include "BankingSystem.h"

void testBankCreation() {
    std::cout << "Testing bank creation..." << std::endl;
    std::vector<std::string> bankNames = { "BankA", "BankB", "BankC" };
    BankingSystem bankingSystem;

    for (const auto& name : bankNames) {
        bankingSystem.createBank(name);
    }

    std::cout << "Successfully created banks: " << std::endl;
    for (const auto& name : bankNames) {
        std::cout << name << " Balance: $" << bankingSystem.getBankBalance(name) << std::endl;
    }

    std::cout << std::endl;

    assert(bankingSystem.getBankCount() == bankNames.size());
    std::cout << "Bank creation test passed." << std::endl;
}

void testAddClient() {
    std::cout << "Testing adding clients to banks..." << std::endl;
    std::vector<std::pair<std::string, std::string>> clientData = {
        {"BankA", "Vasya"},
        {"BankA", "Petya"},
        {"BankB", "Dima"},
        {"BankC", "Masha"}
    };
    BankingSystem bankingSystem;

    for (const auto& data : clientData) {
        bankingSystem.createBank(data.first);
        bankingSystem.addIndividualClient(data.first, data.second, "12345", 1000);
    }

    std::cout << "Successfully created clients: " << std::endl;
    for (const auto& data : clientData) {
        std::cout << "In bank " << data.first << ": " << data.second << std::endl;
    }

    std::cout << "Adding clients test passed." << std::endl;
    std::cout << std::endl;
}


void testRemoveClient() {
    std::cout << "Testing removing clients from bank..." << std::endl;
    BankingSystem bankingSystem;
    bankingSystem.createBank("BankA");
    bankingSystem.addIndividualClient("BankA", "Vasya", "12345", 1000);
    bankingSystem.addLegalClient("BankA", "Inc.", "67890", 5000);

    assert(bankingSystem.removeClient("BankA", "Vasya"));
    assert(bankingSystem.removeClient("BankA", "Inc."));
    assert(!bankingSystem.removeClient("BankA", "NonExistentClient"));

    const auto& clients = bankingSystem.getBankClients("BankA");
    assert(clients.empty());
    std::cout << "Removing clients test passed." << std::endl;
    std::cout << std::endl;
}


void testIndividualTransfer() {
    std::cout << "Testing individual client money transfer..." << std::endl;

    BankingSystem bankingSystem;
    bankingSystem.createBank("BankA");

    bankingSystem.addIndividualClient("BankA", "Vasya", "12345", 1000);
    bankingSystem.addIndividualClient("BankA", "Petya", "67890", 2000);

    const auto& clients = bankingSystem.getBankClients("BankA");
    Client* client1 = clients[0];
    Client* client2 = clients[1];

    std::cout << "Client 1 balance before transfer: " << client1->getBalance() << std::endl;
    std::cout << "Client 2 balance before transfer: " << client2->getBalance() << std::endl;

    double amount = 500;
    std::cout << "Transfer amount: $" << amount << std::endl;

    double commission = bankingSystem.transferMoney("BankA", client1, "BankA", client2, amount);

    double expectedBalance1 = 1000 - amount - commission;
    double expectedBalance2 = 2000 + amount;

    std::cout << "Bank sender: $" << bankingSystem.getBankBalance("BankA") << std::endl;
    std::cout << "Client 1 balance after transfer: " << client1->getBalance() << std::endl;
    std::cout << "Client 2 balance after transfer: " << client2->getBalance() << std::endl;

    assert(client1->getBalance() == expectedBalance1);
    assert(client2->getBalance() == expectedBalance2);

    std::cout << "Individual client money transfer test passed." << std::endl;
    std::cout << std::endl;
}

void testLegalToLegalTransfer() {
    std::cout << "Testing transfer between legal clients of the same bank..." << std::endl;

    BankingSystem bankingSystem;
    bankingSystem.createBank("BankA");

    bankingSystem.addLegalClient("BankA", "Inc.", "12345", 10000);
    bankingSystem.addLegalClient("BankA", "Corp.", "67890", 20000);

    const auto& clients = bankingSystem.getBankClients("BankA");
    Client* client1 = clients[0];
    Client* client2 = clients[1];

    std::cout << "Client 1 balance before transfer: " << client1->getBalance() << std::endl;
    std::cout << "Client 2 balance before transfer: " << client2->getBalance() << std::endl;

    double amount = 5000;
    std::cout << "Transfer amount: $" << amount << std::endl;

    double commission = bankingSystem.transferMoney("BankA", client1, "BankA", client2, amount);

    double expectedBalance1 = 10000 - amount - commission;
    double expectedBalance2 = 20000 + amount;

    std::cout << "Bank sender: $" << bankingSystem.getBankBalance("BankA") << std::endl;
    std::cout << "Client 1 balance after transfer: " << client1->getBalance() << std::endl;
    std::cout << "Client 2 balance after transfer: " << client2->getBalance() << std::endl;

    assert(client1->getBalance() == expectedBalance1);
    assert(client2->getBalance() == expectedBalance2);

    std::cout << "Legal to legal client money transfer test passed." << std::endl;
    std::cout << std::endl;
}


void testLegalToIndividualTransfer() {
    std::cout << "Testing transfer from legal client to individual client in different banks..." << std::endl;
    BankingSystem bankingSystem;
    bankingSystem.createBank("BankA");
    bankingSystem.createBank("BankB");

    bankingSystem.addLegalClient("BankA", "Inc.", "12345", 10000);
    bankingSystem.addIndividualClient("BankB", "Vasya", "67890", 1000);

    const auto& clients1 = bankingSystem.getBankClients("BankA");
    Client* client1 = clients1[0];
    
    const auto& clients2 = bankingSystem.getBankClients("BankB");
    Client* client2 = clients2[0];

    std::cout << "Legal client balance before transfer: " << client1->getBalance() << std::endl;
    std::cout << "Individual client balance before transfer: " << client2->getBalance() << std::endl;

    double amount = 1500;
    std::cout << "Transfer amount: $" << amount << std::endl;

    double commission = bankingSystem.transferMoney("BankA", client1, "BankB", client2, amount);

    double expectedBalance1 = 10000 - amount - commission;
    double expectedBalance2 = 1000 + amount;

    std::cout << "Bank sender: $" << bankingSystem.getBankBalance("BankA") << std::endl;
    std::cout << "Legal client balance after transfer: " << client1->getBalance() << std::endl;
    std::cout << "Individual client balance after transfer: " << client2->getBalance() << std::endl;

    assert(client1->getBalance() == expectedBalance1);
    assert(client2->getBalance() == expectedBalance2);

    std::cout << "Legal to individual client money transfer test passed." << std::endl;
    std::cout << std::endl;
}

void testIndividualToDifferentBankTransfer() {
    std::cout << "Testing transfer from individual client to client in a different bank..." << std::endl;

    BankingSystem bankingSystem;
    bankingSystem.createBank("BankA");
    bankingSystem.createBank("BankB");

    bankingSystem.addIndividualClient("BankA", "Petya", "12345", 2000);
    bankingSystem.addIndividualClient("BankB", "Vasya", "67890", 3000);

    const auto& clients1 = bankingSystem.getBankClients("BankA");
    Client* client1 = clients1[0];

    const auto& clients2 = bankingSystem.getBankClients("BankB");
    Client* client2 = clients2[0];

    std::cout << "Individual client in bank 1 balance before transfer: " << client1->getBalance() << std::endl;
    std::cout << "Individual client in bank 2 balance before transfer: " << client2->getBalance() << std::endl;

    double amount = 1500;
    std::cout << "Transfer amount: $" << amount << std::endl;

    double commission = bankingSystem.transferMoney("BankA", client1, "BankB", client2, amount);

    double expectedBalance1 = 2000;
    double expectedBalance2 = 3000;

    std::cout << "Bank sender: $" << bankingSystem.getBankBalance("BankA") << std::endl;
    std::cout << "Individual client in bank 1 balance after transfer: " << client1->getBalance() << std::endl;
    std::cout << "Individual client in bank 2 balance after transfer: " << client2->getBalance() << std::endl;

    assert(client1->getBalance() == expectedBalance1);
    assert(client2->getBalance() == expectedBalance2);

    std::cout << "Individual to different bank client money transfer test passed." << std::endl;
    std::cout << std::endl;
}


void displayMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1 - Run tests" << std::endl;
    std::cout << "2 - Create bank" << std::endl;
    std::cout << "3 - View banks" << std::endl;
    std::cout << "4 - Create individual client" << std::endl;
    std::cout << "5 - Create legal client" << std::endl;
    std::cout << "6 - View all clients" << std::endl;
    std::cout << "7 - Make transfer" << std::endl;
    std::cout << "0 - Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void handleBankCreation(BankingSystem& bankingSystem, std::vector<Bank*>& banks) {
    std::string bankName;
    std::cout << "Enter bank name: ";
    std::cin >> bankName;
    bankingSystem.createBank(bankName);
    banks = bankingSystem.getBanks();
}

void displayBanks(const std::vector<Bank*>& banks) {
    std::cout << "Banks:" << std::endl;
    for (const auto& bank : banks) {
        std::cout << bank->getName() << std::endl;
    }
}

void createClient(BankingSystem& bankingSystem, std::vector<Bank*>& banks, bool isIndividual) {
    if (bankingSystem.getBankCount() > 0) {
        int bankIndex;
        std::cout << "Enter bank index to create client: ";
        std::cin >> bankIndex;
        if (bankIndex >= 0 && bankIndex < bankingSystem.getBankCount()) {
            std::string clientName, accountId;
            double initialBalance;
            std::cout << "Enter client name: ";
            std::cin >> clientName;
            std::cout << "Enter account ID: ";
            std::cin >> accountId;
            std::cout << "Enter initial balance: ";
            std::cin >> initialBalance;
            if (isIndividual) {
                bankingSystem.addIndividualClient(bankingSystem.getBankName(bankIndex), clientName, accountId, initialBalance);
            }
            else {
                bankingSystem.addLegalClient(bankingSystem.getBankName(bankIndex), clientName, accountId, initialBalance);
            }
            banks = bankingSystem.getBanks();
        }
        else {
            std::cout << "Invalid bank index." << std::endl;
        }
    }
    else {
        std::cout << "No banks created yet." << std::endl;
    }
}

void enterBankAndClientIndex(const BankingSystem& bankingSystem, const std::string& prompt, int& bankIndex, int& clientIndex) {
    std::cout << prompt;
    std::cin >> bankIndex;
    if (bankIndex >= 0 && bankIndex < bankingSystem.getBankCount()) {
        const std::vector<Client*>& bankClients = bankingSystem.getBankClients(bankingSystem.getBankName(bankIndex));
        std::cout << "Enter client index: ";
        std::cin >> clientIndex;
        if (clientIndex < 0 || clientIndex >= bankClients.size()) {
            std::cout << "Invalid client index." << std::endl;
            clientIndex = -1;
        }
    }
    else {
        std::cout << "Invalid bank index." << std::endl;
        bankIndex = -1;
    }
}

void performTransfer(BankingSystem& bankingSystem) {
    int senderBankIndex, senderClientIndex, recipientBankIndex, recipientClientIndex;
    double amount;

    std::cout << "Enter sender bank index: ";
    enterBankAndClientIndex(bankingSystem, "Enter sender bank index: ", senderBankIndex, senderClientIndex);
    if (senderBankIndex == -1 || senderClientIndex == -1) return;

    std::cout << "Enter recipient bank index: ";
    enterBankAndClientIndex(bankingSystem, "Enter recipient bank index: ", recipientBankIndex, recipientClientIndex);
    if (recipientBankIndex == -1 || recipientClientIndex == -1) return;

    std::cout << "Enter transfer amount: $";
    std::cin >> amount;

    double senderClientBalanceBefore = bankingSystem.getBankClients(bankingSystem.getBankName(senderBankIndex))[senderClientIndex]->getBalance();
    double recipientClientBalanceBefore = bankingSystem.getBankClients(bankingSystem.getBankName(recipientBankIndex))[recipientClientIndex]->getBalance();

    double commission = bankingSystem.transferMoney(
        bankingSystem.getBankName(senderBankIndex),
        bankingSystem.getBankClients(bankingSystem.getBankName(senderBankIndex))[senderClientIndex],
        bankingSystem.getBankName(recipientBankIndex),
        bankingSystem.getBankClients(bankingSystem.getBankName(recipientBankIndex))[recipientClientIndex],
        amount
    );

    std::cout << "Transfer completed." << std::endl;
    std::cout << "Sender client balance before transfer: $" << senderClientBalanceBefore << std::endl;
    std::cout << "Recipient client balance before transfer: $" << recipientClientBalanceBefore << std::endl;
    std::cout << "Sender client balance after transfer: $" << bankingSystem.getBankClients(bankingSystem.getBankName(senderBankIndex))[senderClientIndex]->getBalance() << std::endl;
    std::cout << "Recipient client balance after transfer: $" << bankingSystem.getBankClients(bankingSystem.getBankName(recipientBankIndex))[recipientClientIndex]->getBalance() << std::endl;
}

int main() {
    int choice;
    bool exit = false;
    BankingSystem bankingSystem;
    std::vector<Bank*> banks;
    std::string bankName = "";

    while (!exit) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            testBankCreation();
            testAddClient();
            testRemoveClient();
            testIndividualTransfer();
            testLegalToLegalTransfer();
            testLegalToIndividualTransfer();
            testIndividualToDifferentBankTransfer();
            break;
        case 2:
            handleBankCreation(bankingSystem, banks);
            break;
        case 3:
            displayBanks(banks);
            break;
        case 4:
            createClient(bankingSystem, banks, true);            
            break;

        case 5:
            createClient(bankingSystem, banks, false);
            break;
        case 6:
            std::cout << "Banks:" << std::endl;
            for (size_t i = 0; i < bankingSystem.getBankCount(); ++i) {
                bankName = bankingSystem.getBankName(i);
                std::cout << "Bank: " << bankName << std::endl;

                const auto& clients = bankingSystem.getBankClients(bankName);
                for (const auto& client : clients) {
                    std::cout << "   - " << client->getName() << std::endl;
                }
            }
            break;


        case 7:
            if (bankingSystem.getBankCount() > 0) {
                performTransfer(bankingSystem);
            }
            else {
                std::cout << "No banks created yet." << std::endl;
            }
            break;
        case 0:
            exit = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}