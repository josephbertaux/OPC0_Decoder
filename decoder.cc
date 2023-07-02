#include "decoder.h"

std::map<std::string, Int_t*> arr_type_branches =
{
    {"flx_chn", nullptr},
    {"chp", nullptr},
    {"chn", nullptr},

    {"flx_bco", nullptr},
    {"adc", nullptr},
};

TFile* file = nullptr;
TTree* tree = nullptr;
struct PerEventValues_s event_values = (struct PerEventValues_s){};
struct PerHitValues_s hit_values = (struct PerHitValues_s){};

int pinit()
{
    return 0;
}

int setup(std::string const& filename)
{
    event_values = (struct PerEventValues_s){};
    hit_values = (struct PerHitValues_s){};


    if(!file)
    {
        TFile* file = TFile::Open(filename.c_str(), "RECREATE");
    }
    file->cd();

    if(!tree)
    {
        tree = new TTree("tree", "tree");
        tree->Branch("n_evt", &(event_values.n_evt));
        tree->Branch("num_hits", &(event_values.num_hits));
        tree->Branch("gtm_bco", &(event_values.gtm_bco));
        tree->Branch("flx_svr", &(event_values.flx_svr));
   
        for(std::map<std::string, Int_t*>::iterator itr = arr_type_branches.begin(); itr != arr_type_branches.end(); ++itr)
        {
            //printf("%s\n", itr->first.c_str());
            tree->Branch(itr->first.c_str(), itr->second, (itr->first + std::string("[num_hits]/I")).c_str());
        }
    }

    //tree->Print();

    return 0;
}

int process_event(Event* e)
{
    if(!e)return 0;

    for(event_values.flx_svr = 0; event_values.flx_svr < 8; ++event_values.flx_svr) 
    {
        Packet* p = e->getPacket(event_values.flx_svr + 3001);
        if(!p)continue;

        event_values.num_hits = p->iValue(0, "NR_HITS");
        event_values.gtm_bco = p->iValue(0, "BCO");

        for(std::map<std::string, Int_t*>::iterator itr = arr_type_branches.begin(); itr != arr_type_branches.end(); ++itr)
        {
            itr->second = new Int_t[event_values.num_hits];
            tree->GetBranch(itr->first.c_str())->SetAddress(itr->second);
        }

        for(Int_t n = 0; n < event_values.num_hits; ++n)
        {
            hit_values.flx_chn = p->iValue(n, "FEE");
            hit_values.chp = p->iValue(n, "CHIP_ID");
            hit_values.chn = p->iValue(n, "CHANNEL_ID");

            hit_values.flx_bco = p->iValue(n, "FPHX_BCO");
            hit_values.adc = p->iValue(n, "ADC");

            arr_type_branches["flx_chn"][n] = hit_values.flx_chn;
            arr_type_branches["chp"][n] = hit_values.chp;
            arr_type_branches["chp"][n] = hit_values.chn;

            arr_type_branches["flx_bco"][n] = hit_values.flx_bco;
            arr_type_branches["adc"][n] = hit_values.adc;
        }

        tree->Fill();
        ++event_values.n_evt;

        for(std::map<std::string, Int_t*>::iterator itr = arr_type_branches.begin(); itr != arr_type_branches.end(); ++itr)
        {
            delete[] itr->second;
        }

        delete p;
    }

    return 0;
}
