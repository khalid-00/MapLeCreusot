#ifndef MYGRAPHBUILDER_H
#define MYGRAPHBUILDER_H
//////////////////////////////////////////////////////////////////
/// \brief MyGraphBuilder.h Belal Hmedan - 2019                ///
/// Belal_Hmedan@etu.u-bourgogne.fr                            ///
/// This Class intends to Build The Graph(Vertices, and Edges) ///
/// to be used in Finding the Shortest Path With an Algorithm. ///
//////////////////////////////////////////////////////////////////

// Generic Libraries
//===============================================
#include <iostream>
#include <vector>
#include <map>

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

using namespace boost;
using namespace std;

/////////////////////////////////////

class MyGraphBuilder
{
// Also Private but I wrote it down just for clearity
  using locationType = osmium::index::map::FlexMem <osmium::unsigned_object_id_type, osmium::Location&>;
  using tagPair = pair<std::string,string>;
  using idType = osmium::unsigned_object_id_type;
//----------------------------------------------------------
  //typedef osmium::Location::lat() Latitude;
  //typedef osmium::Location::lon() Lnogitude;
  //==================================================
  typedef adjacency_list < vecS,vecS,directedS,property<vertex_name_t, idType>, property < edge_weight_t, double > > graph_t;
  typedef graph_traits < graph_t >::vertex_descriptor Vertex; // Vertex declaration
  typedef pair<idType, idType> Edge; // Edge as link between two Nodes specified by ID
  typedef map<idType, wayData> WayMap;//Define map of Ways ans Their ID
  typedef property<vertex_index_t, idType,
          property<x_t, double,
          property<y_t, double
          >>>> VertexProperty; // Define Vertex (ID , longitude , latitude )
  //==================================================
private:               // This Line is Useless just for clarity
modelData* m_Data;   // pointer from modelData Type (Our DataStructure)
vector <Vertex> ShortPath;   // My Shortest Path is a Vector of Vertices

/////////////////////////////////////////////////////////

public:

  MyGraphBuilder(); // Default Constructor
  MyGraphBuilder(WayMap);// Parameters Constructor
  ~MyGraphBuilder ( ) ; // Destructor
  double Distance(idType,idType); // function to calculate the distance between 2 Verices
  //===============================================
  //Accessors
// function to call the Shortest path as Vector of Nodes
vector <Vertex> getShortPath() const {
return ShortPath;
}
  //===============================================
  //Mutators
// function to assign Shortest path as a whole Vectore
void setShortPath(vector <Vertex> PathVector){
  ShortPath.clear();
  ShortPath = PathVector;
}
// function to assign Shortest path Vertex by Vertex
void setNodePath(Vertex MyNode){
ShortPath.emplace_back(MyNode);
}
  //===============================================
// Function to Get Data by id

  const osmium::Location getNodeLoaction(idType id)
  {
      return m_Data->getNodeLoaction(id);
  }
//=================================================
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
  //===============================================
// Function to Get Data Maps

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
/////////////////////////////////////

#endif // MYGRAPHBUILDER_H
