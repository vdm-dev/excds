#ifndef VEHICLEITEMNODE_H
#define VEHICLEITEMNODE_H


#include <QList>
#include <QIcon>


class VehicleItemNode
{
public:
    VehicleItemNode(VehicleItemNode* parent = Q_NULLPTR);
    VehicleItemNode(const QString& name, VehicleItemNode* parent = Q_NULLPTR);
    virtual ~VehicleItemNode();

    const QString& name() const;
    void setName(const QString& newName);

    const QString& description() const;
    void setDescription(const QString& newDescription);

    const QIcon& icon() const;
    void setIcon(const QIcon& newIcon);

private:
    VehicleItemNode* _parent;
    QList<VehicleItemNode*> _children;
    QString _name;
    QString _description;
    QIcon _icon;
};


inline const QString& VehicleItemNode::name() const
{
    return _name;
}

inline void VehicleItemNode::setName(const QString& newName)
{
    _name = newName;
}

inline const QString& VehicleItemNode::description() const
{
    return _description;
}

inline void VehicleItemNode::setDescription(const QString& newDescription)
{
    _description = newDescription;
}

inline const QIcon& VehicleItemNode::icon() const
{
    return _icon;
}

inline void VehicleItemNode::setIcon(const QIcon& newIcon)
{
    _icon = newIcon;
}


#endif // VEHICLEITEMNODE_H
