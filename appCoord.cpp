//
// Created by HarcioGG on 5/18/2021.
//

#include <QPushButton>
#include <QVBoxLayout>
#include <QLayout>
#include <QApplication>
#include "appCoord.h"
#include "Persistence/FileRepository.h"
#include "Business/Service.h"
#include "Presentation/GUI.h"
#include "Business/UserService.h"
#include "Presentation/UserGUI.h"
#include "Persistence/UndoRedoRepo.h"


appCoord::appCoord() {
    this->initGUI();
    this->connectSignalsAndSlots();
}

void appCoord::initGUI() {
    this->adminButton = new QPushButton{"Admin mode"};
    this->userButton = new QPushButton{"User mode"};
    this->closeButton = new QPushButton{"Exit"};

    QVBoxLayout *mainLayout = new QVBoxLayout{this};

    QGridLayout *buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->adminButton,0,0);
    buttonsLayout->addWidget(this->userButton,0,1);
    buttonsLayout->addWidget(this->closeButton,0,2);

    mainLayout->addLayout(buttonsLayout);
}

void appCoord::connectSignalsAndSlots() {
    QObject::connect(this->adminButton, &QPushButton::clicked, this, &appCoord::runAdminMode);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &appCoord::runUserMode);
    QObject::connect(this->closeButton, &QPushButton::clicked, this, &appCoord::closeApp);
}

void appCoord::runAdminMode() {
    auto *undoRepo = new UndoRedoRepo();
    auto *redoRepo = new UndoRedoRepo();
    auto *repo = new FileRepository("events.log");
    auto *adminSrv = new AdministratorService(repo, undoRepo, redoRepo);

    auto *validator = new Validator();

    auto *gui = new GUI(adminSrv, validator);

    gui->resize(1280, 720);
    gui->show();
}

void appCoord::runUserMode() {
    auto *repo = new FileRepository("events.log");
    auto *usrRepo = new FileRepository("userEvents.log");
    auto *userSrv = new UserService(repo, usrRepo);

    auto *userGui = new UserGUI(userSrv);

    userGui->resize(1280, 920);
    userGui->show();
}

void appCoord::closeApp() {
    close();
}



