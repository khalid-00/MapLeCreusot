/////////////////////////////////////////////////////////////////
/// \brief MyGraphBuilder.cpp Belal Hmedan - 2019             ///
/// Belal_Hmedan@etu.u-bourgogne.fr                           ///
/// This Class intends to Build The Graph(Vertices, and Edges)///
/// to be used in Finding the Shortest Path With an Algorithm.///
/////////////////////////////////////////////////////////////////
// Generic Libraries
//===============================================
#include <iostream>
#include <map>
#include <vector>
#include <math.h>

// Belal Libraries
//===============================================
#include <mygraphbuilder.h>

// Boost Libraries
//===============================================
//#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

// Deng Libraries
//===============================================
#include <modelDataStructure.h>
#include <modelDataHandler.h>
#include <modeldata.h>
#include <model.h>
// Osmium Libraries
//===============================================
#include <osmium/osm.hpp>
#include <osmium/index/map/flex_mem.hpp>
#include <osmium/visitor.hpp>
#include <osmium/osm/location.hpp>
#include <osmium/osm/node_ref.hpp>
//===============================================
/////////////////////////////////////////////////
MyGraphBuilder::MyGraphBuilder() // default Constructor
{
  m_Data = new modelData;
  WayMap MyWayMap = m_Data->getWayMap();
  WayMap::iterator it;
  // it->first  ;// (key = WayID)
  // it->second ;// (Value WayData.nodRefList[idType])
  // map <source distination weight(distance) >
  for ( it = MyWayMap.begin(); it != MyWayMap.end(); it++ ) // Loop the Whole Way Map
    {
      for(it->second.nodeRefList.begin();it->second.nodeRefList != it->second.nodeRefList.rbegin()-1;it->second.nodeRefList++)// Loop The Whole Nodes of Each way
               ;
    }
}

MyGraphBuilder::MyGraphBuilder(WayMap YourWayMap){  // Parameters Constructor
  WayMap::iterator it;
  WayMap MyWayMap = YourWayMap;
  for ( it = MyWayMap.begin(); it != MyWayMap.end(); it++ )
    {

    }
}

MyGraphBuilder::~MyGraphBuilder (){ // default Destructor

}

double MyGraphBuilder::Distance(idType Nod1_ID, idType Nod2_ID){ // Function to calculate Euclidean Distance between Vertices
  osmium::Location L1,L2; // define any 2 locations on earth
  L1 = getNodeLoaction(Nod1_ID) ; // get first location
  L2 = getNodeLoaction(Nod2_ID) ; // get second location
  double dist = 0; // distance
  double x1 = L1.lat(); // first location latitude
  double x2 = L2.lat(); // second location latitude
  double y1 = L1.lon(); // first location longitude
  double y2 = L2.lon(); // second location longitude
  dist = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
  return dist;
}
/////////////////////////////////////////////////
