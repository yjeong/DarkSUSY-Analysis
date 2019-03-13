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

	bool isDiMuonHLTFired;
	int lumi, run, event;
	float selMu0_px, selMu1_px, selMu2_px, selMu3_px;
	float selMu0_py, selMu1_py, selMu2_py, selMu3_py;
	float selMu0_pT, selMu1_pT, selMu2_pT, selMu3_pT;
	float selMu0_eta, selMu1_eta, selMu2_eta, selMu3_eta;
	float selMu0_phi, selMu1_phi, selMu2_phi, selMu3_phi;
	float genA0_m, genA0_px, genA0_py, genA0_pz, genA0_eta, genA0_phi, genA0_Lx, genA0_Ly, genA0_Lz, genA0_Lxy, genA0_L;
	float genA1_m, genA1_px, genA1_py, genA1_pz, genA1_eta, genA1_phi, genA1_Lx, genA1_Ly, genA1_Lz, genA1_Lxy, genA1_L;

	TString Sample_name[Sample_Num] = {"mGammaD_0p25_cT_0p1","mGammaD_5_cT_50"};
	TString Variable[nVariable] = {"event","lumi"};

	TFile *tfile[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tfile[i] = new TFile(PATH_samples+Sample_type_mN1_10+Sample_name[i]+".root");
	}
	TTree *tree[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tree[i] = (TTree*)tfile[i]->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
		tree[i]->SetBranchAddress("event",&event);
		tree[i]->SetBranchAddress("run",&run);
		tree[i]->SetBranchAddress("lumi",&lumi);
		tree[i]->SetBranchAddress("isDiMuonHLTFired",&isDiMuonHLTFired);
		tree[i]->SetBranchAddress("selMu0_px",&selMu0_px);
		tree[i]->SetBranchAddress("selMu1_px",&selMu1_px);
		tree[i]->SetBranchAddress("selMu2_px",&selMu2_px);
		tree[i]->SetBranchAddress("selMu3_px",&selMu3_px);
		tree[i]->SetBranchAddress("selMu0_py",&selMu0_py);
		tree[i]->SetBranchAddress("selMu1_py",&selMu1_py);
		tree[i]->SetBranchAddress("selMu2_py",&selMu2_py);
		tree[i]->SetBranchAddress("selMu3_py",&selMu3_py);
		tree[i]->SetBranchAddress("selMu0_pT",&selMu0_pT);
		tree[i]->SetBranchAddress("selMu1_pT",&selMu1_pT);
		tree[i]->SetBranchAddress("selMu2_pT",&selMu2_pT);
		tree[i]->SetBranchAddress("selMu3_pT",&selMu3_pT);
		tree[i]->SetBranchAddress("selMu0_eta",&selMu0_eta);
		tree[i]->SetBranchAddress("selMu1_eta",&selMu1_eta);
		tree[i]->SetBranchAddress("selMu2_eta",&selMu2_eta);
		tree[i]->SetBranchAddress("selMu3_eta",&selMu3_eta);
		tree[i]->SetBranchAddress("selMu0_phi",&selMu0_phi);
		tree[i]->SetBranchAddress("selMu1_phi",&selMu1_phi);
		tree[i]->SetBranchAddress("selMu2_phi",&selMu2_phi);
		tree[i]->SetBranchAddress("selMu3_phi",&selMu3_phi);
		//--------------------------------------------------
		tree[i]->SetBranchAddress("genA0_m",&genA0_m);
		tree[i]->SetBranchAddress("genA0_px",&genA0_px);
		tree[i]->SetBranchAddress("genA0_py",&genA0_py);
		tree[i]->SetBranchAddress("genA0_pz",&genA0_pz);
		tree[i]->SetBranchAddress("genA0_eta",&genA0_eta);
		tree[i]->SetBranchAddress("genA0_phi",&genA0_phi);
		tree[i]->SetBranchAddress("genA0_Lx",&genA0_Lx);
		tree[i]->SetBranchAddress("genA0_Ly",&genA0_Ly);
		tree[i]->SetBranchAddress("genA0_Lz",&genA0_Lz);
		tree[i]->SetBranchAddress("genA0_Lxy",&genA0_Lxy);
		tree[i]->SetBranchAddress("genA0_L",&genA0_L);
		//-------------------------------------------------
		tree[i]->SetBranchAddress("genA1_m",&genA1_m);
		tree[i]->SetBranchAddress("genA1_px",&genA1_px);
		tree[i]->SetBranchAddress("genA1_py",&genA1_py);
		tree[i]->SetBranchAddress("genA1_pz",&genA1_pz);
		tree[i]->SetBranchAddress("genA1_eta",&genA1_eta);
		tree[i]->SetBranchAddress("genA1_phi",&genA1_phi);
		tree[i]->SetBranchAddress("genA1_Lx",&genA1_Lx);
		tree[i]->SetBranchAddress("genA1_Ly",&genA1_Ly);
		tree[i]->SetBranchAddress("genA1_Lz",&genA1_Lz);
		tree[i]->SetBranchAddress("genA1_Lxy",&genA1_Lxy);
		tree[i]->SetBranchAddress("genA1_L",&genA1_L);

	}

	TH1F *histo_event[Sample_Num][nVariable];
	TCanvas *canv_[Sample_Num][nVariable];

	int nbin[Sample_Num] = {1000,2000};
	float xmin[Sample_Num] = {0,0};
	float xmax[Sample_Num] = {100000,300000};

	if(isDiMuonHLTFired==true) continue;
	//----------------------------------initial value cut-----------------------------------
	if(!(selMu0_px!=-100 && selMu0_py!=-100 && selMu0_pT!=-100 && selMu0_eta!=-100 && selMu0_phi!=-100)) continue;
	if(!(selMu1_px!=-100 && selMu1_py!=-100 && selMu1_pT!=-100 && selMu1_eta!=-100 && selMu1_phi!=-100)) continue;
	if(!(selMu2_px!=-100 && selMu2_py!=-100 && selMu2_pT!=-100 && selMu2_eta!=-100 && selMu2_phi!=-100)) continue;
	if(!(selMu3_px!=-100 && selMu3_py!=-100 && selMu3_pT!=-100 && selMu3_eta!=-100 && selMu3_phi!=-100)) continue;
	if(!(genA0_Lx!=-1000 && genA0_Ly!=-1000 && genA0_Lz!=-1000 && genA0_Lxy!=-1000 && genA0_L!=-1000)) continue;
	if(!(genA1_Lx!=-1000 && genA1_Ly!=-1000 && genA1_Lz!=-1000 && genA1_Lxy!=-1000 && genA1_L!=-1000)) continue;

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

