#include "proxymodel.h"
#include <QFile>
#include <QDataStream>

ProxyModel::ProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}



bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    int height = sourceModel()->index(sourceRow, 0, sourceParent).data().toInt();
    if (height == 0)
    {
        if (!includeUnknown)
            return false;
    }
    else if (height < heightMin || height > heightMax)
        return false;

    int length = sourceModel()->index(sourceRow, 1, sourceParent).data().toInt();
    if (length == 0)
    {
        if (!includeUnknown)
            return false;
    }
    else if (length < lengthMin || length > lengthMax)
        return false;

    int width = sourceModel()->index(sourceRow, 2, sourceParent).data().toInt();
    if (width == 0)
    {
        if (!includeUnknown)
            return false;
    }
    else if (width < widthMin || width > widthMax)
        return false;

    QString driveline = sourceModel()->index(sourceRow, 3, sourceParent).data().toString();
    if (!drivelines.isEmpty() && !drivelines.contains(driveline))
        return false;

    QString fuelType = sourceModel()->index(sourceRow, 9, sourceParent).data().toString();
    if (!fuelTypeString.isEmpty() && fuelType != fuelTypeString)
        return false;

    int year = sourceModel()->index(sourceRow, 15, sourceParent).data().toInt();
    if (year < yearMin || year > yearMax)
        return false;

    QString id = sourceModel()->index(sourceRow, 12, sourceParent).data().toString();
    if (!searchQuery.isEmpty() && !id.contains(searchQuery))
        return false;

    QString make = sourceModel()->index(sourceRow, 13, sourceParent).data().toString();
    if (!makesToExclude.isEmpty() && makesToExclude.contains(make))
        return false;

    return true;
}

void ProxyModel::load(const QString &path)
{
    QFile f(path);
    f.open(QFile::ReadOnly);

    QDataStream ds(&f);
    ds >> heightMin >> heightMax >> lengthMin >> lengthMax >> widthMin >> widthMax >> includeUnknown >> drivelines >> fuelTypeString >> yearMin >> yearMax >> searchQuery >> makesToExclude;

    f.close();

    invalidate();
}

void ProxyModel::save(const QString &path)
{
    QFile f(path);
    f.open(QFile::WriteOnly);

    QDataStream ds(&f);
    ds << heightMin << heightMax << lengthMin << lengthMax << widthMin << widthMax << includeUnknown << drivelines << fuelTypeString << yearMin << yearMax << searchQuery << makesToExclude;

    f.close();
}
