#ifndef AliPHOSMEMORYWATCHER_H
#define AliPHOSMEMORYWATCHER_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice     */
/* $Id$ */
//_________________________________________________________________________
/*Basic Memory Leak utility.
    
    You can use this tiny class to *see* if your program is leaking.
    Usage:
    AliPHOSMemoryWatcher memwatcher;
    some program loop on events here {
      if ( nevents % x == 0 ) 
      {
      // take a sample every x events
        memwatcher.watch(nevents);
      }
    }
    TFile f("out.root","RECREATE");
    memwatcher.write();
    f.Close();
    In the output root file you'll get 3 graphs representing
    the evolAliPHOSon, as a function of the number of events, of :
    - VSIZE is the virtual size (in KBytes) of your program, that is sort of
    the total memory used
    - RSSIZE is the resident size (in KBytes), that is, the part of your 
    program which is really in physical memory.
    - TIME is an estimate of time per event (really it's the time elasped
    between two calls to watch method)
    WARNING: this is far from a bulletproof memory report (it's basically 
    using UNIX command ps -h -p [PID] -o vsize,rssize to do its job).
    It has only been tested on Linux so far.
    
    But by fitting the VSIZE by a pol1 under ROOT, you'll see right away
    by how much your program is leaking.
*/             
//*-- Author: Laurent Aphecetche(SUBATECH)
// --- ROOT system ---
#include "TObject.h" 
class TH2;
class TGraph;
class TStopwatch;
class AliPHOSMemoryWatcher : public TObject 
{
public:
  AliPHOSMemoryWatcher(UInt_t maxsize=10000);
  ~AliPHOSMemoryWatcher();
  void Watch(Int_t x);
  
  UInt_t size(void) const { return fSize; }
  Int_t X(Int_t n) const { return fX[n]; }
  Int_t VSIZE(Int_t n) const { return fVSIZE[n]; }
  Int_t RSSIZE(Int_t n) const { return fRSSIZE[n]; }
  Double_t TIME(Int_t n) const { return fTIME[n]; }
  TGraph* GraphVSIZE(void);
  TGraph* GraphRSSIZE(void);
  TGraph* GraphTIME(void);
  TH2* Frame(void) const ;
  void Write(void);
private:
  Int_t fPID;
  char fCmd[1024];
  UInt_t fMAXSIZE;
  UInt_t fSize;
  Int_t* fX;
  Int_t* fVSIZE;
  Int_t* fRSSIZE;
  Double_t* fTIME;
  TStopwatch* fTimer;
  Bool_t fDisabled;

  ClassDef(AliPHOSMemoryWatcher,1) // General purpose memory watcher

} ;
#endif
