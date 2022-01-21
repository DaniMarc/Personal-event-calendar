//
// Created by HarcioGG on 6/1/2021.
//

#ifndef GUIHOMEWORK_UNDOREDOREPO_H
#define GUIHOMEWORK_UNDOREDOREPO_H

#include <utility>
#include <../Domain/Entity.h>
#include <vector>

typedef std::pair<std::string, Event> TPair;

class BaseRepoClass {
private:
    std::vector<TPair> undoRedoElements;
public:
    BaseRepoClass() = default;

    virtual void pushStore(std::string, Event);

    virtual TPair popRemove();

    virtual void clearUndoes();
};

class UndoRedoRepo : public BaseRepoClass {
public:
    UndoRedoRepo() = default;

    void pushStore(std::string, Event);

    TPair popRemove();

//    void clearUndoes();
};

class UndoRedoException : public std::exception {
private:
    std::string msg;
public:
    UndoRedoException(const std::string& m):msg{m}{};
    friend std::ostream& operator<<(std::ostream& out, const UndoRedoException& ex){out<<ex.msg; return out;};
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> what(){ return this->msg;}
};

#endif //GUIHOMEWORK_UNDOREDOREPO_H
