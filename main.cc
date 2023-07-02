#include "decoder.h"

#include <cstdio>
#include <iostream>
#include <string>

#include <TFile.h>

std::string output_path = "/bbox/commissioning/INTT/hit_files/";

int main(int argc, char** argv)
{
    FILE* fptr = nullptr;
    std::string filename = argv[1];

    pfileopen(filename.c_str());
    
    std::size_t pos = std::string::npos;
    while(true)
    {
        pos = filename.find("/");
        if(pos == std::string::npos)break;
        filename = filename.substr(pos+1);
    }

    setup();
    prun();

    filename = output_path + filename;
    printf("\n\n");
    printf("Writing to file:\n\t%s\n", filename.c_str());
    printf("\n\n");
    TFile* file = TFile::Open(filename.c_str(), "RECREATE");
    file->cd();
    tree->Write();
    file->Write();
    file->Close();

    if(fptr)fclose(fptr);

    return 0;
}
