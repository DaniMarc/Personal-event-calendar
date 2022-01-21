//
// Created by HarcioGG on 5/8/2021.
//

#include "CSVRepository.h"


void CSVRepository::writeToFile() {
    std::ofstream csvFile("CSVuserEvents.csv");
    csvFile << "Title" << "," << "Description" << "," << "Date and time" << "," << "Nr People" << "," << "Link" << "\n";

    std::ofstream f(this->filename);
    if(!f.is_open())
        throw RepositoryException("File could not be opened!\n");
    Event ev;
    std::vector<Event> events = Repository::getAll();
    int i;
    for(i=0; i<events.size(); i++) {
        ev = events[i];
        f << ev;
        csvFile << ev.getTitle() << "," << ev.getDescription() << "," << ev.getDateAndTime() << "," << ev.getNrPeople() << "," << ev.getLink() << "\n";
    }
    Repository::removeAllElements();
    f.close();
    csvFile.close();
}

CSVRepository::CSVRepository(const std::string &fileName1) : FileRepository{fileName1} {
    this->filename = fileName1;
}


