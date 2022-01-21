//

#include "FileRepository.h"

//
// Created by HarcioGG on 4/18/2021.
FileRepository::FileRepository(const std::string &filename):filename{filename} {}

void FileRepository::readFromFile() {
    std::ifstream f(this->filename);
    if(!f.is_open())
        throw RepositoryException("File could not be opened!\n");
    Event ev;
    while(f>>ev)
        Repository::store(ev);

    f.close();
}

void FileRepository::writeToFile() {
    std::ofstream f(this->filename);
    if(!f.is_open())
        throw RepositoryException("File could not be opened!\n");
    Event ev;
    std::vector<Event> events = Repository::getAll();
    int i;
    for(i=0; i<events.size(); i++) {
        ev = events[i];
        f << ev;
    }
    Repository::removeAllElements();
    f.close();
}

void FileRepository::store(const Event &ev) {
    this->readFromFile();
    Repository::store(ev);
    this->writeToFile();
}

void FileRepository::remove(int pos) {
    this->readFromFile();
    Repository::remove(pos);
    this->writeToFile();
}

Event FileRepository::getElementAtPos(int pos){
    Event retEvent;
    this->readFromFile();
    retEvent = Repository::getElementAtPos(pos);
    Repository::removeAllElements();
    return retEvent;
}

std::vector<Event> FileRepository::getAll() noexcept{
    this->readFromFile();
    std::vector<Event> elems;
    elems = Repository::getAll();
    Repository::removeAllElements();
    return elems;
}

int FileRepository::getLength() {
    int length;
    this->readFromFile();
    length = Repository::getLength();
    Repository::removeAllElements();
    return length;
}

void FileRepository::changePeopleAmount(const Event &addedEv, const std::string &sign) {
    this->readFromFile();
    Repository::changePeopleAmount(addedEv, sign);
    this->writeToFile();
}

void FileRepository::updateEvent(int pos, const std::string &title, const std::string &description,
                                 const std::string &dateAndTime, const std::string &link) {
    this->readFromFile();
    Repository::updateEvent(pos, title, description, dateAndTime, link);
    this->writeToFile();
}
