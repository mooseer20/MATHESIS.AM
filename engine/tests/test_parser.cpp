
// test_parser.cpp
//
// Ձեռքով գրված test-եր, framework-ի կարիք չկա (Catch2 կգա ավելի ուշ):
// Կանչել. make test

#include "../include/parser.h"
#include <iostream>
#include <cmath>

int tests_run = 0;
int tests_failed = 0;

void check(const std::string& expr, double expected) {
    ++tests_run;
    std::vector<Token> tokens = tokenize(expr);
    Parser parser(std::move(tokens));
    double actual = parser.parseExpression();

    if (std::fabs(actual - expected) > 1e-9) {
        ++tests_failed;
        std::cout << "FAIL: \"" << expr << "\" -- ակնկալվում էր " << expected
                  << ", ստացվեց " << actual << std::endl;
    } else {
        std::cout << "PASS: \"" << expr << "\" = " << actual << std::endl;
    }
}

int main() {
    check("2 + 3", 5);
    check("2 + 3 * (4 - 1)", 11);
    check("10 / 2 - 3", 2);
    check("-5 + 3", -2);
    check("2 + 9", 11);
    check("9 /11", 9.0 / 11.0);

    // TODO (եթե parsePower()-ը արդեն գրած ես) -- ապակոմենտար արա.
     check("2 ^ 3", 8);
    check("2 ^ 3 ^ 2", 512);

    std::cout << "\n" << (tests_run - tests_failed) << "/" << tests_run << " passed" << std::endl;
    return tests_failed == 0 ? 0 : 1;
}