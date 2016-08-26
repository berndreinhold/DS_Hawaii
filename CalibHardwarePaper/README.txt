Aug. 26, 2016:
- the main file is DS_CALIS_hardware.tex, there you can see all other files that are included. There is only one level of inclusion, i.e. only DS_CALIS_hardware.tex has file includes, e.g. calibrationcampaign.tex et al. don't have further file includes
- all figures included in the tex-files are in the Figures/-directory. There are subdirectories in the Figures/-dir in case there is a collection of items related to one figure. There is a lot of files and documents in the Figures/-dir, which allow to modify or regenerate all figures of the paper, hence its rather big size.
- different versions of the paper are on the DarkSide-50 DocDB 1585.
- when compiling the latex file, only the latest version of the paper is produced 
- I compiled the DS_CALIS_hardware.tex under windows using miktex and texworks
- the compilation is done using a sequence of pdflatex, bibtex, pdflatex, pdflatex
- contact me in case of questions

Bernd Reinhold, UH (email: bernd@hawaii.edu)