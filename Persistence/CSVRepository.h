//
// Created by HarcioGG on 5/8/2021.
//

#ifndef A45_POPANDAULMARCDANIEL_CSVREPOSITORY_H
#define A45_POPANDAULMARCDANIEL_CSVREPOSITORY_H
#include <iostream>
#include <string>
#include "FileRepository.h"

class CSVRepository : public FileRepository{
public:
    CSVRepository(const std::string& fileName);
private:
    std::string filename;
    void writeToFile();
};
#endif //A45_POPANDAULMARCDANIEL_CSVREPOSITORY_H
