//
// Created by HarcioGG on 4/4/2021.
//

#include <cstring>
#include <vector>
#include <sstream>
#include "Entity.h"

Event::Event():title{""}, description{""}, dateAndTime{""}, nrPeople{0}, link{""} {}

Event::Event(const std::string &title, const std::string &description, const std::string &dateAndTime, int nrPeople, const std::string &link):title{title}, description{description}, dateAndTime{dateAndTime},nrPeople{nrPeople}, link{link}{}

Event::Event(const Event &ev):title{ev.title}, description{ev.description}, dateAndTime{ev.dateAndTime}, nrPeople{ev.nrPeople}, link{ev.link}{}

Event &Event::operator=(const Event &ev){
    this->title = ev.title;
    this->description = ev.description;
    this->dateAndTime = ev.dateAndTime;
    this->nrPeople = ev.nrPeople;
    this->link = ev.link;
    return *this;
}

bool Event::operator==(const Event &ev) const{
    if(this->link == ev.link)
        return true;
    return false;
}

std::vector<std::string> tokenize(std::string str, char delimiter){
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Event &ev) {
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, '&');
    if(tokens.size() != 5)
        return is;
    ev.title = tokens[0];
    ev.description = tokens[1];
    ev.dateAndTime = tokens[2];
    ev.nrPeople = stoi(tokens[3]);
    ev.link = tokens[4];

    return is;
}

std::ostream &operator<<(std::ostream &os, const Event &ev) {
    os<<ev.title<<"&"<<ev.description<<"&"<<ev.dateAndTime<<"&"<<ev.nrPeople<<"&"<<ev.link<<"\n";
    return os;
}

int Event::getNrPeople() const {
    return nrPeople;
}

const std::string &Event::getTitle() const {
    return title;
}

const std::string &Event::getDescription() const {
    return description;
}

const std::string &Event::getDateAndTime() const {
    return dateAndTime;
}

const std::string &Event::getLink() const {
    return link;
}

void Event::incrementNrPeople() {
    this->nrPeople = this->nrPeople+1;
}

void Event::decrementNrPeople() {
    this->nrPeople--;
}

void Event::setTitle(const std::string& newTitle) {
    this->title = newTitle;
}

void Event::setDescription(const std::string &newDescription) {
    this->description = newDescription;
}

void Event::setDateAndTime(const std::string &newDateAndTime) {
    this->dateAndTime = newDateAndTime;
}

void Event::setLink(const std::string &newLink) {
    this->link = newLink;
}

