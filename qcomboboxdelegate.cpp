#include "qcomboboxdelegate.h"

QComboBoxDelegate::QComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *QComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QComboBox *edit = new QComboBox(parent);
    edit->setAutoFillBackground(true);
    return edit;
}

void QComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QComboBox *edit = static_cast<QComboBox*>(editor);
    edit->addItem("string");
    edit->addItem("int");
    edit->addItem("float");
}

void QComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QComboBox *edit = static_cast<QComboBox*>(editor);
    if(model->setData(index, edit->currentText()) == 0){
        QMessageBox MesBox;
        MesBox.setText("Wrong type for this value");
        MesBox.exec();
    }
}

void QComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    editor->setGeometry(option.rect);
}
