//
// Created by HarcioGG on 4/8/2021.
//
#include "../Domain/Entity.h"
#include "UserService.h"

UserService::UserService(Repository* repo, Repository* repoUser):repo{repo}, repoUser{repoUser} {}

int UserService::getDataBaseLength() {
    return this->repo->getLength();
}

int UserService::getUserDataBaseLength() {
    return this->repoUser->getLength();
}

Event UserService::getElemAtPos(int pos) {
    return this->repo->getElementAtPos(pos);
}

Event UserService::getUserElemAtPos(int pos) {
    return this->repoUser->getElementAtPos(pos);
}

bool UserService::addUserEventService(int pos) {
    std::vector<Event> allEvents = this->repo->getAll();
    Event addedEvent = allEvents[pos];
    this->repo->changePeopleAmount(addedEvent, "+");
    this->repoUser->store(addedEvent);
    return true;
}

bool UserService::removeUserEventService(int pos) {
    std::vector<Event> allEvents = this->repo->getAll();
    Event removedEvent = allEvents[pos];
    Event compareEvent;

    if(pos >= this->repoUser->getLength())
        return false;

    this->repo->changePeopleAmount(removedEvent, "-");
    this->repoUser->remove(pos);
    return true;
}

std::vector<Event> UserService::getUserElements() {
    return this->repoUser->getAll();
}

std::vector<Event> UserService::getAll() {
    return this->repo->getAll();
}

std::vector<Event> UserService::getAllUser() {
    return this->repoUser->getAll();
}


