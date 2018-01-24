#include "tablemodel.h"

TableModel::TableModel(TreeItem *treeItem)
{
    treeItem->getListData(sData, iData, fData);
    rows = sData.count() + iData.count() + fData.count();
}

int TableModel::rowCount(const QModelIndex & /*parent*/) const
{
   return rows;
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(index.column() == 0){
            if((index.row() + 1) <= sData.count()){
                return QString("string");
            }
            if((index.row() + 1) > sData.count() && (index.row() + 1) <= iData.count() + sData.count()){
                return QString("int");
            }
            if((index.row() + 1) > iData.count() + sData.count() && (index.row() + 1) <= rows){
                return QString("float");
            }
        }
        if(index.column() == 1){
            if((index.row()) < sData.count()){
                return QString(sData[index.row()]);
            }
            if((index.row()) >= sData.count() && (index.row() + 1) <= iData.count() + sData.count()){
                return QString(QString::number(iData[index.row() - sData.count()]));
            }
            if((index.row()) >= iData.count() + sData.count() && (index.row() + 1) <= rows){
                return QString(QString::number(fData[index.row() - sData.count() - iData.count()]));
            }
        }

//       return QString("Row%1, Column%2")
//                   .arg(index.row() + 1)
//                   .arg(index.column() +1);
//        return QString("%1, %2")
//                    .arg("string")
//                    .arg(sData[0]);
    }
    return QVariant();
}
