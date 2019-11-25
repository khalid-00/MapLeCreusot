//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <osmium/io/pbf_input.hpp>
#include <osmium/io/input_iterator.hpp>
#include <osmium/handler.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>
#include <osmium/area/assembler.hpp>
#include <osmium/area/multipolygon_manager.hpp>
#include <osmium/geom/coordinates.hpp>
#include <string>
#include <osmium/storage/item_stash.hpp>
//==================================================
#include <model.h>
#include <modelDataHandler.h>
//==================================================
#include <mygraphbuilder.h>
#include <myalgorithm.h>
//==================================================
using namespace std;
using namespace boost;
//==================================================
int main()
{
  double duration;
  clock_t start, stop;
  start = clock();

  const string filePath = "G:/QT/Projects/database/Le_Creusot.osm.pbf";

  Model mapModel;

  mapModel.setFilePath(filePath);
  mapModel.loadFile();

  stop = clock();
  duration = double(stop - start);
  printf("Used time for loading file: %f\n",(duration/CLOCKS_PER_SEC));
  //==========================================================
  MyGraphBuilder builder(mapModel);
  builder.generateGraph();
  builder.printGraph();
  cout<<"Graph was Built Done!"<<endl;
  //================================================================
  //Example:
  idType x = 6739123642, y = 6739123811;
  MyAlgorithm algo(builder.getGraph(),builder.getGraphMap(), x); //x = 1387258667 is a Start Node id
  cout<<"\nAlgorithm Worked Done!"<<endl;
  //algo.PrintRawData();
  Path p = algo.getShortPath(builder.getGraphMap(),y); //y = 1387258368 is Target Node id
  algo.PrintPath();
  cout<<"\nShortest Path Done!"<<endl;
  //======================================================================
  // // Note: if Node is unreachable !
  // //vertex 4 is unreachable:
  //  try {
  //      auto p4 = algo.getShortPath(4);
  //  } catch(exception const& e) {
  //      cout << "Error getting path for vertex 4: " << e.what() << "\n";
  //  }
  //======================================================================

  return EXIT_SUCCESS;
}
