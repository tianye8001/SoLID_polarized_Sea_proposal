#include <fstream>
#include <iostream>

void SaveTH2FToText() {

TFile *file1 = new TFile("./analysis_8.8GeV_LA_threshold3GeV.root");
  
 TH1F* h2;
  //hf = (TH2F*)file1->Get("acceptance_ThetaP_forwardangle");
    h2 = (TH1F*)file1->Get("Q2_rate_hist");  // Replace with your actual histogram name

    if (!h2) {
        std::cerr << "Histogram not found!" << std::endl;
        return;
    }

    std::ofstream outFile("DIS_LA_rate_Q2_bins_8.8GeV_threshold3GeV_2017.txt");

    int nBinsX = h2->GetNbinsX();
    //int nBinsY = h2->GetNbinsY();

    outFile << "Q2_center\tN_total\n";

    for (int ix = 1; ix <= nBinsX; ++ix) {
        //for (int iy = 1; iy <= nBinsY; ++iy) {
            double xCenter = h2->GetXaxis()->GetBinCenter(ix);
           // double yCenter = h2->GetYaxis()->GetBinCenter(iy);
            double content = h2->GetBinContent(ix);
	    if(content>0){ //cout<<"content="<<content<<endl;
            outFile << xCenter << "\t" << content << "\n";
	    }
        //}
    }

    outFile.close();
    std::cout << "Output saved to hist2D_output.txt" << std::endl;
}
