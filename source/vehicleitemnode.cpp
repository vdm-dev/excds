#include "vehicleitemnode.h"


VehicleItemNode::VehicleItemNode(VehicleItemNode* parent)
    : _parent(parent)
{

}

VehicleItemNode::VehicleItemNode(const QString& name, VehicleItemNode* parent)
    : _parent(parent)
    , _name(name)
{

}

VehicleItemNode::~VehicleItemNode()
{
    for (int i = 0; i < _children.size(); ++i)
    {
        if (_children[i])
            delete _children[i];
    }
}
