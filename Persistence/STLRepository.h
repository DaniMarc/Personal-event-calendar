#ifndef A45_POPANDAULMARCDANIEL_STLREPOSITORY_H
#define A45_POPANDAULMARCDANIEL_STLREPOSITORY_H

#include "../Domain/Entity.h"
#include <vector>
#include <string>
#include <ostream>

class Repository{
private:
    std::vector<Event> elements;

public:
    Repository() = default;

    virtual void store(const Event&);

    virtual void remove(int);
    const Event& find(const std::string&) const;

    virtual Event getElementAtPos(int) const;

    virtual std::vector<Event> getAll() noexcept;

    virtual int getLength();

    virtual void changePeopleAmount(const Event&, const std::string&);

    void removeAllElements();

    virtual void updateEvent(int pos, const std::string &title, const std::string &description, const std::string &dateAndTime, const std::string &link);
private:
    bool exists(const Event&) const;

};

class RepositoryException : public std::exception{
private:
    std::string msg;
public:
    RepositoryException(const std::string& m):msg{m}{};
    friend std::ostream& operator<<(std::ostream& out, const RepositoryException& ex);
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> what(){ return this->msg;}
};
//std::ostream& operator<<(std::ostream& out, const RepositoryException& ex);

#endif //A45_POPANDAULMARCDANIEL_STLREPOSITORY_H
