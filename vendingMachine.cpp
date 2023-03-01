//
// Created by Mehdi Haddoud on 2023-02-11.
//

#include "vendingMachine.h"
#include <cmath>
#include <utility>

/**
 * @var v0_05
 * @brief Coin of value 0.05$
 * */
Coin* v0_05 = new Coin(0.05);
/**
 * @var v0_10
 * @brief Coin of value 0.10$
 * */
Coin* v0_10 = new Coin(0.1);

/**
 * @var v0_25
 * @brief Coin of value 0.25$
 * */
Coin* v0_25 = new Coin(0.25);

/**
 * @var v1_00
 * @brief Coin of value 1.00$
 * */
Coin* v1_00 = new Coin(1.0);

/**
 * @var v5_00
 * @brief Coin of value 5.00$
 * */
Coin* v5_00 = new Coin(5.0);

vendingMachine::vendingMachine(std::unordered_map<Product*, int> catalog) : catalog(std::move(catalog))
{
    this->balance[v0_05] = 100;
    this->balance[v0_10] = 50;
    this->balance[v0_25] = 30;
    this->balance[v1_00] = 10;
    this->balance[v5_00] = 5;
}


void vendingMachine::buy(std::istream &input, std::ostream &output) {

    do{
        std::string selection;

        int i  = 0;

        for (auto product : this->catalog)
        {

            output << "Product " << i + 1 << " : " <<product.first->getName() << " ("<< product.first->getPrice()<< "$)"<< '\t';

            output << "Quantity  : " << product.second << '\n';

            i++;
        }

        output << "Select a product number : \n";

        do {
            do{
                input >> selection;
            }while(!std::regex_match(selection,std::regex("^[1-9][0-9]*$")));
        }while(std::stoi(selection) > i);

        auto it = this->catalog.begin();

        std::advance(it,std::stoi(selection) -1 );

        if(it->second > 0)
        {
            output << '\n';

            output << "Enter quantity : \n";

            bool restart = true;

            do {
                do{
                    input >> selection;
                }while(!std::regex_match(selection,std::regex("^[1-9][0-9]*$")));

                if(std::stoi(selection) > it->second)
                {

                    restart = true;

                    output << "Not enough quantity, enter new number : \n";
                }
                else
                    restart = false;

            }while(restart);

            int quantity = std::stoi(selection);

            this->catalog[it->first] -= quantity; //Make a piece a code that return quantity when the transaction fails

            double toPay = it->first->getPrice() * std::stoi(selection);

            output << "Amount to pay : " << toPay << "$"<< '\n';

            std::unordered_map<Coin*,int> moneyGiven;

            moneyGiven[v0_05] = 0;

            moneyGiven[v0_10] = 0;

            moneyGiven[v0_25] = 0;

            moneyGiven[v1_00] = 0;

            moneyGiven[v5_00] = 0;

            std::unordered_map<Coin*,int> moneyReturned;

            moneyReturned[v0_05] = 0;

            moneyReturned[v0_10] = 0;

            moneyReturned[v0_25] = 0;

            moneyReturned[v1_00] = 0;

            moneyReturned[v5_00] = 0;

            double difference = pay(toPay, moneyGiven, input, output);

            returnMoney(difference,it->first,quantity,moneyGiven,moneyReturned,input,output);

        }
        else
            output << "Product is out of stock.\n";


    }while(continueSelection(input,output));

}

bool continueSelection(std::istream& in, std::ostream& out){

    std::string answer;

    out << "Continue? (y/n)\n";

    do{

        in >> answer;

    }while(!std::regex_match(answer,std::regex("^y|n$")));

    if(answer == "y")
        return true;
    else
        return false;

}

void vendingMachine::returnMoney(double difference,Product* product,int& quantity,std::unordered_map<Coin*,int>& moneyGiven, std::unordered_map<Coin*,int>& moneyReturned, std::istream& in,std::ostream& out) {

    returnCoin(difference, moneyReturned, v5_00, out);

    returnCoin(difference, moneyReturned, v1_00, out);

    returnCoin(difference, moneyReturned, v0_25, out);

    returnCoin(difference, moneyReturned, v0_10, out);

    returnCoin(difference, moneyReturned, v0_05, out);

    bool doTransaction = false;

    if (difference > 0.05) {
        out << "Not enough coins in the machine to return : " << difference
            << "$.\n Would you like to proceed with the payment?(y/n)\n";

        std::string answer;

        do {
            in >> answer;

        } while (!std::regex_match(answer, std::regex("^y|n$")));

        if (answer == "y")
            doTransaction = true;

    } else
        doTransaction = true;

    if (doTransaction)
    {

        fillBalance(moneyGiven);

        out << "Returning : \n";

        displayMapContent(moneyReturned, out);

        withDrawFromBalance(moneyReturned);

    }
    else
    {
        out << "Returning : \n";

        this->catalog[product] += quantity;

        displayMapContent(moneyGiven,out);
    }

}

