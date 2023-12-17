#ifndef SIMPLEECUDATABASE_H
#define SIMPLEECUDATABASE_H


#include "iecudatabase.h"

#include <QList>


class SimpleEcuDatabase : public IEcuDatabase
{
public:
    SimpleEcuDatabase();

    virtual int countOfBrands() const;

protected:
    QList<BrandEntry> _brands;
};


#endif // SIMPLEECUDATABASE_H
