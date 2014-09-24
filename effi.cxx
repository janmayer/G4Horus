inline bool file_exists (const char* name) {
    if (FILE *file = fopen(name, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

inline int file_size (const char* name) {
    FILE *p_file = NULL;
    p_file = fopen(name,"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

double peak_volume(TH1D *th, int pos){
	int width = 2;
	return 2.*th->Integral(pos-width,pos+width)-1.*th->Integral(pos-2*width,pos+2*width);
	//return th->Integral(pos-2,pos+2);
}

double efficiency(TH1D *th, int pos, int off){
	if (off > pos) {
		return 0;
	} else {
		return peak_volume(th,pos-off)/(th->GetEntries()*1.);
	}
	/*} else {
		return th->Integral(pos+1,pos)/(th->GetEntries()*1.);
	}*/

}

void get_effi(int energie){
	std::vector<string> detectors = {"Ge00", "Ge01", "Ge02", "Ge03", "Ge04", "Ge05", "Ge07", "Ge08", "Ge09", "Ge10", "Ge11", "Ge12", "Ge13"};
	//std::vector<std::string> detectors = {"Ge01", "Ge02", "Ge04", "Ge05", "Ge07", "Ge08", "Ge11", "Ge12", "Ge13"};
	//std::vector<std::string> detectors = {"Ge02", "Ge03"};

	// Using c_str() gives cling error -> dirty c
	// TFile *f = TFile::Open( ("/scratch/jmayer/G4/" + std::to_string(energie) + ".root").data() );
	char cstr[80];
   	sprintf(cstr, "/scratch/jmayer/G4/%d.root", energie);
   	if( file_exists(cstr) && file_size(cstr) > 20000 ){

		TFile *f = TFile::Open(cstr);
		TH1D *h = new TH1D();

		for ( auto &det : detectors ) {
			TH1D *h = (TH1D*)f->Get( ("histograms/"+det).c_str() );
			cout << det << "\t" << energie << "\t" << efficiency(h, energie, 0) << "\t" << efficiency(h, energie, 511) << "\t" << efficiency(h, energie, 2*511) << endl;
		}
	}
}

void effi(){
	int estep = 100;
	for (int i=1;i<101;i++){
		get_effi(estep*i);
	}
}
