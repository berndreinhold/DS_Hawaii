#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ struct darkart::EventInfo+;
#pragma link C++ struct darkart::Channel+;
#pragma link C++ struct darkart::ChannelData+;
#pragma link C++ struct darkart::Channel::ChannelID+;
#pragma link C++ struct darkart::Baseline+;
#pragma link C++ struct darkart::Pmt+;
#pragma link C++ struct darkart::WaveformInfo+;
#pragma link C++ struct darkart::Pulse+;
#pragma link C++ struct darkart::PulseData+;
#pragma link C++ struct darkart::Pulse::PulseID+;
#pragma link C++ struct darkart::PulseParam+;
#pragma link C++ struct darkart::Roi+;
#pragma link C++ struct darkart::EventData+;
#pragma link C++ struct darkart::Spe+;
#pragma link C++ struct darkart::PositionParam+;
//#pragma link C++ class HistogramSelector+;
//#pragma link C++ struct PMTGeom+;
//#pragma link C++ class XYReconstructor+;
//#pragma link C++ class XYRecHelper+;
#pragma link C++ struct VetoEvent+;
#pragma link C++ struct vector<VetoEvent>+;
 //https://neutrinoustc.wordpress.com/2013/05/02/use-vector-as-a-branch-in-ttree/ to avoid the statement: "Error in <TTree::Branch>: The pointer specified for … is not of a class or type known to ROOT"
#endif
