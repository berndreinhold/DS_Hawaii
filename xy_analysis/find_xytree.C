void find_xytree(){
#include <fstream>

  string dir="/ds50/data/test_processing/darkart_release3/";
  //string filename="";
  vector<string> vFilename;
  /*vFilename.push_back("xytree.root");
  vFilename.push_back("xytree_v01.root");
  vFilename.push_back("xytree_v02.root");
  vFilename.push_back("xytree_v03.root");
  vFilename.push_back("xytree_v04.root");
  vFilename.push_back("xytree_v05b.root");
  vFilename.push_back("xytree_v06a.root");
  vFilename.push_back("xytree_v06b.root");
  vFilename.push_back("xytree_v06c.root");
  vFilename.push_back("xytree_v07.root");
  vFilename.push_back("xytree_v08.root");
  vFilename.push_back("xytree_v09.root");
  vFilename.push_back("xytree_v10.root");
  */
  vFilename.push_back("xytree_v10b.root");

  string outfile_name="xytree_location_10b.txt";
  ofstream ofs;
  ofs.open(outfile_name.c_str(), ios_base::out);
  
  for(int i=0;i<vFilename.size();++i){
    TFile f((dir+vFilename.at(i)).c_str());  
    //f.ls();
    
    TIter nextkey(f.GetListOfKeys());
    TKey *key;
    string run("");
    string output("");
    int j=0;
    while (key = (TKey*)nextkey()) {
      //    Event *event = (Event*)key->ReadObj();
      //    event->Process();
      run=key->GetTitle();
      output=Form("%s, %s, %s, %s", run.substr(3,6).c_str(), run.c_str(), vFilename.at(i).c_str(), dir.c_str());
      if(j<10) std::cout << output << std::endl;
      ofs << output << std::endl;
      j++;
    }
    f.Close();
  }
}
