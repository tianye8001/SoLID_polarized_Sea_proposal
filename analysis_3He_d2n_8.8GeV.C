#include <iostream> 
#include <fstream>
#include <cmath> 
#include <math.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <THnSparse.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>
#include <TVector3.h>
#include "TRandom3.h"
#include "TSystem.h"
#include "TLorentzRotation.h"
// #include "analysis_tree_solid_spd.C"
// #include "analysis_tree_solid_mrpc.C"
// #include "analysis_tree_solid_ec.C"


using namespace std;

void analysis_3He_d2n_8.8GeV(string input_filename){
gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);

const double DEG=180./3.1415926;

char the_filename[200];
sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());
TFile *file1;
TH2F *hf,*hl,*hall;
file1 = new TFile("/w/halla-scifs17exp/solid/tianye/solid_svn/study/acceptance/result_SIDIS_He3/201701/acceptance_solid_SIDIS_He3_electron_201701_1e7_output_final.root");
  

  hf = (TH2F*)file1->Get("acceptance_ThetaP_forwardangle");
  hl = (TH2F*)file1->Get("acceptance_ThetaP_largeangle");
  hall = (TH2F*)file1->Get("acceptance_ThetaP_overall");
const int m=12;
//char *detector_name[m]={"GEM 1","GEM 2","GEM 3","GEM 4","GEM 5","GEM 6","LGC","HGC","FASPD","LASPD","FAEC","LAEC"};
//TH2F *hflux_hitxy[m];
//for (Int_t i=0;i<m;i++) {
//hflux_hitxy[i]=new TH2F(Form("hflux_hitxy_%i",i),Form("flux_hitxy %s;x(cm);y(cm)",detector_name[i]),600,-300,300,600,-300,300);
//}

  THnSparseF *Q2_Xjb_theta_mom_gen_hist;
  THnSparseF *Q2_Xjb_theta_mom_EC_hist;
  TH2F *Q2_Xjb_dxs_hist;
  int bins[4] = {220,200,30,1000};
  double xmin1[4] = {0.0,0.0,5.0,0};
  //double xmax1[4] = {11.0,1.0,35.0,360};                       
  double xmax1[4] = {11.0,1.0,35.0,1};                       
  Q2_Xjb_theta_mom_gen_hist = new THnSparseF("Q2_Xjb_theta_mom_gen_hist","Q2_Xjb_theta_mom_gen_hist",4,bins,xmin1,xmax1);
  Q2_Xjb_theta_mom_gen_hist->Sumw2();
  Q2_Xjb_theta_mom_EC_hist = new THnSparseF("Q2_Xjb_theta_mom_EC_hist","Q2_Xjb_theta_mom_EC_hist",4,bins,xmin1,xmax1);
  Q2_Xjb_theta_mom_EC_hist->Sumw2();
  Q2_Xjb_dxs_hist = new TH2F("Q2_Xjb_dxs_hist","Q2_Xjb_dxs_hist",220,0,11,200,0,1);
TFile *file=new TFile(input_filename.c_str());
if (file->IsZombie()) {
    cout << "Error opening file" << input_filename << endl;
    exit(-1);
}
else cout << "open file " << input_filename << endl;    

TTree *tree_header = (TTree*) file->Get("T");

   Double_t        Abeam;
   Double_t        AL;
   Double_t        x;
   Double_t        y;
   Double_t        W;
   Double_t        Q2;
   Double_t        rate_pre;
   Int_t           charge;
   Int_t           particle_id;
   Double_t        px;
   Double_t        py;
   Double_t        pz;
   Double_t        Ep;
   Double_t        mass;
   Double_t        vx;
   Double_t        vy;
   Double_t        vz;
   Double_t        xs;
   Double_t        dxs;
   Double_t        theta;
   Double_t        phi;
   Double_t        rate;

   // List of branches
   TBranch        *b_data;   //!
