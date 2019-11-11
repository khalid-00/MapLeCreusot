#ifndef MODELDATASTRUCTURE_H
#define MODELDATASTRUCTURE_H
#include <string>
#include <vector>
#include <osmium/osm.hpp>

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
};

struct wayData
{
    vector<idType> nodeRefList;
    vector<tagPair> tagList;
};
#endif // MODELDATASTRUCTURE_H
