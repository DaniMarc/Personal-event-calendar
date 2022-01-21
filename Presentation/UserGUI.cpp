//
// Created by HarcioGG on 5/23/2021.
//

#include <QLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <fstream>
#include "UserGUI.h"

UserGUI::UserGUI(UserService *service) {
    this->serv = service;
    this->initGUI();
    this->connectSignalsAndSlots();
    this->populateList();
    this->populateForm();
}

void UserGUI::initGUI() {
    this->mainL = new QVBoxLayout;

    this->userEventsListWidget = new QListWidget;
    this->userEventsLabel = new QLabel{"Your events:"};
    this->toBeAddedEvent = new QLabel{"\nEvent you can add:"};

    this->titleLineEdit = new QLineEdit{};
    this->descriptionLineEdit = new QLineEdit{};
    this->dateAndTimeLineEdit = new QLineEdit{};
    this->nrOfPeopleLineEdit = new QLineEdit{};
    this->linkLineEdit = new QLineEdit{};

    this->addButton = new QPushButton{"Add event"};
    this->deleteButton = new QPushButton{"Delete event"};
    this->nextButton = new QPushButton{"Next >"};
    this->previousButton = new QPushButton{"< Prev"};
    this->csvButton = new QPushButton{"Display events in CSV"};
    this->htmlButton = new QPushButton{"Display events in HTML"};
    this->exitButton = new QPushButton{"EXIT"};

    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    mainLayout->addWidget(this->userEventsLabel);
    mainLayout->addWidget(this->userEventsListWidget);

    QFormLayout *eventDetails = new QFormLayout{};
    eventDetails->addRow("Title", this->titleLineEdit);
    eventDetails->addRow("Description", this->descriptionLineEdit);
    eventDetails->addRow("Date and time", this->dateAndTimeLineEdit);
    eventDetails->addRow("Number of people attending", this->nrOfPeopleLineEdit);
    eventDetails->addRow("Link to the event", this->linkLineEdit);
    mainLayout->addWidget(this->toBeAddedEvent);
    mainLayout->addLayout(eventDetails);

    QGridLayout *buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 1);
    buttonsLayout->addWidget(this->previousButton, 0, 0);
    buttonsLayout->addWidget(this->nextButton, 0, 2);
    mainLayout->addLayout(buttonsLayout);

    QGridLayout *buttonsLayout2 = new QGridLayout{};
    buttonsLayout2->addWidget(this->deleteButton, 0, 1);
    buttonsLayout2->addWidget(this->csvButton, 0, 0);
    buttonsLayout2->addWidget(this->htmlButton, 0, 2);
    mainLayout->addLayout(buttonsLayout2);

    QGridLayout *buttonsLayout3 = new QGridLayout{};
    buttonsLayout3->addWidget(this->exitButton, 0, 0);
    mainLayout->addLayout(buttonsLayout3);

    this->tableModel = new TableModel{this->serv};
    this->tableView = new QTableView{};
    this->tableView->setModel(this->tableModel);
    mainLayout->addWidget(this->tableView);
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->mainL = mainLayout;
}

void UserGUI::connectSignalsAndSlots() {
    QObject::connect(this->userEventsListWidget, &QListWidget::itemSelectionChanged, [this](){
        int selectedIndex = this->getSelectedIndex();

        if(selectedIndex < 0)
            return;

        Event ev = this->serv->getAllUser()[selectedIndex];
        this->titleLineEdit->setText(QString::fromStdString(ev.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(ev.getDescription()));
        this->dateAndTimeLineEdit->setText(QString::fromStdString(ev.getDateAndTime()));
        this->nrOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(ev.getNrPeople())));
        this->linkLineEdit->setText(QString::fromStdString(ev.getLink()));
    });

    QObject::connect(this->exitButton, &QPushButton::clicked, this, &UserGUI::exitApp);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addEventUser);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &UserGUI::deleteEventUser);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::displayNextEvent);
    QObject::connect(this->previousButton, &QPushButton::clicked, this, &UserGUI::displayPrevEvent);
    QObject::connect(this->csvButton, &QPushButton::clicked, this, &UserGUI::displayCSVEvents);
    QObject::connect(this->htmlButton, &QPushButton::clicked, this, &UserGUI::displayHTMLEvents);
}

