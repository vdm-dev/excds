#ifndef VEHICLEITEMMODEL_H
#define VEHICLEITEMMODEL_H


#include <QStandardItemModel>


class QXmlStreamReader;


class VehicleItemModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit VehicleItemModel(QObject* parent = nullptr);
    virtual ~VehicleItemModel();

    void load(const QString& fileName);

private:
    void readBrands(QXmlStreamReader& xml, QStandardItem* brands);
    void readBrand(QXmlStreamReader& xml, QStandardItem* brand);
    void readModels(QXmlStreamReader& xml, QStandardItem* brand);
    void readModel(QXmlStreamReader& xml, QStandardItem* model);
    void readGenerations(QXmlStreamReader& xml, QStandardItem* models);
    void readGeneration(QXmlStreamReader& xml, QStandardItem* generation);
    void readModules(QXmlStreamReader& xml, QStandardItem* generation);
    void readModule(QXmlStreamReader& xml, QStandardItem* module);
};


#endif // VEHICLEITEMMODEL_H
