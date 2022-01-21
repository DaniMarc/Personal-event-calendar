//
// Created by HarcioGG on 4/18/2021.
//

#ifndef A45_POPANDAULMARCDANIEL_FILEREPOSITORY_H
#define A45_POPANDAULMARCDANIEL_FILEREPOSITORY_H
#include "../Domain/Entity.h"
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include "STLRepository.h"
class FileRepository : public Repository{
public:
    FileRepository(const std::string&);
    void store(const Event&);
    void remove(int);
    Event getElementAtPos(int);
    std::vector<Event> getAll() noexcept;
    int getLength();
    void changePeopleAmount(const Event&, const std::string&);
    void updateEvent(int pos, const std::string &title, const std::string &description, const std::string &dateAndTime, const std::string &link);

private:
    std::string filename;
    void readFromFile();
    virtual void writeToFile();
//    void appendToFile();
};




#endif //A45_POPANDAULMARCDANIEL_FILEREPOSITORY_H
