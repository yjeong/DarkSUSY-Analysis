double My_dPhi(double phi1, double phi2){
	double dPhi = phi1 - phi2;
	if(dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
	if(dPhi < -TMath::Pi()) dPhi += 2*TMath::Pi();
	return fabs(dPhi);
}

void set_canvas_style(TCanvas* c)
{
	c->SetFillColor(0);
	c->SetBorderMode(0);
	c->SetBorderSize(2);
	c->SetTickx(1);
	c->SetTicky(1);
	c->SetLeftMargin(0.15);
	c->SetRightMargin(0.18);
	c->SetTopMargin(0.07);
	c->SetBottomMargin(0.17);
	c->SetFrameFillStyle(0);
	c->SetFrameBorderMode(0);
	c->SetFrameFillStyle(0);
	c->SetFrameBorderMode(0);
}

void DarkSUSY_FiducialRegion(){
	gROOT->SetStyle("Plain");

	//gStyle->SetOptStat("mr");//To display the mean and RMS: SetOptStat("mr"), nemruoi, ;
	//gStyle->SetOptDate(0);//display date position

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.2);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.1);
	gStyle->SetPadBorderMode(0);

	int canvas_x = 600, canvas_y = 600;

	TString PATH_samples;
	PATH_samples = "/afs/cern.ch/work/y/yjeong/Run2_DarkSUSY_CentralMC/";
	TString Sample_type;
	Sample_type = "out_ana_";
	TString Save_dir;
	Save_dir = "/afs/cern.ch/work/y/yjeong/darkSUSY_script/test/";

	const int Sample_Num = 1;
	const int nVariable = 2;

	bool isDiMuonHLTFired;
	int event;
	float selMu0_px, selMu1_px, selMu2_px, selMu3_px;
	float selMu0_pz, selMu1_pz, selMu2_pz, selMu3_pz;
	float selMu0_pT, selMu1_pT, selMu2_pT, selMu3_pT;
	float selMu0_eta, selMu1_eta, selMu2_eta, selMu3_eta;
	float selMu0_phi, selMu1_phi, selMu2_phi, selMu3_phi;
	float genA0_px, genA0_py, genA0_pz, genA0_pT, genA0_eta, genA0_phi, genA0_Lx, genA0_Ly, genA0_Lz, genA0_Lxy, genA0_L;
	float genA1_px, genA1_py, genA1_pz, genA1_pT, genA1_eta, genA1_phi, genA1_Lx, genA1_Ly, genA1_Lz, genA1_Lxy, genA1_L;

	//TString Sample_name[Sample_Num] = {"mN1_10_mGammaD_5_cT_50","mGammaD_0p25_cT_0p1"};
	//TString Sample_name[Sample_Num] = {"Run2_mN1_10"};
	TString Sample_name[Sample_Num] = {"mN1_10_mGammaD_5_cT_50"};
	TString Variable[nVariable] = {"event","lumi"};

	TFile *tfile[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tfile[i] = new TFile(PATH_samples+Sample_type+Sample_name[i]+".root");
	}
	TTree *tree[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tree[i] = (TTree*)tfile[i]->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
		tree[i]->SetBranchAddress("event",&event);
		tree[i]->SetBranchAddress("isDiMuonHLTFired",&isDiMuonHLTFired);
		tree[i]->SetBranchAddress("selMu0_px",&selMu0_px);
		tree[i]->SetBranchAddress("selMu1_px",&selMu1_px);
		tree[i]->SetBranchAddress("selMu2_px",&selMu2_px);
		tree[i]->SetBranchAddress("selMu3_px",&selMu3_px);
		tree[i]->SetBranchAddress("selMu0_pz",&selMu0_pz);
		tree[i]->SetBranchAddress("selMu1_pz",&selMu1_pz);
		tree[i]->SetBranchAddress("selMu2_pz",&selMu2_pz);
		tree[i]->SetBranchAddress("selMu3_pz",&selMu3_pz);
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

	int nbin = 100;
	int xmin = -7;
	int xmax = 7;

	int eff_nbin_x = 100;
	int eff_nbin_y = 80;
	float eff_xmin_x = 0;
	float eff_xmax_x = 80;
	float eff_xmin_y = 0;
	float eff_xmax_y = 80;

	for(int nSam=0; nSam < Sample_Num; nSam++){
		for(int nVar=0; nVar < nVariable; nVar++){
			canv_[nVar][nSam] = new TCanvas(Form("Canv_%d_%d",nVar,nSam),Form(""),canvas_x,canvas_y);
			//histo_event[nVar][nSam] = new TH1F(Form("histo_event_%d_%d",nVar,nSam),Form(""),nbin[nVar][nSam],xmin[nVar][nSam],xmax[nVar][nSam]);
			histo_event[nVar][nSam] = new TH1F(Form("histo_event_%d_%d",nVar,nSam),Form(""),100,0,300000);
			tree[nSam]->Project(Form("histo_event_%d_%d",nVar,nSam),Variable[nVar]);

			histo_event[nVar][nSam]->Draw();
			//canv_[nVar][nSam]->SaveAs(Save_dir+Sample_type+Sample_name[nSam]+"_"+Variable[nVar]+".png");
		}
	}

	TH1F *histo_dR_A0[Sample_Num];
	TCanvas *canv_dR_A0[Sample_Num];

	TH1F *histo_dR_A1[Sample_Num];
	TCanvas *canv_dR_A1[Sample_Num];

	TH2F *eff_2D_num_A0[Sample_Num];
	TH2F *eff_2D_den_A0[Sample_Num];
	TH2F *eff_2D_A0[Sample_Num];
	TCanvas *canv_eff_2D_num_A0[Sample_Num];
	TCanvas *canv_eff_2D_den_A0[Sample_Num];
	TCanvas *canv_eff_2D_A0[Sample_Num];


	for(int nSam=0; nSam < Sample_Num; nSam++){
		canv_dR_A0[nSam] = new TCanvas(Form("canv_dR_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		histo_dR_A0[nSam] = new TH1F(Form("histo_dR_A0_%d",nSam),Form(""),200,0,1);

		canv_dR_A1[nSam] = new TCanvas(Form("canv_dR_A1_%d",nSam),Form(""),canvas_x,canvas_y);
		histo_dR_A1[nSam] = new TH1F(Form("histo_dR_A1_%d",nSam),Form(""),200,0,1);

		eff_2D_num_A0[nSam] = new TH2F(Form("eff_2D_num_A0_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x,eff_nbin_y,eff_xmin_y,eff_xmax_y);
		eff_2D_den_A0[nSam] = new TH2F(Form("eff_2D_den_A0_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x,eff_nbin_y,eff_xmin_y,eff_xmax_y);
		eff_2D_A0[nSam] = new TH2F(Form("eff_2D_A0_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x,eff_nbin_y,eff_xmin_y,eff_xmax_y);
		canv_eff_2D_num_A0[nSam] = new TCanvas(Form("canv_eff_2D_num_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		canv_eff_2D_den_A0[nSam] = new TCanvas(Form("canv_eff_2D_den_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		canv_eff_2D_A0[nSam] = new TCanvas(Form("canv_eff_2D_A0_%d",nSam),Form(""),canvas_x,canvas_y);

		unsigned int recMuA0 = 0;

		float RecMuPt = 0;
		float RecMuPz = 0;
		float RecMuEta = 0;
		float dEta_A0 = 0;
		float dPhi_A0 = 0;
		float dR_A0 = 0;
		float dEta_A1 = 0;
		float dPhi_A1 = 0;
		float dR_A1 = 0;

		float genA0_pT = 0;

		float effPt = 0;
		float effPz = 0;

		for(int nev=0; nev < tree[nSam]->GetEntries(); nev++){
			tree[nSam]->GetEntry(nev);

			if(!(isDiMuonHLTFired == true)) continue;
			if(!(genA0_Lz<=80 && genA0_Lxy<=80)) continue;
			genA0_pT = sqrt(pow(genA0_px,2)+pow(genA0_py,2));
			genA1_pT = sqrt(pow(genA1_px,2)+pow(genA1_py,2));
			if(fabs(selMu0_eta)!=100) recMuA0++;
			if(fabs(selMu1_eta)!=100) recMuA0++;
			if(fabs(selMu2_eta)!=100) recMuA0++;
			if(fabs(selMu3_eta)!=100) recMuA0++;

			for(int i = 0; i < recMuA0; i++){
				if(i==0){
					dEta_A0 = genA0_eta-selMu0_eta;
					dPhi_A0 = My_dPhi(selMu0_phi,genA0_phi);
					dEta_A1 = genA1_eta-selMu0_eta;
					dPhi_A1 = My_dPhi(selMu1_phi,genA0_phi);
					RecMuEta = selMu0_eta;
				}

				if(i==1){
					dEta_A0 = genA0_eta-selMu1_eta;
					dPhi_A0 = My_dPhi(selMu1_phi,genA0_phi);
					dEta_A1 = genA1_eta-selMu1_eta;
					dPhi_A1 = My_dPhi(selMu1_phi,genA0_phi);
					RecMuEta = selMu1_eta;
				}

				if(i==2){
					dEta_A0 = genA0_eta-selMu2_eta;
					dPhi_A0 = My_dPhi(selMu2_phi,genA0_phi);
					dEta_A1 = genA1_eta-selMu2_eta;
					dPhi_A1 = My_dPhi(selMu2_phi,genA0_phi);
					RecMuEta = selMu2_eta;
				}

				if(i==3){
					dEta_A0 = genA0_eta-selMu3_eta;
					dPhi_A0 = My_dPhi(selMu3_phi,genA0_phi);
					dEta_A1 = genA1_eta-selMu3_eta;
					dPhi_A1 = My_dPhi(selMu3_phi,genA0_phi);
					RecMuEta = selMu3_eta;
				}
			}

			//cout<<recMuA0<<endl;

			dR_A0 = sqrt(pow(dEta_A0,2)+pow(dPhi_A0,2));
			histo_dR_A0[nSam]->Fill(dR_A0);
			dR_A1 = sqrt(pow(dEta_A1,2)+pow(dPhi_A1,2));
			histo_dR_A1[nSam]->Fill(dR_A1);

			if(dR_A0<0.1){
				if(fabs(selMu0_pT)!=100) RecMuPt = selMu0_pT;
				if(fabs(selMu0_pz)!=100) RecMuPz = selMu0_pz;
			}

			//effPt = RecMuPt/genA0_pT;
			//effPz = genA0_pT/genA0_pz;
			effPt = selMu0_pT/genA0_pT;
			effPz = selMu0_pz/genA0_pz;

			eff_2D_num_A0[nSam]->Fill(selMu0_pT,selMu0_pz);
			eff_2D_den_A0[nSam]->Fill(genA0_pT,genA0_pz);
			eff_2D_A0[nSam]->Fill(effPt,effPz);

		}
		canv_dR_A0[nSam]->cd();
		set_canvas_style(canv_dR_A0[nSam]);
		canv_dR_A0[nSam]->SetLogy();
		histo_dR_A0[nSam]->Draw();
		canv_dR_A0[nSam]->SaveAs(Save_dir+Sample_type+Sample_name[nSam]+"_"+"dR_A0.png");

		canv_dR_A1[nSam]->cd();
		set_canvas_style(canv_dR_A1[nSam]);
		canv_dR_A1[nSam]->SetLogy();
		histo_dR_A1[nSam]->Draw();
		canv_dR_A1[nSam]->SaveAs(Save_dir+Sample_type+Sample_name[nSam]+"_"+"dR_A1.png");

		canv_eff_2D_num_A0[nSam]->cd();
		eff_2D_num_A0[nSam]->Draw("colz");
		canv_eff_2D_num_A0[nSam]->SaveAs(Save_dir+Sample_type+Sample_name[nSam]+"_"+"eff_2D_num_A0.png");

		canv_eff_2D_den_A0[nSam]->cd();
		eff_2D_den_A0[nSam]->Draw("colz");
		canv_eff_2D_den_A0[nSam]->SaveAs(Save_dir+Sample_type+Sample_name[nSam]+"_"+"eff_2D_den_A0.png");

		canv_eff_2D_A0[nSam]->cd();
		eff_2D_A0[nSam]->Draw("colz");
		canv_eff_2D_A0[nSam]->SaveAs(Save_dir+Sample_type+Sample_name[nSam]+"_"+"eff_2D_A0.png");
	}
}
