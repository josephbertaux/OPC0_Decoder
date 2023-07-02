#include "decoder.h"

#include <cstdio>
#include <iostream>
#include <string>

#include <TFile.h>

std::string output_path = "/bbox/commissioning/INTT/josephb/";

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

    filename = output_path + filename;
    printf("\n\n");
    printf("Will write to file:\n\t%s\nwhen done\n", filename.c_str());
    printf("\n\n");
    setup(filename);

    prun();

    tree->Write();
    file->Write();
    file->Close();

    if(fptr)fclose(fptr);

    return 0;
}
