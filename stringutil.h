//  .
// ..: P. Chang, philip@physics.ucsd.edu

#ifndef stringutil_h
#define stringutil_h

// Adopted to RooUtil by P. Chang (UCSD)

// Originally written by
// T. M. Hong, tmhong@hep.upenn.edu
// P. Chang, pcchang2@illinois.edu
// B. Cerio, bcc11@phy.duke.edu
// https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/HiggsPhys/HSG3/WWDileptonAnalysisCode/HWWMVAShared/trunk/mvashared/src/MvaStringUtils.cxx

// std
#include <string>
#include <sstream>
#include <vector>
#include <glob.h>

// ROOT
#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"

namespace RooUtil
{
    namespace StringUtil
    {
        typedef std::vector<TString> vecTString;
        // --------------------------------------------------------------------------
        // MvaStringUtils.cxx : python-like string manipulations
        vecTString  filter(vecTString &vec, TString keyword);

        // -- Python-like functions
        void       rstrip     (TString &in,   TString separator="#"                                       );
        vecTString split      (TString in,    TString separator=" "                                       );
        TString    join       (vecTString in, TString joiner=":",                        Int_t rm_blanks=1);
        TString    sjoin      (TString in,    TString separator=" ", TString joiner=":", Int_t rm_blanks=1);
        vecTString glob       (TString patt);
    }
}

//#############################################################################
// rstrip TString
//
void RooUtil::StringUtil::rstrip(TString &in, TString separator)
{
    TString save(in);
    if (separator.EqualTo(" "))
    {
        // Remove end-of-line spaces
        std::string str = in.Data();
        str.erase(str.find_last_not_of(" \n\r\t") + 1);
        in = str.c_str();
    }
    else
    {
        // Remove text after separator
        TObjArray *list = in.Tokenize(separator);
        if (list->GetEntries() != 0)
        { in = ((TObjString*)list->At(0))->GetString(); }
    }
    // Print
    return;
}

//#############################################################################
// Convert TString -> vector<TString>
// like ' '.split()
//
RooUtil::StringUtil::vecTString RooUtil::StringUtil::split(TString in, TString separator)
{
    RooUtil::StringUtil::vecTString out;
    TObjArray *list = in.Tokenize(separator);
    for (unsigned i = 0; i < (unsigned)list->GetEntries(); ++i)
    {
        TString token = ((TObjString*)list->At(i))->GetString();
        out.push_back(token);
    }
    if (out.size() == 0)
    { out.push_back(""); }
    return out;
}

//#############################################################################
// Convert vector<TString> -> TString
// like ':'.join()
//
TString RooUtil::StringUtil::join(RooUtil::StringUtil::vecTString in, TString joiner, Int_t rm_blanks)
{
    std::stringstream ss;
    for (unsigned i = 0; i < in.size(); ++i)
    {
        TString token = in[i];
        ss << token << ((i < in.size() - 1) ? joiner : "");
    }
    // Remove blanks
    TString out = ss.str();
    if (rm_blanks)
    { out.ReplaceAll(" ", ""); }
    return out;
}

//#############################################################################
// Convert TString -> vector<TString> -> TString
//
TString RooUtil::StringUtil::sjoin(TString in, TString separator, TString joiner, Int_t rm_blanks)
{
    RooUtil::StringUtil::vecTString vec = RooUtil::StringUtil::split(in, separator);
    TString out = RooUtil::StringUtil::join(vec, joiner, rm_blanks);
    return out;
}

//#############################################################################
RooUtil::StringUtil::vecTString RooUtil::StringUtil::filter(RooUtil::StringUtil::vecTString &vec, TString keyword)
{
    RooUtil::StringUtil::vecTString newvec;
    for (unsigned i = 0; i < vec.size(); ++i)
    {
        if (! vec[i].Contains(keyword))
        {
            continue;
        }
        newvec.push_back(vec[i]);
    }
    return newvec;
}

//#############################################################################
RooUtil::StringUtil::vecTString RooUtil::StringUtil::glob(TString patt)
{
    glob_t glob_result;
    glob(patt.Data(), GLOB_TILDE, NULL, &glob_result);
    std::vector<TString> ret;
    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i)
    {
        ret.push_back(glob_result.gl_pathv[i]);
    }
    globfree(&glob_result);
    return ret;
}

#endif
