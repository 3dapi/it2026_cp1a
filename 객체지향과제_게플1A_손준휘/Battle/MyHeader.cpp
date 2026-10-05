#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "MyHeader.h"


int InputInt(std::string announce)
{
    std::string input;
    int value{};

    if (announce != "")
    {
        std::cout << announce;
    }

    while (true)
    {
        std::getline(std::cin, input);

        std::stringstream ss(input);
        std::string remain;

        if (ss >> value && !(ss >> remain))
        {
            return value;
        }

        std::cout << "잘못된 입력입니다. 다시 시도하십시오.\n";
    }
}

std::string InputString(std::string announce)
{ 
    std::string input;

    if (announce != "")
    {
        std::cout << announce;
    }

    while (true)
    {
        if (std::getline(std::cin, input))
        {
            return input;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "잘못된 입력입니다. 다시 시도하십시오.\n";
    }
}

void Messege(std::string input)
{
    std::cout << input;
}

void ToNext(const bool doSkip)
{
    if (doSkip)
    {
        return;
    }

    std::string input;


    std::cout << ">>\n";


    while (true)
    {
        if (std::getline(std::cin, input))
        {
            return;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "잘못된 입력입니다. 다시 시도하십시오.\n";
    }
}

std::string ToSignedNumber(const int num)
{
    std::string str{};

    if (0 == num)
    {
        str = '0';
    }
    else if (0 < num)
    {
        str += "+";
        str += std::to_string(num);
    }
    else
    {
        str = std::to_string(num);
    }
    
    return str;
}
