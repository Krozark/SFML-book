#include <SFML-utils/map/VLayer.hpp>

namespace sfutils
{
    namespace map
    {
        VLayer::VLayer(const std::string& type,int z,bool isStatic) :_isStatic(isStatic), _type(type), _z(z)
        {
        }

        VLayer::~VLayer()
        {
        }

        int VLayer::z()const
        {
            return _z;
        }

        const std::string& VLayer::getType()const
        {
            return _type;
        }

        bool VLayer::isStatic()const
        {
            return _isStatic;
        }


    }
}
