#include "../include/parser.h"

#include <exception>
#include <iostream>
#include <string>

int main() {
    try {
        std::string expression;
        Variables variables;

        std::cout << "Expression: ";
        std::getline(std::cin, expression);

        while (true) {
            std::string name;
            std::cout << "Variable name (press Enter when done): ";
            std::getline(std::cin, name);

            if (name.empty()) {
                break;
            }

            std::string value_text;
            std::cout << "Value for " << name << ": ";
            std::getline(std::cin, value_text);

            const double value = std::stod(value_text);
            variables[name] = value;
        }

        const double result = evaluate(expression, variables);

        std::cout << "Result: " << result << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}