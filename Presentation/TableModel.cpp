//
// Created by HarcioGG on 6/3/2021.
//

#include "TableModel.h"
#include <vector>

TableModel::TableModel(UserService *service, QObject *parent) {
    this->serv = service;
}

int TableModel::rowCount(const QModelIndex &parent) const {
    return this->serv->getAllUser().size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    std::vector<Event> allEvents = this->serv->getAllUser();
    int row = index.row();
    int col = index.column();
    if(role == Qt::DisplayRole){
        if(col == 0){
            return QString::fromStdString(allEvents[row].getTitle());
        }
        else if(col == 1){
            return QString::fromStdString(allEvents[row].getDescription());
        }
        else if(col == 2){
            return QString::fromStdString(allEvents[row].getDateAndTime());
        }
        else if(col == 3){
            return allEvents[row].getNrPeople();
        }
        else if(col == 4){
            return QString::fromStdString(allEvents[row].getLink());
        }
    }
    return QVariant();
}
