//
// Created by HarcioGG on 4/12/2021.
//

#include "../Domain/Entity.h"
#include "STLRepository.h"
#include <iostream>

bool Repository::exists(const Event &ev) const {
    try{
        std::string searchLink = ev.getLink();
        this->find(searchLink);
        return true;
    }
    catch (RepositoryException&){
        return false;
    }
}

void Repository::store(const Event& ev)
{
    Event compareEv;
    for(int i=0; i < elements.size(); i++){
        compareEv = this->getElementAtPos(i);
        if(ev == compareEv)
            throw RepositoryException("There is already an event with the link " + ev.getLink() + "\n");
    }
    this->elements.push_back(ev);
}

void Repository::remove(int pos) {
    if(pos >= elements.size())
        throw RepositoryException("You are trying to erase a nonexistent element!\n");
    this->elements.erase(this->elements.begin()+pos);
}

const Event& Repository::find(const std::string& link) const {
    Event ev;
    for(int i=0; i<elements.size(); i++){
        ev = getElementAtPos(i);
        if (ev.getLink() == link){
            return ev;
        }
    }
    throw RepositoryException("There is no event with the provided link "+link+"\n");
}

std::vector<Event> Repository::getAll() noexcept {
    return elements;
}

int Repository::getLength() {
    return this->elements.size();
}

Event Repository::getElementAtPos(int pos) const {
    return this->elements[pos];
}

void Repository::removeAllElements() {
    this->elements.clear();
}


std::ostream& operator<<(std::ostream& out, const RepositoryException& ex){
    out<<ex.msg;
    return out;
}

void Repository::changePeopleAmount(const Event &addedEvent, const std::string &sign) {
    if(sign == "+") {
        int i=0;
        for (auto ev : this->elements) {
            if (addedEvent == ev) {
                ev.incrementNrPeople();
                this->elements[i].incrementNrPeople();
                break;
            }
            i++;
        }
    } else if(sign == "-"){
        int i=0;
        for(auto ev : this->elements) {
            if (addedEvent == ev) {
                ev.decrementNrPeople();
                this->elements[i].decrementNrPeople();
                break;
            }
            i++;
        }
    }
}

void Repository::updateEvent(int pos, const std::string &title, const std::string &description, const std::string &dateAndTime, const std::string &link) {
    this->elements[pos].setTitle(title);
    this->elements[pos].setDescription(description);
    this->elements[pos].setLink(link);
    this->elements[pos].setDateAndTime(dateAndTime);

}
