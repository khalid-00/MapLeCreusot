/////////////////////////////////////////////////////////////////
/// ShortPath.h Belal Hmedan - 2019                           ///
/// Belal_Hmedan@etu.u-bourgogne.fr                           ///
/// This Class intends to Get the Shortest Path of Vertices   ///
/// Using Other Classes Built Before                          ///
/////////////////////////////////////////////////////////////////
#ifndef SHORTPATH_H
#define SHORTPATH_H
#include <mygraphbuilder.h>
#include <myalgorithm.h>
#include <model.h>
class ShortPath
{
private:
  vector <idType> mypath;
  idType Source_ID,Destination_ID;
  Model OurModel;
public:
  ShortPath();//Default Constructor
  ShortPath(idType,idType,Model);//Parameters Constructor
  ~ShortPath();//Destructor

  //------------------------------------------
  //Accessors
  Path getYourPath();
  Model getModel();
  idType getSource();
  idType getDestination();
  //------------------------------------------
  //Mutators
  void setMyPath(Path);
  void setModel(Model);
  void setSource(idType);
  void setDestination(idType);
  //------------------------------------------
  //Print
  void printMyPath();
};

#endif // SHORTPATH_H
