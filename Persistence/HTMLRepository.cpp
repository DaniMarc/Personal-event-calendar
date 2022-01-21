//
// Created by HarcioGG on 5/9/2021.
//

#include "HTMLRepository.h"
HTMLRepository::HTMLRepository(const std::string &fileName) : FileRepository{fileName} {
    this->filename = fileName;
}

void HTMLRepository::writeToFile() {
    std::ofstream htmlFile("HTMLuserEvents.html");

    htmlFile<<"<!DOCTYPE html>\n";
    htmlFile<<"<html>\n";
    htmlFile<<"<head>\n";
    htmlFile<<"<title>Events</title>\n";
    htmlFile<<"</head>\n";
    htmlFile<<"<body>\n";
    htmlFile<<"<table border=\"1\">\n";
    htmlFile<<"\t<tr>\n\t\t<td><b>Event title</b></td>\n\t\t<td><b>Description</b></td>\n\t\t<td><b>Date and time</b></td>\n\t\t<td><b>People attending</b></td>\n\t\t<td><b>Facebook link</b></td>\n\t</tr>\n";

    std::ofstream f(this->filename);
    if(!f.is_open())
        throw RepositoryException("File could not be opened!\n");
    Event ev;
    std::vector<Event> events = Repository::getAll();
    int i;
    for(i=0; i<events.size(); i++) {
        ev = events[i];
        f << ev;
        htmlFile<<"\t<tr>\n\t\t<td>"<<ev.getTitle()<<"</td>\n\t\t<td>"<<ev.getDescription()<<"</td>\n\t\t<td>"<<ev.getDateAndTime()<<"</td>\n\t\t<td>"<<ev.getNrPeople()<<"</td>\n\t\t<td><a href=\"https://"<<ev.getLink()<<"\">"<<"Link"<<"</a></td>\n\t</tr>\n";
    }

    htmlFile<<"</table>";
    htmlFile<<"</body>";
    htmlFile<<"</html>";

    Repository::removeAllElements();
    f.close();
}