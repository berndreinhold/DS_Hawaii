#!/usr/bin/python

import sys
import os
#os._exit(-1) to exit unconditionally
sys.argv.append( '-b' ) #batch mode, or call as: python main_script.py -b
import string
import MCTuning_FusedSilicaUVAbs as MCT
#import MCTuningBase as MCT
from ROOT import TTree, TGraph, TCanvas, gROOT


class MCTuning_Plot(MCT.MCTuning_FusedSilicaUVAbs):
#class MCTuning_Plot(MCT.MCTuning):
    """ plot the chi2 of TopBottom-PMT ratio and Collection Efficiency found in the various MCTuning classes and in the output file e.g. chi2_FusedSilicaUVAbs.txt"""
    def Plot(self):
        t = TTree()
        t.SetNameTitle("chi2","chi2 vs. varied MC parameter")
        #t.ReadFile("%s/%s/chi2_%s.txt" % (self._output_dir, self._par1_name, self._par1_name),"par1:chi2_colleff:chi2_topbottom", ",");
        t.ReadFile("%s/%s/chi2_%s_%s.txt" % (self._output_dir, self._par1_name, self._g4ds_output_prefix, self._par1_name),"par1:chi2_colleff:chi2_topbottom:ndf_colleff:ndf_topbottom");

        c = TCanvas()
        c.Divide(1,2)
        c1=c.cd(1)
        gr1=TGraph()
        t.Draw("chi2_colleff:par1")
        #gr1=gROOT.Get("gr1")
        #gr1.SetMarkerColor(kBlue)
        #gr1.SetMarkerSize(0.15)
        
        if self._par1_linlog=="log":
            c1.SetLogx()

        c2=c.cd(2)
        t.Draw("chi2_topbottom:par1")
        if self._par1_linlog=="log":
            c2.SetLogx()

        c.SaveAs("%s/%s/chi2_%s_%s.C" % (self._output_dir, self._par1_name, self._g4ds_output_prefix, self._par1_name))
        c.SaveAs("%s/%s/chi2_%s_%s.png" % (self._output_dir, self._par1_name, self._g4ds_output_prefix, self._par1_name))
        
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def main():
    x = MCTuning_Plot()
    print x.__doc__
    x.Plot() 

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if __name__ == "__main__":
    main()
