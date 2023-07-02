#ifndef DECODER_H
#define DECODER_H

#include <pmonitor/pmonitor.h>
#include <Event/Event.h>
#include <Event/EventTypes.h>

#include <cstdio>
#include <cstdint>
#include <map>
#include <string>

#include <TFile.h>
#include <TTree.h>

struct PerEventValues_s
{
    Int_t n_evt = 0;
    Int_t num_hits = 0;
    Long64_t gtm_bco = 0;
    Int_t flx_svr = 0;
};
extern struct PerEventValues_s event_values;

struct PerHitValues_s
{
    Int_t flx_bco = 0;
    Int_t flx_chn = 0;
    Int_t chp = 0;
    Int_t chn = 0;
    Int_t adc = 0;
};
extern struct PerHitValues_s hit_values;
extern std::map<std::string, Int_t*> arr_type_branches;

extern TFile* file;
extern TTree* tree;

int pinit();
int setup(std::string const&);
int process_event(Event*);

#endif//DECODER_H
