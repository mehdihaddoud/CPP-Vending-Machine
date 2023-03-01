//
// Created by Mehdi Haddoud on 2023-02-11.
//
/**
 * @file vendingMachine.h
 * @author Mehdi Haddoud
 * @date 2023-02-27
 * @brief vendingMachine class to manipulate a vending machine
 * */

#ifndef VENDING_MACHINE_VENDINGMACHINE_H
#define VENDING_MACHINE_VENDINGMACHINE_H
#include "Product.h"
#include "Coin.h"
#include <iostream>
#include <regex>
#include <unordered_map>


/**
 * @class vendingMachine
 * @brief Class that represents a vending machine
 * */
class vendingMachine {

public:
    /**
     * @brief Constructor of the vendingMachine class
     * @param catalog Catalog variable used to initialize the catalog of the vending machine
     * */
    vendingMachine(std::unordered_map<Product*, int> catalog);

    /**
     * @brief empty the balance of the vending machine
     * @param out output stream
     * */
    void empty(std::ostream& out);

    /**
     * @brief Function that handles the buying process
     * @param input input stream
     * @param output output stream
     * */
    void buy(std::istream& input, std::ostream& output);

    /**
     * @brief Function that handles the money return once the buyer has given the money
     * @param difference Money difference to be returned
     * @param product product that has been bought
     * @param quantity Quantity of the product that has been bought
     * @param moneyGiven all the money that has been given by the user
     * @param moneyReturned money that should be returned at the end of the transaction
     * @param in input stream
     * @param out output stream
     * */
    void returnMoney(double difference,Product* product,int& quantity,std::unordered_map<Coin*,int>& moneyGiven, std::unordered_map<Coin*,int>& moneyReturned,std::istream& in, std::ostream& out) ;

    /**
     * @brief Function that handles the payment process
     * @param productPrice Price of the product that has been bought
     * @param moneyGiven map that stores all the coins given by the user
     * @param in input stream
     * @param out output stream
     * */
    double pay(double productPrice, std::unordered_map<Coin*,int>& moneyGiven, std::istream& in, std::ostream& out);

    /**
     * @brief add coins to the vending machine
     * @param money map containing all the coins to be added to the vending machine
     * */
    void fillBalance(std::unordered_map<Coin*,int>& moneyGiven);

    /**
     * @brief Remove coins from the vending machine
     * @param moneyReturned map containing all the coins that must be removed from the vending machine
     * */
    void withDrawFromBalance(const std::unordered_map<Coin*,int>& moneyReturned);

    /**
     * @brief display all the coins in the vending machine
     * @param out output stream
     * */
    void displayBalance(std::ostream& out) const;

    /**
     * @brief Function that returns a certain amount of coins to the user
     * @param difference Amount of coins that must be returned
     * @param moneyReturned
     * @param coins type of coins that will be returned
     * @param out output stream
     * */
    void returnCoin(double& difference, std::unordered_map<Coin*,int>& moneyReturned, Coin* coins, std::ostream& out);
    /**
     * @brief Function that assesses what is the most efficient set of coins that should be taken from the user in order to reduce the difference that must be returned
     * @param coin Type of coins that are assessed
     * @param newDifference New calculated difference
     * @param moneyGiven Map that contains all the coins given by the user
     * @param moneyKept Map that contains all the coins that should be kept from the user in order to minimize the difference to be returned
     * */
    void assessCoins(Coin* coin,double& newDifference,std::unordered_map<Coin*,int>& moneyGiven, std::unordered_map<Coin*,int>& moneyKept);

private:

    /**
     * @var catalog
     * @brief Catalog of products and their quantities
     * */
   std::unordered_map<Product*,int> catalog;

   /**
    * @var balance
    * @brief Data structure that contains all the coins in the vending machine
    * */
   std::unordered_map<Coin*,int> balance;
};

/**
 * @brief Function that prompts the user whether to continue buying
 * @param in input stream
 * @param output stream
 * */
bool continueSelection(std::istream& in, std::ostream& out);

void displayMapContent(const std::unordered_map<Coin*,int>& input, std::ostream& out);


#endif //VENDING_MACHINE_VENDINGMACHINE_H
