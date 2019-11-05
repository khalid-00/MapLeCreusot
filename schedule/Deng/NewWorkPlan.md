<font size = 4>

# Possible solutions for the project

with practical details

drafted by Deng

## Solution 1: Using one-for-all library

- Data manipulation
  - Done in `Marble` or `Cartotype`

- Map rendering: Done in `Marble` with open source.
  - Modifications on left click manu
  - Modifications on right click manu
  - Place new text box for place search and routing
  - Other improvements on UI by change the source code

- Routing
  - Done in the library
  - Maybe update some algorithms in the library

- Advantage:
  - Simple and promising on performance.
  - Fullfill all the functional requirement.

- Disadvantage:
  - Too simple, basically nothing to code for us
  - Definitly won't get good marks for this.

- Suggestions:
  - Maybe we can placed this solution as a backup. | **Deng**

## Solution 2: Only use osm data access library

description: we use well-written library for data access, but we write our own rendering library base on the osm data & implement our own routing algorithms.

- Data manipulation
  - File access supported using written library
  - Manage data | we can use `Marble::GeoDocument` as reference
    - Provide all the position data(lon & lat & aera) for map rendering
    - Provide relations for routing
    - Provide places detail for UI
    - Provide infromation for place searching

- Rendering | Notes: It's better to build our own class derived from QWidget
  - how to build & use a custom widget in QT
    - [Build a custom widget](https://doc.qt.io/qt-5/designer-creating-custom-widgets.html)
    - [Use custom widget in QT mainwindow](https://doc.qt.io/qt-5/designer-using-custom-widgets.html)
  - How to draw | Library for drawing, we can use `Marble::GeoPainter` as reference. Or see [here](https://doc.qt.io/qt-5/qpaintdevice.html)
    - draw buildings (draw retangles as buildings)
    - draw roads
    - draw routes
    - draw text
    - draw different layers (fields layer, building layer, text layer) | [Tutorial on layer rendering](https://www.qt.io/blog/2009/04/23/layered-rendering-part-2-it-helps-solve-many-problems)
  - How to interact | since the widget class is derived from QtWidget, we can use same interact functions from QtWidget
    - Zoom in & Zoom out
      - Tutorial on [QPainter rotate and scale](https://doc.qt.io/qt-5/qtwidgets-painting-transformations-example.html)
    - right click menu
    - lift click menu

- Advantage:
  - We will learn a lot with this solution
  - We can build something and we don't need to build too much
  - We have a lot of reference for the implementation (for Qt related questions)
  - Dependencies we need is basically Qt, so the code can be cross-platform
  - This is a very technical solution for the project

- Disadvantage:
  - Not sure we have enough time for all the coding. Maye be we can't finish this before Dec.

- Suggestions:
  - I personnally recommand this solution, it worths a try | **Deng**

## Solution 3: Display the map using img

- Data manipulation:
  - do the same thing as **solution2**

- Map rendering:
  - using screen shots or other source img to display
  - zoom in & zoom out
  - how to connect different imgs to get a smooth drag in the map
  - do calibrations to connect the img and back-end data for interactions
    - Select place
    - show routes on the img
  - Write custom functions for drawing routes

- Advantage:
  - Simple coding for map displaying, it saves dev time.
  - We will also build our library for data manipulation & routing
  - It looks easy

- Disadvantage:
  - It requires too much of calibration. It's time consuming and dirty. (Not a technical solution)

- Suggestions:
  - Maybe we can placed this solution as a backup. | **Deng**

PS: since routing algorithms can be highly independent for the library we choose. Hence, it is now completely parallel under going by **Belal**. Once he finishes drafting the code for the algorithm, he can help us on the solutions purposed above.
