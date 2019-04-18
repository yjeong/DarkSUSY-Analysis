double My_dPhi(double phi1, double phi2){
	double dPhi = phi1 - phi2;
	if(dPhi > TMath::Pi()) dPhi -= 2*TMath::Pi();
	if(dPhi < -TMath::Pi()) dPhi += 2*TMath::Pi();
	return fabs(dPhi);
}

void set_canvas_style(TCanvas* c){
	c->SetFillColor(0);
	c->SetBorderMode(0);
	c->SetBorderSize(2);
	c->SetTickx(1);
	c->SetTicky(1);
	c->SetLeftMargin(0.12);
	c->SetRightMargin(0.15);
	c->SetTopMargin(0.12);
	c->SetBottomMargin(0.12);
	c->SetFrameFillStyle(0);
	c->SetFrameBorderMode(0);
	c->SetFrameFillStyle(0);
	c->SetFrameBorderMode(0);
	c->RedrawAxis();
}

void set_legend_style(TLegend *l){
	l->SetFillColor(0);
	l->SetLineColor(0);
	l->SetLineStyle(kSolid);
	l->SetLineWidth(1);
	l->SetFillStyle(1001);
	l->SetTextFont(42);
	l->SetTextSize(0.025);
}

void set_histo_frame_1D(TH1F *h){
	h->GetXaxis()->SetLabelSize(0.025);
	h->GetXaxis()->SetTitleSize(0.04);
	h->GetYaxis()->SetTitleOffset(1.2);
	h->GetYaxis()->SetTitle("Number of events");
	h->GetYaxis()->SetTitleSize(0.04);
	h->GetYaxis()->SetLabelSize(0.03);
}

void set_histo_frame_2D(TH2F *h){
	h->GetXaxis()->SetTitleSize(0.04);
	h->GetXaxis()->SetTitleOffset(1.2);
}

