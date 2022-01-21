//
// Created by HarcioGG on 5/23/2021.
//

#ifndef GUIHOMEWORK_USERGUI_H
#define GUIHOMEWORK_USERGUI_H
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <Qlabel>
#include <QLineEdit>
#include <QTableView>
#include "../Business/UserService.h"
#include "TableModel.h"
#include "QHeaderView"

class UserGUI : public QWidget {
private:
    UserService* serv;
    QListWidget* userEventsListWidget;
    QLabel* userEventsLabel, *toBeAddedEvent;
    QLineEdit *titleLineEdit, *descriptionLineEdit, *dateAndTimeLineEdit, *linkLineEdit, *nrOfPeopleLineEdit;
    QPushButton *addButton, *deleteButton, *nextButton, *previousButton, *csvButton, *htmlButton, *exitButton;
    TableModel *tableModel;
    QTableView *tableView;
    QVBoxLayout *mainL;
public:
    UserGUI(UserService*);
private:

    void initGUI();

    void connectSignalsAndSlots();

    void populateForm();

    void addEventUser();

    void deleteEventUser();

    void exitApp();

    void populateList();

    int getSelectedIndex();

    void displayNextEvent();

    void displayPrevEvent();

    void displayCSVEvents();

    void displayHTMLEvents();

    void writeToCSV();

    void writeToHTML();

    void populateTable();
};





#endif //GUIHOMEWORK_USERGUI_H
