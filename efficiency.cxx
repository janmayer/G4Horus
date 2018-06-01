/*
* Get Efficiency for FEP, SEP and DEP from root files created by Geant4
* Filenames are supposed to be formatted like <energy>.root (e.g. 100.root)
* Note: In a root macro, the function with the same name as the file will be executed
* usage: $ root -l -b -q 'effi.cxx("/scratch/jmayer/G4")'
* --> for ROOT Version 6 or higher <--
*/

int FileSize(const char *name)
{
    int size = 0;
    if (FILE *file = fopen(name, "r")) {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fclose(file);
    }
    return size;
}

inline double PeakVolume(const TH1D &th, const int &pos)
{
    int width = 2;
    return 2. * th.Integral(pos - width, pos + width) - 1. * th.Integral(pos - 2 * width, pos + 2 * width);
}

inline double Efficiency(const TH1D &th, const int &pos, const int &off)
{
    if (off > pos) {
        return 0;
    } else {
        return PeakVolume(th, pos - off) / (th.GetEntries() * 1.);
    }
}

std::vector<TH1D> SpectraFromFile(const TString &directory, const TString &file)
{
    std::vector<TH1D> spectra;

    TFile *f = TFile::Open(directory + file);
    f->cd("histograms");
    TDirectory *histdir = gDirectory;
    TKey *key;
    TIter nextkey(histdir->GetListOfKeys());
    while ((key = (TKey *)nextkey())) {
        if (gROOT->GetClass(key->GetClassName())->InheritsFrom(TH1D::Class())) {
            spectra.push_back(*dynamic_cast<TH1D *>(key->ReadObj()));
        }
    }

    return spectra;
}

std::vector<TString> GeBGOPairNumbers(const std::vector<TString> &in)
{
    std::vector<TString> out;

    for (const TString &l1 : in) {
        if (l1.BeginsWith("Ge")) {
            for (const TString &l2 : in) {
                if (l2.BeginsWith("BGO") && TString(l2(3, 2)).EqualTo(TString(l1(2, 2)))) {
                    out.push_back(TString(l2(3, 2)));
                }
            }
        }
    }

    return out;
}

std::vector<TString> LeavesInTChain(TChain *t)
{
    std::vector<TString> leafnames;

    TLeaf *obj;
    TObjArrayIter nextleaf(t->GetListOfLeaves());
    while ((obj = (TLeaf *)nextleaf())) {
        leafnames.push_back(TString(obj->GetName()));
    }

    return leafnames;
}

std::vector<TH1D> VetoedSpectraFromTChain(const TString &directory, const TString &file)
{
    std::vector<TH1D> spectra;

    // TODO: Replace cstr this with someting better
    char cstr[80];
    sprintf(cstr, "%s%d_t*.root", directory.Data(), file.Atoi());

    TChain *t = new TChain("ntuple/Horus");
    t->CanDeleteRefs(false);
    t->Add(cstr);

    if (t->GetNbranches() > 0) {
        for (const TString &leaf : GeBGOPairNumbers(LeavesInTChain(t))) {
            TString name = "V" + leaf;
            TH1D *h = new TH1D(name, name, 20000, 0, 20000);
            // Project TChain Data to spectrum with name name, leaf GeXX with energy in keV, if the corresponding BGO has no deposited energy
            t->Project(name, "Ge" + leaf + "*1000.", "BGO" + leaf + "==0");
            spectra.push_back(*h);
            delete h;
        }
    }

    return spectra;
}

std::vector<TString> EfficiencyFilesIn(const TString &dirname)
{
    const TString ext = ".root";
    std::vector<TString> m;

    TSystemDirectory dir(dirname, dirname);
    TList *files = dir.GetListOfFiles();
    if (files) {
        TSystemFile *file;
        TString fname;
        TIter next(files);
        while ((file = (TSystemFile *)next())) {
            fname = file->GetName();
            // Check if file is not a directory, is a root file, is not a partial (_t) root file, and is of resonable size (== finished)
            if (!file->IsDirectory() && fname.EndsWith(ext) && !fname.SubString("_t") && FileSize(dirname + fname) > 20000) {
                m.push_back(fname);
            }
        }
    }
    std::sort(m.begin(), m.end(), [](const TString &a, const TString &b) -> bool { return a.Atoi() < b.Atoi(); });
    return m;
}

void efficiency(const TString &directory)
{
    const auto files = EfficiencyFilesIn(directory);
    for (const auto &file : files) {
        int energy = file.Atoi();
        cout << "# Data for E = " << energy << " keV from file " << file << ":" << endl;

        auto spectra = SpectraFromFile(directory, file);
        for (const TH1D &h : spectra) {
            cout << h.GetName() << "\t" << energy << "\t" << Efficiency(h, energy, 0) << "\t" << Efficiency(h, energy, 511) << "\t" << Efficiency(h, energy, 2 * 511) << endl;
        }

        auto vetoedspectra = VetoedSpectraFromTChain(directory, file);
        for (const TH1D &h : vetoedspectra) {
            cout << h.GetName() << "\t" << energy << "\t" << Efficiency(h, energy, 0) << "\t" << Efficiency(h, energy, 511) << "\t" << Efficiency(h, energy, 2 * 511) << endl;
        }
    }
}
