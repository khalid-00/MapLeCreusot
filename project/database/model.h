#ifndef MODEL_H
#define MODEL_H
#include <modelDataStructure.h>
#include <modelDataHandler.h>
#include <osmium/osm.hpp>
#include <osmium/index/map/flex_mem.hpp>
#include <osmium/io/pbf_input.hpp>
#include <osmium/visitor.hpp>
#include <modeldata.h>
//class Model
//{
//public:
//    Model(){}
//};

class Model
{

    using locationType = osmium::index::map::FlexMem<osmium::unsigned_object_id_type, osmium::Location>;
    using tagPair = std::pair<std::string,std::string>;
    using idType = osmium::unsigned_object_id_type;

    bool m_isFileLoaded;
    string m_filePath;
    modelData* m_Data;

    void loadFile()
    {
        osmium::io::File inputFile(m_filePath);
        modelDataHandler handler(m_Data);
        osmium::io::Reader reader(inputFile, osmium::io::read_meta::no);
        osmium::apply(reader, handler);
        reader.close();
    }

public:
    Model()
    {
        m_Data = new modelData;
        m_isFileLoaded = false;
        m_filePath = "";
    }

    void setFilePath(string filePath){
        if(filePath != m_filePath)
        {
            m_filePath = filePath;
            loadFile();
        }
    }

    const osmium::Location getNodeLoaction(idType id)
    {
        return m_Data->getNodeLoaction(id);
    }

    const nodeData getNodeData(idType id)
    {
        return m_Data->getNodeData(id);
    }

    const wayData getWayData(idType id)
    {
        return m_Data->getWayData(id);
    }

    const relationData getRelationData(idType id)
    {
        return m_Data->getRelationData(id);
    }

    const map<idType,nodeData> getNodeMap()
    {
        return m_Data->getNodeMap();
    }

    const map<idType,wayData> getWayMap()
    {
        return m_Data->getWayMap();
    }

    const map<idType,relationData> getRelationMap()
    {
        return m_Data->getRelationMap();
    }


};

#endif // MODEL_H
