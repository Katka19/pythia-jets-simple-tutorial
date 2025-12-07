#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TMath.h"
#include "TVector2.h"

#include <vector>
#include <iostream>
#include <cmath>

void anaTree(TString inputFileName="jets_ptHat_10_20_jetR0.4.root") {

<<<<<<< HEAD
  TFile inputFile(inputFileName, "READ");
  if (inputFile.IsZombie()) {
=======
  TFile outFile("anaTrees.root", "RECREATE");
  // -------------------------
  // 1) Define histograms
  // -------------------------

  // Event-level
  TH1D hNJetsPerEvent("hNJetsPerEvent", "Number of jets per event;N_{jets};Counts", 12, 0, 12); // 0 to 12 jets

  // Single-jet level
  TH1D hJetPt("hJetPt", ";jet p_{T} (GeV/c);Counts", 100, 0, 100); // 0 to 100 GeV/c
  TH1D hJetEta("hJetEta", ";jet #eta;Counts", 60, -3, 3); // -3 to 3 in eta
  TH1D hJetPhi("hJetPhi", ";jet #phi;Counts", 64, -TMath::Pi(), TMath::Pi()); // -pi to pi in phi
  TH1D hJetArea("hJetArea", ";jet area;Counts", 50, 0, 1); // 0 to 1 in area

  // Dijet level
  TH1D hAsymmetry("hAsymmetry", ";Dijet asymmetry A_{J};Counts", 50, 0, 1); // from 0 to 1
  TH1D hDeltaPhi("hDeltaPhi", ";#Delta#phi;Counts", 200, 0, TMath::TwoPi()); // 0 to 2pi

  // -------------------------
  // 2) Open input file & tree
  // -------------------------


  TFile inputFile(inputFileName);
    if (inputFile.IsZombie()) {
>>>>>>> 41726f8 (added jet area + other finalising modifications)
    std::cout << "Cannot open input file " << inputFileName << std::endl;
    return;
  }

  TTree *tree = (TTree*)inputFile.Get("events");
  if (!tree) {
    std::cout << "Cannot find tree 'events'" << std::endl;
    return;
  }

  TFile outFile("anaTrees.root", "RECREATE");

  // event / jet histograms
  TH1D hNJetsPerEvent("hNJetsPerEvent", ";N_{jets};Counts", 12, 0, 12);
  TH1D hJetPt("hJetPt", ";jet p_{T} (GeV/c);Counts", 100, 0, 100);
  TH1D hJetEta("hJetEta", ";jet #eta;Counts", 60, -3, 3);
  TH1D hJetPhi("hJetPhi", ";jet #phi;Counts", 64, -TMath::Pi(), TMath::Pi());

  // dijet histograms
  TH1D hAsymmetry("hAsymmetry", ";A_{J};Counts", 50, 0, 1);
  TH1D hDeltaPhi("hDeltaPhi", ";#Delta#phi;Counts", 64, 0, TMath::Pi());

  // one constituent histogram for dijet events
  TH1D hConstPtDijet("hConstPtDijet", ";constituent p_{T} (GeV/c);Counts", 100, 0, 20);

  // branches
  int nJets = 0;
<<<<<<< HEAD
  int nConstituents = 0;

  std::vector<double> *jetPt = 0;
  std::vector<double> *jetEta = 0;
  std::vector<double> *jetPhi = 0;

  std::vector<int>    *constJetIndex = 0;
  std::vector<double> *constPt = 0;

  tree->SetBranchAddress("nJets", &nJets);
  tree->SetBranchAddress("nConstituents", &nConstituents);
=======
  double pt[kMaxJets];
  double eta[kMaxJets];
  double phi[kMaxJets];
  double area[kMaxJets];

  tree->SetBranchAddress("nJets", &nJets);
  tree->SetBranchAddress("pt", pt);
  tree->SetBranchAddress("eta", eta);
  tree->SetBranchAddress("phi", phi);
  tree->SetBranchAddress("area", area);
>>>>>>> 41726f8 (added jet area + other finalising modifications)

  tree->SetBranchAddress("jetPt",  &jetPt);
  tree->SetBranchAddress("jetEta", &jetEta);
  tree->SetBranchAddress("jetPhi", &jetPhi);

  tree->SetBranchAddress("constituentJetIndex", &constJetIndex);
  tree->SetBranchAddress("constituentPt",       &constPt);

  Long64_t nEntries = tree->GetEntries();

  for (Long64_t iEvent = 0; iEvent < nEntries; ++iEvent) {
    tree->GetEntry(iEvent);

    hNJetsPerEvent.Fill(nJets);

    // single-jet histograms
    for (int iJet = 0; iJet < nJets; ++iJet) {
<<<<<<< HEAD
      hJetPt.Fill(jetPt->at(iJet));
      hJetEta.Fill(jetEta->at(iJet));
      hJetPhi.Fill(jetPhi->at(iJet));
=======
      hJetPt.Fill(pt[iJet]);
      hJetEta.Fill(eta[iJet]);
      hJetPhi.Fill(phi[iJet]);  
      hJetArea.Fill(area[iJet]);
>>>>>>> 41726f8 (added jet area + other finalising modifications)
    }

    // dijet analysis - only look at events with exactly 2 jets
    if (nJets == 2) { 
      double pt1 = jetPt->at(0);
      double pt2 = jetPt->at(1);

      double AJ = (pt1 - pt2) / (pt1 + pt2);
      hAsymmetry.Fill(AJ);

      double dphi = std::fabs(TVector2::Phi_mpi_pi(jetPhi->at(0) - jetPhi->at(1)));
      hDeltaPhi.Fill(dphi);

<<<<<<< HEAD
      // fill one constituent histogram using all constituents from both jets
      for (int iConst = 0; iConst < nConstituents; ++iConst) {
        const int jetIndex = constJetIndex->at(iConst);
        if (jetIndex != 0 && jetIndex != 1) continue;
=======
      double phi1 = phi[0];
      double phi2 = phi[1];

      // calculate delta phi between the two jets and fill into histogram
      double deltaPhi = std::abs(phi1 - phi2);
      hDeltaPhi.Fill(deltaPhi);
>>>>>>> 41726f8 (added jet area + other finalising modifications)

        hConstPtDijet.Fill(constPt->at(iConst));
      }
      
    }
  }

  outFile.Write();
  outFile.Close();
  inputFile.Close();
}