//
// Created by HarcioGG on 4/4/2021.
//

#include "Service.h"
#include "../Domain/Entity.h"

AdministratorService::AdministratorService(Repository *repo, UndoRedoRepo* undoRedo, UndoRedoRepo* redoRepo): repo{repo}, undoRepo{undoRedo}, redoRepo{redoRepo} {}

bool AdministratorService::addEventService(const std::string &title, const std::string &description, const std::string &dateAndTime, int nrPeople, const std::string &link) {
    Event ev(title, description, dateAndTime, nrPeople, link);
    this->undoRepo->pushStore("add", ev);
    this->repo->store(ev);
    return true;
}

bool AdministratorService::removeEventService(int pos) {
    Event ev = this->repo->getAll()[pos];
    this->undoRepo->pushStore("remove", ev);
    this->repo->remove(pos);
    return true;
}

bool AdministratorService::updateEventService(int pos, const std::string &title, const std::string &description, const std::string &dateAndTime, int  nrPeople, const std::string &link) {
    if(!title.empty() && !description.empty() && !dateAndTime.empty() && !link.empty()) {
        Event ev(title, description, dateAndTime, nrPeople, link);
        Event oldEvent = this->repo->getAll()[pos];

        this->undoRepo->pushStore("update", oldEvent);
        this->repo->updateEvent(pos, title, description, dateAndTime, link);
        return true;
    }
    return false;
}

int AdministratorService::getLength() {
    return this->repo->getLength();
}

Event AdministratorService::getElemAtPos(int i) {
    return this->repo->getAll()[i];
}

std::vector<Event> AdministratorService::getElements() {
    return this->repo->getAll();
}

void AdministratorService::queryDumpEvents() {
    this->repo->removeAllElements();
}

void AdministratorService::undoService() {
    TPair undoElement = this->undoRepo->popRemove();
    Event ev = std::get<1>(undoElement);
    std::string operation = std::get<0>(undoElement);
    if(operation == "remove"){
        this->redoRepo->pushStore("remove", ev);
        this->repo->store(ev);
    }
    else if(operation == "add"){
        int posToRemove;
        posToRemove = this->getElementsPos(ev);
        if(posToRemove == -1)
            throw RepositoryException("Error in undo! Can't find element to delete!");
        this->redoRepo->pushStore("add", ev);
        this->repo->remove(posToRemove);
    }
    else if(operation == "update"){
        int posToUpdate;
        std::string title = ev.getTitle(), description = ev.getDescription(), dateAndTime = ev.getDateAndTime(), link = ev.getLink();
        posToUpdate = this->getElementsPos(ev);
        if(posToUpdate == -1)
            throw RepositoryException("Error in undo! Can't find element to update!");
        Event oldEvent = this->repo->getAll()[posToUpdate];
        this->redoRepo->pushStore("update", oldEvent);
        this->repo->updateEvent(posToUpdate, title, description, dateAndTime, link);
    }
}

int AdministratorService::getElementsPos(Event event) {
    std::vector<Event> allElements = this->repo->getAll();
    int length = allElements.size(), i;
    for(i=0; i<=length; i++){
        if(allElements[i] == event)
            return i;
    }
    return -1;
}

void AdministratorService::redoService() {
    TPair redoElement = this->redoRepo->popRemove();
    Event ev = std::get<1>(redoElement);
    std::string operation = std::get<0>(redoElement);
    if(operation == "remove"){
        int posToRemove;
        posToRemove = this->getElementsPos(ev);
        if(posToRemove == -1)
            throw RepositoryException("Error in redo! Can't find element to delete!");
        this->undoRepo->pushStore("remove", ev);
        this->repo->remove(posToRemove);
    }
    else if(operation == "add"){
        this->undoRepo->pushStore("add", ev);
        this->repo->store(ev);
    }
    else if(operation == "update"){
        int posToUpdate;
        std::string title = ev.getTitle(), description = ev.getDescription(), dateAndTime = ev.getDateAndTime(), link = ev.getLink();
        posToUpdate = this->getElementsPos(ev);
        if(posToUpdate == -1)
            throw RepositoryException("Error in undo! Can't find element to update!");
        Event oldEvent = this->repo->getAll()[posToUpdate];
        this->undoRepo->pushStore("update", oldEvent);
        this->repo->updateEvent(posToUpdate, title, description, dateAndTime, link);
    }
}
