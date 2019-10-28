<font size = 4>

# Main schedule

Drafted by Deng 23/10/2019
Modified by Deng 28/10/2019

## Research

- [x] General research for libraries we will use.
  - Due date: end of Oct.
  - Result:
    - ~~Decide to use `cartotype` for our development. `Libosmium` and other library recommended in Yohan's tutorial will be considered as backup plan.~~
    - `Cartotype` is a totally blackbox for the teammates. With limited documentations, it is very difficult to set up environments. Thus, we need to switch to another library. The new solution maybe using `Libosmium` for data manipulation to support algorithms and use `Marble` for map displaying in GUI.
- [ ] Simple guide about using `Marble` for osm data rendering | **Deng**
  - Due date: end of Oct.

## Coding / Development | `From 23 Oct. to 23 Nov.`

- [ ] Development | `From 23rd Oct. to 23rd Nov.`
  - [ ] Basic data manipulation | **Deng**
    - [ ] Switch to `Libosmium`
    - [ ] How to interact with `Marble`
    - [ ] Map conversion
    - [ ] Load map data
    - [ ] Database Interface
      - [ ] ~~original interface from `cartotype`~~
  - [ ] User Interface | **Azadeh**
    - [ ] Map display
    - [ ] Interactions
      - [ ] Zoom in & Zoom out
      - [ ] Pin to get detailed information for a spot/place
      - [ ] How to do place searching for users
      - [ ] How to search path for users
      - [ ] choose travel mode
      - [ ] showing path for navigation

  - [ ] Key algorithm implementation | **Belal**
    - [ ] Research on the basic principles for path planning
    - [ ] Research on libraries for path planing/ Or build our own library for this
    - [ ] Implement the algorithms
      - [ ] Basic path planning
      - [ ] Basic path planning for different travel mode
    - [ ] Modification on the data base in order to implement the algorithm
- [ ] Discuss IO standard for these 3 module. | `estimated at 10th Nov, the second discussion in Nov.`
- [ ] Merge & Test & Debug | `From 23rd Nov to 1st Dec`
  - [ ] User interface with data manipulation
  - [ ] User interface with path planning
  - [ ] data maniulation with path planning
- [ ] Release | `1st Dec`

## Upgrades & hotfix

### Upgrades

- [ ] Data Manipulation
  - [ ] newly added / customed interface for other features
    - [ ] Show contact of the place
    - [ ] Show opening time of the place
    - [ ] Show pictrues of the place
- [ ] User Interface
  - [ ] Better looking?
- [ ] Key algorithms
  - [ ] Complex path planning
    - [ ] multiple terminal path planning
    - [ ] multiple travel mode path planning
    - [ ] multiple terminal with multiple travel mode path planning

### Hotfix

## Report preparation `Start on 1st Dec.`

- [ ] Report for the project
- [ ] Slides for defend
- [ ] Documentation for the project
  - [ ] User Guide
    - [ ] Installation
    - [ ] Usage
    - [ ] Reference
  - [ ] Known Issues
