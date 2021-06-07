#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QList>

class Model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void loadcsv(const QString &path);
    void savecsv(const QString &path);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void appendRow(QList<QString> newRow);
    void removeRow(int row);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<QList<QString>> room;
    QList<QString> columns;
};

#endif // MODEL_H