void UserGUI::exitApp(){
    close();
}

void UserGUI::populateForm() {
    this->titleLineEdit->clear();
    this->descriptionLineEdit->clear();
    this->dateAndTimeLineEdit->clear();
    this->nrOfPeopleLineEdit->clear();
    this->linkLineEdit->clear();
    std::vector<Event> allEvents = this->serv->getAll();
    if(!allEvents.empty()) {
        Event ev = allEvents[0];
        this->titleLineEdit->setText(QString::fromStdString(ev.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(ev.getDescription()));
        this->dateAndTimeLineEdit->setText(QString::fromStdString(ev.getDateAndTime()));
        this->nrOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(ev.getNrPeople())));
        this->linkLineEdit->setText(QString::fromStdString(ev.getLink()));
    }
    else{
        this->titleLineEdit->setText("No events to display!");
        this->descriptionLineEdit->setText("No events to display!");
        this->dateAndTimeLineEdit->setText("No events to display!");
        this->nrOfPeopleLineEdit->setText("No events to display!");
        this->linkLineEdit->setText("No events to display!");
    }
}

void UserGUI::addEventUser() {
    std::string link = this->linkLineEdit->text().toStdString();
    std::vector<Event> allEvents = this->serv->getAll();
    int index=0;
    auto listSize = allEvents.size();
    for(index=0; index<listSize; index++)
        if(allEvents[index].getLink() == link)
            try {
                this->serv->addUserEventService(index);
            }
            catch (RepositoryException& re) {
                QMessageBox::critical(this, "Error#69420",QString::fromStdString(re.what()),"Please, forgiveness!");
                return;
            }

    this->populateTable();
    this->populateList();
}

void UserGUI::deleteEventUser() {
    int selectedIndex = this->getSelectedIndex();
    if(selectedIndex < 0){
        QMessageBox::critical(this, "Error#69420","No event was selected!","Please, forgiveness!");
        return;
    }
    Event ev = this->serv->getAllUser()[selectedIndex];
    this->serv->removeUserEventService(selectedIndex);
    this->populateTable();
    this->populateList();
}

void UserGUI::populateTable() {
    this->mainL->removeWidget(this->tableView);
    delete this->tableModel;
    delete this->tableView;
    this->tableModel = new TableModel{this->serv};
    this->tableView = new QTableView{};
    this->tableView->setModel(this->tableModel);
    this->mainL->addWidget(this->tableView);
    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void UserGUI::populateList() {
    this->userEventsListWidget->clear();
    int index=1;
    std::vector<Event> allUserEvents = this->serv->getAllUser();
    for(auto& ev : allUserEvents){
        this->userEventsListWidget->addItem(QString::fromStdString( std::to_string(index)+". " + ev.getTitle() +"\n"));
        index++;
    }

}

int UserGUI::getSelectedIndex() {
    QModelIndexList selectedIndexes = this->userEventsListWidget->selectionModel()->selectedIndexes();
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

void UserGUI::displayNextEvent() {
    std::string link = this->linkLineEdit->text().toStdString();
    std::vector<Event> allEvents = this->serv->getAll();
    if(link == ""){
        Event ev = allEvents[0];
        this->titleLineEdit->setText(QString::fromStdString(ev.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(ev.getDescription()));
        this->dateAndTimeLineEdit->setText(QString::fromStdString(ev.getDateAndTime()));
        this->nrOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(ev.getNrPeople())));
        this->linkLineEdit->setText(QString::fromStdString(ev.getLink()));
    }
    else {
        int i, savedIndex = 0;
        auto listSize = allEvents.size();
        for(i=0; i<listSize; i++){
            if(allEvents[i].getLink() == link){
                savedIndex = i+1;
                break;
            }
        }
        if(savedIndex >= listSize)
            savedIndex = 0;

        Event ev = allEvents[savedIndex];
        this->titleLineEdit->setText(QString::fromStdString(ev.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(ev.getDescription()));
        this->dateAndTimeLineEdit->setText(QString::fromStdString(ev.getDateAndTime()));
        this->nrOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(ev.getNrPeople())));
        this->linkLineEdit->setText(QString::fromStdString(ev.getLink()));
    }
}

