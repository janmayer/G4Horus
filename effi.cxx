/*
* Get Efficiency for FEP, SEP and DEP from root files created by Geant4
* Filenames are supposed to be formatted like <energy>.root (e.g. 100.root)
* Note: In a root macro, the function with the same name as the file will be executed
* usage: $ root -l -b -q 'effi.cxx("/scratch/jmayer/G4")'
* --> for ROOT Version 6 or higher <--
*/

inline int FileSize (const char* name) {
	int size = 0;
	if (FILE *file = fopen(name,"r")) {
		fseek(file,0,SEEK_END);
		size = ftell(file);
		fclose(file);
	}
	return size;
}


inline double PeakVolume(const TH1D* th, const int& pos){
	int width = 2;
	return 2.*th->Integral(pos-width,pos+width)-1.*th->Integral(pos-2*width,pos+2*width);
}


inline double Efficiency(const TH1D* th, const int& pos, const int& off){
	if (off > pos) {
		return 0;
	} else {
		return PeakVolume(th,pos-off)/(th->GetEntries()*1.);
	}
}


void EfficencyForEnergyFromFile(const int& energie, const TString& file){
	TFile *f = TFile::Open(file);
	f->cd("histograms");
	TDirectory *histdir = gDirectory;

	TH1D *h = new TH1D();

	TKey *key;
	TIter nextkey(histdir->GetListOfKeys());
	while ( (key = (TKey*)nextkey()) ) {
		if (gROOT->GetClass( key->GetClassName() )->InheritsFrom( TH1D::Class() )){
			h = (TH1D*)(key->ReadObj());
			cout << key->GetName() << "\t" << energie << "\t" << Efficiency(h, energie, 0) << "\t" << Efficiency(h, energie, 511) << "\t" << Efficiency(h, energie, 2*511) << endl;
		}
	}
}


std::map<int, TString> EfficiencyFilesIn(const TString& dirname)
{
	const TString ext = ".root";
	std::map<int, TString> m;

	TSystemDirectory dir(dirname, dirname);
	TList *files = dir.GetListOfFiles();
	if (files) {
		TSystemFile *file;
		TString fname;
		TIter next(files);
		int i = 0;
		while ((file=(TSystemFile*)next())) {
			fname = file->GetName();
			// Check if file is not a directory, is a root file, is not a partial (_t) root file, and is of resonable size (== finished)
			if ( !file->IsDirectory() && fname.EndsWith(ext) && !fname.SubString("_t") && FileSize(dirname+"/"+fname) > 20000 ) {
				// Get energy from filename
				if (sscanf(fname, "%d.root", &i) == 1){
					m.insert({i, dirname+"/"+fname});
				}
			}
		}
	}
	return m;
}


void effi(const TString& directory){
	auto files = EfficiencyFilesIn(directory);
	for ( auto &file : files ) {
		cout << "# Data for E = " << file.first << " keV from file " << file.second << ":" << endl;
		EfficencyForEnergyFromFile(file.first, file.second);
	}
}
