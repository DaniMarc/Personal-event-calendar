//
// Created by HarcioGG on 4/6/2021.
//

#ifndef A45_POPANDAULMARCDANIEL_EXCEPTIONS_H
#define A45_POPANDAULMARCDANIEL_EXCEPTIONS_H
#include <exception>
#include <string>

class ValidationException: public std::exception {
public:
    ValidationException(const std::string& msg):exception(){}
};
#endif //A45_POPANDAULMARCDANIEL_EXCEPTIONS_H
