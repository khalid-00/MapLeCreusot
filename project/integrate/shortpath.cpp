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
  setMyPath(algo.getShortPath(builder.getGraphMap(),Destination_ID)); // Target Node id
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
vector <idType> ShortPath::getYourPath(){return mypath;}
//----------------------------------------------------------------
//Mutator
void ShortPath::setMyPath(vector<idType> ThePath){mypath = ThePath;}
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
