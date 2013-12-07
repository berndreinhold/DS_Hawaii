UseGoodGuysBadGuys(){
  { 
    TFile *f=new TFile("data/gun_x34_veto.root");
    TTree *veto=(TTree *)f->Get("veto");
    
    veto->AddFriend("classific = tN_Classification","data/gun_x34_veto_goodguysbadguys.root");
    
    //veto->Scan("process:particle:spawn_volume:spawn_KE:spawn_time:track_id:parent_id:qdep_active:qdep_veto","flag<0");
    ConsistencyCheck(veto);
    
    f->Close();
  }
  {
    TFile *f=new TFile("data/gun_x34_veto_goodguysbadguys.root");
    TNtuple *tN=(TNtuple *)f->Get("tN_Classification");
    SanityCheck(tN);
    f->Close();
  }
}

void ConsistencyCheck(TTree *veto){
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << "consistency between the original tree and the classification tree:" << endl;
  cout << "all numbers should return 0!" << endl;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << veto->GetEntries("event_id!=classific.event_id || n_particles!=classific.particles") << endl;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
}

void SanityCheck(TNtuple *tN){

  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << "sanity check within the classification tree:" << endl;
  cout << "all numbers should return 0!" << endl;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  //1st level
  cout << tN->GetEntries("particles!=particles__inel+particles__he+particles__other") << endl;

  cout << tN->GetEntries("TMath::Abs(qdep_active-(qdep_active__inel+qdep_active__he+qdep_active__other))>0.1") << endl;
  cout << tN->GetEntries("TMath::Abs(qdep_veto-(qdep_veto__inel+qdep_veto__he+qdep_veto__other))>0.1") << endl;
  //2nd level
  cout << tN->GetEntries("TMath::Abs(particles__inel-(particles__inel_active+particles__inel_scint+particles__inel_other))>0.1") << endl;
  cout << tN->GetEntries("TMath::Abs(particles__he-(particles__he_active+particles__he_scint+particles__he_other))>0.1") << endl;
  cout << tN->GetEntries("TMath::Abs(particles__other-(particles__other_active+particles__other_scint+particles__other_other))>0.1") << endl;

  cout << tN->GetEntries("TMath::Abs(qdep_active__inel-(qdep_active__inel_active+qdep_active__inel_scint+qdep_active__inel_other))>0.1") << endl;
  cout << tN->GetEntries("TMath::Abs(qdep_active__he-(qdep_active__he_active+qdep_active__he_scint+qdep_active__he_other))>0.1") << endl;
  cout << tN->GetEntries("TMath::Abs(qdep_active__other-(qdep_active__other_active+qdep_active__other_scint+qdep_active__other_other))>0.1") << endl;

  cout << tN->GetEntries("TMath::Abs(qdep_veto__inel-(qdep_veto__inel_active+qdep_veto__inel_scint+qdep_veto__inel_other))>0.1") << endl;
  cout << tN->GetEntries("TMath::Abs(qdep_veto__he-(qdep_veto__he_active+qdep_veto__he_scint+qdep_veto__he_other))>0.1") << endl;
  cout << tN->GetEntries("TMath::Abs(qdep_veto__other-(qdep_veto__other_active+qdep_veto__other_scint+qdep_veto__other_other))>0.1") << endl;

  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
}
