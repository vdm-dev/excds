#ifndef IADAPTER_H
#define IADAPTER_H


#include <QObject>
#include <QIcon>


class QWidget;


class IAdapter : public QObject
{
    Q_OBJECT

public:
    IAdapter(QObject* parent = nullptr) : QObject(parent) { }
    virtual ~IAdapter() { }

    virtual bool open() = 0;
    virtual void close() = 0;

    virtual void reconfigure() = 0;

    virtual bool isOpen() const = 0;

    virtual QIcon icon() const = 0;
    virtual QString name() const = 0;

    virtual QWidget* widget() = 0;
};


#endif // IADAPTER_H
