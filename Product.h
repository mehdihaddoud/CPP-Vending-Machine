/**
 * @file Product.h
 * @author Mehdi Haddoud
 * @date 2023-02-27
 * @brief Product class that manipulates a product in a vending machine
 * */
#ifndef VENDING_MACHINE_PRODUCT_H
#define VENDING_MACHINE_PRODUCT_H


#include <string>
#include <utility>

/**
 * @class Product
 * @brief Product class representing a product in a vending machine
 * */
class Product {

public:
    /**
     * @brief Constructor of Product
     * @param price Price of the product
     * @param name Name of the product
     * */
    Product(double price, std::string name) : price(price), name(std::move(name)){}

    /**
     * @brief Function that returns the price of the product
     * @return The exact price of the product
     * */
    double getPrice() const {
        return price;
    }
    /**
     * @brief Function that returns the name of the product
     * @return the name of the product
     * */
    const std::string& getName() const {
        return name;
    }

private:

    /**
     * @var price
     * @brief The price of the product
     * */
    double price;

    /**
     * @var name
     * @brief the name of the product
     * */
    std::string name;

};


#endif //VENDING_MACHINE_PRODUCT_H