/*   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;   //!
   TBranch        *b_data;*/   //!
   tree_header->SetBranchAddress("Abeam", &Abeam, &b_data);
   tree_header->SetBranchAddress("AL", &AL, &b_data);
   tree_header->SetBranchAddress("x", &x, &b_data);
   tree_header->SetBranchAddress("y", &y, &b_data);
   tree_header->SetBranchAddress("W", &W, &b_data);
   tree_header->SetBranchAddress("Q2", &Q2, &b_data);
   tree_header->SetBranchAddress("rate_pre", &rate_pre, &b_data);
   tree_header->SetBranchAddress("charge", &charge, &b_data);
   tree_header->SetBranchAddress("particle_id", &particle_id, &b_data);
   tree_header->SetBranchAddress("px", &px, &b_data);
   tree_header->SetBranchAddress("py", &py, &b_data);
   tree_header->SetBranchAddress("pz", &pz, &b_data);
   tree_header->SetBranchAddress("Ep", &Ep, &b_data);
   tree_header->SetBranchAddress("mass", &mass, &b_data);
   tree_header->SetBranchAddress("vx", &vx, &b_data);
   tree_header->SetBranchAddress("vy", &vy, &b_data);
   tree_header->SetBranchAddress("vz", &vz, &b_data);
   tree_header->SetBranchAddress("xs", &xs, &b_data);
   tree_header->SetBranchAddress("dxs", &dxs, &b_data);
   tree_header->SetBranchAddress("theta", &theta, &b_data);
   tree_header->SetBranchAddress("phi", &phi, &b_data);
   tree_header->SetBranchAddress("rate", &rate, &b_data);
int nevent = (int)tree_header->GetEntries();
int nselected = 0;
double phi_value=0;
cout << "nevent " << nevent << endl;
  int bin,binx,biny,binz;
  double accep_e_1, accep_e_2;

for (Int_t i=0;i<nevent;i++) { 
  cout << i << "\r";
  tree_header->GetEntry(i);
   tree_header->GetEntry(i);  
   int pid_gen=0;
   double Q2_gen=0, rate_gen=0, W_gen=0,dxs_gen=0;
   double theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;      
       pid_gen=particle_id;
       px_gen=px;
       py_gen=py;
       pz_gen=pz;
       vx_gen=vx;
       vy_gen=vy;
       vz_gen=vz;
       Q2_gen=Q2;
       W_gen = W;
       dxs_gen =dxs;
       rate_gen= rate;
       p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
       theta_gen=acos(pz_gen/p_gen)*DEG;
       phi_gen=atan2(py_gen,px_gen)*DEG;
       if(phi_gen<0){
         phi_value=phi_gen+360;
       }else phi_value=phi_gen;
//         if(dxs_gen>10 && Q2_gen>1){
//          cout<<"dxs_gen="<<dxs_gen<<endl; 
//         }

       bin=hf->FindBin(theta_gen,p_gen);
       hf->GetBinXYZ(bin,binx,biny,binz);
      if(pid_gen==11 && Q2_gen>1 && W_gen>2){
      accep_e_1 = hf->GetBinContent(binx,biny);
      accep_e_2 = hall->GetBinContent(binx,biny); 
     // double genvar[4] = {Q2_gen,x,theta_gen,phi_value}; 
      double genvar[4] = {Q2_gen,x,theta_gen,dxs_gen}; 
      double weight = rate_gen; 
      Q2_Xjb_theta_mom_gen_hist->Fill(genvar,weight); 
      if(accep_e_2>0){
        double weight_EC=rate_gen;
        double  ECvar[4] = {Q2_gen,x,theta_gen,dxs_gen}; 
        //double  ECvar[4] = {Q2_gen,x,theta_gen,phi_value}; 
        Q2_Xjb_theta_mom_EC_hist->Fill(ECvar,weight_EC); 
        Q2_Xjb_dxs_hist->Fill(Q2_gen,x,dxs_gen);
      }
  }
 }
file->Close();

TFile *outputfile_final=new TFile("analysis_8.8GeV.root", "recreate");
outputfile_final->Append(Q2_Xjb_theta_mom_gen_hist);
outputfile_final->Append(Q2_Xjb_dxs_hist);
outputfile_final->Append(Q2_Xjb_theta_mom_EC_hist);
outputfile_final->Write();
outputfile_final->Flush();

}
