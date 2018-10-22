//  .
// ..: P. Chang, philip@physics.ucsd.edu

#ifndef fileutil_h
#define fileutil_h

#include <vector>
#include <map>
#include <dirent.h>

#include "TChain.h"
#include "TDirectory.h"
#include "TH1.h"
#include "stringutil.h"
#include "multidraw.h"
#include "printutil.h"
#include "json.h"

using json = nlohmann::json;

namespace RooUtil
{
    namespace FileUtil
    {
        TChain* createTChain(TString, TString);
        TMultiDrawTreePlayer* createTMulti(TChain*);
        TMultiDrawTreePlayer* createTMulti(TString, TString);
        TH1* get(TString);
        std::map<TString, TH1*> getAllHistograms(TFile*);
        void saveAllHistograms(std::map<TString, TH1*>, TFile*);
        void saveJson(json& j, TFile*, TString="json");
        json getJson(TFile*, TString="json");
        std::vector<TString> getFilePathsInDirectory(TString dirpath);
    }
}

#endif
