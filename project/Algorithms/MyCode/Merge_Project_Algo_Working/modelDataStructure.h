#ifndef MODELDATASTRUCTURE_H
#define MODELDATASTRUCTURE_H
#include <string>
#include <vector>
#include <osmium/osm.hpp>
//enum class item_type : uint16_t {

//    undefined                              = 0x00,
//    node                                   = 0x01,
//    way                                    = 0x02,
//    relation                               = 0x03,
//    area                                   = 0x04,
//    changeset                              = 0x05,
//    tag_list                               = 0x11,
//    way_node_list                          = 0x12,
//    relation_member_list                   = 0x13,
//    relation_member_list_with_full_members = 0x23,
//    outer_ring                             = 0x40,
//    inner_ring                             = 0x41,
//    changeset_discussion                   = 0x80

//};
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
