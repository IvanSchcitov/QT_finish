#ifndef QCOMBOBOXDELEGATE_H
#define QCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QMessageBox>


class QComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QComboBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // QCOMBOBOXDELEGATE_H
