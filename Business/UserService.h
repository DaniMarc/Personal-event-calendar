#ifndef A45_POPANDAULMARCDANIEL_USERSERVICE_H
#define A45_POPANDAULMARCDANIEL_USERSERVICE_H
#include "../Persistence/STLRepository.h"
#include "../Domain/Entity.h"

class UserService{
private:
    Repository* repo;
    Repository* repoUser;
public:
    UserService(Repository*, Repository*);

    int getDataBaseLength();

    Event getElemAtPos(int i);

    bool addUserEventService(int i);

    int getUserDataBaseLength();

    Event getUserElemAtPos(int i);

    bool removeUserEventService(int i);

    std::vector<Event> getUserElements();

    std::vector<Event> getAll();

    std::vector<Event> getAllUser();
};



#endif //A45_POPANDAULMARCDANIEL_USERSERVICE_H
