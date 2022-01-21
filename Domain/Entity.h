//
// Created by HarcioGG on 4/4/2021.
//

#ifndef A45_POPANDAULMARCDANIEL_ENTITY_H
#define A45_POPANDAULMARCDANIEL_ENTITY_H

#include <string>
#include <iostream>

class Event{
private:
    std::string title;
    std::string description;
    std::string dateAndTime;
    int nrPeople;
    std::string link;

public:
    Event();
    Event(const std::string&, const std::string&, const std::string&, int, const std::string&);
    Event(const Event&);
    Event& operator=(const Event&);
    bool operator==(const Event&) const;
    friend std::ostream& operator<<(std::ostream&, const Event&);
    friend std::istream& operator>>(std::istream&, Event&);

    ///Method that returns the number of the people attending an event
    int getNrPeople() const;

    ///Method that updates the number of people attending an event
    void incrementNrPeople();

    ///Method that returns the title of an event
    const std::string& getTitle() const;

    ///Method that updates the title of an event
    void setTitle(const std::string&);

    ///Method that returns the description of an event
    const std::string& getDescription() const;

    ///Method that updates the description of an event
    void setDescription(const std::string&);

    ///Method that returns the date and time of an event
    const std::string& getDateAndTime() const;

    ///Method that updates the date and time of an event
    void setDateAndTime(const std::string&);

    ///Method that returns the link to an event
    const std::string& getLink() const;

    ///Method that updates the link to an event
    void setLink(const std::string&);

    void decrementNrPeople();
};


#endif //A45_POPANDAULMARCDANIEL_ENTITY_H