void UserGUI::displayPrevEvent() {
    std::string link = this->linkLineEdit->text().toStdString();
    std::vector<Event> allEvents = this->serv->getAll();
    if(link == ""){
        Event ev = allEvents[0];
        this->titleLineEdit->setText(QString::fromStdString(ev.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(ev.getDescription()));
        this->dateAndTimeLineEdit->setText(QString::fromStdString(ev.getDateAndTime()));
        this->nrOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(ev.getNrPeople())));
        this->linkLineEdit->setText(QString::fromStdString(ev.getLink()));
    }
    else {
        int i, savedIndex = 0;
        auto listSize = allEvents.size();
        for(i=0; i<listSize; i++){
            if(allEvents[i].getLink() == link){
                break;
            }
        }
        if(i == 0)
            savedIndex = listSize-1;
        else
            savedIndex = i-1;

        Event ev = allEvents[savedIndex];
        this->titleLineEdit->setText(QString::fromStdString(ev.getTitle()));
        this->descriptionLineEdit->setText(QString::fromStdString(ev.getDescription()));
        this->dateAndTimeLineEdit->setText(QString::fromStdString(ev.getDateAndTime()));
        this->nrOfPeopleLineEdit->setText(QString::fromStdString(std::to_string(ev.getNrPeople())));
        this->linkLineEdit->setText(QString::fromStdString(ev.getLink()));
    }
}

void UserGUI::writeToCSV(){
    std::ofstream csvFile("CSVuserEvents.csv");
    csvFile << "Title" << "," << "Description" << "," << "Date and time" << "," << "Nr People" << "," << "Link" << "\n";
    std::vector<Event> events = this->serv->getAllUser();
    int i;
    Event ev;
    for(i=0; i<events.size(); i++) {
        ev = events[i];
        csvFile << ev.getTitle() << "," << ev.getDescription() << "," << ev.getDateAndTime() << "," << ev.getNrPeople() << "," << ev.getLink() << "\n";
    }
    csvFile.close();
}

void UserGUI::displayCSVEvents() {
    this->writeToCSV();
    system("CSVuserEvents.csv");
}

void UserGUI::writeToHTML() {
    std::ofstream htmlFile("HTMLuserEvents.html");

    htmlFile<<"<!DOCTYPE html>\n";
    htmlFile<<"<html>\n";
    htmlFile<<"<head>\n";
    htmlFile<<"<title>Events</title>\n";
    htmlFile<<"</head>\n";
    htmlFile<<"<body>\n";
    htmlFile<<"<table border=\"1\">\n";
    htmlFile<<"\t<tr>\n\t\t<td><b>Event title</b></td>\n\t\t<td><b>Description</b></td>\n\t\t<td><b>Date and time</b></td>\n\t\t<td><b>People attending</b></td>\n\t\t<td><b>Facebook link</b></td>\n\t</tr>\n";

    Event ev;
    std::vector<Event> events = this->serv->getAllUser();
    int i;
    for(i=0; i<events.size(); i++) {
        ev = events[i];
        htmlFile<<"\t<tr>\n\t\t<td>"<<ev.getTitle()<<"</td>\n\t\t<td>"<<ev.getDescription()<<"</td>\n\t\t<td>"<<ev.getDateAndTime()<<"</td>\n\t\t<td>"<<ev.getNrPeople()<<"</td>\n\t\t<td><a href=\"https://"<<ev.getLink()<<"\">"<<"Link"<<"</a></td>\n\t</tr>\n";
    }

    htmlFile<<"</table>";
    htmlFile<<"</body>";
    htmlFile<<"</html>";

    htmlFile.close();
}

void UserGUI::displayHTMLEvents() {
    this->writeToHTML();
    system("HTMLuserEvents.html");
}



// QT IMAGE INSERT

//QHBoxLayout *photoLayout = new QHBoxLayout{};
//QPixmap pixmap("cat.jpg");
//auto image = new QLabel();
//image->setPixmap(pixmap.scaled(100,100,Qt::KeepAspectRatio));
//photoLayout->addWidget(image);
//mainLayout->addLayout(photoLayout);
