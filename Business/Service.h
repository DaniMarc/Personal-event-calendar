//
// Created by HarcioGG on 4/4/2021.
//

#ifndef A45_POPANDAULMARCDANIEL_SERVICE_H
#define A45_POPANDAULMARCDANIEL_SERVICE_H

#include <string>
#include "../Persistence/STLRepository.h"
#include "../Domain/Entity.h"
#include "../Persistence/UndoRedoRepo.h"

class AdministratorService{
private:
    Repository* repo;
    UndoRedoRepo* undoRepo;
    UndoRedoRepo* redoRepo;
public:
    AdministratorService(Repository*, UndoRedoRepo*, UndoRedoRepo*);
    bool addEventService(const std::string&, const std::string&, const std::string&, int, const std::string&);

    int getLength();

    Event getElemAtPos(int i);

    bool removeEventService(int i);

    bool
    updateEventService(int i, const std::string &title, const std::string &description, const std::string &dateAndTime,
                       int nrPeople,const std::string &link);

    std::vector<Event> getElements();

    void queryDumpEvents();

    void undoService();

    void redoService();

    int getElementsPos(Event event);
};


#endif //A45_POPANDAULMARCDANIEL_SERVICE_H
