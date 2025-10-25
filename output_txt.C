#include <fstream>
#include <iostream>

void SaveTH2FToText() {

//TFile *file1 = new TFile("./analysis_8.8GeV_LA_threshold3GeV_noWcut_Longitudinal.root");
TFile *file1 = new TFile("./analysis_8.8GeV_FA_noWcut_Longitudinal.root");
  
 TH2F* h2;
  //hf = (TH2F*)file1->Get("acceptance_ThetaP_forwardangle");
    h2 = (TH2F*)file1->Get("Q2_Xjb_rate_hist");  // Replace with your actual histogram name

    if (!h2) {
        std::cerr << "Histogram not found!" << std::endl;
        return;
    }

    //std::ofstream outFile("DIS_LA_rate_x_Q2_bins_8.8GeV_noWcut_Longitudinal.txt");
    std::ofstream outFile("DIS_FA_rate_x_Q2_bins_8.8GeV_noWcut_Longitudinal.txt");

    int nBinsX = h2->GetNbinsX();
    int nBinsY = h2->GetNbinsY();

    outFile << "Q2_center\txbj_center\tContent\n";

    for (int ix = 1; ix <= nBinsX; ++ix) {
        for (int iy = 1; iy <= nBinsY; ++iy) {
            double xCenter = h2->GetXaxis()->GetBinCenter(ix);
            double yCenter = h2->GetYaxis()->GetBinCenter(iy);
            double content = h2->GetBinContent(ix, iy);
	    if(content>0){ //cout<<"content="<<content<<endl;
            outFile << xCenter << "\t" << yCenter << "\t" << content << "\n";
	    }
        }
    }

    outFile.close();
    std::cout << "Output saved to hist2D_output.txt" << std::endl;
}
