#include "model.h"
#include <QFile>
#include <QTextStream>

Model::Model(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return room.size();
}

int Model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columns.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    QString data = room[index.row()][index.column()];
    switch (index.column())
    {
    case 0:
    case 1:
    case 2:
        return data.toInt();
    case 3:
    case 4:
        return data;
    case 5:
        return data == "True" || data == "true";
    case 6:
        return data.toInt();
    case 7:
        return data;
    case 8:
        return data.toInt();
    case 9:
        return data;
    case 10:
        return data.toInt();
    case 11:
    case 12:
    case 13:
    case 14:
        return data;
    case 15:
    case 16:
    case 17:
        return data.toInt();
    }

    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation != Qt::Horizontal)
        return section + 1;
    return columns.value(section);
}

void Model::appendRow(QList<QString> newRow)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    room.append(newRow);
    endInsertRows();
}

void Model::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    room.removeAt(row);
    endRemoveRows();
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {

        room[index.row()][index.column()] = value.toString();

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

void Model::loadcsv(const QString &path)
{
    QFile f(path);
    f.open(QFile::ReadOnly | QFile::Text);

    QTextStream fs(&f);
    while (!fs.atEnd())
    {
        QString newLine = fs.readLine();

        QList<QString> newRow;
        for (QString item : newLine.split(","))
        {
            if (item.startsWith('"') && item.endsWith('"'))
                item = item.mid(1, item.size() - 2);
            newRow.append(item);
        }

        if (columns.isEmpty())
        {
            beginInsertColumns(QModelIndex(), 0, newRow.size() - 1);
            columns = newRow;
            endInsertColumns();
        }
        else
        {
            appendRow(newRow);
        }
    }

    f.close();
}

void Model::savecsv(const QString &path)
{
    QFile f(path);
    f.open(QFile::WriteOnly | QFile::Text);

    QTextStream fs(&f);
    for (int column = 0; column < columns.size(); column++)
    {
        if (column != 0)
            fs << ',';
        fs << '"' << columns[column] << '"';
    }
    fs << '\n';
    for (int row = 0; row < room.size(); row++)
    {
        for (int column = 0; column < columns.size(); column++)
        {
            if (column != 0)
                fs << ',';
            fs << '"' << room[row][column] << '"';
        }
        fs << '\n';
    }

    f.close();
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

