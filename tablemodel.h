#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "treeitem.hpp"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(TreeItem* treeItem);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    int rows;
    QList<QString> sData;
    QList<int> iData;
    QList<float> fData;
};

#endif // TABLEMODEL_H
