#include "vehicleitemmodel.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QUuid>


VehicleItemModel::VehicleItemModel(QObject* parent)
    : QStandardItemModel(parent)
{
}

VehicleItemModel::~VehicleItemModel()
{
}

void VehicleItemModel::load(const QString& fileName)
{
    clear();

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return;

    QXmlStreamReader xml(&file);

    while (xml.readNextStartElement())
    {
        if (xml.name() != QLatin1String("brands"))
        {
            xml.skipCurrentElement();
            continue;
        }

        readBrands(xml, invisibleRootItem());
    }
}

void VehicleItemModel::readBrands(QXmlStreamReader& xml, QStandardItem* brands)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() != QLatin1String("brand"))
        {
            xml.skipCurrentElement();
            continue;
        }

        auto name = xml.attributes().value(QLatin1String("name")).toString();
        auto brand = new QStandardItem(name);
        auto flags = brand->flags();
        flags.setFlag(Qt::ItemIsEditable, false);
        brand->setFlags(flags);

        readBrand(xml, brand);

        brands->appendRow(brand);
    }
}

void VehicleItemModel::readBrand(QXmlStreamReader& xml, QStandardItem* brand)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("image"))
        {
            auto iconName = xml.readElementText();
            if (!iconName.isEmpty())
                brand->setIcon(QIcon(iconName));
        }
        else if (xml.name() == QLatin1String("description"))
        {
            brand->setStatusTip(xml.readElementText());
        }
        else if (xml.name() == QLatin1String("models"))
        {
            readModels(xml, brand);
        }
        else
        {
            xml.skipCurrentElement();
        }
    }
}

void VehicleItemModel::readModels(QXmlStreamReader& xml, QStandardItem* brand)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() != QLatin1String("model"))
        {
            xml.skipCurrentElement();
            continue;
        }

        auto name = xml.attributes().value(QLatin1String("name")).toString();
        auto model = new QStandardItem(name);
        auto flags = model->flags();
        flags.setFlag(Qt::ItemIsEditable, false);
        model->setFlags(flags);

        readModel(xml, model);

        brand->appendRow(model);
    }
}

void VehicleItemModel::readModel(QXmlStreamReader& xml, QStandardItem* model)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("image"))
        {
            auto iconName = xml.readElementText();
            if (!iconName.isEmpty())
                model->setIcon(QIcon(iconName));
        }
        else if (xml.name() == QLatin1String("description"))
        {
            model->setStatusTip(xml.readElementText());
        }
        else if (xml.name() == QLatin1String("generations"))
        {
            readGenerations(xml, model);
        }
        else
        {
            xml.skipCurrentElement();
        }
    }
}

void VehicleItemModel::readGenerations(QXmlStreamReader& xml, QStandardItem* model)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() != QLatin1String("generation"))
        {
            xml.skipCurrentElement();
            continue;
        }

        auto name = xml.attributes().value(QLatin1String("name")).toString();
        auto generation = new QStandardItem(name);
        auto flags = generation->flags();
        flags.setFlag(Qt::ItemIsEditable, false);
        generation->setFlags(flags);

        readGeneration(xml, generation);

        model->appendRow(generation);
    }
}

void VehicleItemModel::readGeneration(QXmlStreamReader& xml, QStandardItem* generation)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("image"))
        {
            auto iconName = xml.readElementText();
            if (!iconName.isEmpty())
                generation->setIcon(QIcon(iconName));
        }
        else if (xml.name() == QLatin1String("description"))
        {
            generation->setStatusTip(xml.readElementText());
        }
        else if (xml.name() == QLatin1String("modules"))
        {
            readModules(xml, generation);
        }
        else
        {
            xml.skipCurrentElement();
        }
    }
}

void VehicleItemModel::readModules(QXmlStreamReader& xml, QStandardItem* generation)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() != QLatin1String("module"))
        {
            xml.skipCurrentElement();
            continue;
        }

        auto name = xml.attributes().value(QLatin1String("name")).toString();
        auto module = new QStandardItem(name);
        auto flags = module->flags();
        flags.setFlag(Qt::ItemIsEditable, false);
        module->setFlags(flags);

        readModule(xml, module);

        generation->appendRow(module);
    }
}

void VehicleItemModel::readModule(QXmlStreamReader& xml, QStandardItem* module)
{
    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("image"))
        {
            auto iconName = xml.readElementText();
            if (!iconName.isEmpty())
                module->setIcon(QIcon(iconName));
        }
        else if (xml.name() == QLatin1String("description"))
        {
            module->setStatusTip(xml.readElementText());
        }
        else if (xml.name() == QLatin1String("uuid"))
        {
            auto uuid = QUuid::fromString(xml.readElementText());
            module->setData(uuid);
        }
        else
        {
            xml.skipCurrentElement();
        }
    }
}

