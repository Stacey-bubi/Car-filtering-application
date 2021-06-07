#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
public:
    explicit ProxyModel(QObject *parent = nullptr);


    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    void load(const QString &path);
    void save(const QString &path);

    int heightMin;
    int heightMax;
    int lengthMin;
    int lengthMax;
    int widthMin;
    int widthMax;
    bool includeUnknown;
    QList<QString> drivelines;
    QString fuelTypeString;
    int yearMin;
    int yearMax;
    QString searchQuery;
    QList<QString> makesToExclude;
};

#endif // PROXYMODEL_H
