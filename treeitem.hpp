#ifndef TREEITEM_HPP
#define TREEITEM_HPP

#include <QList>
#include <QVector>
#include <QVariant>

class TreeItem
{
public:
    //TreeItem();
    explicit TreeItem (const QString &data,
        TreeItem *parent = 0); //Конструктор узла дерева
    ~TreeItem();               //...и деструктор

    void appendChild(TreeItem *child); //Добавить узел-потомок
    TreeItem *child(int row); //Вернуть дочерний элемент
    int childCount() const; //Количество дочерних элементов
    int columnCount() const; //Вернуть количество столбцов элемента
    QVariant data(int column) const; //Вернуть данные указанного столбца
    int childNumber() const; //Вернуть номер строки элемента

    TreeItem *parentItem(); //Вернуть родительский элемент
    bool insertChildren(int position, int count, int columns); //Вставить потомков (строки)
    bool removeChildren(int position, int count);  //Удалить потомков
    bool setData(int column, const QVariant &value); //Установить данные

    bool initListData(QString type, QString data);
    void getListData(QList<QString> &sData, QList<int> &iData, QList<float> &fData);
    void setListData(QList<QString> sData, QList<int> iData, QList<float> fData);

private: //Внутреннее представление данных:
    QList <TreeItem*> m_childItems; //Список дочерних элементов
    QString m_itemData; //Список данных текущего узла
    TreeItem *m_parentItem; //Ссылка на родительский узел

    QList <QString> m_stringData; //Список данных листа типа String
    QList <int> m_intData; //Список данных листа типа Int
    QList <float> m_floatData; //Список данных листа типа Float
};

#endif // TREEITEM_HPP
