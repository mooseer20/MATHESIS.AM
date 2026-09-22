// parser.h
//
// Tokenizer-ը, Parser class-ը և numeric derivative helpers-ը։

#pragma once

#include <cctype>
#include <cmath>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// -----------------------------------------------------------------------------
// Tokenizer
// -----------------------------------------------------------------------------

enum class TokenType {
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    Caret,
    LParen,
    RParen,
    End
};

struct Token {
    TokenType type;
    double value = 0.0;
};

inline std::vector<Token> tokenize(const std::string& expr) {
    std::vector<Token> tokens;
    std::size_t i = 0;

    while (i < expr.size()) {
        const char c = expr[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            const std::size_t start = i;
            bool has_dot = false;

            while (i < expr.size()) {
                const char current = expr[i];

                if (std::isdigit(static_cast<unsigned char>(current))) {
                    ++i;
                } else if (current == '.' && !has_dot) {
                    has_dot = true;
                    ++i;
                } else {
                    break;
                }
            }

            const std::string number_text = expr.substr(start, i - start);

            try {
                tokens.push_back({TokenType::Number, std::stod(number_text)});
            } catch (const std::exception&) {
                throw std::runtime_error("invalid number: " + number_text);
            }

            continue;
        }

        switch (c) {
            case '+': tokens.push_back({TokenType::Plus});   break;
            case '-': tokens.push_back({TokenType::Minus});  break;
            case '*': tokens.push_back({TokenType::Star});   break;
            case '/': tokens.push_back({TokenType::Slash});  break;
            case '^': tokens.push_back({TokenType::Caret});  break;
            case '(': tokens.push_back({TokenType::LParen}); break;
            case ')': tokens.push_back({TokenType::RParen}); break;

            default:
                throw std::runtime_error(
                    std::string("անճանաչ նշան (unexpected character): ") + c
                );
        }

        ++i;
    }

    tokens.push_back({TokenType::End});
    return tokens;
}

// -----------------------------------------------------------------------------
// Parser
//
// Grammar:
//   expr   := term (('+' | '-') term)*
//   term   := unary (('*' | '/') unary)*
//   unary  := ('+' | '-') unary | power
//   power  := factor [ '^' unary ]
//   factor := number | '(' expr ')'
// -----------------------------------------------------------------------------

class Parser {
public:
    explicit Parser(std::vector<Token> tokens)
        : tokens_(std::move(tokens)) {}

    double parse() {
        const double result = parseExpression();

        if (!atEnd()) {
            throw std::runtime_error(
                "անսպասելի ավելորդ նշաններ (unexpected trailing input)"
            );
        }

        return result;
    }

    double parseExpression() {
        double result = parseTerm();

        while (peek().type == TokenType::Plus ||
               peek().type == TokenType::Minus) {
            const Token op = advance();
            const double rhs = parseTerm();

            if (op.type == TokenType::Plus) {
                result += rhs;
            } else {
                result -= rhs;
            }
        }

        return result;
    }

    bool atEnd() const {
        return peek().type == TokenType::End;
    }

private:
    const Token& peek() const {
        return tokens_[pos_];
    }

    Token advance() {
        return tokens_[pos_++];
    }

    double parseFactor() {
        const Token token = advance();

        if (token.type == TokenType::Number) {
            return token.value;
        }

        if (token.type == TokenType::LParen) {
            const double result = parseExpression();

            if (peek().type != TokenType::RParen) {
                throw std::runtime_error(
                    "սպասվում էր ')' (expected closing parenthesis)"
                );
            }

            advance();
            return result;
        }

        throw std::runtime_error(
            "սպասվում էր թիվ կամ '(' (expected number or '(')"
        );
    }

     double parsePower() {
        const double base = parseFactor();
    
        if (peek().type == TokenType::Caret) {
            advance();  // required: consume '^'
    
            const double exponent = parseUnary();
            return std::pow(base, exponent);
        }
    
        return base;
    }

  

    double parseUnary() {
        if (peek().type == TokenType::Plus) {
            advance();
            return parseUnary();
        }

        if (peek().type == TokenType::Minus) {
            advance();
            return -parseUnary();
        }

        return parsePower();
    }

    double parseTerm() {
        double result = parseUnary();

        while (peek().type == TokenType::Star ||
               peek().type == TokenType::Slash) {
            const Token op = advance();
            const double rhs = parseUnary();

            if (op.type == TokenType::Star) {
                result *= rhs;
            } else {
                if (rhs == 0.0) {
                    throw std::runtime_error(
                        "զրոյի բաժանում (division by zero)"
                    );
                }

                result /= rhs;
            }
        }

        return result;
    }

    std::vector<Token> tokens_;
    std::size_t pos_ = 0;
};

// -----------------------------------------------------------------------------
// Evaluation and numeric derivative
// -----------------------------------------------------------------------------

inline double evaluate(const std::string& expression) {
    Parser parser(tokenize(expression));
    return parser.parse();
}

inline double evaluate_at(const std::string& expr,
                 const std::string& var,
                       double value) {
    std::ostringstream value_stream;
    value_stream << '(' << value << ')';

    std::string substituted = expr;
    std::size_t pos = 0;

    while ((pos = substituted.find(var, pos)) != std::string::npos) {
        substituted.replace(pos, var.size(), value_stream.str());
        pos += value_stream.str().size();
    }

    return evaluate(substituted);
}

inline double derivative_at(const std::string& expr,
                            const std::string& var,
                            double x,
                            double h = 1e-5) {
    const double f_plus = evaluate_at(expr, var, x + h);
    const double f_minus = evaluate_at(expr, var, x - h);

    return (f_plus - f_minus) / (2.0 * h);
}


