//
// Created by HarcioGG on 4/6/2021.
//

#ifndef A45_POPANDAULMARCDANIEL_VALIDATOR_H
#define A45_POPANDAULMARCDANIEL_VALIDATOR_H

#include <string>

class Validator{
public:
    bool performAddValidation(const std::string &title, const std::string &description, const std::string &dateAndTime, const std::string &link);
    bool performUpdateValidation(const std::string &title, const std::string &description, const std::string &dateAndTime, const std::string &link);
};

class ValidationException : public std::exception{
private:
    std::string msg;
public:
    ValidationException(const std::string& m):msg{m}{};
    friend std::ostream& operator<<(std::ostream& out, const ValidationException& ex);
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> what(){ return this->msg;}
};

#endif //A45_POPANDAULMARCDANIEL_VALIDATOR_H
