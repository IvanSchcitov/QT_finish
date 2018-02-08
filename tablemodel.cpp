#include "tablemodel.h"

TableModel::TableModel(TreeItem *treeItem)
{
    treeIt = treeItem;
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
    if (role == Qt::DisplayRole || role == Qt::EditRole)
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

    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if (role != Qt::EditRole) return false;

    if(index.column() == 0){
        QString str = "";

        if(index.row() < sData.count()){
            str = sData[index.row()];
            sData.removeAt(index.row());
        }else if(index.row() >= sData.count() && index.row() < (iData.count() + sData.count())){
            str = QString::number(iData[index.row() - sData.count()]);
            iData.removeAt(index.row() - sData.count());
        }else if(index.row() >= (sData.count() + iData.count())){
            str = QString::number(fData[index.row() - (sData.count() + iData.count())]);
            fData.removeAt(index.row() - (sData.count() + iData.count()));
        }

        if(value.toString() == "string"){
            sData << str;
            str = "";
        }else if(value.toString() == "int"){
            iData << str.toInt();
            str = "";
        }else if(value.toString() == "float"){
            fData << str.toFloat();
            str = "";
        }
        treeIt->setListData(sData, iData, fData);
        return 1;
    }

    if(index.column() == 1){
        if((index.row()) < sData.count()){
            sData[index.row()] = value.toString();
        }else if((index.row()) >= sData.count() && (index.row() + 1) <= iData.count() + sData.count()){
            iData[index.row() - sData.count()] = value.toInt();
        }else if((index.row()) >= iData.count() + sData.count() && (index.row() + 1) <= rows){
            fData[index.row() - sData.count() - iData.count()] = value.toFloat();
        }
        treeIt->setListData(sData, iData, fData);
        return 1;
    }
//    stringCheck(str);
//    TreeItem *item = getItem(index);
//    bool result = item->setData(index.column(), value);
//    if (result) {
//        emit dataChanged(index, index);
//    }
//    return result;

    return 0;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return 0;
    return Qt::ItemIsEditable | /*QAbstractItemModel::flags(index) |*/ Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void TableModel::delString(QModelIndex index){

    if(index.row() >= 0){
        beginRemoveRows(QModelIndex(), index.row(), index.row());
            if(index.row() < sData.count()){
                sData.removeAt(index.row());
                --rows;
            }else if(index.row() >= sData.count() && index.row() < (iData.count() + sData.count())){
                iData.removeAt(index.row() - sData.count());
                --rows;
            }else if(index.row() >= (sData.count() + iData.count())){
                fData.removeAt(index.row() - (sData.count() + iData.count()));
                --rows;
            }
        endRemoveRows();
        treeIt->setListData(sData, iData, fData);
    }

}

void TableModel::addString(QModelIndex index){

    beginInsertRows(QModelIndex(), 0, 0);
        sData << "New String";
        rows++;
    endInsertRows();
    treeIt->setListData(sData, iData, fData);

}


