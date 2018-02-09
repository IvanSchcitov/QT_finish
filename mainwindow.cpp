#include "mainwindow.h"
#include "ui_mainwindow.h"


TreeModel *model;
TableModel *t_model;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbCreate,SIGNAL(clicked()),this,SLOT(insertRow()));
    connect(ui->pbDelete,SIGNAL(clicked()),this,SLOT(removeRow()));
    connect(ui->pbCreateNode,SIGNAL(clicked()),this,SLOT(insertChild()));
    connect(ui->pbAdd,SIGNAL(clicked()),this,SLOT(insertTableRow()));
    connect(ui->pbDel,SIGNAL(clicked()),this,SLOT(removeTableRow()));
    //и обновить состояние кнопок:
//    updateActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertChild() {
    if(!model) return;
    //Получаем модельный индекс и модель элемента:
    QModelIndex index = ui->TreeView_obj->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->TreeView_obj->model();
    //Вставляем данные:
    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index)) return;
    }
    if (!model->insertRow(0, index)) return;
    //Инициализируем их:
    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("Данные"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("Столбец"), Qt::EditRole);
    }
    //Выбираем вставленный узел:
    ui->TreeView_obj->selectionModel()->setCurrentIndex(model->index(0, 0, index),
    QItemSelectionModel::ClearAndSelect);
    //Меняем состояние кнопок:
    updateActions();
}

void MainWindow::insertRow() {
    if(!model) return;
    QModelIndex index = ui->TreeView_obj->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->TreeView_obj->model();
    if (!model->insertRow(index.row()+1, index.parent())) return;
    updateActions();
    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("Данные"), Qt::EditRole);
    }
}

void MainWindow::removeRow() {
    if(!model) return;
    QModelIndex index = ui->TreeView_obj->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->TreeView_obj->model();
    if (model->removeRow(index.row(), index.parent())) updateActions();
}


void MainWindow::updateActions(const QItemSelection &selected, const QItemSelection &deselected) {
    QModelIndex index = ui->TreeView_obj->selectionModel()->currentIndex();
    if(t_model) delete t_model;
    t_model = new TableModel(model->getItemPublic(index));
    ui->tableView->setModel(t_model);
    QComboBoxDelegate *delegate = new QComboBoxDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, delegate);
    for (int column = 0; column < t_model->columnCount(); ++column) ui->tableView->setColumnWidth(column, (ui->tableView->width()-17) / 2);

    updateActions();
}

void MainWindow::updateActions() {
    //Обновим состояние кнопок:
    bool hasSelection = !ui->TreeView_obj->selectionModel()->selection().isEmpty();
    ui->pbDelete->setEnabled(hasSelection);
    bool hasCurrent = ui->TreeView_obj->selectionModel()->currentIndex().isValid();
    ui->pbCreate->setEnabled(hasCurrent);
    //Покажем информацию в заголовке окна:
    if (hasCurrent) {
    ui->TreeView_obj->closePersistentEditor(ui->TreeView_obj->selectionModel()->currentIndex());
        int row = ui->TreeView_obj->selectionModel()->currentIndex().row();
        int column = ui->TreeView_obj->selectionModel()->currentIndex().column();
        if (ui->TreeView_obj->selectionModel()->currentIndex().parent().isValid())
            this->setWindowTitle(tr("(row,col)=(%1,%2)").arg(row).arg(column));
        else
            this->setWindowTitle(tr("(row,col)=(%1,%2) ВЕРХ").arg(row).arg(column));
    }
}

void MainWindow::insertTableRow() {
    if(!t_model) return;

    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    t_model->addString(index);

}

void MainWindow::removeTableRow() {
    if(!t_model) return;

    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    t_model->delString(index);

}

void MainWindow::on_pbLoadXML_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.xml");
    if(str == "") return;

    QFile file(str);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << file.errorString();
        exit(0);
    }


    //Создаем заголовки столбцов:
    QString headers;
    headers = "Nodes";
    //Загружаем данные в модель:
    model = new TreeModel(headers, file);
    file.close();
    ui->TreeView_obj->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column) ui->TreeView_obj->resizeColumnToContents(column);

    connect(ui->TreeView_obj->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
            this, SLOT(updateActions(const QItemSelection&,const QItemSelection&)));
}

void MainWindow::on_pbSaveXML_clicked()
{
    if(!model){
        QMessageBox MesBox;
        MesBox.setText("XML is not loading");
        MesBox.exec();
        return;
    }

    QString str = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("XML Files (*.xml)"));

    if (str != "") {
            QFile file(str);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox MesBox;
                MesBox.setText("Couldn't open File for save");
                MesBox.exec();
            } else {
                model->saveXML(file);
                file.close();
            }
        }
}
