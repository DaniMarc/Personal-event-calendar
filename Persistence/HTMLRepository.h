//
// Created by HarcioGG on 5/9/2021.
//

#ifndef A45_POPANDAULMARCDANIEL_HTMLREPOSITORY_H
#define A45_POPANDAULMARCDANIEL_HTMLREPOSITORY_H
#include <iostream>
#include <string>
#include "FileRepository.h"

class HTMLRepository : public FileRepository{
public:
    HTMLRepository(const std::string& fileName);
private:
    std::string filename;
    void writeToFile();
};

#endif //A45_POPANDAULMARCDANIEL_HTMLREPOSITORY_H
