#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addrecorddialog.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    carsmodel = new Model(this);
    proxymodel = new ProxyModel(this);
    proxymodel->setSourceModel(carsmodel);
    ui->tableView->setModel(proxymodel);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete carsmodel;
    delete proxymodel;
}

void MainWindow::on_actionLoad_data_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath(), "CSV files (*.csv)");
    if (!fileName.isEmpty())
    {
        carsmodel->loadcsv(fileName);
        if (carsmodel->rowCount() > 0)
        {
            int heightMin = 999999;
            int heightMax = 0;
            int lengthMin = 999999;
            int lengthMax = 0;
            int widthMin = 999999;
            int widthMax = 0;
            QSet<QString> drivelines;
            QSet<QString> fuelTypes;
            int yearMin = 999999;
            int yearMax = 0;
            for (int row = 0; row < carsmodel->rowCount(); row++)
            {
                int height = carsmodel->index(row, 0).data().toInt();
                if (height != 0)
                {
                    if (height < heightMin)
                        heightMin = height;
                    if (height > heightMax)
                        heightMax = height;
                }

                int length = carsmodel->index(row, 1).data().toInt();
                if (length != 0)
                {
                    if (length < lengthMin)
                        lengthMin = length;
                    if (length > lengthMax)
                        lengthMax = length;
                }

                int width = carsmodel->index(row, 2).data().toInt();
                if (width != 0)
                {
                    if (width < widthMin)
                        widthMin = width;
                    if (width > widthMax)
                        widthMax = width;
                }

                QString driveline = carsmodel->index(row, 3).data().toString();
                drivelines.insert(driveline);

                QString fuelType = carsmodel->index(row, 9).data().toString();
                fuelTypes.insert(fuelType);

                int year = carsmodel->index(row, 15).data().toInt();
                if (year != 0)
                {
                    if (year < yearMin)
                        yearMin = year;
                    if (year > yearMax)
                        yearMax = year;
                }
            }

            ui->heightMin->setRange(heightMin, heightMax);
            ui->heightMax->setRange(heightMin, heightMax);
            ui->heightMin->setValue(heightMin);
            ui->heightMax->setValue(heightMax);

            ui->lengthMin->setRange(lengthMin, lengthMax);
            ui->lengthMax->setRange(lengthMin, lengthMax);
            ui->lengthMin->setValue(lengthMin);
            ui->lengthMax->setValue(lengthMax);

            ui->widthMin->setRange(widthMin, widthMax);
            ui->widthMax->setRange(widthMin, widthMax);
            ui->widthMin->setValue(widthMin);
            ui->widthMax->setValue(widthMax);

            ui->driveline->clear();
            for (QString driveline : drivelines)
            {
                QListWidgetItem *item = new QListWidgetItem(driveline);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(Qt::Unchecked);
                ui->driveline->addItem(item);
            }

            ui->fuelType->clear();
            ui->fuelType->addItem("");
            for (QString fuelType : fuelTypes)
                ui->fuelType->addItem(fuelType);

            ui->yearMin->setRange(yearMin, yearMax);
            ui->yearMax->setRange(yearMin, yearMax);
            ui->yearMin->setValue(yearMin);
            ui->yearMax->setValue(yearMax);

            ui->search->click();
        }
    }
}

void MainWindow::on_actionSave_data_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Name", QDir::homePath(), "CSV files (*.csv)" );
    if (!fileName.isEmpty())
        carsmodel->savecsv(fileName);
}

void MainWindow::on_actionAdd_record_triggered()
{
    AddRecordDialog *dialog = new AddRecordDialog(this);
    QList<QString> row = dialog->createRecord();
    if (!row.isEmpty())
        carsmodel->appendRow(row);
    delete dialog;
}


void MainWindow::on_search_clicked()
{
    proxymodel->heightMin = ui->heightMin->value();
    proxymodel->heightMax = ui->heightMax->value();
    proxymodel->lengthMin = ui->lengthMin->value();
    proxymodel->lengthMax = ui->lengthMax->value();
    proxymodel->widthMin = ui->widthMin->value();
    proxymodel->widthMax = ui->widthMax->value();
    proxymodel->includeUnknown = ui->includeUnknown->isChecked();
    proxymodel->drivelines.clear();
    for (int row = 0; row < ui->driveline->count(); row++)
    {
        if (ui->driveline->item(row)->checkState() == Qt::Checked)
            proxymodel->drivelines.append(ui->driveline->item(row)->text());
    }
    proxymodel->fuelTypeString = ui->fuelType->currentText();
    proxymodel->yearMin = ui->yearMin->value();
    proxymodel->yearMax = ui->yearMax->value();
    proxymodel->searchQuery = ui->searchQuery->text();
    proxymodel->makesToExclude = ui->makesToExclude->text().split(',');
    proxymodel->invalidate();
}

void MainWindow::on_deleteRow_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    index = proxymodel->mapToSource(index);
    carsmodel->removeRow(index.row());
}


void MainWindow::on_actionSave_search_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Name", QDir::homePath(), "Search files (*.search)");
    if (!fileName.isEmpty())
        proxymodel->save(fileName);
}


void MainWindow::on_actionLoad_search_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath(), "Search files (*.search)");
    if (!fileName.isEmpty())
    {
        proxymodel->load(fileName);
        ui->heightMin->setValue(proxymodel->heightMin);
        ui->heightMax->setValue(proxymodel->heightMax);
        ui->lengthMin->setValue(proxymodel->lengthMin);
        ui->lengthMax->setValue(proxymodel->lengthMax);
        ui->widthMin->setValue(proxymodel->widthMin);
        ui->widthMax->setValue(proxymodel->widthMax);
        ui->includeUnknown->setChecked(proxymodel->includeUnknown);
        for (int row = 0; row < ui->driveline->count(); row++)
        {
            if (proxymodel->drivelines.contains(ui->driveline->item(row)->text()))
                ui->driveline->item(row)->setCheckState(Qt::Checked);
            else
                ui->driveline->item(row)->setCheckState(Qt::Unchecked);
        }
        ui->fuelType->setCurrentText(proxymodel->fuelTypeString);
        ui->yearMin->setValue(proxymodel->yearMin);
        ui->yearMax->setValue(proxymodel->yearMax);
        ui->searchQuery->setText(proxymodel->searchQuery);
        ui->makesToExclude->setText(QStringList(proxymodel->makesToExclude).join(','));
    }
}


void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->exec();
    delete dialog;
}