void DarkSUSY_FiducialRegion(){
	gROOT->SetStyle("Plain");

	//gStyle->SetOptStat(0);//To display the mean and RMS: SetOptStat("mr"), nemruoi, ;
	//gStyle->SetOptDate(0);//display date position

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.1);
	gStyle->SetPadBorderMode(0);

	int canvas_x = 600, canvas_y = 600;

	TString PATH_samples;
	PATH_samples = "/afs/cern.ch/work/y/yjeong/Run2_DarkSUSY_CentralMC/out_ana_";
	TString Save_dir;
	Save_dir = "/afs/cern.ch/work/y/yjeong/darkSUSY_script/plots/";

	const int Sample_Num = 8;
	const int nVariable = 15;

	bool isDiMuonHLTFired, is4GenMu8, is1SelMu17 , is2SelMu8;
	int event;
	float selMu0_px, selMu1_px, selMu2_px, selMu3_px;
	float selMu0_pz, selMu1_pz, selMu2_pz, selMu3_pz;
	float selMu0_pT, selMu1_pT, selMu2_pT, selMu3_pT;
	float selMu0_eta, selMu1_eta, selMu2_eta, selMu3_eta;
	float selMu0_phi, selMu1_phi, selMu2_phi, selMu3_phi;
	float genA0_px, genA0_py, genA0_pz, genA0_pT, genA0_eta, genA0_phi, genA0_Lx, genA0_Ly, genA0_Lz, genA0_Lxy, genA0_L;
	float genA1_px, genA1_py, genA1_pz, genA1_pT, genA1_eta, genA1_phi, genA1_Lx, genA1_Ly, genA1_Lz, genA1_Lxy, genA1_L;

	//TString Sample_name[Sample_Num] = {"mN1_10_mGammaD_5_cT_50","mN1_10_mGammaD_0p25_cT_0p1"};
	TString Sample_name[Sample_Num] = {
		"mN1_10_mGammaD_5_cT_10",
		"mN1_10_mGammaD_5_cT_50",
		"mN1_60_mGammaD_58_cT_50",
		"mN1_60_mGammaD_58_cT_2",
		"mN1_10_mGammaD_0p7_cT_100",
		"mN1_10_mGammaD_0p7_cT_0p05",
		"mN1_10_mGammaD_8p5_cT_100",
		"mN1_10_mGammaD_8p5_cT_0p05"
	};

	//TString Sample_name[Sample_Num] = {"Run2_mN1_10"};
	//TString Sample_name[Sample_Num] = {"Run2_mN1_10","mN1_10_mGammaD_5_cT_50"};

	TString Variable[nVariable] = {
		"genA0_Lxy",
		"genA1_Lxy",
		"genA0_Lz",
		"genA1_Lz",
		"sqrt(pow(genA0_px,2)+pow(genA0_py,2))",
		"sqrt(pow(genA1_px,2)+pow(genA1_py,2))",
		"genA0_m",
		"genA1_m",
		"genA0_L",
		"genA1_L",
		"genH_m",
		"diMuonC_FittedVtx_m",
		"diMuonF_FittedVtx_m",
		"diMuonC_FittedVtx_Lxy",
		"diMuonF_FittedVtx_Lxy"
	};

	TString Legend_name[Sample_Num] = {
		"mN1=10 GeV, #gamma_{D}=5 GeV, c#tau=10 mm",
		"mN1=10 GeV, #gamma_{D}=5 GeV, c#tau=50 mm",
		"mN1=60 GeV, #gamma_{D}=58 GeV, c#tau=50 mm",
		"mN1=60 GeV, #gamma_{D}=58 GeV, c#tau=2 mm",
		"mN1=10 GeV, #gamma_{D}=0.7 GeV, c#tau=100 mm",
		"mN1=10 GeV, #gamma_{D}=0.7 GeV, c#tau=0.05 mm",
		"mN1=10 GeV, #gamma_{D}=8.5 GeV, c#tau=100 mm",
		"mN1=10 GeV, #gamma_{D}=8.5 GeV, c#tau=0.05 mm"
	};

	TString xTitle[nVariable] = {
		"genA0_Lxy [cm]",
		"genA1_Lxy [cm]",
		"genA0_Lz [cm]",
		"genA1_Lz [cm]",
		"genA0_P_{t} [GeV]",
		"genA1_P_{t} [GeV]",
		"genA0_m [GeV]",
		"genA1_m [GeV]",
		"genA0_L [cm]",
		"genA1_L [cm]",
		"genH_m [GeV]",
		"diMuonC_FittedVtx_m [GeV]",
		"diMuonF_FittedVtx_m [GeV]",
		"diMuonC_FittedVtx_Lxy [cm]",
		"diMuonF_FittedVtx_Lxy [cm]"
	};

	TString Cut_base;
	Cut_base = "diMuonF_FittedVtx_Lxy != 1000 && diMuonF_FittedVtx_m != 1000 && diMuonC_FittedVtx_Lxy != 1000 && diMuonC_FittedVtx_m != 1000";

	int nbin[nVariable][Sample_Num] = {
		{100,100,100,100,100,100,100,100},//genA0_Lxy
		{40,40,40,40,40,40,40,40},//genA1_Lxy
		{100,100,100,100,100,100,100,100},//genA0_Lz
		{50,50,50,50,50,50,50,50},//genA1_Lz
		{50,50,50,50,50,50,50,50},//sqrt(pow(genA0_px,2)+pow(genA0_py,2))
		{50,50,50,50,50,50,50,50},//sqrt(pow(genA1_px,2)+pow(genA1_py,2))
		{50,50,50,50,50,50,50,50},//genA0_m
		{50,50,50,50,50,50,50,50},//genA1_m
		{50,50,50,50,50,50,50,50},//genA0_L
		{50,50,50,50,50,50,50,50},//genA1_L
		{50,50,50,50,50,50,50,50},//genH_m
		{50,50,50,50,50,50,50,50},//diMuonC_FittedVtx_m
		{50,50,50,50,50,50,50,50},//diMuonF_FittedVtx_m
		{50,50,50,50,50,50,50,50},//diMuonC_FittedVtx_Lxy
		{50,50,50,50,50,50,50,50}//diMuonF_FittedVtx_Lxy
	};//===[2][4] = {{1,2,3,4},{1,2,3,4}};//---

	float xmin[nVariable][Sample_Num] = {
		{0,0,0,0,0,0,0,0},//genA0_Lxy
		{0,0,0,0,0,0,0,0},//genA1_Lxy
		{-10000,-10000,-1000,-1000,-40000,-40000,-2000,-2000},//genA0_Lz
		{-10000,-10000,-100,-100,-10000,-10000,-1500,-1500},//genA1_Lz
		{0,0,0,0,0,0,0,0},//sqrt(pow(genA0_px,2)+pow(genA0_py,2))
		{0,0,0,0,0,0,0,0},//sqrt(pow(genA1_px,2)+pow(genA1_py,2))
		{4,4,59.5,59.5,0.69,0.69,8.49,8.49},//genA0_m
		{4,4,59.5,59.5,0.69,0.69,8.49,8.49},//genA1_m
		{0,0,0,0,0,0,0,0},//genA0_L
		{0,0,0,0,0,0,0,0},//genA1_L
		{124,124,124,124,124,124,124,124},//genH_m
		{4.9985,4.9985,-100,-100,-15,-15,-20,-20},//diMuonC_FittedVtx_m
		{4.9985,4.9985,-100,-100,-10,-10,-20,-20},//diMuonF_FittedVtx_m
		{-40,-40,-40,-40,-10,-10,-40,-40},//diMuonC_FittedVtx_Lxy
		{-40,-40,-40,-40,-10,-10,-40,-40}//diMuonF_FittedVtx_Lxy
	};

	float xmax[nVariable][Sample_Num] = {
		{2000,2000,300,300,6000,6000,600,600},//genA0_Lxy
		{1000,1000,150,150,2500,2500,300,300},//genA1_Lxy
		{10000,10000,1000,1000,40000,40000,2000,2000},//genA0_Lz
		{10000,10000,100,100,10000,10000,1500,1500},//genA1_Lz
		{1000,1000,1000,1000,1000,1000,1000},//sqrt(pow(genA0_px,2)+pow(genA0_py,2))
		{400,400,600,600,1000,1000,1000},//sqrt(pow(genA1_px,2)+pow(genA1_py,2))
		{6,6,58.5,58.5,0.71,0.71,8.51,8.51},//genA0_m
		{6,6,58.5,58.5,0.71,0.71,8.51,8.51},//genA1_m
		{12000,12000,1200,1200,25000,25000,2000,2000},//genA0_L
		{9000,9000,1000,1000,10000,10000,2000,2000},//genA1_L
		{126,126,126,126,126,126,126,126},//genH_m
		{5.0015,5.0015,100,100,15,15,20,20},//diMuonC_FittedVtx_m
		{5.0015,5.0015,100,100,10,10,20,20},//diMuonF_FittedVtx_m
		{40,40,40,40,10,10,40,40},//diMuonC_FittedVtx_Lxy
		{40,40,40,40,10,10,40,40}//diMuonF_FittedVtx_Lxy
	};

	/*int mkdir (const char *dirname);
	  char strFolderPath[] = {"/afs/cern.ch/work/y/yjeong/darkSUSY_script/abs"};
	  int nResult = mkdir(strFolderPath);*/


	const int Number = 5;
	double Red[Number] = {0.00, 0.09, 0.18, 0.09, 0.00};
	double Green[Number] = {0.01, 0.02, 0.39, 0.68, 0.97};
	double Blue[Number] = {0.17, 0.39, 0.62, 0.79, 0.97};
	double Length[Number] = {0.00, 0.34, 0.61, 0.84, 1.00};

	const int nb = 50;
	TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
	int colors[] = {0,1,2,3,4,5,6};
	gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)), colors);

	double levels[8] = {-10,0.0,0.2,0.4,0.6,0.8,1.0, 3.4e38};

	const int NRGBs = 5;
	const int NCont = 104;

	double stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
	double red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	double green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	double blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

	gStyle->SetNumberContours(NCont);

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
		tree[i]->SetBranchAddress("is1SelMu17",&is2SelMu8);
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

	/*int nbin = 100;
	  int xmin = -7;
	  int xmax = 7;*/

	float bin_edges[81] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};

	float bin_edges_Lz[41] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
	//float bin_edges_Lz[81] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};

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
	//------histo setting------
	int eff_nbin_x = 40;
	int eff_nbin_y = 80;
	float eff_xmin_x = 0;
	float eff_xmax_x = 80;
	float eff_xmin_y = 0;
	float eff_xmax_y = 80;

	//------legend setting-----
	float lx1 = 0.55;
	float ly1 = 0.64;
	float lx2 = 0.70;
	float ly2 = 0.74;

	TH1F *histo[Sample_Num][nVariable];
	TCanvas *canv_[nVariable];
	TLegend *l_1[nVariable];
	TLegend *l_2[nVariable];
	TLegend *l_3[nVariable];
	TLegend *l_4[nVariable];

	for(int nVar=0; nVar < nVariable; nVar++){
		canv_[nVar] = new TCanvas(Form("canv_%d",nVar),Form(""),canvas_x,canvas_y);
		l_1[nVar] = new TLegend(lx1,ly1,lx2,ly2);
		set_legend_style(l_1[nVar]);
		l_2[nVar] = new TLegend(lx1,ly1,lx2,ly2);
		set_legend_style(l_2[nVar]);
		l_3[nVar] = new TLegend(lx1,ly1,lx2,ly2);
		set_legend_style(l_3[nVar]);
		l_4[nVar] = new TLegend(lx1,ly1,lx2,ly2);
		set_legend_style(l_4[nVar]);

		for(int nSam=0; nSam < Sample_Num; nSam++){
			histo[nVar][nSam] = new TH1F(Form("histo_%d_%d",nVar,nSam),Form(""),nbin[nVar][nSam],xmin[nVar][nSam],xmax[nVar][nSam]);
			tree[nSam]->Project(Form("histo_%d_%d",nVar,nSam),Variable[nVar],Cut_base);
			if(nSam==0 || nSam==2 || nSam==4 || nSam==6)histo[nVar][nSam]->SetLineColor(kRed);
			if(nSam==1 || nSam==3 || nSam==5 || nSam==7)histo[nVar][nSam]->SetLineColor(kBlue);

			if(nSam==0){//mN1_10_mGammaD_5_cT_10
				l_1[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->GetXaxis()->SetTitle(xTitle[nVar]);
				set_histo_frame_1D(histo[nVar][nSam]);
				histo[nVar][nSam]->Draw();
			}
			if(nSam==1){//mN1_10_mGammaD_5_cT_50
				l_1[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->Draw("same");
				l_1[nVar]->Draw();
				canv_[nVar]->SaveAs(Save_dir+"_"+Sample_name[nSam]+"_"+Variable[nVar]+".png");
			}
			if(nSam==2){//mN1_10_mGammaD_58_cT_50
				l_2[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->GetXaxis()->SetTitle(xTitle[nVar]);
				set_histo_frame_1D(histo[nVar][nSam]);
				histo[nVar][nSam]->Draw();
			}
			if(nSam==3){//mN1_10_mGammaD_58_cT_2
				l_2[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->Draw("same");
				l_2[nVar]->Draw();
				canv_[nVar]->SaveAs(Save_dir+"_"+Sample_name[nSam]+"_"+Variable[nVar]+".png");
			}
			if(nSam==4){//mN1_10_mGammaD_0p7_cT_100
				l_3[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->GetXaxis()->SetTitle(xTitle[nVar]);
				set_histo_frame_1D(histo[nVar][nSam]);
				histo[nVar][nSam]->Draw();
			}
			if(nSam==5){//mN1_10_mGammaD_0p7_cT_0p05
				l_3[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->Draw("same");
				l_3[nVar]->Draw();
				canv_[nVar]->SaveAs(Save_dir+"_"+Sample_name[nSam]+"_"+Variable[nVar]+".png");
			}
			if(nSam==6){//mN1_10_mGammaD_8p5_cT_100
				l_4[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->GetXaxis()->SetTitle(xTitle[nVar]);
				set_histo_frame_1D(histo[nVar][nSam]);
				histo[nVar][nSam]->Draw();
			}
			if(nSam==7){//mN1_10_mGammaD_8p5_cT_0p05
				l_4[nVar]->AddEntry(histo[nVar][nSam],Legend_name[nSam],"l");
				histo[nVar][nSam]->Draw("same");
				l_4[nVar]->Draw();
				canv_[nVar]->SaveAs(Save_dir+"_"+Sample_name[nSam]+"_"+Variable[nVar]+".png");
			}
		}
	}

	TH1F *histo_dR_A0[Sample_Num];
	TCanvas *canv_dR_A0[Sample_Num];

	TH1F *histo_dR_A1[Sample_Num];
	TCanvas *canv_dR_A1[Sample_Num];


	/*const int ndeltaR = 5;
	  float dR_cut[ndeltaR] = {0.1,0.2,0.3,0.4,0.5};
	  TString dR_txt[ndeltaR] = {"dR<0.1","dR<0.2","dR<0.3","dR<0.4","dR<0.5"};//-*/
	const int ndeltaR = 1;
	float dR_cut[ndeltaR] = {0.2};
	TString dR_txt[ndeltaR] = {"dR<0.2"};//-*/

	TH2F *eff_2D_A0[Sample_Num][ndeltaR];
	TH2F *eff_2D_A1[Sample_Num][ndeltaR];
	TCanvas *canv_2D_A0[Sample_Num][ndeltaR];
	TCanvas *canv_2D_A1[Sample_Num][ndeltaR];

	for(int nSam=0; nSam < Sample_Num; nSam++){
		canv_dR_A0[nSam] = new TCanvas(Form("canv_dR_A0_%d",nSam),Form(""),canvas_x,canvas_y);
		histo_dR_A0[nSam] = new TH1F(Form("histo_dR_A0_%d",nSam),Form(""),200,0,1);

		canv_dR_A1[nSam] = new TCanvas(Form("canv_dR_A1_%d",nSam),Form(""),canvas_x,canvas_y);
		histo_dR_A1[nSam] = new TH1F(Form("histo_dR_A1_%d",nSam),Form(""),200,0,1);

		for(int ndR = 0; ndR < ndeltaR; ndR++){
			eff_2D_A0[nSam][ndR] = new TH2F(Form("eff_2D_A0_%d_%d",nSam,ndR),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x,eff_nbin_y,eff_xmin_y,eff_xmax_y);
			eff_2D_A1[nSam][ndR] = new TH2F(Form("eff_2D_A1_%d_%d",nSam,ndR),Form(""),eff_nbin_x,eff_xmin_x,eff_xmax_x,eff_nbin_y,eff_xmin_y,eff_xmax_y);
			canv_2D_A0[nSam][ndR] = new TCanvas(Form("canv_2D_A0_%d_%d",nSam,ndR),Form(""),canvas_x,canvas_y);
			canv_2D_A1[nSam][ndR] = new TCanvas(Form("canv_2D_A1_%d_%d",nSam,ndR),Form(""),canvas_x,canvas_y);

			float dEta_A0 = 0;
			float dPhi_A0 = 0;
			float dR_A0 = 0;
			float dEta_A1 = 0;
			float dPhi_A1 = 0;
			float dR_A1 = 0;

			for(int nev=0; nev < tree[nSam]->GetEntries(); nev++){
				tree[nSam]->GetEntry(nev);

				if(!(isDiMuonHLTFired == true)) continue;
				if(!(is4GenMu8 == true)) continue;
				if(!(is2SelMu8 == true)) continue;
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
						if(!(recMu>1)) continue;
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
							if(dR_A0<dR_cut[ndR]) match_mu++;
						}
						if(match_mu==2){
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
						if(!(recMu>1)) continue;
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
							if(dR_A1<dR_cut[ndR]) match_mu++;
						}
						if(match_mu==2){
							count_rec_A1[k][j]++;
						}
					}	
				}
			}

			for(int k = 0; k < 40; k++){
				for(int j = 0; j < 80; j++){
					if(count_gam_A0[k][j]!=0) eff_A0[k][j] = count_rec_A0[k][j]/count_gam_A0[k][j];
					if(count_rec_A0[k][j]==0 && count_gam_A0[k][j]!=0) eff_A0[k][j] = 0.0001;
					eff_2D_A0[nSam][ndR]->SetBinContent(k+1,j+1,eff_A0[k][j]);

					if(count_gam_A1[k][j]!=0) eff_A1[k][j] = count_rec_A1[k][j]/count_gam_A1[k][j];
					if(count_rec_A1[k][j]==0 && count_gam_A1[k][j]!=0) eff_A1[k][j] = 0.0001;
					eff_2D_A1[nSam][ndR]->SetBinContent(k+1,j+1,eff_A1[k][j]);
				}
			}

			eff_2D_A0[nSam][ndR]->GetZaxis()->SetRangeUser(0,1);
			eff_2D_A1[nSam][ndR]->GetZaxis()->SetRangeUser(0,1);

			canv_2D_A0[nSam][ndR]->cd();
			set_canvas_style(canv_2D_A0[nSam][ndR]);
			gStyle->SetOptStat(0);
			eff_2D_A0[nSam][ndR]->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
			eff_2D_A0[nSam][ndR]->SetContour(NCont);
			set_histo_frame_2D(eff_2D_A0[nSam][ndR]);
			eff_2D_A0[nSam][ndR]->GetXaxis()->SetTitle(Legend_name[nSam]+", "+dR_txt[ndR]);
			eff_2D_A0[nSam][ndR]->Draw("colz");
			canv_2D_A0[nSam][ndR]->SaveAs(Save_dir+Sample_name[nSam]+"_"+dR_txt[ndR]+"_"+"eff_2D_A0.png");

			canv_2D_A1[nSam][ndR]->cd();
			set_canvas_style(canv_2D_A1[nSam][ndR]);
			eff_2D_A1[nSam][ndR]->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
			eff_2D_A1[nSam][ndR]->SetContour(NCont);
			gStyle->SetOptStat(0);
			set_histo_frame_2D(eff_2D_A1[nSam][ndR]);
			eff_2D_A1[nSam][ndR]->GetXaxis()->SetTitle(Legend_name[nSam]+", "+dR_txt[ndR]);
			eff_2D_A1[nSam][ndR]->Draw("colz");
			canv_2D_A1[nSam][ndR]->SaveAs(Save_dir+Sample_name[nSam]+"_"+dR_txt[ndR]+"_"+"eff_2D_A1.png");
		}
		canv_dR_A0[nSam]->cd();
		canv_dR_A0[nSam]->SetLogy();
		set_histo_frame_1D(histo_dR_A0[nSam]);
		histo_dR_A0[nSam]->GetXaxis()->SetTitle(Legend_name[nSam]+"  "+"dR_A0");
		histo_dR_A0[nSam]->Draw();
		canv_dR_A0[nSam]->SaveAs(Save_dir+Sample_name[nSam]+"_"+"dR_A0.png");

		canv_dR_A1[nSam]->cd();
		canv_dR_A1[nSam]->SetLogy();
		set_histo_frame_1D(histo_dR_A1[nSam]);
		histo_dR_A1[nSam]->GetXaxis()->SetTitle(Legend_name[nSam]+"  "+"dR_A1");
		histo_dR_A1[nSam]->Draw();
		canv_dR_A1[nSam]->SaveAs(Save_dir+Sample_name[nSam]+"_"+"dR_A1.png");
	}
}
