/**
 * @file main.cpp
 *
 * @brief A program that simulates a vending machine.
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include "vendingMachine.h"

#define NB_OPTIONS 3

/**
 * @brief Launches the main loop of the vending machine.
 *
 * @param it A pointer to the vending machine object.
 * @param in The input stream for reading user input.
 * @param out The output stream for displaying messages to the user.
 */
void launch(vendingMachine* it,std::istream& in, std::ostream& out);

/**
 * @brief The main function of the program.
 *
 * @return 0 if the program runs successfully.
 */
int main() {

    std::ifstream inputFile;

    inputFile.open("/Users/mehdihaddoud/Documents/C-CPP/cpp/object-oriented-design/vending-machine/vendingMachine_init");

    std::string productName;
    double price;
    int quantity;

    std::unordered_map<Product*,int> productCatalog;

    while(!inputFile.eof())
    {
        inputFile >> productName >> price >> quantity;
        auto newEntry = new Product(price,productName);
        productCatalog[newEntry] = quantity;
    }

    inputFile.close();

    auto it = new vendingMachine(productCatalog);

    launch(it,std::cin,std::cout);


    return 0;
}

void launch(vendingMachine* it,std::istream& in, std::ostream& out)
{
    while(true)
    {
        out << "Choose action : \n 1)Buy \n 2)Check balance\n 3)Empty()\n->";

        std::string selection;

        do {
            do{
                in >> selection;
            }while(!std::regex_match(selection,std::regex("^[1-9][0-9]*$")));
        }while(std::stoi(selection) > NB_OPTIONS || std::stoi(selection) <= 0);

        switch (std::stoi(selection)) {
            case 1:
                it->buy(in,out);
                break;

            case 2:
                it->displayBalance(out);
                break;

            case 3:
                it->empty(out);
                break;
        }

    }

}