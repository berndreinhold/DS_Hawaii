#define GoodGuysBadGuys_cxx
#include "GoodGuysBadGuys.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <iostream>
#include <algorithm> //std::sort

using namespace std;

int main(int argc, char* argv[]){

    GoodGuysBadGuys ggbg;
    ggbg.Loop();

}

//http://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair
//http://stackoverflow.com/questions/2699060/stl-map-sort-by-value
struct sort_pred {
    bool operator()(const std::pair<TString,int> &left, const std::pair<TString,int> &right) {
        return left.second > right.second;
    }
};

void GoodGuysBadGuys::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L GoodGuysBadGuys.C
//      Root > GoodGuysBadGuys t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //value=1; //start off with a positive value (good guy), if negative turns into a bad guy

      //basic consistency check: these vectors should all have the same size
      if(process->size()!=static_cast<unsigned>(n_particles)) exit(-1);
      if(process->size()!=particle->size()) exit(-1);
      if(process->size()!=type->size()) exit(-1);
      if(process->size()!=spawn_volume->size()) exit(-1);

      //clear all variable containers
      ClearVars();

      //here decide about good guy or bad guy and fill the ntuple
      //loop through all "instances" of an event:
      
      for(int i=0;i<n_particles;++i){
	//if(process->at(i)=="inelastic" && spawn_volume->at(i)!="p_scint" && type->at(i)=="nucleus") value=-1;
	if(process->at(i)=="HadronElastic"){
	  if(spawn_volume->at(i)=="p_scint"){
	    	    
	    he_scint.qdep_active+=qdep_active->at(i);
	    he_scint.qdep_veto+=qdep_veto->at(i);
	    he_scint.particles+=1;
	  } else if(spawn_volume->at(i)=="p_active"){
	    he_active.qdep_active+=qdep_active->at(i);
	    he_active.qdep_veto+=qdep_veto->at(i);
	    he_active.particles+=1;
	  } else {
	    he_other.qdep_active+=qdep_active->at(i);
	    he_other.qdep_veto+=qdep_veto->at(i);
	    he_other.particles+=1;
	  }
	  he.qdep_active+=qdep_active->at(i);
	  he.qdep_veto+=qdep_veto->at(i);
	  he.particles+=1;

	} else if(process->at(i)=="inelastic"){
	  if(spawn_volume->at(i)=="p_scint"){
	    if(type->at(i)=="nucleus"){
	      inel_scint_nucleus.qdep_active+=qdep_active->at(i);
	      inel_scint_nucleus.qdep_veto+=qdep_veto->at(i);
	      inel_scint_nucleus.particles+=1;
	    } else if(type->at(i)=="baryon"){
	      inel_scint_baryon.qdep_active+=qdep_active->at(i);
	      inel_scint_baryon.qdep_veto+=qdep_veto->at(i);
	      inel_scint_baryon.particles+=1;
	    } else {
	      /*
	      inel_scint_other.qdep_active+=qdep_active->at(i);
	      inel_scint_other.qdep_veto+=qdep_veto->at(i);
	      inel_scint_other.particles+=1;
	      */
	    }

	    inel_scint.qdep_active+=qdep_active->at(i);
	    inel_scint.qdep_veto+=qdep_veto->at(i);
	    inel_scint.particles+=1;
	  } else if(spawn_volume->at(i)=="p_active"){
	    if(type->at(i)=="nucleus"){
	      inel_active_nucleus.qdep_active+=qdep_active->at(i);
	      inel_active_nucleus.qdep_veto+=qdep_veto->at(i);
	      inel_active_nucleus.particles+=1;
	    } else if(type->at(i)=="baryon"){
	      inel_active_baryon.qdep_active+=qdep_active->at(i);
	      inel_active_baryon.qdep_veto+=qdep_veto->at(i);
	      inel_active_baryon.particles+=1;
	    } else {
	      /*
	      inel_active_other.qdep_active+=qdep_active->at(i);
	      inel_active_other.qdep_veto+=qdep_veto->at(i);
	      inel_active_other.particles+=1;
	      */
	    }

	    inel_active.qdep_active+=qdep_active->at(i);
	    inel_active.qdep_veto+=qdep_veto->at(i);
	    inel_active.particles+=1;
	  } else {
	    inel_other.qdep_active+=qdep_active->at(i);
	    inel_other.qdep_veto+=qdep_veto->at(i);
	    inel_other.particles+=1;
	  }
	  inel.qdep_active+=qdep_active->at(i);
	  inel.qdep_veto+=qdep_veto->at(i);
	  inel.particles+=1;
	} else {
	  if(spawn_volume->at(i)=="p_scint"){
	    other_scint.qdep_active+=qdep_active->at(i);
	    other_scint.qdep_veto+=qdep_veto->at(i);
	    other_scint.particles+=1;
	  } else if(spawn_volume->at(i)=="p_active"){
	    other_active.qdep_active+=qdep_active->at(i);
	    other_active.qdep_veto+=qdep_veto->at(i);
	    other_active.particles+=1;
	  } else {
	    other_other.qdep_active+=qdep_active->at(i);
	    other_other.qdep_veto+=qdep_veto->at(i);
	    other_other.particles+=1;
	  }
	  other.qdep_active+=qdep_active->at(i);
	  other.qdep_veto+=qdep_veto->at(i);
	  other.particles+=1;
	}
	//all particles in this event:
	all_particles.qdep_active+=qdep_active->at(i);
	all_particles.qdep_veto+=qdep_veto->at(i);
	all_particles.particles+=1;

	
	//the following just lists the possible values for process, particle, spawn_volume, type - B. is still learning
	mProcess[process->at(i)]++;
	mParticle[particle->at(i)]++;
	mSpawn_volume[spawn_volume->at(i)]++;
	mType[type->at(i)]++;
	
      }

      RefillVars(); //from the class containers into the vector from which the ntuple can be filled.
      tN->Fill(&vFillBuffer.at(0));

      // if (Cut(ientry) < 0) continue;
   }
}


