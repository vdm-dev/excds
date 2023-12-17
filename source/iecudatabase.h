#ifndef IECUDATABASE_H
#define IECUDATABASE_H


#include <QString>
#include <QIcon>
#include <QPixmap>


struct BrandEntry
{
    int id;
    QString name;
    QString description;
    QIcon icon;
    QPixmap picture;
};

struct ModelEntry
{
    int id;
    int brand;
    QString name;
    QString description;
    QPixmap picture;
};

struct GenerationEntry
{
    int id;
    int model;
    QString name;
    QString description;
    QPixmap picture;
};

struct EcuEntry
{
    int id;
    int generation;
    QString name;
    QString description;
    QPixmap picture;
};


class IEcuDatabase
{
public:
    IEcuDatabase() { }
    virtual ~IEcuDatabase() { }

    virtual int countOfBrands() const = 0;
};


#endif // IECUDATABASE_H
