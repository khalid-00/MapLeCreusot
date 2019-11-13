#ifndef MODELDATA_H
#define MODELDATA_H
#include <map>
#include <osmium/osm.hpp>
#include <string>
#include <modelDataStructure.h>

#include <osmium/index/map/flex_mem.hpp>
#include <modelDataHandler.h>

class modelData
{
    using locationType = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
    using tagPair = std::pair<std::string,std::string>;
    using idType = osmium::unsigned_object_id_type;
    locationType m_NodesLocation;
    std::map<idType, nodeData> m_NodeMap;
    std::map<idType, wayData> m_WayMap;
    std::map<idType, relationData> m_RelationMap;

    friend class modelDataHandler;

public:
    modelData(){}

    const osmium::Location getNodeLoaction(idType id)
    {
        return m_NodesLocation.get(id);
    }

    const nodeData getNodeData(idType id)
    {
        return m_NodeMap.at(id);
    }

    const wayData getWayData(idType id)
    {
        return m_WayMap.at(id);
    }

    const relationData getRelationData(idType id)
    {
        return m_RelationMap.at(id);
    }

    const map<idType,nodeData> getNodeMap()
    {
        return m_NodeMap;
    }

    const map<idType,wayData> getWayMap()
    {
        return m_WayMap;
    }

    const map<idType,relationData> getRelationMap()
    {
        return m_RelationMap;
    }

};

#endif // MODELDATA_H
