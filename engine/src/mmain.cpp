// mmain.cpp -- բարակ CLI wrapper. Ամբողջ math logic-ը parser.h-ում է:
#include "../include/parser.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "{\"error\": \"no problem provided\"}" << std::endl;
        return 1;
    }
    std::string problem = argv[1];
    try {
        std::vector<Token> tokens = tokenize(problem);
        Parser parser(std::move(tokens));
        double result = parser.parseExpression();
        std::cout << "{\"input\": \"" << problem << "\", \"result\": " << result << "}" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "{\"input\": \"" << problem << "\", \"error\": \"" << e.what() << "\"}" << std::endl;
        return 1;
    }
    return 0;
}
