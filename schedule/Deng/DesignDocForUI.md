# Design Logic of UI

## Right click menu logic

**global choice with same action:** 
1. search place
2. set source(reset if already selected)
3. set dest(reset if already selected)

**state**

- S0: nothing was selecting
- S1: source was set
  - choice: cancel source
- S2: dest was set
  - choice: cancel source
  

## Backend logic for different choices

- decide if it is clicking on an object

```C++
    auto pos = event->pos();
    auto scenePos = mapToScene(pos);
    std::cout << "mouse press" << std::endl;
    auto item = this->scene()->itemAt(scenePos, QTransform());
    if(qgraphicsitem_cast<Multipolygon *>(item))
    {
        // yes, the user is clicking on a building
        // store the address of the selected building here;
        m_selectedBuilding = qgraphicsitem_cast<Multipolygon *>(item);
    }
    else
    {
        // it's not a building
        // nothing to do
    }
```

- for cancelling source/destination or if the user didn't choose the building

```C++
    //reset all the pointer;
    m_selectedBuilding = nullptr;
    m_sourec = nullptr;
    m_dest = nullptr;
```

- get the center point of the building

```C++
    QPoint getPosition(Multipolygon const *item)
    {
        auto bounding = item->boundingRect();
        //loop over the bounding to get the center point
        return QPoint();
    }
```

- draw a pin on the selected object (optional)

  Init two pin item in the scene, but set them to be invisible. And after the place was selected, set them to visible, in the position from `getPosition()`

## Idea for palce searching

**Entries**

1. from right click menu
2. from tool bar in mainwindow

### Search by type

- limited type can be choose by the user through.....

### Search by name

- take an input string for searching ( accurate searching)

### Highlight searching result

- create an vector of pin icon and set them to respective position

- delete them when exit the place searching

### how to exit the place searching status

- any right click will exit
