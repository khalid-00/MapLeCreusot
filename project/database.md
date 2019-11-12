# Brief Doc for database

Drafted by DJ in 12/11/2019

It is very inconvenient and difficult for libosmium to store in the ram, I decided to build a much simpler database for data access. And just use the libosmium to read the file.

## Dependency

Check what is needed for libosmium. All other codes are only using STL.

## Basic concept for class

### class Model

Top level class for data manipulation. It is used for loading the file and storing the data. Other parts of this project will access data through this class.

#### Functions

The code is extremely simple to understand. So I am not explaining in this part.

**Except:**

- void loadFile();

  Use libosmium to read the data from the `pbf` file.

### class ModelData

A class contains all the osm data.

#### Member

- m_NodeLocation: Containing all the locations in longitude and latitude, u can accessing by node id. Built from osmium::flex_mem. Using `osm::location` to contain the lon&lat as `int32_t`.
- m_NodeMap: Containing the tags list in a node(if it has). Note: if a node doesn't have tags, u just can't find it here. You can use id to access all the m_*Map member in this class. And they are all built from STL map
- m_WayMap: Containng the nodes list and the tags list of the way object in osm file.
- m_RelationMap: Containing the member list and tags list

### class ModelDataHandler

using the osm to read the file and store the data, no need to understand this for data access. We won't have other usage for this now.

## Data Structure

### ModelDataStructure.h

- nodeData:
  - tagList: using std::pair to group up the tag key and tag value.
  
  ```C++
  tag = NodeData.tagList[0];
  tag.first;    // for tag key
  tag.second;   // for tag value
  ```

- wayData:
  - tagList
  - nodeRefList: containing a list of node of this way using std::vector. the list is in the same order of that in the osm file. storing as osmium::unsigned_object_id_type. You can use this directly to index it's location in `m_NodeLocation`.

- relationData:
  - tagList
  - memberList: containing a list of member using std::vector.

- relationMember:
  - type: uint16_t value, check what it means at the comment of the code.
  - role: string
  - ref: osmium::unsigned_object_id_type

**Notes for nodeLocation**

Use osmium::Location for lon & lat(int32_t for both)
