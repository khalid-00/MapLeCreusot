# Research notes by Deng

## Mapnik

<font size = 3>

- [x] Cross platform
- [x] offline supported

### Features

- Platform supported
  - windows
  - linux
  - freeBSD
  - Mac OS X
  - Solaris
- Detailed installation documentation
- Support OSM XML dataset

### Problems

- No enough example and API documentation to get familiar with it, may cause a bit more time to go through the library
- require python for the project, makes it a multi-language project, more difficult to manage.

### Qt Location

- [x] Cross platform
- [x] offline support

### Features

- Tons of API
- Forum support
- maybe more stable

### Problems

- To complete the application, as the documentation stated: [Currently it is not possible to interact with maps via C++. Mapping applications must use the Maps and Navigation (QML) API.](https://doc-snapshots.qt.io/qt5-5.11/location-maps-cpp.html) In this case, if we use this library, it would be a multi-language project.

## Cartotype

- [x] Cross platform
- [x] offline support

### Features

- You can find basically all the functions you need for this project.
- Officially support [OpenStreetMap offline](https://wiki.openstreetmap.org/wiki/Using_OpenStreetMap_offline)
- A complete map app with open source code using this library. Basically shows you everything about how to do this project
- [API documentation](http://www.cartotype.com/assets/api_doc/index.html)
- [Main Page](http://www.cartotype.com)

### Problems

- The library is so well-developed that it just makes the porject too easy

### Detailed Questions

- Q2: How they manage the data of the map
  - A: No detailed tutorial or diagram on its website. We need to go through the code by ourself. We may get some hints [here](http://www.cartotype.com/assets/api_doc/classCartoType_1_1CFramework.html#a656390a9c833c04da194c9ae1de9f5f8)

- Q3: Detailed for how to import and use in the project(graph or diagram, no code)
  - A: [Envirement setup for different platform](http://www.cartotype.com/articles/102-cartotype-and-qt)

- Q5: Is it easy to use( detailed documentation for beginner in both library)
  - A: 
    - [API](http://www.cartotype.com/assets/api_doc/)
    - [Sample code](https://github.com/CartoType/CartoType-Public)
    - [Simple tutorial](http://www.cartotype.com/developers/documentation/42-cartotype-tutorial)
    - In the example code, the library reads the map data format `CTM1`. The OSM data need to be converted to `CTM1` before it is used. [Tutorial here](http://www.cartotype.com/developers/documentation/50-how-to-create-map-files-for-cartotype-ctm1-files)
    - No document for top-level veiw of the library, as suggested in the website, we should go through the `example code`
