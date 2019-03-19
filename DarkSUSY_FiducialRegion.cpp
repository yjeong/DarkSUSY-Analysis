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
	PATH_samples = "/afs/cern.ch/work/y/yjeong/Run2_DarkSUSY_CentralMC/out_ana_";
	TString Save_dir;
	Save_dir = "/afs/cern.ch/work/y/yjeong/darkSUSY_script/test/";

	const int Sample_Num = 2;
	const int nVariable = 2;

	bool isDiMuonHLTFired, is4GenMu8, is2SelMu8;
	int event;
	float selMu0_px, selMu1_px, selMu2_px, selMu3_px;
	float selMu0_pz, selMu1_pz, selMu2_pz, selMu3_pz;
	float selMu0_pT, selMu1_pT, selMu2_pT, selMu3_pT;
	float selMu0_eta, selMu1_eta, selMu2_eta, selMu3_eta;
	float selMu0_phi, selMu1_phi, selMu2_phi, selMu3_phi;
	float genA0_px, genA0_py, genA0_pz, genA0_pT, genA0_eta, genA0_phi, genA0_Lx, genA0_Ly, genA0_Lz, genA0_Lxy, genA0_L;
	float genA1_px, genA1_py, genA1_pz, genA1_pT, genA1_eta, genA1_phi, genA1_Lx, genA1_Ly, genA1_Lz, genA1_Lxy, genA1_L;

	TString Sample_name[Sample_Num] = {"mN1_10_mGammaD_5_cT_50","mN1_10_mGammaD_0p25_cT_0p1"};
	//TString Sample_name[Sample_Num] = {"Run2_mN1_10"};
	//TString Sample_name[Sample_Num] = {"Run2_mN1_10","mN1_10_mGammaD_5_cT_50"};
	TString Variable[nVariable] = {"event","lumi"};

	/*int mkdir (const char *dirname);
	  char strFolderPath[] = {"/afs/cern.ch/work/y/yjeong/darkSUSY_script/abs"};
	  int nResult = mkdir(strFolderPath);*/

	TFile *tfile[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tfile[i] = new TFile(PATH_samples+Sample_name[i]+".root");
	}
	TTree *tree[Sample_Num];
	for(int i = 0; i < Sample_Num; i++){
		tree[i] = (TTree*)tfile[i]->Get("cutFlowAnalyzerPXBL3PXFL2/Events");
		tree[i]->SetBranchAddress("event",&event);
		tree[i]->SetBranchAddress("isDiMuonHLTFired",&isDiMuonHLTFired);
		tree[i]->SetBranchAddress("is4GenMu8",&is4GenMu8);
		tree[i]->SetBranchAddress("is2SelMu8",&is2SelMu8);
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

	int nbin[nVariable][Sample_Num] = {{1000,2000},{100,150}};//===[2][4] = {{1,2,3,4},{1,2,3,4}};//---
	float xmin[nVariable][Sample_Num] = {{0,0},{0,0}};
	float xmax[nVariable][Sample_Num] = {{100000,300000},{100,150}};

	/*int nbin = 100;
	  int xmin = -7;
	  int xmax = 7;*/

	float bin_edges[81] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};
	//float bin_edges_Lz[81] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};

	float bin_edges_Lz[41] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};

	float count_gam_A0[41][81];
	float count_rec_A0[41][81];
	float eff_A0[41][81];

	float count_gam_A1[41][81];
	float count_rec_A1[41][81];
	float eff_A1[41][81];

	for(int k=0;k<40;k++){
		for(int j=0;j<80;j++){
			count_gam_A0[k][j]=0.0;
			count_rec_A0[k][j]=0.0;
			eff_A0[k][j]=0.0;

			count_gam_A1[k][j]=0.0;
			count_rec_A1[k][j]=0.0;
			eff_A1[k][j]=0.0;
		}
	}

	int eff_nbin_x = 40;
	int eff_nbin_y = 80;
	float eff_xmin_x = 0;
	float eff_xmax_x = 80;
	float eff_xmin_y = 0.0;
	float eff_xmax_y = 80.0;

	for(int nSam=0; nSam < Sample_Num; nSam++){
		for(int nVar=0; nVar < nVariable; nVar++){
			canv_[nVar][nSam] = new TCanvas(Form("Canv_%d_%d",nVar,nSam),Form(""),canvas_x,canvas_y);
			histo_event[nVar][nSam] = new TH1F(Form("histo_event_%d_%d",nVar,nSam),Form(""),nbin[nVar][nSam],xmin[nVar][nSam],xmax[nVar][nSam]);
			//histo_event[nVar][nSam] = new TH1F(Form("histo_event_%d_%d",nVar,nSam),Form(""),100,0,300000);
			tree[nSam]->Project(Form("histo_event_%d_%d",nVar,nSam),Variable[nVar]);

			histo_event[nVar][nSam]->Draw();
			//canv_[nVar][nSam]->SaveAs(Save_dir+Sample_name[nSam]+"_"+Variable[nVar]+".png");
		}
	}

	TH1F *histo_dR_A0[Sample_Num];
	TCanvas *canv_dR_A0[Sample_Num];

	TH1F *histo_dR_A1[Sample_Num];
	TCanvas *canv_dR_A1[Sample_Num];

	TH2F *eff_2D_A0[Sample_Num];
	TH2F *eff_2D_A1[Sample_Num];
	TCanvas *canv_2D_A0[Sample_Num];
	TCanvas *canv_2D_A1[Sample_Num];

	for(int nSam=0; nSam < Sample_Num; nSam++){
		canv_dR_A0[nSam] = new TCanvas(Form("canv_dR_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		histo_dR_A0[nSam] = new TH1F(Form("histo_dR_A0_%d",nSam),Form(""),200,0,1);

		canv_dR_A1[nSam] = new TCanvas(Form("canv_dR_A1_%d",nSam),Form(""),canvas_x,canvas_y);
		histo_dR_A1[nSam] = new TH1F(Form("histo_dR_A1_%d",nSam),Form(""),200,0,1);

		eff_2D_A0[nSam] = new TH2F(Form("eff_2D_A0_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x,eff_nbin_y,eff_xmin_y,eff_xmax_y);
		eff_2D_A1[nSam] = new TH2F(Form("eff_2D_A1_%d",nSam),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x,eff_nbin_y,eff_xmin_y,eff_xmax_y);
		canv_2D_A0[nSam] = new TCanvas(Form("canv_2D_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		canv_2D_A1[nSam] = new TCanvas(Form("canv_2D_A1_%d",nSam),Form(""),canvas_x,canvas_y);

		float dEta_A0 = 0;
		float dPhi_A0 = 0;
		float dR_A0 = 0;
		float dEta_A1 = 0;
		float dPhi_A1 = 0;
		float dR_A1 = 0;

		float dR_cut = 0.2;

		for(int nev=0; nev < tree[nSam]->GetEntries(); nev++){
			tree[nSam]->GetEntry(nev);

			if(!(isDiMuonHLTFired == true)) continue;
			if(!(is4GenMu8 == true)) continue;
			if(!(fabs(genA0_Lz)<=80 && genA0_Lxy<=80)) continue;
			if(!(fabs(genA1_Lz)<=80 && genA1_Lxy<=80)) continue;

			for(int k = 0; k < 40; k++){
				if(!(fabs(genA0_Lz)>bin_edges_Lz[k] && fabs(genA0_Lz)<bin_edges_Lz[k+1])) continue;
				for(int j = 0; j < 80; j++){
					if(!(genA0_Lxy>bin_edges[j] && genA0_Lxy<bin_edges[j+1])) continue;
					count_gam_A0[k][j]++;
					unsigned int recMu = 0;
					if(fabs(selMu0_eta)!=100) recMu++;
					if(fabs(selMu1_eta)!=100) recMu++;
					if(fabs(selMu2_eta)!=100) recMu++;
					if(fabs(selMu3_eta)!=100) recMu++;
					if(!(recMu>0 && is2SelMu8==true)) continue;
					unsigned int match_mu = 0;
					for(int i = 0; i < recMu; i++){
						if(i==0){
							dEta_A0 = genA0_eta-selMu0_eta;
							dPhi_A0 = My_dPhi(selMu0_phi,genA0_phi);
						}

						if(i==1){
							dEta_A0 = genA0_eta-selMu1_eta;
							dPhi_A0 = My_dPhi(selMu1_phi,genA0_phi);
						}

						if(i==2){
							dEta_A0 = genA0_eta-selMu2_eta;
							dPhi_A0 = My_dPhi(selMu2_phi,genA0_phi);
						}

						if(i==3){
							dEta_A0 = genA0_eta-selMu3_eta;
							dPhi_A0 = My_dPhi(selMu3_phi,genA0_phi);
						}
						dR_A0 = sqrt(pow(dEta_A0,2)+pow(dPhi_A0,2));
						histo_dR_A0[nSam]->Fill(dR_A0);
						if(dR_A0<dR_cut) match_mu++;
					}
					if(match_mu>1){
						count_rec_A0[k][j]++;
					}
				}
			}

			for(int k = 0; k < 40; k++){
				if(!(fabs(genA1_Lz)>bin_edges_Lz[k] && fabs(genA1_Lz)<bin_edges_Lz[k+1])) continue;
				for(int j = 0; j < 80; j++){
					if(!(genA1_Lxy>bin_edges[j] && genA1_Lxy<bin_edges[j+1])) continue;
					count_gam_A1[k][j]++;
					unsigned int recMu = 0;
					if(fabs(selMu0_eta)!=-100) recMu++;
					if(fabs(selMu1_eta)!=-100) recMu++;
					if(fabs(selMu2_eta)!=-100) recMu++;
					if(fabs(selMu3_eta)!=-100) recMu++;
					if(!(recMu>0 && is2SelMu8==true)) continue;
					unsigned int match_mu=0;
					for(int j = 0; j < recMu; j++){
						if(j==0){
							dEta_A1 = genA1_eta-selMu0_eta;
							dPhi_A1 = My_dPhi(selMu0_phi,genA1_phi);
						}
						if(j==1){
							dEta_A1 = genA1_eta-selMu1_eta;
							dPhi_A1 = My_dPhi(selMu1_phi,genA1_phi);
						}
						if(j==2){
							dEta_A1 = genA1_eta-selMu2_eta;
							dPhi_A1 = My_dPhi(selMu2_phi,genA1_phi);
						}
						if(j==3){
							dEta_A1 = genA1_eta-selMu3_eta;
							dPhi_A1 = My_dPhi(selMu3_phi,genA1_phi);
						}
						dR_A1 = sqrt(pow(dEta_A1,2)+pow(dPhi_A1,2));
						histo_dR_A1[nSam]->Fill(dR_A1);
						if(dR_A1<dR_cut) match_mu++;
					}
					if(match_mu>1){
						count_rec_A1[k][j]++;
					}
				}	
			}
		}

		for(int k = 0; k < 40; k++){
			for(int j = 0; j < 80; j++){
				if(count_gam_A0[k][j]!=0) eff_A0[k][j] = count_rec_A0[k][j]/count_gam_A0[k][j];
				if(count_rec_A0[k][j]==0 && count_gam_A0[k][j]!=0) eff_A0[k][j] = 0.0001;
				eff_2D_A0[nSam]->SetBinContent(k+1,j+1,eff_A0[k][j]);

				if(count_gam_A1[k][j]!=0) eff_A1[k][j] = count_rec_A1[k][j]/count_gam_A1[k][j];
				if(count_rec_A1[k][j]==0 && count_gam_A1[k][j]!=0) eff_A1[k][j] = 0.0001;
				eff_2D_A1[nSam]->SetBinContent(k+1,j+1,eff_A1[k][j]);
			}
		}

		eff_2D_A0[nSam]->GetZaxis()->SetRangeUser(0,1);
		eff_2D_A1[nSam]->GetZaxis()->SetRangeUser(0,1);

		canv_dR_A0[nSam]->cd();
		set_canvas_style(canv_dR_A0[nSam]);
		canv_dR_A0[nSam]->SetLogy();
		histo_dR_A0[nSam]->Draw();
		canv_dR_A0[nSam]->SaveAs(Save_dir+Sample_name[nSam]+"_"+"dR_A0.png");

		canv_dR_A1[nSam]->cd();
		set_canvas_style(canv_dR_A1[nSam]);
		canv_dR_A1[nSam]->SetLogy();
		histo_dR_A1[nSam]->Draw();
		canv_dR_A1[nSam]->SaveAs(Save_dir+Sample_name[nSam]+"_"+"dR_A1.png");

		canv_2D_A0[nSam]->cd();
		set_canvas_style(canv_2D_A0[nSam]);
		gStyle->SetOptStat(0);
		eff_2D_A0[nSam]->Draw("colz");
		canv_2D_A0[nSam]->SaveAs(Save_dir+Sample_name[nSam]+"_"+"eff_2D_A0.png");

		canv_2D_A1[nSam]->cd();
		set_canvas_style(canv_2D_A1[nSam]);
		gStyle->SetOptStat(0);
		eff_2D_A1[nSam]->Draw("colz");
		canv_2D_A1[nSam]->SaveAs(Save_dir+Sample_name[nSam]+"_"+"eff_2D_A1.png");
	}
}
