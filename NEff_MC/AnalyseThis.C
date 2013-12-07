AnalyseThis(){
   
    TFile *f=new TFile("data/gun_x34_veto.root");
    TTree *veto=(TTree *)f->Get("veto");
    
    veto->AddFriend("classific = tN_Classification","data/gun_x34_veto_goodguysbadguys.root");
    
    //veto->Scan("process:particle:spawn_volume:spawn_KE:spawn_time:track_id:parent_id:qdep_active:qdep_veto","flag<0");

    return 1;
}
