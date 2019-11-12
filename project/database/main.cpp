#include <iostream>
#include <osmium/io/pbf_input.hpp>
#include <osmium/index/map/flex_mem.hpp>
#include <osmium/io/input_iterator.hpp>
#include <osmium/visitor.hpp>
#include <osmium/handler.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>
#include <osmium/area/assembler.hpp>
#include <osmium/area/multipolygon_manager.hpp>
#include <osmium/geom/coordinates.hpp>
#include <string>
#include <modelDataHandler.h>
#include <osmium/storage/item_stash.hpp>
#include <map>
#include "model.h"
using namespace std;


int main()
{
    double duration;
    clock_t start, stop;
    start = clock();

    const string filePath = "/home/dj/git/cpp_project/data/Le_Creusot.pbf";

    Model mapModel;

    mapModel.setFilePath(filePath);
    mapModel.loadFile();

    stop = clock();
    duration = double(stop - start);

    printf("Used time for loading file: %f\n",(duration/CLOCKS_PER_SEC));

//    auto testNode = myhandler.getNodeMap();
//    cout << "No. of nodes: " << testNode.size() << endl;
//    auto testWay = myhandler.getWayMap();
//    cout << "No. of ways: " << testWay.size() << endl;
//    auto test = myhandler.getRelationMap();
//    cout << "No. of relations: " << test.size() << endl;

//    start = clock();
//    for(auto &r:test)
//    {
//        for(auto &t:r.second.tagList)
//        {
//            cout << t.first << ": " << t.second << endl;
//        }
//    }
//    stop = clock();
//    duration = stop - start;
//    printf("\nUsed time for looping tags in all relation: %f\n\n",(duration/CLOCKS_PER_SEC));


    return 0;
}
