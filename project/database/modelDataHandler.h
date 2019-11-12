#ifndef MODELDATAHANDLER_H
#define MODELDATAHANDLER_H

#include <osmium/osm.hpp>
#include <osmium/index/map/flex_mem.hpp>
#include <osmium/handler.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <modelDataStructure.h>
#include <modeldata.h>

class modelDataHandler : public osmium::handler::Handler
{
//    using namespace osmium;
    using locationType = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
    using tagPair = std::pair<std::string,std::string>;
    using idType = osmium::unsigned_object_id_type;

    void getTags(std::vector<tagPair>& tagStore, const osmium::TagList& tagList)
    {
        for(const auto& tag:tagList)
        {
            auto tempKey = tag.key();
            auto tempValue = tag.value();
            tagStore.emplace_back(std::make_pair(tempKey,tempValue));
        }
    }

//    friend class modelData;

    modelData* m_modelData;

public:
    modelDataHandler(modelData* Data)
    {
        m_modelData = Data;
    }
    void node(const osmium::Node& node)
    {
        const int64_t id = node.id();
        if (id >= 0)    //now only support unsign id
        {
            m_modelData->m_NodesLocation.set(static_cast<idType>(id), node.location());
            if(!node.tags().empty())
            {
                nodeData temp;
                getTags(temp.tagList, node.tags());
                m_modelData -> m_NodeMap[static_cast<idType>(id)] = temp;
                std::cout << temp.tagList[0].first << std::endl;
            }
        }
    }

    void way(const osmium::Way &ways)
    {
        const int64_t id = ways.id();
        if (id >= 0)    //now only support unsign id
        {
            wayData temp;

            //get node reference list
            for(const auto node:ways.nodes())
                temp.nodeRefList.emplace_back(node.ref());
            //get tag list
            getTags(temp.tagList, ways.tags());
            m_modelData->m_WayMap[static_cast<idType>(id)] = temp;
        }
    }

    void relation(const osmium::Relation& relations)
    {
        const int64_t id = relations.id();
        if(id >= 0)
        {
            relationData tempData;

            // store memberList
            const osmium::RelationMemberList& rml = relations.members();
            for(const osmium::RelationMember& rm : rml)
            {
                relationMember tempMem;
                tempMem.ref = rm.ref();
                tempMem.type = rm.type();
                tempMem.role = rm.role();
                tempData.memberList.emplace_back(tempMem);
            }
            getTags(tempData.tagList, relations.tags());

            m_modelData->m_RelationMap[static_cast<idType>(id)] = tempData;
        }

    }

};

#endif // MODELDATAHANDLER_H
