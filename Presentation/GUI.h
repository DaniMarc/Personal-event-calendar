//
// Created by HarcioGG on 5/17/2021.
//

#ifndef GUIHOMEWORK_GUI_H
#define GUIHOMEWORK_GUI_H
#include <qwidget.h>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QShortcut>
#include "../Business/Service.h"
#include "../Validation/Validator.h"


class GUI : public QWidget{
private:
    AdministratorService* serv;
    Validator* valid;
    QListWidget* eventsListWidget;
    QLineEdit *titleLineEdit, *descriptionLineEdit, *dateAndTimeLineEdit, *linkLineEdit, *nrOfPeopleLineEdit;
    QPushButton *addButton, *deleteButton, *updateButton, *exitButton;
    QPushButton *undoButton, *redoButton;
    QShortcut *undoShortcut, *redoShortcut;

public:
    GUI(AdministratorService*, Validator*);

private:
    void initGUI();
    void populateList();
    void connectSignalsAndSlots();

    int getSelectedIndex() const;
    void addEvent();
    void deleteEvent();
    void updateEvent();
    void performUndo();
    void performRedo();
    void exitApp();
};


#endif //GUIHOMEWORK_GUI_H
