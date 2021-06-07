#include "addrecorddialog.h"
#include "ui_addrecorddialog.h"

AddRecordDialog::AddRecordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddRecordDialog)
{
    ui->setupUi(this);
}

AddRecordDialog::~AddRecordDialog()
{
    delete ui;
}

QList<QString> AddRecordDialog::createRecord()
{
    if (exec())
    {
        return QList<QString>()
                << QString::number(ui->height->value())
                << QString::number(ui->length->value())
                << QString::number(ui->width->value())
                << ui->driveline->text()
                << ui->engineType->text()
                << "True"
                << QString::number(ui->numberOfForwardGears->value())
                << ui->transmission->text()
                << QString::number(ui->cityMpg->value())
                << ui->fuelType->text()
                << QString::number(ui->highwayMpg->value())
                << ui->classification->text()
                << ui->id->text()
                << ui->make->text()
                << ui->modelYear->text()
                << QString::number(ui->year->value())
                << QString::number(ui->horsepower->value())
                << QString::number(ui->torque->value());
    }
    else
    {
        return QList<QString>();
    }
}

void AddRecordDialog::on_pushButton_clicked()
{
    accept();
}
