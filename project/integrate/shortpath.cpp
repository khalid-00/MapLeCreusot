/////////////////////////////////////////////////////////////////
/// ShortPath.cpp Belal Hmedan - 2019                         ///
/// Belal_Hmedan@etu.u-bourgogne.fr                           ///
/// This Class intends to Get the Shortest Path of Vertices   ///
/// Using Other Classes Built Before                          ///
/////////////////////////////////////////////////////////////////
#include <shortpath.h>
//=============================================================
// Default Constructor
ShortPath::ShortPath()
{
  cout<<"Dear User careful, This is Empty Path !"<<endl;
}
// Parameters Constructor
ShortPath::ShortPath(idType Source1,idType Destination1, Model mModel)
{
  setSource(Source1);
  setDestination(Destination1);
  setModel(mModel);
  // make it as member of main window, no need to call it always
  MyGraphBuilder builder(getModel());
  builder.generateGraph();
  MyAlgorithm algo(builder.getGraph(),builder.getGraphMap(), Source_ID); //Start Node id
  //cout<<"\nAlgorithm Worked Done!"<<endl;
  //algo.PrintRawData();
 if (algo.getFlag()){
       setMyPath(algo.getShortPath(builder.getGraphMap(),Destination_ID));
   }
 else cout << "please enter valid node\t"<<endl;
  // Target Node id
  //-------------------------------------------------------------------
  //  printMyPath();
  //  cout<<"Path Size\t"<<mypath.size()<<endl;

}
ShortPath::~ShortPath(){}//Destructor
//========================================
// Start
// Accessor
Model ShortPath::getModel(){return OurModel;}
idType ShortPath::getSource(){return Source_ID;}
idType ShortPath::getDestination(){return Destination_ID;}
Path ShortPath::getYourPath(){return mypath;}
//----------------------------------------------------------------
//Mutator
void ShortPath::setMyPath(Path ThePath){mypath = ThePath;}
void ShortPath::setSource(idType Src){Source_ID = Src;}
void ShortPath::setDestination(idType Des){Destination_ID = Des;}
void ShortPath::setModel(Model YourModel){OurModel = YourModel;}
//---------------------------------------------------------------------
// Print Function
void ShortPath::printMyPath(){
  for(vector<idType>::iterator it = mypath.begin(); it != mypath.end(); ++it) {
      cout <<"MyPath is \t"<< *it <<endl;}
}
// End
//========================================
