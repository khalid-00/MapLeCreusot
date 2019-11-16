#ifndef MODELDATASTRUCTURE_H
#define MODELDATASTRUCTURE_H
#include <string>
#include <vector>
#include "osmium/osm.hpp"
#include <Qt>

using namespace std;
using tagPair = pair<string,string>;

using idType = osmium::unsigned_object_id_type;

struct relationMember
{
    osmium::item_type type;
    idType ref;
    string role;
};

struct relationData
{
    vector<relationMember> memberList;
    vector<tagPair> tagList;
};

struct nodeData
{
    vector<tagPair> tagList;
//    qreal x_part; // x = (x_size) * 2 ^ zoomlevel
//    qreal y_part;
};

struct wayData
{
    vector<idType> nodeRefList;
    vector<tagPair> tagList;
};
#endif // MODELDATASTRUCTURE_H
