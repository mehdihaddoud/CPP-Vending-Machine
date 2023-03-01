/**
 * @file Coin.h
 * @author Mehdi Haddoud
 * @date 2023-02-27
 * @brief Coin class that manipulates money coins
 * */

#ifndef VENDING_MACHINE_COIN_H
#define VENDING_MACHINE_COIN_H

/**
 * @class Coin
 * @brief Class representing a money coin to be used in vending machines
 * */
class Coin {

public:

    /**
     * @brief Constructor of Coin
     * @param value Value that the coin has
     * */
    Coin(double value) : value(value) {}

    /**
     * @brief Function that returns the exact value of the coin
     * @return Exact value representing the coin
     * */
    double getValue() const {
        return value;
    }

private:
    /**
     * @var value
     * @brief Exact value representing the coin
     * */
    double value;
};


#endif //VENDING_MACHINE_COIN_H
