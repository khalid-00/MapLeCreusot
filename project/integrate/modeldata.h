#ifndef MODELDATA_H
#define MODELDATA_H
#include <map>
#include <osmium/osm.hpp>
#include <string>
#include <modelDataStructure.h>
#include <boost/algorithm/string.hpp>
#include <osmium/index/map/flex_mem.hpp>
#include <modelDataHandler.h>

using namespace std;

class modelData
{
    using locationType = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
    using tagPair = pair<string,string>;
    using idType = osmium::unsigned_object_id_type;
    locationType m_NodesLocation;
    map<idType, nodeData> m_NodeMap;
    map<idType, wayData> m_WayMap;
    map<idType, relationData> m_RelationMap;
    map<idType, vector<idType>> m_Multipolygon;
    vector<catagoryData> m_Amenity;

    friend class modelDataHandler;


    vector<string> findName(vector<tagPair> &tags)
    {
        vector<string> tempVec;
        for(auto it = tags.begin(); it != tags.end(); it ++)
        {
            if(it->first.find("name") != string::npos)
            {
                tempVec.emplace_back(boost::algorithm::to_lower_copy(it->second));
            }
        }
        return tempVec;
    }


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

    const map<idType, vector<idType>> getMultipolygon()
    {
        return m_Multipolygon;
    }

    template <typename T>
    void buildAmenityCatagory(const T &data)
    {
        vector<tagPair> tags = data.tagList;
        if(tags.size() != 0)
        {
            for(auto it = tags.begin(); it != tags.end(); it ++)
            {
                if(it->first == "amenity")
                {
                    catagoryData temp;

                    temp.id = data.id;
                    temp.itemType = data.osmType;
                    temp.type = boost::algorithm::to_lower(it->second);
                    temp.name = findName(tags);
                    m_Amenity.emplace_back(temp);
                }
            }
        }
    }


    //return a vector of catagory data
    vector<catagoryData> searchAmenityByName(string name)
    {
        vector<catagoryData> result;
        for(auto it = m_Amenity.begin(); it != m_Amenity.end(); it ++)
        {
            for(auto it2 = it->name.begin(); it2 != it->name.end(); it2 ++)
            {
                if(it2->find(name) != string::npos)
                {
                    result.emplace_back(*it);
                    break;
                }
            }
        }
        return result;
    }

//    vector<catagoryData> searchAmenityByType(string type)
//    {
//        vector<catagoryData> result;
//        for(auto it = m_Amenity.begin(); it != m_Amenity.end(); it ++)
//        {
//            if(it->type.find(boost::algorithm::to_lower(type)) != string::npos)
//                result.emplace_back(*it);
//        }
//        return result;
//    }


};

#endif // MODELDATA_H
