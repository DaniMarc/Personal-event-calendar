//
// Created by HarcioGG on 5/17/2021.
//

#include <QLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "GUI.h"

GUI::GUI(AdministratorService* service, Validator* validator){
    this->serv = service;
    this->valid = validator;
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    this->eventsListWidget = new QListWidget{};

    this->titleLineEdit = new QLineEdit{};
    this->descriptionLineEdit = new QLineEdit{};
    this->dateAndTimeLineEdit = new QLineEdit{};
    this->nrOfPeopleLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};

    this->addButton = new QPushButton{"Add event"};
    this->deleteButton = new QPushButton{"Delete event"};
    this->updateButton = new QPushButton{"Update event"};
    this->undoButton = new QPushButton{"U N D O"};
    this->redoButton = new QPushButton{"R E D O"};
    this->exitButton = new QPushButton{"Exit"};

    this->undoShortcut = new QShortcut{QKeySequence("Ctrl+Z"), this};
    this->redoShortcut = new QShortcut{QKeySequence("Ctrl+Y"), this};

    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    mainLayout->addWidget(this->eventsListWidget);

    QFormLayout* eventDetails = new QFormLayout{};
    eventDetails->addRow("Title", this->titleLineEdit);
    eventDetails->addRow("Description", this->descriptionLineEdit);
    eventDetails->addRow("Date and time", this->dateAndTimeLineEdit);
    eventDetails->addRow("Number of people attending", this->nrOfPeopleLineEdit);
    eventDetails->addRow("Link to the event", this->linkLineEdit);
    mainLayout->addLayout(eventDetails);

    QGridLayout *buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->updateButton, 0, 2);
    mainLayout->addLayout(buttonsLayout);

    QGridLayout *undoRedoLayer = new QGridLayout{};
    undoRedoLayer->addWidget(this->undoButton, 0, 0);
    undoRedoLayer->addWidget(this->redoButton, 0, 1);
    mainLayout->addLayout(undoRedoLayer);

    mainLayout->addWidget(this->exitButton);
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->eventsListWidget, &QListWidget::itemSelectionChanged, [this](){
        int selectedIndex = this->getSelectedIndex();

        if(selectedIndex < 0)
            return;

        Event ev = this->serv->getElements()[selectedIndex];
        this->titleLineEdit->setText(QString::fromStdString(ev.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(ev.getDescription()));
        this->dateAndTimeLineEdit->setText(QString::fromStdString(ev.getDateAndTime()));
        this->nrOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(ev.getNrPeople())));
        this->linkLineEdit->setText(QString::fromStdString(ev.getLink()));
    });

    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addEvent);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteEvent);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateEvent);
    QObject::connect(this->exitButton, &QPushButton::clicked, this, &GUI::exitApp);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::performUndo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::performRedo);
    QObject::connect(this->undoShortcut, &QShortcut::activated, this, &GUI::performUndo);
    QObject::connect(this->redoShortcut, &QShortcut::activated, this, &GUI::performRedo);
}

void GUI::populateList() {
    this->eventsListWidget->clear();
    int index=1;
    std::vector<Event> allEvents = this->serv->getElements();
    for(auto& ev : allEvents) {
        this->eventsListWidget->addItem(QString::fromStdString( std::to_string(index)+". " + ev.getTitle() +"\n"));
        index++;
    }
}

int GUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->eventsListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.empty()){
        this->titleLineEdit->clear();
        this->descriptionLineEdit->clear();
        this->dateAndTimeLineEdit->clear();
        this->nrOfPeopleLineEdit->clear();
        this->linkLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void GUI::addEvent() {
    std::string title = this->titleLineEdit->text().toStdString();
    std::string description = this->descriptionLineEdit->text().toStdString();
    std::string dateAndTime = this->dateAndTimeLineEdit->text().toStdString();
    std::string stringNrOfPeople = this->nrOfPeopleLineEdit->text().toStdString();
    int nrOfPeople;
    try{
        nrOfPeople = std::stoi(stringNrOfPeople);
    }
    catch (...){
        QMessageBox::critical(this, "Error#69420","Invalid number of people!","Please, forgiveness!");
        return;
    }
    std::string link = this->linkLineEdit->text().toStdString();

    try {
        this->valid->performAddValidation(title, description, dateAndTime, link);
    }
    catch (ValidationException& ve){
        QMessageBox::critical(this, "Error#69420",QString::fromStdString(ve.what()),"Please, forgiveness!");
        return;
    }

    ///Adding operation
    try {
        this->serv->addEventService(title, description, dateAndTime, nrOfPeople, link);
    }
    catch (RepositoryException& re){
        QMessageBox::critical(this, "Error#69420",QString::fromStdString(re.what()),"Please, forgiveness!");
        return;
    }

    this->populateList();

    int lastElement = this->serv->getElements().size() - 1;
    this->eventsListWidget->setCurrentRow(lastElement);
}

void GUI::deleteEvent() {
    int selectedIndex = this->getSelectedIndex();
    if(selectedIndex < 0){
        QMessageBox::critical(this, "Error#69420","No event was selected!","Please, forgiveness!");
        return;
    }
    Event ev = this->serv->getElements()[selectedIndex];
    this->serv->removeEventService(selectedIndex);
    this->populateList();
}

void GUI::updateEvent() {
    int selectedIndex = this->getSelectedIndex();

    std::string title = this->titleLineEdit->text().toStdString();
    std::string description = this->descriptionLineEdit->text().toStdString();
    std::string dateAndTime = this->dateAndTimeLineEdit->text().toStdString();
    std::string stringNrOfPeople = this->nrOfPeopleLineEdit->text().toStdString();
    int nrOfPeople;
    try{
        nrOfPeople = std::stoi(stringNrOfPeople);
    }
    catch (...){
        QMessageBox::critical(this, "Error#69420","Invalid number of people!","Please, forgiveness!");
        return;
    }
    std::string link = this->linkLineEdit->text().toStdString();

    try{
        if(!(this->serv->updateEventService(selectedIndex, title, description, dateAndTime, nrOfPeople, link)))
            QMessageBox::critical(this, "Error#69420","Invalid data!","Please, forgiveness!");
    }
    catch(...){QMessageBox::critical(this, "Error#69420","Invalid data!","Please, forgiveness!");
        return;}

    this->populateList();
    this->eventsListWidget->setCurrentRow(selectedIndex);
}

void GUI::performUndo() {
    try{
        this->serv->undoService();
        this->populateList();
    } catch (UndoRedoException& ue){
        QMessageBox::critical(this, "Error#69420", QString::fromStdString(ue.what()),"Please, forgiveness!");
        return;
    }
}

void GUI::performRedo() {
    try{
        this->serv->redoService();
        this->populateList();
    } catch (UndoRedoException& re){
        QMessageBox::critical(this, "Error#69420", QString::fromStdString(re.what()),"Please, forgiveness!");
        return;
    }
}

void GUI::exitApp() {
    close();
}
