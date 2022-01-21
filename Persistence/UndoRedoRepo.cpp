//
// Created by HarcioGG on 6/1/2021.
//

#include "UndoRedoRepo.h"

void BaseRepoClass::pushStore(std::string operation, Event event) {
    TPair newElement;
    std::get<0>(newElement) = operation;
    std::get<1>(newElement) = event;
    this->undoRedoElements.push_back(newElement);
}

TPair BaseRepoClass::popRemove() {
    TPair returnElement;
    if(!this->undoRedoElements.empty()) {
        returnElement = this->undoRedoElements.back();
        this->undoRedoElements.pop_back();
        return returnElement;
    }
    else
        throw UndoRedoException("Action impossible to perform!");
}

void BaseRepoClass::clearUndoes() {
    this->undoRedoElements.clear();
}

/// DERIVED CLASS
void UndoRedoRepo::pushStore(std::string op, Event ev) {
    BaseRepoClass::pushStore(op, ev);
}

TPair UndoRedoRepo::popRemove() {
    return BaseRepoClass::popRemove();
}
