//
// Created by HarcioGG on 6/3/2021.
//

#ifndef GUIHOMEWORK_TABLEMODEL_H
#define GUIHOMEWORK_TABLEMODEL_H


#include <QAbstractTableModel>
#include <QWidget>
#include "../Business/UserService.h"
#include "../Business/Service.h"

class TableModel : public QAbstractTableModel {
private:
    UserService* serv;
public:
    TableModel(UserService*, QObject *parent = NULL);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};


#endif //GUIHOMEWORK_TABLEMODEL_H