double vendingMachine::pay(double productPrice, std::unordered_map<Coin*,int>& moneyGiven, std::istream& in, std::ostream& out) {

    double amountEntered = 0;

    bool abort = false;

    out << "Enter coins ('q' to abort operator) : \n";

    out << "(1) 0.05 $ \n";

    out << "(2) 0.10 $\n";

    out << "(3) 0.25 $\n";

    out << "(4) 1.00 $\n";

    out << "(5) 5.00 $\n";

    std::string selection;

    std::unordered_map<Coin*, int>::iterator it; //stopped debugging here

    double difference = productPrice;

    while(difference > 0) {

        do {
            in >> selection;

        } while (!std::regex_match(selection, std::regex("^[1-5]|q$")));

        if (selection == "q")
        {
            abort = true;

            break;
        }

        switch (std::stoi(selection))
        {

            case 1 :


                it = moneyGiven.find(v0_05);

                it->second += 1;

                amountEntered+= 0.05;

                break;

            case 2 :

                amountEntered+= 0.10;

                it = moneyGiven.find(v0_10);

                it->second += 1;

                break;

            case 3 :

                amountEntered+= 0.25;

                it = moneyGiven.find(v0_25);

                it->second += 1;

                break;

            case 4 :

                amountEntered+= 1.0;

                it = moneyGiven.find(v1_00);

                it->second += 1;

                break;

            case 5 :

                amountEntered+= 5.0;

                it = moneyGiven.find(v5_00);

                it->second += 1;

                break;

        }

        out << "Total : " << amountEntered << " $\n";

        difference = productPrice - amountEntered;

        if(difference > 0)
            out << "Left : " << difference << " $\n";
    }

    if(abort)
        return 0;

    else {

        if(difference < 0) {

            std::unordered_map<Coin*,int> moneyKept;

            moneyKept[v0_05] = 0;
            moneyKept[v0_10] = 0;
            moneyKept[v0_25] = 0;
            moneyKept[v1_00] = 0;
            moneyKept[v5_00] = 0;

            double newDifference = productPrice;

            assessCoins(v5_00,newDifference,moneyGiven,moneyKept);
            assessCoins(v1_00,newDifference,moneyGiven,moneyKept);
            assessCoins(v0_25,newDifference,moneyGiven,moneyKept);
            assessCoins(v0_10,newDifference,moneyGiven,moneyKept);
            assessCoins(v0_05,newDifference,moneyGiven,moneyKept);

            for (auto& element: moneyGiven) {
                element.second = moneyKept.find(element.first)->second;
            }

            out << "Giving : \n";

            displayMapContent(moneyKept,out);

            out << "---------------------\n";

            if(newDifference != 0.0)
                out << "Returning " << -newDifference << "$\n";
            else
                out << "Returning " << 0 << "$\n";

            out << "---------------------\n";
            return -newDifference;
        }
        return 0;
    }
}

void vendingMachine::assessCoins(Coin* coin,double& newDifference,std::unordered_map<Coin*,int>& moneyGiven, std::unordered_map<Coin*,int>& moneyKept)
{
    auto given = moneyGiven.find(coin);

    auto kept = moneyKept.find(coin);

    if(newDifference > 0 && given->second > 0)
    {

        int nbCoins = ceil(newDifference/coin->getValue());

        if(nbCoins > 0)
        {

            if(nbCoins < given->second)
            {
                newDifference -= nbCoins * given->first->getValue();

                kept->second += nbCoins;

                given->second -= nbCoins;

            }
            else
            {
                newDifference -= given->second * given->first->getValue();

                kept->second += given->second;

                given->second -= 0;

            }

        }

    }
}
void vendingMachine::fillBalance(std::unordered_map<Coin*,int>& moneyGiven)
{

    for (auto element: moneyGiven)
        this->balance[element.first] += element.second;
}

void vendingMachine::withDrawFromBalance(const std::unordered_map<Coin*,int>& moneyReturned)
{
    for (auto element: moneyReturned)
        this->balance[element.first] -= element.second;

}

void vendingMachine::displayBalance(std::ostream &out) const {

    displayMapContent(this->balance,out);
}

void vendingMachine::empty(std::ostream& out)
{
    bool allEmpty = true;

    for (auto& element : this->balance) {

        if(element.second != 0) {
            allEmpty = false;
            out << "Removing " << element.second << " " << element.first->getValue() <<"$\n";
            element.second = 0;
        }
    }

    if (allEmpty)
        out << "Nothing to empty.\n";

}


void vendingMachine::returnCoin(double& difference, std::unordered_map<Coin*,int>& moneyReturned, Coin* coins, std::ostream& out)
{
    auto it = this->balance.find(coins);

    int div = 0;

    if (it->second > 0 && difference > 0) {

//        if(coins->getValue() >= 1.0)
//            div = int(std::floor(difference)) / int(std::floor(coins->getValue()));
//        else
//            div = int(std::floor(difference*100)) / int(std::floor(coins->getValue()*100));

        div = std::floor(difference/coins->getValue());

        if (div > 0)
        {
            if (it->second > div)
            {

//                this->balance[coins] = it->second - div;

                difference -= div * coins->getValue();

                moneyReturned[coins] += div;

            }
            else
            {

                moneyReturned[coins] += it->second;

                difference -= it->second * coins->getValue();
//
//                this->balance[coins] = 0;

            }

        }

    }
}

void displayMapContent(const std::unordered_map<Coin *, int> &input,std::ostream& out) {

    for (auto element : input  ) {
        out << element.first->getValue() << "$ : " << element.second << '\n';
    }
}

