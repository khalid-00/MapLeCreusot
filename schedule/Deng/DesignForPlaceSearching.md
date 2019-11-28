# Documents for place searching

## Data will be used in this feature

- an orphant node storing only the name or other information of the node
- a way representing a building or street

## Connected with rendering

- when the result is a node:
  1. getNodeLocation
  2. project the location to scene coordinate
  3. get the repective item in the position
  4. add an `pin-point` item on the object
  5. delete the `pin-point` when exit the searching mode

- when the result is a node:
  1. calculate the center position of the object with wayData
  2. add an `pin-point` item in the scene
  3. delete the `pin-point` item when exit the searching mode


