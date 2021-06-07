#ifndef ADDRECORDDIALOG_H
#define ADDRECORDDIALOG_H

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AddRecordDialog; }
QT_END_NAMESPACE

class AddRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecordDialog(QWidget *parent = nullptr);
    ~AddRecordDialog();

    QList<QString> createRecord();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddRecordDialog *ui;
};

#endif // ADDRECORDDIALOG_H