void GoodGuysBadGuys::RefillVars(){
  vFillBuffer.clear();
  vFillBuffer.push_back(event_id);

  vFillBuffer.push_back(all_particles.particles);
  vFillBuffer.push_back(all_particles.qdep_active);
  vFillBuffer.push_back(all_particles.qdep_veto);

  //first level

  vFillBuffer.push_back(inel.particles);
  vFillBuffer.push_back(inel.qdep_active);
  vFillBuffer.push_back(inel.qdep_veto);

  vFillBuffer.push_back(he.particles);
  vFillBuffer.push_back(he.qdep_active);
  vFillBuffer.push_back(he.qdep_veto);

  vFillBuffer.push_back(other.particles);
  vFillBuffer.push_back(other.qdep_active);
  vFillBuffer.push_back(other.qdep_veto);

  //2nd level
  vFillBuffer.push_back(inel_active.particles);
  vFillBuffer.push_back(inel_active.qdep_active);
  vFillBuffer.push_back(inel_active.qdep_veto);

  vFillBuffer.push_back(inel_scint.particles);
  vFillBuffer.push_back(inel_scint.qdep_active);
  vFillBuffer.push_back(inel_scint.qdep_veto);

  vFillBuffer.push_back(inel_other.particles);
  vFillBuffer.push_back(inel_other.qdep_active);
  vFillBuffer.push_back(inel_other.qdep_veto);

  vFillBuffer.push_back(he_active.particles);
  vFillBuffer.push_back(he_active.qdep_active);
  vFillBuffer.push_back(he_active.qdep_veto);

  vFillBuffer.push_back(he_scint.particles);
  vFillBuffer.push_back(he_scint.qdep_active);
  vFillBuffer.push_back(he_scint.qdep_veto);

  vFillBuffer.push_back(he_other.particles);
  vFillBuffer.push_back(he_other.qdep_active);
  vFillBuffer.push_back(he_other.qdep_veto);

  vFillBuffer.push_back(other_active.particles);
  vFillBuffer.push_back(other_active.qdep_active);
  vFillBuffer.push_back(other_active.qdep_veto);

  vFillBuffer.push_back(other_scint.particles);
  vFillBuffer.push_back(other_scint.qdep_active);
  vFillBuffer.push_back(other_scint.qdep_veto);

  vFillBuffer.push_back(other_other.particles);
  vFillBuffer.push_back(other_other.qdep_active);
  vFillBuffer.push_back(other_other.qdep_veto);
  //vFillBuffer.push_back(all_particles.qdep_inactive);

  //3rd level
  vFillBuffer.push_back(inel_active_nucleus.particles);
  vFillBuffer.push_back(inel_active_nucleus.qdep_active);
  vFillBuffer.push_back(inel_active_nucleus.qdep_veto);

  vFillBuffer.push_back(inel_active_baryon.particles);
  vFillBuffer.push_back(inel_active_baryon.qdep_active);
  vFillBuffer.push_back(inel_active_baryon.qdep_veto);
  //
  vFillBuffer.push_back(inel_scint_nucleus.particles);
  vFillBuffer.push_back(inel_scint_nucleus.qdep_active);
  vFillBuffer.push_back(inel_scint_nucleus.qdep_veto);

  vFillBuffer.push_back(inel_scint_baryon.particles);
  vFillBuffer.push_back(inel_scint_baryon.qdep_active);
  vFillBuffer.push_back(inel_scint_baryon.qdep_veto);
}

//for the summary

vector<pair<TString,int> > GoodGuysBadGuys::FillPairs(map<TString, int> m){
  
  vector<pair<TString,int> > vpBuffer;
  pair<TString,int> pBuffer;
  map<TString,int>::iterator it;

  for (it = m.begin(); it != m.end(); ++it) {
    //cout << "key: \"" << it->first << "\" " << "value: " << it->second << endl;
    pBuffer=make_pair(it->first,it->second);
    vpBuffer.push_back(pBuffer);
  }

  
  return vpBuffer;
}


void GoodGuysBadGuys::PrintPossibleValues(map<TString,int> m, string var){
  
  //pair<TString,int> pBuffer;
  map<TString,int>::iterator it;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << "possible " << var << " values (sorted alphabetically):" << endl;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  for (it = m.begin(); it != m.end(); ++it) {
    cout << "key: \"" << it->first << "\" "
	 << "value: " << it->second << endl;
    //pBuffer[it->first]=it->second;
    //vpProcess.push_back(pBuffer);
  }
  cout << endl << endl;

}

void GoodGuysBadGuys::PrintPossibleValues(vector<pair<TString,int> > v, string var){

  std::sort(v.begin(),v.end(),sort_pred());
  //pair<TString,int> pBuffer;
  vector<pair<TString,int> >::iterator it;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << "possible " << var << " values (sorted by value):" << endl;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  for (it = v.begin(); it != v.end(); ++it) {
    cout << "key: \"" << it->first << "\" "
	 << "value: " << it->second << endl;
  }
  cout << endl << endl;

}
