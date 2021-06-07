#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QList>
#include "model.h"
#include "proxymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_data_triggered();

    void on_actionSave_data_triggered();

    void on_actionAdd_record_triggered();

    void on_search_clicked();

    void on_deleteRow_clicked();

    void on_actionSave_search_triggered();

    void on_actionLoad_search_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    Model *carsmodel;
    ProxyModel *proxymodel;
};

#endif // MAINWINDOW_H
