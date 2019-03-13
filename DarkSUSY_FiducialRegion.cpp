{
	gROOT->SetStyle("Plain");
	int canvas_x = 600, canvas_y = 600;

	TString PATH_samples;
	PATH_samples = "/afs/cern.ch/work/y/yjeong/Run2_DarkSUSY_CentralMC/";
	TString Sample_type_mN1_10;
	Sample_type_mN1_10 = "out_ana_mN1_10_";
	TString Save_dir;
	Save_dir = "/afs/cern.ch/work/y/yjeong/darkSUSY_script/test/";

	const int Sample_Num = 2;
	const int nVariable = 2;
	int event, lumi;//tree variable

	TString Sample_name[Sample_Num] = {"mGammaD_0p25_cT_0p1","mGammaD_5_cT_50"};
	TString Variable[nVariable] = {"event","lumi"};

	TFile *tfile[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tfile[i] = new TFile(PATH_samples+Sample_type_mN1_10+Sample_name[i]+".root");
	}
	TTree *tree[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tree[i] = (TTree*)tfile[i]->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
	}

	TH1F *histo_event[Sample_Num][nVariable];
	TCanvas *canv_[Sample_Num][nVariable];

	int nbin[Sample_Num] = {1000,2000};
	float xmin[Sample_Num] = {0,0};
	float xmax[Sample_Num] = {100000,300000};

	for(int nVar=0; nVar < nVariable; nVar++){
		for(int nSam=0; nSam < Sample_Num; nSam++){
			canv_[nVar][nSam] = new TCanvas(Form("Canv_%d_%d",nVar,nSam),Form(""),canvas_x,canvas_y);
			histo_event[nVar][nSam] = new TH1F(Form("histo_event_%d_%d",nVar,nSam),Form(""),nbin[nSam],xmin[nSam],xmax[nSam]);
			tree[nSam]->Project(Form("histo_event_%d_%d",nVar,nSam),Variable[nVar]);

			histo_event[nVar][nSam]->Draw();
			canv_[nVar][nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+Variable[nVar]+".png");
		}
	}
}

