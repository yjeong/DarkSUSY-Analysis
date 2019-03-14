{
	gROOT->SetStyle("Plain");

	//gStyle->SetOptStat("mr");//To display the mean and RMS: SetOptStat("mr"), nemruoi, ;
	//gStyle->SetOptDate(0);//display date position

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.2);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.1);
	gStyle->SetPadBorderMode(0);

	int canvas_x = 600, canvas_y = 600;

	/*static Int_t  colors[50];
	  static Bool_t initialized = kFALSE;
	  Double_t Red[3]    = { 1.00, 0.00, 0.00};
	  Double_t Green[3]  = { 0.00, 1.00, 0.00};
	  Double_t Blue[3]   = { 1.00, 0.00, 1.00};
	  Double_t Length[3] = { 0.00, 0.50, 1.00};
	  if(!initialized){
	  Int_t FI = TColor::CreateGradientColorTable(3,Length,Red,Green,Blue,50);
	  for (int i=0; i<50; i++) colors[i] = FI+i;
	  initialized = kTRUE;
	  return;
	  }
	  gStyle->SetPalette(50,colors);*/

	TString PATH_samples;
	PATH_samples = "/afs/cern.ch/work/y/yjeong/Run2_DarkSUSY_CentralMC/";
	TString Sample_type_mN1_10;
	Sample_type_mN1_10 = "out_ana_mN1_10_";
	TString Save_dir;
	Save_dir = "/afs/cern.ch/work/y/yjeong/darkSUSY_script/test/";

	const int Sample_Num = 1;
	const int nVariable = 2;

	bool isDiMuonHLTFired;
	int lumi_, run, event;
	float selMu0_px, selMu1_px, selMu2_px, selMu3_px;
	float selMu0_py, selMu1_py, selMu2_py, selMu3_py;
	float selMu0_pT, selMu1_pT, selMu2_pT, selMu3_pT;
	float selMu0_eta, selMu1_eta, selMu2_eta, selMu3_eta;
	float selMu0_phi, selMu1_phi, selMu2_phi, selMu3_phi;
	float genA0_m, genA0_px, genA0_py, genA0_pz, genA0_eta, genA0_phi, genA0_Lx, genA0_Ly, genA0_Lz, genA0_Lxy, genA0_L;
	float genA1_m, genA1_px, genA1_py, genA1_pz, genA1_eta, genA1_phi, genA1_Lx, genA1_Ly, genA1_Lz, genA1_Lxy, genA1_L;

	//TString Sample_name[Sample_Num] = {"mGammaD_5_cT_50","mGammaD_0p25_cT_0p1"};
	TString Sample_name[Sample_Num] = {"mGammaD_5_cT_50"};
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
		tree[i]->SetBranchAddress("lumi",&lumi_);
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

	/*int nbin[nVariable][Sample_Num] = {{1000,2000},{100,150}};
	float xmin[nVariable][Sample_Num] = {{0,0},{0,0}};
	float xmax[nVariable][Sample_Num] = {{100000,300000},{100,150}};*/

	int eff_nbin_x = 100;
	//int eff_nbin_y = 80;
	float eff_xmin_x = -7;
	float eff_xmax_x = 7;
	//float eff_xmin_y = 0;
	//float eff_xmax_y = 500;

	for(int nSam=0; nSam < Sample_Num; nSam++){
		for(int nVar=0; nVar < nVariable; nVar++){
			canv_[nVar][nSam] = new TCanvas(Form("Canv_%d_%d",nVar,nSam),Form(""),canvas_x,canvas_y);
			//histo_event[nVar][nSam] = new TH1F(Form("histo_event_%d_%d",nVar,nSam),Form(""),nbin[nVar][nSam],xmin[nVar][nSam],xmax[nVar][nSam]);
			histo_event[nVar][nSam] = new TH1F(Form("histo_event_%d_%d",nVar,nSam),Form(""),100,0,300000);
			tree[nSam]->Project(Form("histo_event_%d_%d",nVar,nSam),Variable[nVar]);

			histo_event[nVar][nSam]->Draw();
			//canv_[nVar][nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+Variable[nVar]+".png");
		}
	}

	TH1F *histo_den_A0[Sample_Num];
	TH1F *histo_num_A0[Sample_Num];
	TH1F *histo_dR_A0[Sample_Num];
	TCanvas *canv_eff_den_A0[Sample_Num];
	TCanvas *canv_eff_num_A0[Sample_Num];
	TCanvas *canv_dR_A0[Sample_Num];

	TH1F *histo_den_A1[Sample_Num];
	TH1F *histo_num_A1[Sample_Num];
	TH1F *histo_dR_A1[Sample_Num];
	TCanvas *canv_eff_den_A1[Sample_Num];
	TCanvas *canv_eff_num_A1[Sample_Num];
	TCanvas *canv_dR_A1[Sample_Num];


	int nGenMuA0 = 0;
	float RecMuEta = 0;
	float dEta_A0 = 0;
	float dPhi_A0 = 0;
	float dR_A0 = 0;
	float dEta_A1 = 0;
	float dPhi_A1 = 0;
	float dR_A1 = 0;

	for(int nSam=0; nSam < Sample_Num; nSam++){
		canv_eff_den_A0[nSam] = new TCanvas(Form("canv_eff_den_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		canv_eff_num_A0[nSam] = new TCanvas(Form("canv_eff_num_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		canv_dR_A0[nSam] = new TCanvas(Form("canv_dR_A0_%d",nSam),Form(""),canvas_x,canvas_y);


		histo_den_A0[nSam] = new TH1F(Form("histo_den_A0_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x);
		//tree[nSam]->Project(Form("histo_den_A0_%d",nSam),"genA0_eta");
		histo_num_A0[nSam] = new TH1F(Form("histo_num_A0_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x);
		histo_dR_A0[nSam] = new TH1F(Form("histo_dR_A0_%d",nSam),Form(""),200,0,1);


		canv_eff_den_A1[nSam] = new TCanvas(Form("canv_eff_den_A1_%d",nSam),Form(""),canvas_x,canvas_y);
		canv_eff_num_A1[nSam] = new TCanvas(Form("canv_eff_num_A1_%d",nSam),Form(""),canvas_x,canvas_y);
		canv_dR_A1[nSam] = new TCanvas(Form("canv_dR_A1_%d",nSam),Form(""),canvas_x,canvas_y);


		histo_den_A1[nSam] = new TH1F(Form("histo_den_A1_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x);
		//tree[nSam]->Project(Form("histo_den_A1_%d",nSam),"genA1_eta");
		histo_num_A1[nSam] = new TH1F(Form("histo_num_A1_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x);
		histo_dR_A1[nSam] = new TH1F(Form("histo_dR_A1_%d",nSam),Form(""),200,0,1);


		for(int nev=0; nev < tree[nSam]->GetEntries(); nev++){
			tree[nSam]->GetEntry(nev);

			if(isDiMuonHLTFired == true) continue;
			if(fabs(selMu0_eta)!=100){
				dEta_A0 = genA0_eta-selMu0_eta;
				dPhi_A0 = genA0_phi-selMu0_phi;
				dEta_A1 = genA1_eta-selMu0_eta;
				dPhi_A1 = genA1_phi-selMu0_phi;
				RecMuEta = selMu0_eta;
			}

			if(fabs(selMu1_eta)!=100){
				dEta_A0 = genA0_eta-selMu1_eta;
				dPhi_A0 = genA0_phi-selMu1_phi;
				dEta_A1 = genA1_eta-selMu1_eta;
				dPhi_A1 = genA1_phi-selMu1_phi;
				RecMuEta = selMu1_eta;
			}

			if(fabs(selMu2_eta)!=100){
				dEta_A0 = genA0_eta-selMu2_eta;
				dPhi_A0 = genA0_phi-selMu2_phi;
				dEta_A1 = genA1_eta-selMu2_eta;
				dPhi_A1 = genA1_phi-selMu2_phi;
				RecMuEta = selMu2_eta;
			}

			if(fabs(selMu3_eta)!=100){
				dEta_A0 = genA0_eta-selMu3_eta;
				dPhi_A0 = genA0_phi-selMu3_phi;
				dEta_A1 = genA1_eta-selMu3_eta;
				dPhi_A1 = genA1_phi-selMu3_phi;
				RecMuEta = selMu3_eta;
			}

			dR_A0 = sqrt(pow(dEta_A0,2)+pow(dPhi_A0,2));
			histo_dR_A0[nSam]->Fill(dR_A0);
			dR_A1 = sqrt(pow(dEta_A1,2)+pow(dPhi_A1,2));
			histo_dR_A1[nSam]->Fill(dR_A1);

			if(dR_A0<0.1) histo_num_A0[nSam]->Fill(RecMuEta);
			histo_den_A0[nSam]->Fill(genA0_eta);
			if(dR_A1<0.1) histo_num_A1[nSam]->Fill(RecMuEta);
			histo_den_A1[nSam]->Fill(genA1_eta);
		}
		canv_eff_den_A0[nSam]->cd();
		histo_den_A0[nSam]->Draw();
		canv_eff_den_A0[nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+"eff_den_A0.png");
		canv_eff_num_A0[nSam]->cd();
		histo_num_A0[nSam]->Draw();
		canv_eff_num_A0[nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+"eff_num_A0.png");
		canv_dR_A0[nSam]->cd();
		canv_dR_A0[nSam]->SetLogy();
		histo_dR_A0[nSam]->Draw();
		canv_dR_A0[nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+"dR_A0.png");

		canv_eff_den_A1[nSam]->cd();
		histo_den_A1[nSam]->Draw();
		canv_eff_den_A1[nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+"eff_den_A1.png");
		canv_eff_num_A1[nSam]->cd();
		histo_num_A1[nSam]->Draw();
		canv_eff_num_A1[nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+"eff_num_A1.png");
		canv_dR_A1[nSam]->cd();
		canv_dR_A1[nSam]->SetLogy();
		histo_dR_A1[nSam]->Draw();
		canv_dR_A1[nSam]->SaveAs(Save_dir+Sample_type_mN1_10+Sample_name[nSam]+"_"+"dR_A1.png");
	}
}

