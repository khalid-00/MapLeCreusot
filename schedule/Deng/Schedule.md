# Start form Nov. 8th

reconstructure since we are now only two.

## Data manipulation

- [x] Know what the content in osm file means and how they work
  - [x] Nodes
  - [x] Ways
  - [x] Relations
- [x] Parssing file | using libosmium
- [x] Accessing data | using libosmium
- [ ] Construct a data structure to do the rendering and routing | Estimate to be done before Nov.17
  - [ ] How to define an indepent point?
  - [ ] Lon&Lat transision before drawing
  - [ ] How to do tag filtering for searching ( Reference: Marble )
  - [ ] How to index the node location and manage the relation member
  - [ ] How to group the ways in different types( [Reference](https://github.com/cpp-io2d/P0267_RefImpl) )

## Rendering

- [ ] How to interact with the drawing in QT | Estimate to be done before Nov. 09, if I get what I need from the reference
  - [ ] How to zoom in & zoom out([Reference](https://github.com/robert1207/QtDrawingPaperEditorDemo))
  - [ ] How to drag the map([Reference](https://github.com/robert1207/QtDrawingPaperEditorDemo))
- [ ] Get to know how to use the Geo data to paint the map | this task is coupled with the data structure
  - [ ] Use simple code to test first

Estimate to be done before Nov.17

- [ ] Code the rendering library | Estimated to be done before Nov.27
  - [ ] Draw independent point
  - [ ] Draw lines
  - [ ] Draw buildings
  - [ ] Draw different fileds or layers ([Reference](https://github.com/cpp-io2d/P0267_RefImpl))

## UI | This part will be scheduled when Belal finished the algorithms

- [ ] Textbox for searching place / routing
- [ ] pop up menu when clicking the place
  - [ ] Left click
  - [ ] Right click
- [ ] zoom in & zoom out with mouseScroll
- [ ] codes for localizing where u r clicking(node or ways or building or other concepts we defined)
- [ ] Other features...
