// engine/src/derivative_demo.cpp

#include "../include/parser.h"

#include <exception>
#include <iostream>
#include <string>

int main() {
    try {
        std::string expression;
        std::string x_text;

        std::cout << "Artahajtutjun ogtagordzelov x (orinak: x^3 + 2*x): ";
        std::getline(std::cin, expression);

        std::cout << "arjeq@  x: ";
        std::getline(std::cin, x_text);

        const double x = std::stod(x_text);
        const double result = derivative_at(expression, "x", x);

        std::cout << "d/dx(" << expression << ") at x=" << x
                  << " = " << result << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}