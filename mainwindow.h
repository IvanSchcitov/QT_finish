#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets>
#include <QFile>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateActions(); //слот для обновления состояния кнопок

private:
    Ui::MainWindow *ui;

private slots: //слоты для действий, выполняемых по кнопкам
    void insertChild();

    void insertRow();

    void removeRow();
public slots: //для реализации сигнала selectionChanged у QTreeView::selectionModel
    void updateActions(const QItemSelection &,const QItemSelection &);
};

#endif // MAINWINDOW_H
