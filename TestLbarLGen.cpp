// A macro attempted to perform event generator that only based and run on (CERN) ROOT.
// For the reaction of PbarP -> LambdabarLambda -> PbarPiplus PPiminus in this test
// And might try to extend to PbarP -> OmegabarOmega in the future.
// 
// Random (uniform) angle distribution of decay particles in lambda(and lambdabar) rest frame
// And them boost to CM frame with caluclation of corresponding 4-vectors relations 
// In LambdaRest, LambdabarRest and CM frame.
//
// author: Vitor Jose Shen
// supervisor: Michael Papenbrock
// at Uppsala University
//
// Version 02 May 2022
// Revised 20 June 2022
//------------------------------------------------------------------------

// include section
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMath.h"
#include "TTree.h"

//------------------------------------------------------------------------

int TestLbarLGen(){
    cout << "As ROOT macro to perform llbar with default generation of 10^6 events or set the event number inside () of function:" << endl;
    cout << "To test the angle's distribution only, use function: testAngle()" << endl;
    cout << "The overall event generation including 4-momentum and angles, use function: testGenllbar()" << endl;
    // cout << "The number of events can be also set by enter number inside (), the default number is 1 million" << endl;
    cout << "Check 4-vector conservation, use function: CheckLbarL()" << endl;
    return 0;
}
//------------------------------------------------------------------------

void testGenllbar(Int_t nrEvents=1000000){

    // Int_t nrEvents=1000000
    // cout << "The number of events should be an integer and greater than 0" << endl;
    // cout << "Please enter the number of events that you want to simulatie:" << endl;
    // cin >> nrEvents;
    // cout << nrEvents << "Events will be simulated then!" << endl;

    TFile* f = TFile::Open("testGenllbar.root","RECREATE");
    TRandom3 *r3=new TRandom3();
    r3->SetSeed(time(NULL));
    
    // TNtuple *ntuple = new TNtuple;
    /////////////////////////////////////////////////////////////////////////////
    // Tree: Rest frame of lambda or lambdabar
    /////////////////////////////////////////////////////////////////////////////
    //
    // Hyperon side
    TTree *protonTree=new TTree("Proton_LambdaRF","Proton in Lambda Rest Frame");
    Float_t protonPhi, protonCosTheta, protonTheta;
    Float_t m_proton, E_proton, p_proton, px_proton, py_proton, pz_proton, pt_proton;    //used in Tree Branch
    // Float_t m_protontest;
    protonTree->Branch("protonPhi", &protonPhi, "protonPhi/F");
    protonTree->Branch("protonCosTheta", &protonCosTheta, "protonCosTheta/F");
    protonTree->Branch("protonTheta", &protonTheta, "protonTheta/F");
    protonTree->Branch("m_proton", &m_proton, "m_proton/F");
    // protonTree->Branch("m_protontest", &m_protontest, "m_protontest/F");
    protonTree->Branch("E_proton", &E_proton, "E_proton/F");
    protonTree->Branch("p_proton", &p_proton, "p_proton/F");
    protonTree->Branch("px_proton", &px_proton, "px_proton/F");
    protonTree->Branch("py_proton", &py_proton, "py_proton/F");
    protonTree->Branch("pz_proton", &pz_proton, "pz_proton/F");
    protonTree->Branch("pt_proton", &pt_proton, "pt_proton/F");

    TTree *piminusTree=new TTree("Piminus_LambdaRF","Piminus in Lambda Rest Frame");
    Float_t piminusPhi, piminusCosTheta, piminusTheta;
    Float_t E_piminus, p_piminus, px_piminus, py_piminus, pz_piminus, pt_piminus;    //used in Tree Branch
    // Float_t m_piminustest;
    Float_t m_piminus;
    piminusTree->Branch("piminusPhi", &piminusPhi, "piminusPhi/F");
    piminusTree->Branch("piminusCosTheta", &piminusCosTheta, "piminusCosTheta/F");
    piminusTree->Branch("piminusTheta", &piminusTheta, "piminusTheta/F");
    piminusTree->Branch("m_piminus", &m_piminus, "m_piminus/F");
    // piminusTree->Branch("m_piminustest", &m_piminustest, "m_piminustest/F");
    piminusTree->Branch("E_piminus", &E_piminus, "E_piminus/F");
    piminusTree->Branch("p_piminus", &p_piminus, "p_piminus/F");
    piminusTree->Branch("px_piminus", &px_piminus, "px_piminus/F");
    piminusTree->Branch("py_piminus", &py_piminus, "py_piminus/F");
    piminusTree->Branch("pz_piminus", &pz_piminus, "pz_piminus/F");
    piminusTree->Branch("pt_piminus", &pt_piminus, "pt_piminus/F");

    //
    // Anti-hyperon side
    TTree *protonbarTree=new TTree("Protonbar_LambdaRF","Protonbar in Lambda Rest Frame");
    Float_t protonbarPhi, protonbarCosTheta, protonbarTheta;
    Float_t m_protonbar, E_protonbar, p_protonbar, px_protonbar, py_protonbar, pz_protonbar, pt_protonbar;    //used in Tree Branch
    // Float_t m_protonbartest;
    protonbarTree->Branch("protonbarPhi", &protonbarPhi, "protonbarPhi/F");
    protonbarTree->Branch("protonbarCosTheta", &protonbarCosTheta, "protonbarCosTheta/F");
    protonbarTree->Branch("protonbarTheta", &protonbarTheta, "protonbarTheta/F");
    protonbarTree->Branch("m_protonbar", &m_protonbar, "m_protonbar/F");
    // protonbarTree->Branch("m_protonbartest", &m_protonbartest, "m_protonbartest/F");
    protonbarTree->Branch("E_protonbar", &E_protonbar, "E_protonbar/F");
    protonbarTree->Branch("p_protonbar", &p_protonbar, "p_protonbar/F");
    protonbarTree->Branch("px_protonbar", &px_protonbar, "px_protonbar/F");
    protonbarTree->Branch("py_protonbar", &py_protonbar, "py_protonbar/F");
    protonbarTree->Branch("pz_protonbar", &pz_protonbar, "pz_protonbar/F");
    protonbarTree->Branch("pt_protonbar", &pt_protonbar, "pt_protonbar/F");

    TTree *piplusTree=new TTree("Piplus_LambdaRF","Piplus in Lambda Rest Frame");
    Float_t piplusPhi, piplusCosTheta, piplusTheta;
    Float_t E_piplus, p_piplus, px_piplus, py_piplus, pz_piplus, pt_piplus;    //used in Tree Branch
    // Float_t m_piplustest;
    Float_t m_piplus;
    piplusTree->Branch("piplusPhi", &piplusPhi, "piplusPhi/F");
    piplusTree->Branch("piplusCosTheta", &piplusCosTheta, "piplusCosTheta/F");
    piplusTree->Branch("piplusTheta", &piplusTheta, "piplusTheta/F");
    piplusTree->Branch("m_piplus", &m_piplus, "m_piplus/F");
    // piplusTree->Branch("m_piplustest", &m_piplustest, "m_piplustest/F");
    piplusTree->Branch("E_piplus", &E_piplus, "E_piplus/F");
    piplusTree->Branch("p_piplus", &p_piplus, "p_piplus/F");
    piplusTree->Branch("px_piplus", &px_piplus, "px_piplus/F");
    piplusTree->Branch("py_piplus", &py_piplus, "py_piplus/F");
    piplusTree->Branch("pz_piplus", &pz_piplus, "pz_piplus/F");
    piplusTree->Branch("pt_piplus", &pt_piplus, "pt_piplus/F");

    /////////////////////////////////////////////////////////////////////////////
    // Tree: CM frame
    /////////////////////////////////////////////////////////////////////////////
    //
    // Hyperon side
    TTree *protonCMTree=new TTree("Proton_CM","Proton in CM Frame");
    Float_t protonPhiCM, protonCosThetaCM, protonThetaCM;
    Float_t m_protonCM, E_protonCM, p_protonCM, px_protonCM, py_protonCM, pz_protonCM, pt_protonCM;    //used in Tree Branch
    protonCMTree->Branch("protonPhiCM", &protonPhiCM, "protonPhiCM/F");
    protonCMTree->Branch("protonCosThetaCM", &protonCosThetaCM, "protonCosThetaCM/F");
    protonCMTree->Branch("protonThetaCM", &protonThetaCM, "protonThetaCM/F");
    protonCMTree->Branch("m_protonCM", &m_protonCM, "m_protonCM/F");
    protonCMTree->Branch("E_protonCM", &E_protonCM, "E_protonCM/F");
    protonCMTree->Branch("p_protonCM", &p_protonCM, "p_protonCM/F");
    protonCMTree->Branch("px_protonCM", &px_protonCM, "px_protonCM/F");
    protonCMTree->Branch("py_protonCM", &py_protonCM, "py_protonCM/F");
    protonCMTree->Branch("pz_protonCM", &pz_protonCM, "pz_protonCM/F");
    protonCMTree->Branch("pt_protonCM", &pt_protonCM, "pt_protonCM/F");

    TTree *piminusCMTree=new TTree("Piminus_CM","Piminus in CM Frame");
    Float_t piminusPhiCM, piminusCosThetaCM, piminusThetaCM;
    Float_t E_piminusCM, p_piminusCM, px_piminusCM, py_piminusCM, pz_piminusCM, pt_piminusCM;    //used in Tree Branch
    Float_t m_piminusCM;
    piminusCMTree->Branch("piminusPhiCM", &piminusPhiCM, "piminusPhiCM/F");
    piminusCMTree->Branch("piminusCosThetaCM", &piminusCosThetaCM, "piminusCosThetaCM/F");
    piminusCMTree->Branch("piminusThetaCM", &piminusThetaCM, "piminusThetaCM/F");
    piminusCMTree->Branch("m_piminusCM", &m_piminusCM, "m_piminusCM/F");
    piminusCMTree->Branch("E_piminusCM", &E_piminusCM, "E_piminusCM/F");
    piminusCMTree->Branch("p_piminusCM", &p_piminusCM, "p_piminusCM/F");
    piminusCMTree->Branch("px_piminusCM", &px_piminusCM, "px_piminusCM/F");
    piminusCMTree->Branch("py_piminusCM", &py_piminusCM, "py_piminusCM/F");
    piminusCMTree->Branch("pz_piminusCM", &pz_piminusCM, "pz_piminusCM/F");
    piminusCMTree->Branch("pt_piminusCM", &pt_piminusCM, "pt_piminusCM/F");

    TTree *lambdaCMTree=new TTree("Lambda_CM","Lambda in CM Frame");
    Float_t lambdaPhiCM, lambdaCosThetaCM, lambdaThetaCM;
    Float_t E_lambdaCM, p_lambdaCM, px_lambdaCM, py_lambdaCM, pz_lambdaCM, pt_lambdaCM;    //used in Tree Branch
    Float_t m_lambdaCM;
    lambdaCMTree->Branch("lambdaPhiCM", &lambdaPhiCM, "lambdaPhiCM/F");
    lambdaCMTree->Branch("lambdaCosThetaCM", &lambdaCosThetaCM, "lambdaCosThetaCM/F");
    lambdaCMTree->Branch("lambdaThetaCM", &lambdaThetaCM, "lambdaThetaCM/F");
    lambdaCMTree->Branch("m_lambdaCM", &m_lambdaCM, "m_lambdaCM/F");
    lambdaCMTree->Branch("E_lambdaCM", &E_lambdaCM, "E_lambdaCM/F");
    lambdaCMTree->Branch("p_lambdaCM", &p_lambdaCM, "p_lambdaCM/F");
    lambdaCMTree->Branch("px_lambdaCM", &px_lambdaCM, "px_lambdaCM/F");
    lambdaCMTree->Branch("py_lambdaCM", &py_lambdaCM, "py_lambdaCM/F");
    lambdaCMTree->Branch("pz_lambdaCM", &pz_lambdaCM, "pz_lambdaCM/F");
    lambdaCMTree->Branch("pt_lambdaCM", &pt_lambdaCM, "pt_lambdaCM/F");
    
    //
    // Anti-hyperon side
    TTree *protonbarCMTree=new TTree("Protonbar_CM","Protonbar in CM Frame");
    Float_t protonbarPhiCM, protonbarCosThetaCM, protonbarThetaCM;
    Float_t m_protonbarCM, E_protonbarCM, p_protonbarCM, px_protonbarCM, py_protonbarCM, pz_protonbarCM, pt_protonbarCM;    //used in Tree Branch
    protonbarCMTree->Branch("protonbarPhiCM", &protonbarPhiCM, "protonbarPhiCM/F");
    protonbarCMTree->Branch("protonbarCosThetaCM", &protonbarCosThetaCM, "protonbarCosThetaCM/F");
    protonbarCMTree->Branch("protonbarThetaCM", &protonbarThetaCM, "protonbarThetaCM/F");
    protonbarCMTree->Branch("m_protonbarCM", &m_protonbarCM, "m_protonbarCM/F");
    protonbarCMTree->Branch("E_protonbarCM", &E_protonbarCM, "E_protonbarCM/F");
    protonbarCMTree->Branch("p_protonbarCM", &p_protonbarCM, "p_protonbarCM/F");
    protonbarCMTree->Branch("px_protonbarCM", &px_protonbarCM, "px_protonbarCM/F");
    protonbarCMTree->Branch("py_protonbarCM", &py_protonbarCM, "py_protonbarCM/F");
    protonbarCMTree->Branch("pz_protonbarCM", &pz_protonbarCM, "pz_protonbarCM/F");
    protonbarCMTree->Branch("pt_protonbarCM", &pt_protonbarCM, "pt_protonbarCM/F");

    TTree *piplusCMTree=new TTree("Piplus_CM","Piplus in CM Frame");
    Float_t piplusPhiCM, piplusCosThetaCM, piplusThetaCM;
    Float_t E_piplusCM, p_piplusCM, px_piplusCM, py_piplusCM, pz_piplusCM, pt_piplusCM;    //used in Tree Branch
    Float_t m_piplusCM;
    piplusCMTree->Branch("piplusPhiCM", &piplusPhiCM, "piplusPhiCM/F");
    piplusCMTree->Branch("piplusCosThetaCM", &piplusCosThetaCM, "piplusCosThetaCM/F");
    piplusCMTree->Branch("piplusThetaCM", &piplusThetaCM, "piplusThetaCM/F");
    piplusCMTree->Branch("m_piplusCM", &m_piplusCM, "m_piplusCM/F");
    piplusCMTree->Branch("E_piplusCM", &E_piplusCM, "E_piplusCM/F");
    piplusCMTree->Branch("p_piplusCM", &p_piplusCM, "p_piplusCM/F");
    piplusCMTree->Branch("px_piplusCM", &px_piplusCM, "px_piplusCM/F");
    piplusCMTree->Branch("py_piplusCM", &py_piplusCM, "py_piplusCM/F");
    piplusCMTree->Branch("pz_piplusCM", &pz_piplusCM, "pz_piplusCM/F");
    piplusCMTree->Branch("pt_piplusCM", &pt_piplusCM, "pt_piplusCM/F");

    TTree *lambdabarCMTree=new TTree("Lambdabar_CM","Lambdabar in CM Frame");
    Float_t lambdabarPhiCM, lambdabarCosThetaCM, lambdabarThetaCM;
    Float_t E_lambdabarCM, p_lambdabarCM, px_lambdabarCM, py_lambdabarCM, pz_lambdabarCM, pt_lambdabarCM;    //used in Tree Branch
    Float_t m_lambdabarCM;
    lambdabarCMTree->Branch("lambdabarPhiCM", &lambdabarPhiCM, "lambdabarPhiCM/F");
    lambdabarCMTree->Branch("lambdabarCosThetaCM", &lambdabarCosThetaCM, "lambdabarCosThetaCM/F");
    lambdabarCMTree->Branch("lambdabarThetaCM", &lambdabarThetaCM, "lambdabarThetaCM/F");
    lambdabarCMTree->Branch("m_lambdabarCM", &m_lambdabarCM, "m_lambdabarCM/F");
    lambdabarCMTree->Branch("E_lambdabarCM", &E_lambdabarCM, "E_lambdabarCM/F");
    lambdabarCMTree->Branch("p_lambdabarCM", &p_lambdabarCM, "p_lambdabarCM/F");
    lambdabarCMTree->Branch("px_lambdabarCM", &px_lambdabarCM, "px_lambdabarCM/F");
    lambdabarCMTree->Branch("py_lambdabarCM", &py_lambdabarCM, "py_lambdabarCM/F");
    lambdabarCMTree->Branch("pz_lambdabarCM", &pz_lambdabarCM, "pz_lambdabarCM/F");
    lambdabarCMTree->Branch("pt_lambdabarCM", &pt_lambdabarCM, "pt_lambdabarCM/F");

    // //
    // // pbarp CM
    TTree *pbarpCMTree=new TTree("PbarP_CM","PbarP in CM Frame");
    Float_t pbarPhiCM, pPhiCM, pbarCosThetaCM, pCosThetaCM,pbarThetaCM, pThetaCM; 
    pbarpCMTree->Branch("pPhiCM", &pPhiCM, "pPhiCM/F");
    pbarpCMTree->Branch("pCosThetaCM", &pCosThetaCM, "pCosThetaCM/F");
    pbarpCMTree->Branch("pThetaCM", &pThetaCM, "pThetaCM/F");
    pbarpCMTree->Branch("pbarPhiCM", &pbarPhiCM, "pbarPhiCM/F");
    pbarpCMTree->Branch("pbarCosThetaCM", &pbarCosThetaCM, "pbarCosThetaCM/F");
    pbarpCMTree->Branch("pbarThetaCM", &pbarThetaCM, "pbarThetaCM/F"); 

    /////////////////////////////////////////////////////////////////////////////
    // Tree: Rotated CM frame
    /////////////////////////////////////////////////////////////////////////////
    // Hyperon side 
    TTree *lambdaCMrotTree=new TTree("Lambda_CMrot","Lambda in CM Rotation Frame");
    Float_t lambdaPhiCMrot, lambdaCosThetaCMrot, lambdaThetaCMrot;
    Float_t E_lambdaCMrot, p_lambdaCMrot, px_lambdaCMrot, py_lambdaCMrot, pz_lambdaCMrot, pt_lambdaCMrot;    //used in Tree Branch
    Float_t m_lambdaCMrot;
    lambdaCMrotTree->Branch("lambdaPhiCMrot", &lambdaPhiCMrot, "lambdaPhiCMrot/F");
    lambdaCMrotTree->Branch("lambdaCosThetaCMrot", &lambdaCosThetaCMrot, "lambdaCosThetaCMrot/F");
    lambdaCMrotTree->Branch("lambdaThetaCMrot", &lambdaThetaCMrot, "lambdaThetaCMrot/F");
    lambdaCMrotTree->Branch("m_lambdaCMrot", &m_lambdaCMrot, "m_lambdaCMrot/F");
    lambdaCMrotTree->Branch("E_lambdaCMrot", &E_lambdaCMrot, "E_lambdaCMrot/F");
    lambdaCMrotTree->Branch("p_lambdaCMrot", &p_lambdaCMrot, "p_lambdaCMrot/F");
    lambdaCMrotTree->Branch("px_lambdaCMrot", &px_lambdaCMrot, "px_lambdaCMrot/F");
    lambdaCMrotTree->Branch("py_lambdaCMrot", &py_lambdaCMrot, "py_lambdaCMrot/F");
    lambdaCMrotTree->Branch("pz_lambdaCMrot", &pz_lambdaCMrot, "pz_lambdaCMrot/F");
    lambdaCMrotTree->Branch("pt_lambdaCMrot", &pt_lambdaCMrot, "pt_lambdaCMrot/F");

    TTree *protonCMrotTree=new TTree("Proton_CMrot","Proton in CM Rotation Frame");
    Float_t protonPhiCMrot, protonCosThetaCMrot, protonThetaCMrot;
    Float_t m_protonCMrot, E_protonCMrot, p_protonCMrot, px_protonCMrot, py_protonCMrot, pz_protonCMrot, pt_protonCMrot;    //used in Tree Branch
    protonCMrotTree->Branch("protonPhiCMrot", &protonPhiCMrot, "protonPhiCMrot/F");
    protonCMrotTree->Branch("protonCosThetaCMrot", &protonCosThetaCMrot, "protonCosThetaCMrot/F");
    protonCMrotTree->Branch("protonThetaCMrot", &protonThetaCMrot, "protonThetaCMrot/F");
    protonCMrotTree->Branch("m_protonCMrot", &m_protonCMrot, "m_protonCMrot/F");
    protonCMrotTree->Branch("E_protonCMrot", &E_protonCMrot, "E_protonCMrot/F");
    protonCMrotTree->Branch("p_protonCMrot", &p_protonCMrot, "p_protonCMrot/F");
    protonCMrotTree->Branch("px_protonCMrot", &px_protonCMrot, "px_protonCMrot/F");
    protonCMrotTree->Branch("py_protonCMrot", &py_protonCMrot, "py_protonCMrot/F");
    protonCMrotTree->Branch("pz_protonCMrot", &pz_protonCMrot, "pz_protonCMrot/F");
    protonCMrotTree->Branch("pt_protonCMrot", &pt_protonCMrot, "pt_protonCMrot/F");

    TTree *piminusCMrotTree=new TTree("Piminus_CMrot","Piminus in CM Rotation Frame");
    Float_t piminusPhiCMrot, piminusCosThetaCMrot, piminusThetaCMrot;
    Float_t E_piminusCMrot, p_piminusCMrot, px_piminusCMrot, py_piminusCMrot, pz_piminusCMrot, pt_piminusCMrot;    //used in Tree Branch
    Float_t m_piminusCMrot;
    piminusCMrotTree->Branch("piminusPhiCMrot", &piminusPhiCMrot, "piminusPhiCMrot/F");
    piminusCMrotTree->Branch("piminusCosThetaCMrot", &piminusCosThetaCMrot, "piminusCosThetaCMrot/F");
    piminusCMrotTree->Branch("piminusThetaCMrot", &piminusThetaCMrot, "piminusThetaCMrot/F");
    piminusCMrotTree->Branch("m_piminusCMrot", &m_piminusCMrot, "m_piminusCMrot/F");
    piminusCMrotTree->Branch("E_piminusCMrot", &E_piminusCMrot, "E_piminusCMrot/F");
    piminusCMrotTree->Branch("p_piminusCMrot", &p_piminusCMrot, "p_piminusCMrot/F");
    piminusCMrotTree->Branch("px_piminusCMrot", &px_piminusCMrot, "px_piminusCMrot/F");
    piminusCMrotTree->Branch("py_piminusCMrot", &py_piminusCMrot, "py_piminusCMrot/F");
    piminusCMrotTree->Branch("pz_piminusCMrot", &pz_piminusCMrot, "pz_piminusCMrot/F");
    piminusCMrotTree->Branch("pt_piminusCMrot", &pt_piminusCMrot, "pt_piminusCMrot/F");

    //
    // Anti-hyperon side
    TTree *lambdabarCMrotTree=new TTree("Lambdabar_CMrot","Lambdabar in CM Rotation Frame");
    Float_t lambdabarPhiCMrot, lambdabarCosThetaCMrot, lambdabarThetaCMrot;
    Float_t E_lambdabarCMrot, p_lambdabarCMrot, px_lambdabarCMrot, py_lambdabarCMrot, pz_lambdabarCMrot, pt_lambdabarCMrot;    //used in Tree Branch
    Float_t m_lambdabarCMrot;
    lambdabarCMrotTree->Branch("lambdabarPhiCMrot", &lambdabarPhiCMrot, "lambdabarPhiCMrot/F");
    lambdabarCMrotTree->Branch("lambdabarCosThetaCMrot", &lambdabarCosThetaCMrot, "lambdabarCosThetaCMrot/F");
    lambdabarCMrotTree->Branch("lambdabarThetaCMrot", &lambdabarThetaCMrot, "lambdabarThetaCMrot/F");
    lambdabarCMrotTree->Branch("m_lambdabarCMrot", &m_lambdabarCMrot, "m_lambdabarCMrot/F");
    lambdabarCMrotTree->Branch("E_lambdabarCMrot", &E_lambdabarCMrot, "E_lambdabarCMrot/F");
    lambdabarCMrotTree->Branch("p_lambdabarCMrot", &p_lambdabarCMrot, "p_lambdabarCMrot/F");
    lambdabarCMrotTree->Branch("px_lambdabarCMrot", &px_lambdabarCMrot, "px_lambdabarCMrot/F");
    lambdabarCMrotTree->Branch("py_lambdabarCMrot", &py_lambdabarCMrot, "py_lambdabarCMrot/F");
    lambdabarCMrotTree->Branch("pz_lambdabarCMrot", &pz_lambdabarCMrot, "pz_lambdabarCMrot/F");
    lambdabarCMrotTree->Branch("pt_lambdabarCMrot", &pt_lambdabarCMrot, "pt_lambdabarCMrot/F");

    TTree *protonbarCMrotTree=new TTree("Protonbar_CMrot","Protonbar in CM Rotation Frame");
    Float_t protonbarPhiCMrot, protonbarCosThetaCMrot, protonbarThetaCMrot;
    Float_t m_protonbarCMrot, E_protonbarCMrot, p_protonbarCMrot, px_protonbarCMrot, py_protonbarCMrot, pz_protonbarCMrot, pt_protonbarCMrot;    //used in Tree Branch
    protonbarCMrotTree->Branch("protonbarPhiCMrot", &protonbarPhiCMrot, "protonbarPhiCMrot/F");
    protonbarCMrotTree->Branch("protonbarCosThetaCMrot", &protonbarCosThetaCMrot, "protonbarCosThetaCMrot/F");
    protonbarCMrotTree->Branch("protonbarThetaCMrot", &protonbarThetaCMrot, "protonbarThetaCMrot/F");
    protonbarCMrotTree->Branch("m_protonbarCMrot", &m_protonbarCMrot, "m_protonbarCMrot/F");
    protonbarCMrotTree->Branch("E_protonbarCMrot", &E_protonbarCMrot, "E_protonbarCMrot/F");
    protonbarCMrotTree->Branch("p_protonbarCMrot", &p_protonbarCMrot, "p_protonbarCMrot/F");
    protonbarCMrotTree->Branch("px_protonbarCMrot", &px_protonbarCMrot, "px_protonbarCMrot/F");
    protonbarCMrotTree->Branch("py_protonbarCMrot", &py_protonbarCMrot, "py_protonbarCMrot/F");
    protonbarCMrotTree->Branch("pz_protonbarCMrot", &pz_protonbarCMrot, "pz_protonbarCMrot/F");
    protonbarCMrotTree->Branch("pt_protonbarCMrot", &pt_protonbarCMrot, "pt_protonbarCMrot/F");

    TTree *piplusCMrotTree=new TTree("Piplus_CMrot","Piplus in CM Rotation Frame");
    Float_t piplusPhiCMrot, piplusCosThetaCMrot, piplusThetaCMrot;
    Float_t E_piplusCMrot, p_piplusCMrot, px_piplusCMrot, py_piplusCMrot, pz_piplusCMrot, pt_piplusCMrot;    //used in Tree Branch
    Float_t m_piplusCMrot;
    piplusCMrotTree->Branch("piplusPhiCMrot", &piplusPhiCMrot, "piplusPhiCMrot/F");
    piplusCMrotTree->Branch("piplusCosThetaCMrot", &piplusCosThetaCMrot, "piplusCosThetaCMrot/F");
    piplusCMrotTree->Branch("piplusThetaCMrot", &piplusThetaCMrot, "piplusThetaCMrot/F");
    piplusCMrotTree->Branch("m_piplusCMrot", &m_piplusCMrot, "m_piplusCMrot/F");
    piplusCMrotTree->Branch("E_piplusCMrot", &E_piplusCMrot, "E_piplusCMrot/F");
    piplusCMrotTree->Branch("p_piplusCMrot", &p_piplusCMrot, "p_piplusCMrot/F");
    piplusCMrotTree->Branch("px_piplusCMrot", &px_piplusCMrot, "px_piplusCMrot/F");
    piplusCMrotTree->Branch("py_piplusCMrot", &py_piplusCMrot, "py_piplusCMrot/F");
    piplusCMrotTree->Branch("pz_piplusCMrot", &pz_piplusCMrot, "pz_piplusCMrot/F");
    piplusCMrotTree->Branch("pt_piplusCMrot", &pt_piplusCMrot, "pt_piplusCMrot/F");

    //
    /////////////////////////////////////////////////////////////////////////////
    // Tree: Rotated in rest frame of lambda or lambdabar
    /////////////////////////////////////////////////////////////////////////////
    //
    // Hyperon side
    TTree *protonRotTree=new TTree("ProtonRot_LambdaRF","Proton in Lambda Rest Frame after rotation");
    Float_t protonRotPhi, protonRotCosTheta, protonRotTheta;
    Float_t m_protonRot, E_protonRot, p_protonRot, px_protonRot, py_protonRot, pz_protonRot, pt_protonRot;    //used in Tree Branch
    // Float_t m_protonRottest;
    protonRotTree->Branch("protonRotPhi", &protonRotPhi, "protonRotPhi/F");
    protonRotTree->Branch("protonRotCosTheta", &protonRotCosTheta, "protonRotCosTheta/F");
    protonRotTree->Branch("protonRotTheta", &protonRotTheta, "protonRotTheta/F");
    protonRotTree->Branch("m_protonRot", &m_protonRot, "m_protonRot/F");
    // protonRotTree->Branch("m_protonRottest", &m_protonRottest, "m_protonRottest/F");
    protonRotTree->Branch("E_protonRot", &E_protonRot, "E_protonRot/F");
    protonRotTree->Branch("p_protonRot", &p_protonRot, "p_protonRot/F");
    protonRotTree->Branch("px_protonRot", &px_protonRot, "px_protonRot/F");
    protonRotTree->Branch("py_protonRot", &py_protonRot, "py_protonRot/F");
    protonRotTree->Branch("pz_protonRot", &pz_protonRot, "pz_protonRot/F");
    protonRotTree->Branch("pt_protonRot", &pt_protonRot, "pt_protonRot/F");

    TTree *piminusRotTree=new TTree("PiminusRot_LambdaRF","Piminus in Lambda Rest Frame after rotation");
    Float_t piminusRotPhi, piminusRotCosTheta, piminusRotTheta;
    Float_t E_piminusRot, p_piminusRot, px_piminusRot, py_piminusRot, pz_piminusRot, pt_piminusRot;    //used in Tree Branch
    // Float_t m_piminusRottest;
    Float_t m_piminusRot;
    piminusRotTree->Branch("piminusRotPhi", &piminusRotPhi, "piminusRotPhi/F");
    piminusRotTree->Branch("piminusRotCosTheta", &piminusRotCosTheta, "piminusRotCosTheta/F");
    piminusRotTree->Branch("piminusRotTheta", &piminusRotTheta, "piminusRotTheta/F");
    piminusRotTree->Branch("m_piminusRot", &m_piminusRot, "m_piminusRot/F");
    // piminusRotTree->Branch("m_piminusRottest", &m_piminusRottest, "m_piminusRottest/F");
    piminusRotTree->Branch("E_piminusRot", &E_piminusRot, "E_piminusRot/F");
    piminusRotTree->Branch("p_piminusRot", &p_piminusRot, "p_piminusRot/F");
    piminusRotTree->Branch("px_piminusRot", &px_piminusRot, "px_piminusRot/F");
    piminusRotTree->Branch("py_piminusRot", &py_piminusRot, "py_piminusRot/F");
    piminusRotTree->Branch("pz_piminusRot", &pz_piminusRot, "pz_piminusRot/F");
    piminusRotTree->Branch("pt_piminusRot", &pt_piminusRot, "pt_piminusRot/F");

    //
    // Anti-hyperon side
    TTree *protonbarRotTree=new TTree("ProtonbarRot_LambdaRF","Protonbar in Lambda Rest Frame after rotation");
    Float_t protonbarRotPhi, protonbarRotCosTheta, protonbarRotTheta;
    Float_t m_protonbarRot, E_protonbarRot, p_protonbarRot, px_protonbarRot, py_protonbarRot, pz_protonbarRot, pt_protonbarRot;    //used in Tree Branch
    // Float_t m_protonbarRottest;
    protonbarRotTree->Branch("protonbarRotPhi", &protonbarRotPhi, "protonbarRotPhi/F");
    protonbarRotTree->Branch("protonbarRotCosTheta", &protonbarRotCosTheta, "protonbarRotCosTheta/F");
    protonbarRotTree->Branch("protonbarRotTheta", &protonbarRotTheta, "protonbarRotTheta/F");
    protonbarRotTree->Branch("m_protonbarRot", &m_protonbarRot, "m_protonbarRot/F");
    // protonbarRotTree->Branch("m_protonbarRottest", &m_protonbarRottest, "m_protonbarRottest/F");
    protonbarRotTree->Branch("E_protonbarRot", &E_protonbarRot, "E_protonbarRot/F");
    protonbarRotTree->Branch("p_protonbarRot", &p_protonbarRot, "p_protonbarRot/F");
    protonbarRotTree->Branch("px_protonbarRot", &px_protonbarRot, "px_protonbarRot/F");
    protonbarRotTree->Branch("py_protonbarRot", &py_protonbarRot, "py_protonbarRot/F");
    protonbarRotTree->Branch("pz_protonbarRot", &pz_protonbarRot, "pz_protonbarRot/F");
    protonbarRotTree->Branch("pt_protonbarRot", &pt_protonbarRot, "pt_protonbarRot/F");

    TTree *piplusRotTree=new TTree("PiplusRot_LambdaRF","PiplusRot in Lambda Rest Frame");
    Float_t piplusRotPhi, piplusRotCosTheta, piplusRotTheta;
    Float_t E_piplusRot, p_piplusRot, px_piplusRot, py_piplusRot, pz_piplusRot, pt_piplusRot;    //used in Tree Branch
    // Float_t m_piplusRottest;
    Float_t m_piplusRot;
    piplusRotTree->Branch("piplusRotPhi", &piplusRotPhi, "piplusRotPhi/F");
    piplusRotTree->Branch("piplusRotCosTheta", &piplusRotCosTheta, "piplusRotCosTheta/F");
    piplusRotTree->Branch("piplusRotTheta", &piplusRotTheta, "piplusRotTheta/F");
    piplusRotTree->Branch("m_piplusRot", &m_piplusRot, "m_piplusRot/F");
    // piplusRotTree->Branch("m_piplusRottest", &m_piplusRottest, "m_piplusRottest/F");
    piplusRotTree->Branch("E_piplusRot", &E_piplusRot, "E_piplusRot/F");
    piplusRotTree->Branch("p_piplusRot", &p_piplusRot, "p_piplusRot/F");
    piplusRotTree->Branch("px_piplusRot", &px_piplusRot, "px_piplusRot/F");
    piplusRotTree->Branch("py_piplusRot", &py_piplusRot, "py_piplusRot/F");
    piplusRotTree->Branch("pz_piplusRot", &pz_piplusRot, "pz_piplusRot/F");
    piplusRotTree->Branch("pt_piplusRot", &pt_piplusRot, "pt_piplusRot/F");

    //
    //
    ////////////////////////////////////////////////////////////////////////////////
    Float_t m_p=0.9383, m_pi=0.1396, m_lam=1.115, m_ome=1.672;   // Mass in GeV
    Float_t E_p, E_pi, E_lam;    // Energy in GeV
    Float_t p_p, p_pi, p_lam;    // Magnitude of 3-vector
    TStopwatch *st=new TStopwatch();
    st->Start();

    ////////////////////////////////////////
    // Lambda Rest frame related pre-computation
    //  (checked in April 2022)
    ////////////////////////////////////////
    p_p = (sqrt(pow((pow(m_lam,2)+pow(m_p,2)-pow(m_pi,2)),2)-4*pow(m_lam,2)*pow(m_p,2))) / (2*m_lam) ;  //proton's magnitute of momentum
    // cout << "Momentum magnitute of proton:" << p_p << endl;
    // E_p = (pow(m_lam,2)+pow(m_p,2)-pow(m_pi,2)) / (2*m_lam);  //proton's Energy
    E_p = sqrt(m_p*m_p + p_p*p_p); // MP: calculate proton energy from mass and momentum
    // cout << "Energy of proton:" << E_p << endl;
    // E_pi = (pow(m_lam,2)+pow(m_pi,2)-pow(m_p,2)) / (2*m_lam);  //piminus's Energy
    E_pi = sqrt(m_pi*m_pi + p_p*p_p); // MP: calculate pion energy from mass and momentum
    // cout << "Energy of piminus:" << E_pi << endl;
    p_pi = p_p;                                                //the same piminus's magnitute of momentum
    // cout << "Momentum magnitute of piminus:" << p_pi << endl;

    ////////////////////////////////////////
    // CM frame related pre-computation
    //  (checked in April 2022)
    ////////////////////////////////////////
    Float_t p_beam = 1.64;    //beam momentum in \pbarp lab frame using 1.64GeV
    Float_t E_pbarp;       //CM frame
    E_pbarp = sqrt(pow(m_p,2)+2*sqrt(pow(p_beam,2)+pow(m_p,2))*m_p+pow(m_p,2));
    E_lam = E_pbarp/2 ;
    // cout << "Energy of lambdaCM:" << E_lam << endl; 
    p_lam = sqrt(pow(E_lam,2)-pow(m_lam,2));
    Float_t gamma_lam, v_lam;
    gamma_lam = E_lam / m_lam; 
    v_lam = p_lam / E_lam;      // gamma_lam = 1/sqrt(1-pow(v_lam,2))

    Float_t beta_lam;
    beta_lam = sqrt(1-(1/(pow(gamma_lam,2))));

    Float_t tau_lam = 2.631E-10;    //mean life time

    TVector3 *v_p = new TVector3;                           // 3-momentum
    TVector3 *v_pi = new TVector3;                           // 3-momentum
    TLorentzVector *lv_p = new TLorentzVector;               // 4-momentum
    TLorentzVector *lv_pi = new TLorentzVector;               // 4-momentum
    TVector3 *v_l = new TVector3;                           // 3-momentum
    TLorentzVector *lv_l = new TLorentzVector;               // 4-momentum

    // add antihyperon side
    TVector3 *v_pbar = new TVector3;                           // 3-momentum
    TVector3 *v_piplus = new TVector3;                           // 3-momentum
    TLorentzVector *lv_pbar = new TLorentzVector;               // 4-momentum
    TLorentzVector *lv_piplus = new TLorentzVector;               // 4-momentum
    TVector3 *v_lbar = new TVector3;                           // 3-momentum
    TLorentzVector *lv_lbar = new TLorentzVector;               // 4-momentum

    // TLorentzVector lv_pi;     
    Float_t RadTheta , RadPhi;
    ////////////////////////////////////////////////////////////////////////////////
    // Generate random angles and corresponding physical poperty by the loop
    ////////////////////////////////////////////////////////////////////////////////
    for (Int_t i=0; i<nrEvents; i++) { 

        // // Hyperon side of LamRestFrame 
        // proton in LamRestFrame below     ///////////////////////////////
            //  (checked in April 2022)
        protonPhi = r3->Uniform(0,360);                        // Phi in degree
        protonCosTheta = r3->Uniform(-1,1);
        protonTheta = TMath::RadToDeg()*TMath::ACos(protonCosTheta); // Theta in degree
        RadTheta = TMath::DegToRad()*protonTheta;       // Theta in radian
        RadPhi = TMath::DegToRad()*protonPhi;           // Phi in radian
        v_p -> TVector3::SetMagThetaPhi(p_p,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        lv_p -> TLorentzVector::SetPxPyPzE(v_p->Px(),v_p->Py(),v_p->Pz(),E_p); 
        // lv_p.SetPxPyPzE(v_p->Px(),v_p->Py(),v_p->Pz(),E_p);
        // m_proton = lv_p.M();
        // m_protontest = m_p;
        m_proton = lv_p -> TLorentzVector::M(); 
        E_proton = lv_p -> TLorentzVector::E();
        // p_proton = p_p;
        p_proton = lv_p -> TLorentzVector::P();
        px_proton = lv_p -> TLorentzVector::Px();
        py_proton = lv_p -> TLorentzVector::Py();
        pz_proton = lv_p -> TLorentzVector::Pz();
        pt_proton = sqrt(pow(px_proton,2)+pow(py_proton,2));

        // piminus in LamRestFRame below    ////////////////////////////////// 
            //  (checked in April 2022)
        if (protonPhi <= 180) {
            piminusPhi = protonPhi + 180;                        // Phi in degree
        }
        else {
            piminusPhi = protonPhi - 180;                        // Phi in degree
        }
        piminusTheta = 180 - protonTheta;                       // Theta in degree        
        RadTheta = TMath::DegToRad()*piminusTheta;              // Theta in radian
        RadPhi = TMath::DegToRad()*piminusPhi;                  // Phi in radian
        piminusCosTheta = TMath::Cos(RadTheta);                 // Cos(Theta)
        v_pi -> TVector3::SetMagThetaPhi(p_pi,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        lv_pi -> TLorentzVector::SetPxPyPzE(v_pi->Px(),v_pi->Py(),v_pi->Pz(),E_pi); 
        // lv_pi.SetPxPyPzE(v_p->Px(),v_p->Py(),v_p->Pz(),E_pi);   
        // m_piminustest = m_pi;
        m_piminus = lv_pi -> TLorentzVector::M();                
        // Why it cannot show properly in Tree ?????? When I use double data type...
        // But it works when using float data type.
        // cout << "check Piminus m:" << m_piminus << endl; 
        E_piminus = lv_pi -> TLorentzVector::E();
        // p_piminus = p_pi;
        p_piminus = lv_pi -> TLorentzVector::P(); 
        px_piminus = lv_pi -> TLorentzVector::Px();
        py_piminus = lv_pi -> TLorentzVector::Py();
        pz_piminus = lv_pi -> TLorentzVector::Pz();
        pt_piminus = sqrt(pow(px_piminus,2)+pow(py_piminus,2));

        /////////////////////////////////////////
        // // Anti-hyperon side of LamRestFrame 
        // antiproton in LamRestFrame below     ///////////////////////////////
            //  (checked in April 2022)
        protonbarPhi = r3->Uniform(0,360);                        // Phi in degree
        protonbarCosTheta = r3->Uniform(-1,1);
        protonbarTheta = TMath::RadToDeg()*TMath::ACos(protonbarCosTheta); // Theta in degree
        RadTheta = TMath::DegToRad()*protonTheta;       // Theta in radian
        RadPhi = TMath::DegToRad()*protonPhi;           // Phi in radian
        v_pbar -> TVector3::SetMagThetaPhi(p_p,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        lv_pbar -> TLorentzVector::SetPxPyPzE(v_pbar->Px(),v_pbar->Py(),v_pbar->Pz(),E_p); 
        m_protonbar = lv_pbar -> TLorentzVector::M(); 
        E_protonbar = lv_pbar -> TLorentzVector::E();
        p_protonbar = lv_pbar -> TLorentzVector::P();
        px_protonbar = lv_pbar -> TLorentzVector::Px();
        py_protonbar = lv_pbar -> TLorentzVector::Py();
        pz_protonbar = lv_pbar -> TLorentzVector::Pz();
        pt_protonbar = sqrt(pow(px_protonbar,2)+pow(py_protonbar,2));

        // piplus in LamRestFRame below    ////////////////////////////////// 
            //  (checked in April 2022)
        if (protonbarPhi <= 180) {
            piplusPhi = protonbarPhi + 180;                        // Phi in degree
        }
        else {
            piplusPhi = protonbarPhi - 180;                        // Phi in degree
        }
        piplusTheta = 180 - protonbarTheta;                       // Theta in degree        
        RadTheta = TMath::DegToRad()*piplusTheta;              // Theta in radian
        RadPhi = TMath::DegToRad()*piplusPhi;                  // Phi in radian
        piplusCosTheta = TMath::Cos(RadTheta);                 // Cos(Theta)
        v_piplus -> TVector3::SetMagThetaPhi(p_pi,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        lv_piplus -> TLorentzVector::SetPxPyPzE(v_piplus->Px(),v_piplus->Py(),v_piplus->Pz(),E_pi); 
        // lv_pi.SetPxPyPzE(v_p->Px(),v_p->Py(),v_p->Pz(),E_pi);   
        // m_piminustest = m_pi;
        m_piplus = lv_piplus -> TLorentzVector::M();                
        // Why it cannot show properly in Tree ?????? When I use double data type...
        // But it works when using float data type.
        // cout << "check Piminus m:" << m_piminus << endl; 
        E_piplus = lv_piplus -> TLorentzVector::E();
        p_piplus = lv_piplus -> TLorentzVector::P();
        px_piplus = lv_piplus -> TLorentzVector::Px();
        py_piplus = lv_piplus -> TLorentzVector::Py();
        pz_piplus = lv_piplus -> TLorentzVector::Pz();
        pt_piplus = sqrt(pow(px_piplus,2)+pow(py_piplus,2));
        //////////////////////////////////////////

        /////////////////////////////////////////
        // pbarp CM frame
        // Float_t pbarPhiCM, pPhiCM, pbarCosThetaCM, pCosThetaCM,pbarThetaCM, pThetaCM; 
            //  (checked in April 2022)
        pPhiCM = r3->Uniform(0,360);   
        pCosThetaCM = r3->Uniform(-1,1);
        pThetaCM = TMath::RadToDeg()*TMath::ACos(pCosThetaCM); 
        if (pPhiCM <= 180) {
            pbarPhiCM = pPhiCM + 180;                        // Phi in degree
        }
        else {
            pbarPhiCM = pPhiCM - 180;                        // Phi in degree
        }
        pbarThetaCM = 180 - pThetaCM;  
        pbarCosThetaCM = TMath::Cos(TMath::DegToRad()*pbarThetaCM);

        /////////////////////////////////////////
        // // Hyperon side of pbarp CMframe 
        // Lambda in CMframe below    ////////////////////////////////// 

        // lambdaPhiCM = r3->Uniform(0,360);                        // Phi in degree
        lambdaPhiCM = pPhiCM;
        // lambdaCosThetaCM = r3->Uniform(-1,1);
        // lambdaThetaCM = TMath::RadToDeg()*TMath::ACos(lambdaCosThetaCM); // Theta in degree
        lambdaThetaCM = 0;
        lambdaCosThetaCM = TMath::Cos(lambdaThetaCM);

        RadTheta = TMath::DegToRad()*lambdaThetaCM;       // Theta in radian
        RadPhi = TMath::DegToRad()*lambdaPhiCM;           // Phi in radian
        v_l -> TVector3::SetMagThetaPhi(p_lam,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        lv_l -> TLorentzVector::SetPxPyPzE(v_l->Px(),v_l->Py(),v_l->Pz(),E_lam); 
        // m_lambda = lv_p.M();
        // m_lambdatest = m_p;
        // m_lambdaCM = m_lam;
        m_lambdaCM = lv_l -> TLorentzVector::M(); 
        E_lambdaCM = lv_l -> TLorentzVector::E();
        // E_lambdaCM = E_lam;
        p_lambdaCM = lv_l->P();
        px_lambdaCM = lv_l -> TLorentzVector::Px();
        py_lambdaCM = lv_l -> TLorentzVector::Py();
        pz_lambdaCM = lv_l -> TLorentzVector::Pz();
        pt_lambdaCM = sqrt(pow(px_lambdaCM,2)+pow(py_lambdaCM,2));
        ////////////////////////////////////////////////////////////////////i///
        // Lorentz Boost below 
        //(same plane (or phi) ideal situation, only theta considered, e.g. x-z plane but not necessary)  

        // 2 May 2022 update: 3D spherical coordinate r theta phi
        // Float_t p_protonX = p_p*TMath::Cos(TMath::DegToRad()*protonPhi)*TMath::Sin(TMath::DegToRad()*protonTheta);      
        // Float_t p_protonY = p_p*TMath::Sin(TMath::DegToRad()*protonPhi)*TMath::Sin(TMath::DegToRad()*protonTheta); 
        // Float_t p_protonZ = p_p*TMath::Cos(TMath::DegToRad()*protonTheta);    
        // MP: Re-calculating the momentum components that have already been generated is error prone
        // MP: Let's reuse the previous ones
        Float_t p_protonX = px_proton;
        Float_t p_protonY = py_proton;
        Float_t p_protonZ = pz_proton;

        Float_t p_piminusX = -p_protonX;
        Float_t p_piminusY = -p_protonY;
        Float_t p_piminusZ = -p_protonZ;

        // Lorentz Boost relation
        Float_t pb_protonX, pb_protonZ, pb_piminusX, pb_piminusZ;
        pb_protonX = p_protonX;
        pb_piminusX = p_piminusX;
        pb_protonZ = gamma_lam * (p_protonZ + v_lam * E_p);
        pb_piminusZ = gamma_lam * (p_piminusZ + v_lam * E_pi);
        // MP: One could have used the boost vector from ROOT here,
        // MP: but it should not make a difference
        // MP: Nevertheless, let's try out below
        TLorentzVector tmp_pCM, tmp_pimCM;
        tmp_pCM = *lv_p;
        tmp_pimCM = *lv_pi;
        tmp_pCM.Boost(-lv_l->BoostVector());
        tmp_pimCM.Boost(-lv_l->BoostVector());

        // Proton in CMframe below    ////////////////////////////////// 
        // Float_t proTheta = TMath::ATan(pb_protonX / pb_protonZ);
        // protonThetaCM = TMath::RadToDeg()*TMath::ATan(pb_protonX / pb_protonZ);
        // protonPhiCM = protonPhi;
        // protonCosThetaCM = TMath::Cos(proTheta);
        //protonThetaCM = tmp_pCM.Theta() ;

        protonThetaCM = tmp_pCM.Theta() * TMath::RadToDeg();
        protonPhiCM = tmp_pCM.Phi() * TMath::RadToDeg();
        protonCosThetaCM = tmp_pCM.CosTheta();

        // MP: Use the updated CM vectors to calculate angles
        RadTheta = TMath::DegToRad()*protonThetaCM;       // Theta in radian
        RadPhi = TMath::DegToRad()*protonPhiCM;           // Phi in radian

        // 2 May 2022 update
        // keep the 4-vector conservation
        // lorentz vector (lv) and p_p (3-vector magnitute)
        // lv_p^2 = E^2 - p_p^2 = m^2
        // since p_p the magnitute changes after boost, E_p also varies.
        // Float_t p_pCM = sqrt(pow(pb_protonX,2)+pow(p_protonY,2)+pow(pb_protonZ,2)); 
        Float_t p_pCM = tmp_pCM.P(); // MP: updated CM momentum

        // MP: Why are v_p and lv_p overwritten here?
        // MP: The resulting values for px, py are wrong (they should not change)
        // MP: Something must be going wrong here
        v_p -> TVector3::SetMagThetaPhi(p_pCM,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        // lv_p -> TLorentzVector::SetPxPyPzE(v_p->Px(),v_p->Py(),pb_protonZ,E_p); 
        Float_t E_pCM = sqrt(pow(m_p,2)+pow(p_pCM,2));
        lv_p -> TLorentzVector::SetPxPyPzE(v_p->Px(),v_p->Py(),v_p->Pz(),E_pCM); 

        // m_protonCM = lv_p -> TLorentzVector::M(); 
        // E_protonCM = lv_p -> TLorentzVector::E();
        // p_protonCM = lv_p -> TLorentzVector::P();
        // px_protonCM = lv_p -> TLorentzVector::Px();
        // py_protonCM = lv_p -> TLorentzVector::Py();
        // pz_protonCM = lv_p -> TLorentzVector::Pz();
        // pt_protonCM = sqrt(pow(px_protonCM,2)+pow(py_protonCM,2));

        // MP: Let's take the values from the new tmp_pCM
        m_protonCM = tmp_pCM.M(); 
        E_protonCM = tmp_pCM.E();
        p_protonCM = tmp_pCM.P();
        px_protonCM = tmp_pCM.Px();
        py_protonCM = tmp_pCM.Py();
        pz_protonCM = tmp_pCM.Pz();
        pt_protonCM = tmp_pCM.Pt();

        // Piminus in CMframe below    ////////////////////////////////// 
        Float_t pimTheta = TMath::ATan(pb_piminusX / pb_piminusZ);
        piminusThetaCM = TMath::RadToDeg()*TMath::ATan(pb_piminusX / pb_piminusZ);

        // 2 May 2022 update
        // minus value of theta degree can also be possible
        // if (piminusThetaCM < 0){
        //     piminusThetaCM = -piminusThetaCM;
        // }

        // piminusPhiCM = piminusPhi;
        // piminusCosThetaCM = TMath::Cos(pimTheta);
        // RadTheta = TMath::DegToRad()*piminusThetaCM;       // Theta in radian
        // RadPhi = TMath::DegToRad()*piminusPhi;           // Phi in radian

        // revised June
        piminusThetaCM = tmp_pimCM.Theta() * TMath::RadToDeg();
        piminusPhiCM = tmp_pimCM.Phi() * TMath::RadToDeg();
        piminusCosThetaCM = tmp_pimCM.CosTheta();

        // 2 May 2022 update
        // keep the 4-vector conservation
        // Float_t p_piCM = sqrt(pow(pb_piminusX,2)+pow(p_piminusY,2)+pow(pb_piminusZ,2)); 
        // v_pi -> TVector3::SetMagThetaPhi(p_piCM,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        // Float_t E_piCM = sqrt(pow(m_pi,2)+pow(p_piCM,2));
        // lv_pi -> TLorentzVector::SetPxPyPzE(v_pi->Px(),v_pi->Py(),v_pi->Pz(),E_piCM); 

        //revised June
        RadTheta = TMath::DegToRad()*piminusThetaCM;       // Theta in radian
        RadPhi = TMath::DegToRad()*piminusPhiCM;           // Phi in radian
        Float_t p_pimCM = tmp_pimCM.P();
        v_pi -> TVector3::SetMagThetaPhi(p_pimCM,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        Float_t E_pimCM = sqrt(pow(m_pi,2)+pow(p_pimCM,2));
        lv_pi -> TLorentzVector::SetPxPyPzE(v_pi->Px(),v_pi->Py(),v_pi->Pz(),E_pimCM); 

        m_piminusCM = lv_pi -> TLorentzVector::M(); 
        E_piminusCM = lv_pi -> TLorentzVector::E();
        p_piminusCM = lv_pi -> TLorentzVector::P();
        px_piminusCM = lv_pi -> TLorentzVector::Px();
        py_piminusCM = lv_pi -> TLorentzVector::Py();
        pz_piminusCM = lv_pi -> TLorentzVector::Pz();
        pt_piminusCM = sqrt(pow(px_piminusCM,2)+pow(py_piminusCM,2));

        /////////////////////////////////////////
        //////////////////////////////
        // // Anti-hyperon side of pbarp CMframe 
        // Lambdabar in CMframe below    ////////////////////////////////// 

        if (lambdaPhiCM <= 180) {
            lambdabarPhiCM = lambdaPhiCM + 180;                        // Phi in degree
        }
        else {
            lambdabarPhiCM = lambdaPhiCM - 180;                        // Phi in degree
        }
        // lambdabarThetaCM = 180 - lambdaThetaCM;                       // Theta in degree  
        lambdabarThetaCM = 180;

        RadTheta = TMath::DegToRad()*lambdabarThetaCM;       // Theta in radian
        RadPhi = TMath::DegToRad()*lambdabarPhiCM;           // Phi in radian
        lambdabarCosThetaCM = TMath::Cos(RadTheta);
        v_lbar -> TVector3::SetMagThetaPhi(p_lam,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        lv_lbar -> TLorentzVector::SetPxPyPzE(v_lbar->Px(),v_lbar->Py(),v_lbar->Pz(),E_lam); 
        // m_lambdabarCM = m_lam;
        m_lambdabarCM = lv_lbar -> TLorentzVector::M(); 
        E_lambdabarCM = lv_lbar -> TLorentzVector::E();
        // E_lambdabarCM = E_lam;
        p_lambdabarCM = lv_lbar->P();
        px_lambdabarCM = lv_lbar -> TLorentzVector::Px();
        py_lambdabarCM = lv_lbar -> TLorentzVector::Py();
        pz_lambdabarCM = lv_lbar -> TLorentzVector::Pz();
        pt_lambdabarCM = sqrt(pow(px_lambdabarCM,2)+pow(py_lambdabarCM,2));
        ////////////////////////////////////////////////////////////////////i///

        // 2 May 2022 update
        // Lorentz Boost below (same phi's plane ideal situation only theta changed considering)   
        // Float_t p_protonbarX = p_p*TMath::Cos(TMath::DegToRad()*protonbarPhi)*TMath::Sin(TMath::DegToRad()*protonbarTheta);      
        // Float_t p_protonbarY = p_p*TMath::Sin(TMath::DegToRad()*protonbarPhi)*TMath::Sin(TMath::DegToRad()*protonbarTheta);      
        // Float_t p_protonbarZ = p_p*TMath::Cos(TMath::DegToRad()*protonbarTheta);      

        //revised June
        Float_t p_protonbarX = px_protonbar;
        Float_t p_protonbarY = py_protonbar;
        Float_t p_protonbarZ = pz_protonbar;

        Float_t p_piplusX = -p_protonbarX;
        Float_t p_piplusY = -p_protonbarY;
        Float_t p_piplusZ = -p_protonbarZ;
        
        // Lorentz Boost relation
        Float_t pb_protonbarX, pb_protonbarZ, pb_piplusX, pb_piplusZ;
        pb_protonbarX = p_protonbarX;
        pb_piplusX = p_piplusX;
        pb_protonbarZ = gamma_lam * (p_protonbarZ + v_lam * E_p);
        pb_piplusZ = gamma_lam * (p_piplusZ + v_lam * E_pi);

        //revised June
        TLorentzVector tmp_pbarCM, tmp_pipCM;
        tmp_pbarCM = *lv_pbar;
        tmp_pipCM = *lv_piplus;
        tmp_pbarCM.Boost(-lv_lbar->BoostVector());
        tmp_pipCM.Boost(-lv_lbar->BoostVector());
        
        // Protonbar in CMframe below    ////////////////////////////////// 
        Float_t probarTheta = TMath::ATan(pb_protonbarX / pb_protonbarZ);
        
        // 26 Feb updated
        // the angles represent the other direction compare to hyperon side
        // protonbarThetaCM = 180 - TMath::RadToDeg()*TMath::ATan(pb_protonbarX / pb_protonbarZ);
        // protonbarPhiCM = protonbarPhi;
        // protonbarCosThetaCM = TMath::Cos(protonbarThetaCM*TMath::DegToRad());

        //revised June
        protonbarThetaCM = tmp_pbarCM.Theta() * TMath::RadToDeg();
        protonbarPhiCM = tmp_pbarCM.Phi() * TMath::RadToDeg();
        protonbarCosThetaCM = tmp_pbarCM.CosTheta();

        RadTheta = TMath::DegToRad()*protonbarThetaCM;       // Theta in radian
        RadPhi = TMath::DegToRad()*protonbarPhiCM;           // Phi in radian

        Float_t p_pbarCM = tmp_pbarCM.P();
        Float_t E_pbarCM = sqrt(pow(m_p,2)+pow(p_pbarCM,2));

        // 2 May 2022 update
        // Float_t p_pCM = sqrt(pow(pb_protonX,2)+pow(p_protonY,2)+pow(pb_protonZ,2)); 
        v_pbar -> TVector3::SetMagThetaPhi(p_pbarCM,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        // Float_t E_pCM = sqrt(pow(m_p,2)+pow(p_pCM,2));
        lv_pbar -> TLorentzVector::SetPxPyPzE(v_p->Px(),v_p->Py(),v_p->Pz(),E_pbarCM); 

        // m_protonbarCM = lv_p -> TLorentzVector::M(); 
        // E_protonbarCM = lv_p -> TLorentzVector::E();
        // p_protonbarCM = lv_p -> TLorentzVector::P();
        // px_protonbarCM = lv_p -> TLorentzVector::Px();
        // py_protonbarCM = lv_p -> TLorentzVector::Py();
        // pz_protonbarCM = lv_p -> TLorentzVector::Pz();

        //revised June
        m_protonbarCM = tmp_pbarCM.M(); 
        E_protonbarCM = tmp_pbarCM.E();
        p_protonbarCM = tmp_pbarCM.P();
        px_protonbarCM = tmp_pbarCM.Px();
        py_protonbarCM = tmp_pbarCM.Py();
        pz_protonbarCM = tmp_pbarCM.Pz();
        pt_protonbarCM = tmp_pbarCM.Pt();

        pt_protonbarCM = sqrt(pow(px_protonbarCM,2)+pow(py_protonbarCM,2));

        // Piplus in CMframe below    ////////////////////////////////// 
        Float_t pipTheta = TMath::ATan(pb_piplusX / pb_piplusZ);
        piplusThetaCM = TMath::RadToDeg()*TMath::ATan(pb_piplusX / pb_piplusZ);

        // 2 May 2022 update
        // minus value of theta degree can also be possible
        // if (piplusThetaCM < 0){
        //     piplusThetaCM = -piplusThetaCM;
        // }

        // 26 Feb updated
        // the angles represent the other direction compare to hyperon side
        // piplusThetaCM = 180 -  piplusThetaCM; 
        // piplusPhiCM = piplusPhi;
        // piplusCosThetaCM = TMath::Cos( piplusThetaCM*TMath::DegToRad());
        //

        // revised June
        piplusThetaCM = tmp_pipCM.Theta() * TMath::RadToDeg();
        piplusPhiCM = tmp_pipCM.Phi() * TMath::RadToDeg();
        piplusCosThetaCM = tmp_pipCM.CosTheta(); 
        RadTheta = TMath::DegToRad()*piplusThetaCM;       // Theta in radian
        RadPhi = TMath::DegToRad()*piplusPhiCM;           // Phi in radian

        // 2 May 2022 update
        // Float_t p_piCM = sqrt(pow(pb_piminusX,2)+pow(p_piminusY,2)+pow(pb_piminusZ,2)); 
        // v_piplus -> TVector3::SetMagThetaPhi(p_piCM,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        // Float_t E_piCM = sqrt(pow(m_pi,2)+pow(p_piCM,2));
        // lv_piplus -> TLorentzVector::SetPxPyPzE(v_piplus->Px(),v_piplus->Py(),v_piplus->Pz(),E_piCM); 

        // revised June
        Float_t p_pipCM = tmp_pipCM.P();
        v_piplus -> TVector3::SetMagThetaPhi(p_pipCM,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        Float_t E_pipCM = sqrt(pow(m_pi,2)+pow(p_pipCM,2));
        lv_piplus -> TLorentzVector::SetPxPyPzE(v_piplus->Px(),v_piplus->Py(),v_piplus->Pz(),E_pipCM); 

        m_piplusCM = lv_piplus -> TLorentzVector::M(); 
        E_piplusCM = lv_piplus -> TLorentzVector::E();
        p_piplusCM = lv_piplus -> TLorentzVector::P();
        px_piplusCM = lv_piplus -> TLorentzVector::Px();
        py_piplusCM = lv_piplus -> TLorentzVector::Py();
        pz_piplusCM = lv_piplus -> TLorentzVector::Pz();
        pt_piplusCM = sqrt(pow(px_piplusCM,2)+pow(py_piplusCM,2));

        // // //
        //////////////////////////////////////////////////////////
        // // Rotation !!
        // // lambdaCMrot       // verify?

        // Float_t rotAxisPhi, rotAxisTheta;
        // if (pThetaCM < 90){
        //     rotAxisTheta = TMath::DegToRad()*pThetaCM + TMath::Pi()/2; 
        // }
        // else {
        //     rotAxisTheta = TMath::DegToRad()*pThetaCM - TMath::Pi()/2; 
        // }

        // rotAxisPhi = lambdaPhiCM;
        // TVector3 rotAxis;
        // rotAxis.SetMagThetaPhi(p_lam,rotAxisTheta,rotAxisPhi);
        // TLorentzRotation lR;
        // if (pTheta <= 90) {
        //     lR.Rotate(-*TMath::DegToRad()*pThetaCM,rotAxis);
        // }
        // else {
        //     lR.Rotate(*TMath::DegToRad()*pThetaCM,rotAxis);
        // }

        // can be reused below
        // lR.Rotate(TMath::DegToRad()*pThetaCM,rotAxis);   // rot +theta
        // TLorentzVector lv_lamRotCM;
        // lv_lamRotCM.SetPxPyPzE(px_lambdaCM,py_lambdaCM,pz_lambdaCM,E_lambdaCM);
        // lv_lamRotCM = lR * lv_lamRotCM;

        // lambdaPhiCMrot = lambdaPhiCM //= r3->Uniform(0,360);                        // Phi in degree
        // // lambdaCosThetaCM = r3->Uniform(-1,1);
        // lambdaThetaCMrot = 0 - lambdaThetaCM  //= TMath::RadToDeg()*TMath::ACos(lambdaCosThetaCM); // Theta in degree
        // RadTheta = TMath::DegToRad()*lambdaThetaCM;       // Theta in radian
        // RadPhi = TMath::DegToRad()*lambdaPhiCM;           // Phi in radian
        // v_l -> TVector3::SetMagThetaPhi(p_lam,RadTheta,RadPhi);     // set momentum component by mag,theta,phi
        // lv_l -> TLorentzVector::SetPxPyPzE(v_l->Px(),v_l->Py(),v_l->Pz(),E_p);

        // lambdaPhiCMrot = TMath::RadToDeg()*lv_lamRotCM.Phi();
        // lambdaThetaCMrot = TMath::RadToDeg()*lv_lamRotCM.Theta(); 
        // lambdaCosThetaCMrot = TMath::Cos(TMath::DegToRad()*lambdaThetaCMrot);

        //**************************************
        // 29 Jan 2021 added
        // rotation of lambda CM update below
        // by finding new pxpypz from new angles
        px_lambdaCMrot = p_lam * TMath::Cos(TMath::DegToRad()*lambdaPhiCM) * TMath::Sin(TMath::DegToRad()*lambdaThetaCM+TMath::DegToRad()*pThetaCM);
        py_lambdaCMrot = p_lam * TMath::Sin(TMath::DegToRad()*lambdaPhiCM) * TMath::Sin(TMath::DegToRad()*lambdaThetaCM+TMath::DegToRad()*pThetaCM);
        pz_lambdaCMrot = p_lam * TMath::Cos(TMath::DegToRad()*lambdaThetaCM+TMath::DegToRad()*pThetaCM);        

        lv_l -> TLorentzVector::SetPxPyPzE(px_lambdaCMrot,py_lambdaCMrot,pz_lambdaCMrot,E_lam);         
        lambdaPhiCMrot = lv_l -> TLorentzVector::Phi()*TMath::RadToDeg();
        lambdaThetaCMrot = lv_l -> TLorentzVector::Theta()*TMath::RadToDeg();
        lambdaCosThetaCMrot = lv_l -> TLorentzVector::CosTheta();
        m_lambdaCMrot = lv_l -> TLorentzVector::M(); 
        E_lambdaCMrot = lv_l -> TLorentzVector::E();
        p_lambdaCMrot = lv_l->P();
        pt_lambdaCMrot = sqrt(pow(px_lambdaCMrot,2)+pow(py_lambdaCMrot,2));

        // lv_l -> TLorentzVector::SetPxPyPzE(lv_lamRotCM.Px(),lv_lamRotCM.Py(),lv_lamRotCM.Pz(),lv_lamRotCM.E()); 
        
        // m_lambdaCMrot = lv_l -> TLorentzVector::M(); 
        // E_lambdaCMrot = lv_l -> TLorentzVector::E();
        // // E_lambdaCM = E_lam;
        // p_lambdaCMrot = lv_l->P();
        // px_lambdaCMrot = lv_l -> TLorentzVector::Px();
        // py_lambdaCMrot = lv_l -> TLorentzVector::Py();
        // pz_lambdaCMrot = lv_l -> TLorentzVector::Pz();
        // pt_lambdaCMrot = sqrt(pow(px_lambdaCMrot,2)+pow(py_lambdaCMrot,2));

        //
        // // Rotation !!
        // // lambdabarCMrot    //verify?
        // lR.Rotate(-TMath::DegToRad()*pbarThetaCM,rotAxis);   // rot -theta
        // TLorentzVector lv_lambarRotCM;
        // lv_lambarRotCM.SetPxPyPzE(px_lambdabarCM,py_lambdabarCM,pz_lambdabarCM,E_lambdabarCM);
        // lv_lambarRotCM = lR * lv_lambarRotCM;

        // lambdabarPhiCMrot = TMath::RadToDeg()*lv_lambarRotCM.Phi();
        // lambdabarThetaCMrot = TMath::RadToDeg()*lv_lambarRotCM.Theta(); 
        // lambdabarCosThetaCMrot = TMath::Cos(TMath::DegToRad()*lambdabarThetaCMrot);

        //**************************************
        // 29 Jan 2021 added
        // Rotation of lambdabar CM update below
        // by finding new pxpypz from new angles
        px_lambdabarCMrot = p_lam * TMath::Cos(TMath::DegToRad()*lambdabarPhiCM) * TMath::Sin(TMath::DegToRad()*lambdabarThetaCM-TMath::DegToRad()*pThetaCM);
        py_lambdabarCMrot = p_lam * TMath::Sin(TMath::DegToRad()*lambdabarPhiCM) * TMath::Sin(TMath::DegToRad()*lambdabarThetaCM-TMath::DegToRad()*pThetaCM);
        pz_lambdabarCMrot = p_lam * TMath::Cos(TMath::DegToRad()*lambdabarThetaCM-TMath::DegToRad()*pThetaCM);        

        lv_lbar -> TLorentzVector::SetPxPyPzE(px_lambdabarCMrot,py_lambdabarCMrot,pz_lambdabarCMrot,E_lam);         
        lambdabarPhiCMrot = lv_lbar -> TLorentzVector::Phi()*TMath::RadToDeg();
        lambdabarThetaCMrot = lv_lbar -> TLorentzVector::Theta()*TMath::RadToDeg();
        lambdabarCosThetaCMrot = lv_lbar -> TLorentzVector::CosTheta();
        m_lambdabarCMrot = lv_lbar -> TLorentzVector::M(); 
        E_lambdabarCMrot = lv_lbar -> TLorentzVector::E();
        p_lambdabarCMrot = lv_lbar->P();
        pt_lambdabarCMrot = sqrt(pow(px_lambdabarCMrot,2)+pow(py_lambdabarCMrot,2));

        // lv_l -> TLorentzVector::SetPxPyPzE(lv_lambarRotCM.Px(),lv_lambarRotCM.Py(),lv_lambarRotCM.Pz(),lv_lambarRotCM.E()); 

        // m_lambdabarCMrot = lv_l -> TLorentzVector::M(); 
        // E_lambdabarCMrot = lv_l -> TLorentzVector::E();
        // p_lambdabarCMrot = lv_l->P();
        // px_lambdabarCMrot = lv_l -> TLorentzVector::Px();
        // py_lambdabarCMrot = lv_l -> TLorentzVector::Py();
        // pz_lambdabarCMrot = lv_l -> TLorentzVector::Pz();
        // pt_lambdabarCMrot = sqrt(pow(px_lambdabarCMrot,2)+pow(py_lambdabarCMrot,2));

        /////////////////////////////////////////////////////////////////////////////
        // // Rotation !!
        // // protonCMrot
        // Float_t rotAxisPhiHyperon, rotAxisThetaHyperon;
        // rotAxisPhiHyperon = TMath::DegToRad()*protonPhi;
        // if (protonThetaCM < 90){
        //     rotAxisThetaHyperon = TMath::DegToRad()*protonThetaCM + TMath::Pi()/2;
        // }
        // else {
        //     rotAxisThetaHyperon = TMath::DegToRad()*protonThetaCM - TMath::Pi()/2;
        // }
        // TVector3 rotAxisHyperon;
        // rotAxisHyperon.SetMagThetaPhi(p_p,rotAxisThetaHyperon,rotAxisPhiHyperon);
        
        // // can be reused below
        // TLorentzRotation lR_hyperon; 
        // lR_hyperon.Rotate(TMath::DegToRad()*protonThetaCM,rotAxisHyperon);   

        // TLorentzVector lv_proRotCM;
        // lv_proRotCM.SetPxPyPzE(px_protonCM,py_protonCM,pz_protonCM,E_protonCM);
        // lv_proRotCM = lR_hyperon * lv_proRotCM;

        // protonPhiCMrot = TMath::RadToDeg()*lv_proRotCM.Phi();
        // protonThetaCMrot = TMath::RadToDeg()*lv_proRotCM.Theta(); 
        // protonCosThetaCMrot = TMath::Cos(TMath::DegToRad()*protonThetaCMrot);

        //**************************************
        // 29 Jan 2021 added
        // Rotation of proton CM update below
        // by finding new pxpypz from new angles 

        Float_t Phi_HyperonNew;

        if (pPhiCM >=0 && pPhiCM <=180){
            Phi_HyperonNew = pPhiCM - 90;
        }    
        if (pPhiCM >180 && pPhiCM <=360){
            Phi_HyperonNew = pPhiCM - 270;
        }

        Float_t Phi_pUse;
        Phi_pUse = protonPhiCM + Phi_HyperonNew;

        if (Phi_pUse > 360){
            Phi_pUse = Phi_pUse - 360;
        }
        if (Phi_pUse < 0){
            Phi_pUse = Phi_pUse + 360;
        }

        Float_t Theta_pUseCM;
        Theta_pUseCM = protonThetaCM + pThetaCM; 


        if (Theta_pUseCM < 0){
            Theta_pUseCM = -Theta_pUseCM;
        }        
        if (Theta_pUseCM > 180){
            Theta_pUseCM = 360 - Theta_pUseCM;
        }

        //2 May 2022 update p_p to p_pCM
        // px_protonCMrot = p_pCM * TMath::Cos(TMath::DegToRad()*Phi_pUse) * TMath::Sin(TMath::DegToRad()*Theta_pUseCM);
        // py_protonCMrot = p_pCM * TMath::Sin(TMath::DegToRad()*Phi_pUse) * TMath::Sin(TMath::DegToRad()*Theta_pUseCM);
        // pz_protonCMrot = p_pCM * TMath::Cos(TMath::DegToRad()*Theta_pUseCM);

        // MP: Take angles from tmp_pCM and try different rotation
        // TVector3 tmp_p3CMRot;
        TLorentzVector tmp_pCMRot = tmp_pCM;
        // tmp_p3CMRot.SetPtThetaPhi(tmp_pCM.P(), Theta_pUseCM * TMath::DegToRad(), Phi_pUse * TMath::DegToRad());
        tmp_pCMRot.RotateX(lv_l->Theta());
        tmp_pCMRot.RotateZ(lv_l->Phi());
        // tmp_p3CMRot.Print();
        px_protonCMrot = tmp_pCMRot.Px();
        py_protonCMrot = tmp_pCMRot.Py();
        pz_protonCMrot = tmp_pCMRot.Pz();
        // cout << px_protonCMrot << " " << py_protonCMrot << " " << pz_protonCMrot << endl;
        // TLorentzVector tmp_pCMRot(tmp_p3CMRot,sqrt(m_p*m_p + tmp_pCM.P()*tmp_pCM.P()));
        // tmp_pCMRot.Print();

        //2 May 2022 update E_p to E_pCM 
        // lv_p -> TLorentzVector::SetPxPyPzE(lv_proRotCM.Px(),lv_proRotCM.Py(),lv_proRotCM.Pz(),lv_proRotCM.E()); 
        lv_p -> TLorentzVector::SetPxPyPzE(px_protonCMrot,py_protonCMrot,pz_protonCMrot,E_pCM); 

        // protonPhiCMrot = lv_p -> TLorentzVector::Phi() * TMath::RadToDeg();
        // protonThetaCMrot = lv_p -> TLorentzVector::Theta() * TMath::RadToDeg();
        // protonCosThetaCMrot = lv_p -> TLorentzVector::CosTheta();

        // m_protonCMrot = lv_p -> TLorentzVector::M(); 
        // E_protonCMrot = lv_p -> TLorentzVector::E();
        // p_protonCMrot = lv_p->P();
        // pt_protonCMrot = sqrt(pow(px_protonCMrot,2)+pow(py_protonCMrot,2));

        protonPhiCMrot = tmp_pCMRot.Phi() * TMath::RadToDeg();
        protonThetaCMrot = tmp_pCMRot.Theta() * TMath::RadToDeg();
        protonCosThetaCMrot = tmp_pCMRot.CosTheta();

        m_protonCMrot = tmp_pCMRot.M(); 
        E_protonCMrot = tmp_pCMRot.E();
        p_protonCMrot = tmp_pCMRot.P();
        pt_protonCMrot = tmp_pCMRot.Pt();


        // // Rotation !!
        // // piminusCMrot
        // lR_hyperon.Rotate(TMath::DegToRad()*piminusThetaCM,rotAxisHyperon);   

        // TLorentzVector lv_pimRotCM;
        // lv_pimRotCM.SetPxPyPzE(px_piminusCM,py_piminusCM,pz_piminusCM,E_piminusCM);
        // lv_pimRotCM = lR_hyperon * lv_pimRotCM;

        // piminusPhiCMrot = TMath::RadToDeg()*lv_pimRotCM.Phi();
        // piminusThetaCMrot = TMath::RadToDeg()*lv_pimRotCM.Theta(); 
        // piminusCosThetaCMrot = TMath::Cos(TMath::DegToRad()*piminusThetaCMrot);

        //**************************************
        // 29 Jan 2021 added
        // Rotation of piminus CM update below
        // by finding new pxpypz from new angles 

        Float_t Phi_piminusUse;
        Phi_piminusUse = piminusPhiCM + Phi_HyperonNew;

        if (Phi_piminusUse > 360){
            Phi_piminusUse = Phi_piminusUse - 360;
        }
        if (Phi_piminusUse < 0){
            Phi_piminusUse = Phi_piminusUse + 360;
        }
        
        Float_t Theta_piminusUseCM;
        Theta_piminusUseCM = piminusThetaCM + pThetaCM; 

        if (Theta_piminusUseCM < 0){
            Theta_piminusUseCM = -Theta_piminusUseCM;
        }        
        if (Theta_piminusUseCM > 180){
            Theta_piminusUseCM = 360 - Theta_piminusUseCM;
        }

        // 2 May 2022 update p_pi to p_piCM
        // px_piminusCMrot = p_piCM * TMath::Cos(TMath::DegToRad()*Phi_piminusUse) * TMath::Sin(TMath::DegToRad()*Theta_piminusUseCM);
        // py_piminusCMrot = p_piCM * TMath::Sin(TMath::DegToRad()*Phi_piminusUse) * TMath::Sin(TMath::DegToRad()*Theta_piminusUseCM);
        // pz_piminusCMrot = p_piCM * TMath::Cos(TMath::DegToRad()*Theta_piminusUseCM);

        // Revised June
        // Take angles from tmp_pimCM and try different rotation
        TLorentzVector tmp_pimCMRot = tmp_pimCM;
        // tmp_p3CMRot.SetPtThetaPhi(tmp_pCM.P(), Theta_pUseCM * TMath::DegToRad(), Phi_pUse * TMath::DegToRad());
        tmp_pimCMRot.RotateX(lv_l->Theta());
        tmp_pimCMRot.RotateZ(lv_l->Phi());
        // tmp_p3CMRot.Print();
        px_piminusCMrot = tmp_pimCMRot.Px();
        py_piminusCMrot = tmp_pimCMRot.Py();
        pz_piminusCMrot = tmp_pimCMRot.Pz();

        // 2 May 2022 update E_pi to E_piCM
        // lv_p -> TLorentzVector::SetPxPyPzE(lv_proRotCM.Px(),lv_proRotCM.Py(),lv_proRotCM.Pz(),lv_proRotCM.E()); 
        lv_pi -> TLorentzVector::SetPxPyPzE(px_piminusCMrot,py_piminusCMrot,pz_piminusCMrot,E_pimCM); 

        piminusPhiCMrot = lv_pi -> TLorentzVector::Phi() * TMath::RadToDeg();
        piminusThetaCMrot = lv_pi -> TLorentzVector::Theta() * TMath::RadToDeg();
        piminusCosThetaCMrot = lv_pi -> TLorentzVector::CosTheta();

        m_piminusCMrot = lv_pi -> TLorentzVector::M(); 
        E_piminusCMrot = lv_pi -> TLorentzVector::E();
        p_piminusCMrot = lv_pi->P();
        pt_piminusCMrot = sqrt(pow(px_piminusCMrot,2)+pow(py_piminusCMrot,2));


        // // Rotation !!
        // // protonRot
        // // Lambda rest frame
        //**************************************
        // 29 Jan 2021 added
        // Rotation of proton in lambda rest frame update below
        // by finding new pxpypz from new angles

        // 26 Feb 2021 updated
        // After rotation of particles in CM frame
        // Should not also rotate particles in hyperon rest frame
        // One should do the Lorentz boost in the other way around instead! 

        //  
        Float_t Theta_pUse;
        //
        // Theta_pUse = protonTheta + pThetaCM;    //This is the problem
        // since pThetaCM is the rotational angle in CM 
        // but not necessarily the same in lambda Rest Frame...

        // px_protonCMrot remains
        // find the pz_protonCMrot
        // pb_protonZ = gamma_lam * (p_protonZ + v_lam * E_p);  //recall

        Float_t pz_protonRotnew;
        pz_protonRotnew = (pz_protonCMrot / gamma_lam) - (v_lam * E_p); 

        Theta_pUse = TMath::ATan(px_protonCMrot / pz_protonRotnew) * TMath::RadToDeg();

        if (Theta_pUse < 0){
            Theta_pUse = -Theta_pUse;
        }        
        if (Theta_pUse > 180){
            Theta_pUse = 360 - Theta_pUse;
        }

        // px_protonRot = p_p * TMath::Cos(TMath::DegToRad()*Phi_pUse) * TMath::Sin(TMath::DegToRad()*Theta_pUse);
        // py_protonRot = p_p * TMath::Sin(TMath::DegToRad()*Phi_pUse) * TMath::Sin(TMath::DegToRad()*Theta_pUse);
        // pz_protonRot = p_p * TMath::Cos(TMath::DegToRad()*Theta_pUse);

        //revised June
        TLorentzVector tmp_p, tmp_pim;
        tmp_p = *lv_p;
        tmp_pim = *lv_pi;
        tmp_p.Boost(lv_l->BoostVector());
        tmp_pim.Boost(lv_l->BoostVector());

        px_protonRot = tmp_p.Px();
        py_protonRot = tmp_p.Py();
        pz_protonRot = tmp_p.Pz();

        lv_p -> TLorentzVector::SetPxPyPzE(px_protonRot,py_protonRot,pz_protonRot,E_p); 

        protonRotPhi = lv_p -> TLorentzVector::Phi() * TMath::RadToDeg();
        protonRotTheta = lv_p -> TLorentzVector::Theta() * TMath::RadToDeg();
        protonRotCosTheta = lv_p -> TLorentzVector::CosTheta();

        m_protonRot = lv_p -> TLorentzVector::M(); 
        E_protonRot = lv_p -> TLorentzVector::E();
        p_protonRot = lv_p->P();
        pt_protonRot = sqrt(pow(px_protonRot,2)+pow(py_protonRot,2));

        // lR_hyperon.Rotate(TMath::DegToRad()*protonTheta,rotAxisHyperon);   

        // TLorentzVector lv_proRot;
        // lv_proRot.SetPxPyPzE(px_proton,py_proton,pz_proton,E_proton);
        // lv_proRot = lR_hyperon * lv_proRot;

        // protonRotPhi = TMath::RadToDeg()*lv_proRot.Phi();
        // protonRotTheta = TMath::RadToDeg()*lv_proRot.Theta(); 
        // protonRotCosTheta = TMath::Cos(TMath::DegToRad()*protonRotTheta);

        // lv_p -> TLorentzVector::SetPxPyPzE(lv_proRot.Px(),lv_proRot.Py(),lv_proRot.Pz(),lv_proRot.E()); 

        // m_protonRot = lv_p -> TLorentzVector::M(); 
        // E_protonRot = lv_p -> TLorentzVector::E();
        // p_protonRot = lv_p->P();
        // px_protonRot = lv_p -> TLorentzVector::Px();
        // py_protonRot = lv_p -> TLorentzVector::Py();
        // pz_protonRot = lv_p -> TLorentzVector::Pz();
        // pt_protonRot = sqrt(pow(px_protonRot,2)+pow(py_protonRot,2));


        // // Rotation !!
        // // piminusRot

        //**************************************
        // 29 Jan 2021 added
        // Rotation of piminus in lambda rest frame update below
        // by finding new pxpypz from new angles

        // 26 Feb 2021 updated
        // After rotation of particles in CM frame
        // Should not also rotate particles in hyperon rest frame
        // One should do the Lorentz boost in the other way around instead! 

        Float_t Theta_piminusUse;
        // Theta_piminusUse = piminusTheta + pThetaCM;  //not this

        // px_piminusCMrot remains
        // find the pz_piminusCMrot
        // pb_piminusZ = gamma_lam * (p_piminusZ + v_lam * E_pi);   //recall

        Float_t pz_piminusRotnew;
        pz_piminusRotnew = (pz_piminusCMrot / gamma_lam) - (v_lam * E_pi); 

        Theta_piminusUse = TMath::ATan(px_piminusCMrot / pz_piminusRotnew)* TMath::RadToDeg();

        if (Theta_piminusUse < 0){
            Theta_piminusUse = -Theta_piminusUse;
        }        
        if (Theta_piminusUse > 180){
            Theta_piminusUse = 360 - Theta_piminusUse;
        }

        // //revised June
        // TLorentzVector tmp_p, tmp_pim;
        // tmp_p = *lv_p;
        // tmp_pim = *lv_pi;
        // tmp_p.Boost(lv_l->BoostVector());
        // tmp_pim.Boost(lv_l->BoostVector());
        px_piminusRot = tmp_pim.Px();
        py_piminusRot = tmp_pim.Py();
        pz_piminusRot = tmp_pim.Pz();

        // px_piminusRot = p_pi * TMath::Cos(TMath::DegToRad()*Phi_piminusUse) * TMath::Sin(TMath::DegToRad()*Theta_piminusUse);
        // py_piminusRot = p_pi * TMath::Sin(TMath::DegToRad()*Phi_piminusUse) * TMath::Sin(TMath::DegToRad()*Theta_piminusUse);
        // pz_piminusRot = p_pi * TMath::Cos(TMath::DegToRad()*Theta_piminusUse);

        // lv_p -> TLorentzVector::SetPxPyPzE(lv_proRotCM.Px(),lv_proRotCM.Py(),lv_proRotCM.Pz(),lv_proRotCM.E()); 
        
        lv_pi -> TLorentzVector::SetPxPyPzE(px_piminusRot,py_piminusRot,pz_piminusRot,E_pi); 

        piminusRotPhi = lv_pi -> TLorentzVector::Phi() * TMath::RadToDeg();
        piminusRotTheta = lv_pi -> TLorentzVector::Theta() * TMath::RadToDeg();
        piminusRotCosTheta = lv_pi -> TLorentzVector::CosTheta();

        m_piminusRot = lv_pi -> TLorentzVector::M(); 
        E_piminusRot = lv_pi -> TLorentzVector::E();
        p_piminusRot = lv_pi->P();
        pt_piminusRot = sqrt(pow(px_piminusRot,2)+pow(py_piminusRot,2));


        // lR_hyperon.Rotate(TMath::DegToRad()*piminusTheta,rotAxisHyperon);   

        // TLorentzVector lv_pimRot;
        // lv_pimRot.SetPxPyPzE(px_piminus,py_piminus,pz_piminus,E_piminus);
        // lv_pimRot = lR_hyperon * lv_pimRot;

        // piminusRotPhi = TMath::RadToDeg()*lv_pimRot.Phi();
        // piminusRotTheta = TMath::RadToDeg()*lv_pimRot.Theta(); 
        // piminusRotCosTheta = TMath::Cos(TMath::DegToRad()*piminusRotTheta);

        // lv_pi -> TLorentzVector::SetPxPyPzE(lv_pimRot.Px(),lv_pimRot.Py(),lv_pimRot.Pz(),lv_pimRot.E()); 

        // m_piminusRot = lv_pi -> TLorentzVector::M(); 
        // E_piminusRot = lv_pi -> TLorentzVector::E();
        // p_piminusRot = lv_pi->P();
        // px_piminusRot = lv_pi -> TLorentzVector::Px();
        // py_piminusRot = lv_pi -> TLorentzVector::Py();
        // pz_piminusRot = lv_pi -> TLorentzVector::Pz();
        // pt_piminusRot = sqrt(pow(px_piminusRot,2)+pow(py_piminusRot,2));
        

        /////////////////////////////////////////////////////////////////////////////
        // // Rotation !!
        // // protonbarCMrot

        //**************************************
        // 29 Jan 2021 added
        // Rotation of protonbar CM update below
        // by finding new pxpypz from new angles 

        Float_t Phi_AntihyperonNew;

        if (pbarPhiCM >=0 && pbarPhiCM <=180){
            Phi_AntihyperonNew = pbarPhiCM - 90;
        }    
        if (pbarPhiCM >180 && pbarPhiCM <=360){
            Phi_AntihyperonNew = pbarPhiCM - 270;
        }

        Float_t Phi_pbarUse;
        Phi_pbarUse = protonbarPhiCM + Phi_AntihyperonNew;

        if (Phi_pbarUse > 360){
            Phi_pbarUse = Phi_pbarUse - 360;
        }
        if (Phi_pbarUse < 0){
            Phi_pbarUse = Phi_pbarUse + 360;
        }

        Float_t Theta_pbarUseCM;
        Theta_pbarUseCM = protonbarThetaCM - pbarThetaCM;   //deduction

        if (Theta_pbarUseCM < 0){
            Theta_pbarUseCM = -Theta_pbarUseCM;
        }        
        if (Theta_pbarUseCM > 180){
            Theta_pbarUseCM = 360 - Theta_pbarUseCM;
        }

        // 2 May 2022 update p_p to p_pCM
        // px_protonbarCMrot = p_pCM * TMath::Cos(TMath::DegToRad()*Phi_pbarUse) * TMath::Sin(TMath::DegToRad()*Theta_pbarUseCM);
        // py_protonbarCMrot = p_pCM * TMath::Sin(TMath::DegToRad()*Phi_pbarUse) * TMath::Sin(TMath::DegToRad()*Theta_pbarUseCM);
        // pz_protonbarCMrot = p_pCM * TMath::Cos(TMath::DegToRad()*Theta_pbarUseCM);

        // revised June
        // Take angles from tmp_pbarCM and do rotation
        TLorentzVector tmp_pbarCMRot = tmp_pbarCM;
        tmp_pbarCMRot.RotateX(lv_lbar->Theta());
        tmp_pbarCMRot.RotateZ(lv_lbar->Phi());
        // tmp_p3CMRot.Print();
        px_protonbarCMrot = tmp_pbarCMRot.Px();
        py_protonbarCMrot = tmp_pbarCMRot.Py();
        pz_protonbarCMrot = tmp_pbarCMRot.Pz();

        // 2 May 2022 update E_p to E_pCM
        lv_pbar -> TLorentzVector::SetPxPyPzE(px_protonbarCMrot,py_protonbarCMrot,pz_protonbarCMrot,E_pbarCM); 

        protonbarPhiCMrot = lv_pbar -> TLorentzVector::Phi() * TMath::RadToDeg();
        protonbarThetaCMrot = lv_pbar -> TLorentzVector::Theta() * TMath::RadToDeg();
        protonbarCosThetaCMrot = lv_pbar -> TLorentzVector::CosTheta();

        m_protonbarCMrot = lv_pbar -> TLorentzVector::M(); 
        E_protonbarCMrot = lv_pbar -> TLorentzVector::E();
        p_protonbarCMrot = lv_pbar->P();
        pt_protonbarCMrot = sqrt(pow(px_protonbarCMrot,2)+pow(py_protonbarCMrot,2));


        // Float_t rotAxisPhiAntiHyperon, rotAxisThetaAntiHyperon;
        // rotAxisPhiAntiHyperon = TMath::DegToRad()*protonbarPhi;
        // if (protonbarThetaCM < 90){
        //     rotAxisThetaAntiHyperon = TMath::DegToRad()*protonbarThetaCM + TMath::Pi()/2;
        // }
        // else {
        //     rotAxisThetaAntiHyperon = TMath::DegToRad()*protonbarThetaCM - TMath::Pi()/2;
        // }
        // TVector3 rotAxisAntiHyperon;
        // rotAxisAntiHyperon.SetMagThetaPhi(p_p,rotAxisThetaAntiHyperon,rotAxisPhiAntiHyperon);
        
        // TLorentzRotation lR_antihyperon; 
        // // can be reused below
        // lR_antihyperon.Rotate(-TMath::DegToRad()*protonbarThetaCM,rotAxisAntiHyperon); 
 
        // TLorentzVector lv_probarRotCM;
        // lv_probarRotCM.SetPxPyPzE(px_protonbarCM,py_protonbarCM,pz_protonbarCM,E_protonbarCM);
        // lv_probarRotCM = lR_antihyperon * lv_probarRotCM;

        // protonbarPhiCMrot = TMath::RadToDeg()*lv_proRotCM.Phi();
        // protonbarThetaCMrot = TMath::RadToDeg()*lv_proRotCM.Theta(); 
        // protonbarCosThetaCMrot = TMath::Cos(TMath::DegToRad()*protonbarThetaCMrot);

        // lv_p -> TLorentzVector::SetPxPyPzE(lv_probarRotCM.Px(),lv_probarRotCM.Py(),lv_probarRotCM.Pz(),lv_probarRotCM.E()); 

        // m_protonbarCMrot = lv_p -> TLorentzVector::M(); 
        // E_protonbarCMrot = lv_p -> TLorentzVector::E();
        // p_protonbarCMrot = lv_p->P();
        // px_protonbarCMrot = lv_p -> TLorentzVector::Px();
        // py_protonbarCMrot = lv_p -> TLorentzVector::Py();
        // pz_protonbarCMrot = lv_p -> TLorentzVector::Pz();
        // pt_protonbarCMrot = sqrt(pow(px_protonbarCMrot,2)+pow(py_protonbarCMrot,2));

        // // Rotation !!
        // // piplusCMrot
        // lR_antihyperon.Rotate(-TMath::DegToRad()*piplusThetaCM,rotAxisAntiHyperon); 
 
        //**************************************
        // 29 Jan 2021 added
        // Rotation of piplus CM update below
        // by finding new pxpypz from new angles 
        Float_t Phi_piplusUse;
        Phi_piplusUse = piplusPhiCM + Phi_AntihyperonNew;

        if (Phi_piplusUse > 360){
            Phi_piplusUse = Phi_piplusUse - 360;
        }
        if (Phi_piplusUse < 0){
            Phi_piplusUse = Phi_piplusUse + 360;
        }

        Float_t Theta_piplusUseCM;
        Theta_piplusUseCM = piplusThetaCM - pbarThetaCM;    // deduction

        if (Theta_piplusUseCM < 0){
            Theta_piplusUseCM = -Theta_piplusUseCM;
        }        
        if (Theta_piplusUseCM > 180){
            Theta_piplusUseCM = 360 - Theta_piplusUseCM;
        }

        // 2 May 2022 update p_pi to p_piCM
        // px_piplusCMrot = p_piCM * TMath::Cos(TMath::DegToRad()*Phi_piplusUse) * TMath::Sin(TMath::DegToRad()*Theta_piplusUseCM);
        // py_piplusCMrot = p_piCM * TMath::Sin(TMath::DegToRad()*Phi_piplusUse) * TMath::Sin(TMath::DegToRad()*Theta_piplusUseCM);
        // pz_piplusCMrot = p_piCM * TMath::Cos(TMath::DegToRad()*Theta_piplusUseCM);

        // revised June
        // Take angles from tmp_pbarCM and do rotation
        TLorentzVector tmp_pipCMRot = tmp_pipCM;
        tmp_pipCMRot.RotateX(lv_lbar->Theta());
        tmp_pipCMRot.RotateZ(lv_lbar->Phi());
        // tmp_p3CMRot.Print();
        px_piplusCMrot = tmp_pipCMRot.Px();
        py_piplusCMrot = tmp_pipCMRot.Py();
        pz_piplusCMrot = tmp_pipCMRot.Pz();

        // 2 May 2022 update E_pi to E_piCM
        lv_piplus -> TLorentzVector::SetPxPyPzE(px_piplusCMrot,py_piplusCMrot,pz_piplusCMrot,E_pipCM); 

        piplusPhiCMrot = lv_piplus -> TLorentzVector::Phi() * TMath::RadToDeg();
        piplusThetaCMrot = lv_piplus -> TLorentzVector::Theta() * TMath::RadToDeg();
        piplusCosThetaCMrot = lv_piplus -> TLorentzVector::CosTheta();

        m_piplusCMrot = lv_piplus -> TLorentzVector::M(); 
        E_piplusCMrot = lv_piplus -> TLorentzVector::E();
        p_piplusCMrot = lv_piplus->P();
        pt_piplusCMrot = sqrt(pow(px_piplusCMrot,2)+pow(py_piplusCMrot,2));

        // TLorentzVector lv_pipRotCM;
        // lv_pipRotCM.SetPxPyPzE(px_piplusCM,py_piplusCM,pz_piplusCM,E_piplusCM);
        // lv_pipRotCM = lR_antihyperon * lv_pipRotCM;

        // piplusPhiCMrot = TMath::RadToDeg()*lv_pipRotCM.Phi();
        // piplusThetaCMrot = TMath::RadToDeg()*lv_pipRotCM.Theta(); 
        // piplusCosThetaCMrot = TMath::Cos(TMath::DegToRad()*piplusThetaCMrot);

        // lv_pi -> TLorentzVector::SetPxPyPzE(lv_pipRotCM.Px(),lv_pipRotCM.Py(),lv_pipRotCM.Pz(),lv_pipRotCM.E()); 

        // m_piplusCMrot = lv_pi -> TLorentzVector::M(); 
        // E_piplusCMrot = lv_pi -> TLorentzVector::E();
        // p_piplusCMrot = lv_pi->P();
        // px_piplusCMrot = lv_pi -> TLorentzVector::Px();
        // py_piplusCMrot = lv_pi -> TLorentzVector::Py();
        // pz_piplusCMrot = lv_pi -> TLorentzVector::Pz();
        // pt_piplusCMrot = sqrt(pow(px_piplusCMrot,2)+pow(py_piplusCMrot,2));


        // // Rotation !!
        // // protonbarRot
        // lR_antihyperon.Rotate(-TMath::DegToRad()*protonbarTheta,rotAxisAntiHyperon); 
 
        //**************************************
        // 29 Jan 2021 added
        // Rotation of protonbar in lambdabar rest frame update below
        // by finding new pxpypz from new angles
        //
        // 26 Feb 2021 updated
        // After rotation of particles in CM frame
        // Should not also rotate particles in antihyperon rest frame
        // One should do the Lorentz boost in the other way around instead! 
        //
        Float_t Theta_pbarUse;
        // Theta_pbarUse = protonbarTheta - pbarThetaCM;   //deduction
        // not this above

        // px_protonbarCMrot remains
        // find the pz_protonbarCMrot
        // pb_protonZ = gamma_lam * (p_protonZ + v_lam * E_p);  //recall

        Float_t pz_protonbarRotnew;
        pz_protonbarRotnew = (pz_protonbarCMrot / gamma_lam) - (v_lam * E_p); 

        Theta_pbarUse = TMath::ATan(px_protonbarCMrot / pz_protonbarRotnew)* TMath::RadToDeg();
        // May 2022 update
        // the angles represent the other direction compare to hyperon side
        Theta_pbarUse = 180 -  Theta_pbarUse; 

        if (Theta_pbarUse < 0){
            Theta_pbarUse = -Theta_pbarUse;
        }        
        if (Theta_pbarUse > 180){
            Theta_pbarUse = 360 - Theta_pbarUse;
        }

        //revised June
        TLorentzVector tmp_pbar, tmp_pip;
        tmp_pbar = *lv_pbar;
        tmp_pip = *lv_piplus;
        tmp_pbar.Boost(lv_lbar->BoostVector());
        tmp_pip.Boost(lv_lbar->BoostVector());

        px_protonbarRot = tmp_pbar.Px();
        py_protonbarRot = tmp_pbar.Py();
        pz_protonbarRot = tmp_pbar.Pz();

        // px_protonbarRot = p_p * TMath::Cos(TMath::DegToRad()*Phi_pbarUse) * TMath::Sin(TMath::DegToRad()*Theta_pbarUse);
        // py_protonbarRot = p_p * TMath::Sin(TMath::DegToRad()*Phi_pbarUse) * TMath::Sin(TMath::DegToRad()*Theta_pbarUse);
        // pz_protonbarRot = p_p * TMath::Cos(TMath::DegToRad()*Theta_pbarUse);

        lv_pbar -> TLorentzVector::SetPxPyPzE(px_protonbarRot,py_protonbarRot,pz_protonbarRot,E_p); 

        protonbarRotPhi = lv_pbar -> TLorentzVector::Phi() * TMath::RadToDeg();
        protonbarRotTheta = lv_pbar -> TLorentzVector::Theta() * TMath::RadToDeg();
        protonbarRotCosTheta = lv_pbar -> TLorentzVector::CosTheta();

        m_protonbarRot = lv_pbar -> TLorentzVector::M(); 
        E_protonbarRot = lv_pbar -> TLorentzVector::E();
        p_protonbarRot = lv_pbar->P();
        pt_protonbarRot = sqrt(pow(px_protonbarRot,2)+pow(py_protonbarRot,2));

        // TLorentzVector lv_probarRot;
        // lv_probarRot.SetPxPyPzE(px_protonbar,py_protonbar,pz_protonbar,E_protonbar);
        // lv_probarRot = lR_antihyperon * lv_probarRot;

        // protonbarRotPhi = TMath::RadToDeg()*lv_proRot.Phi();
        // protonbarRotTheta = TMath::RadToDeg()*lv_proRot.Theta(); 
        // protonbarRotCosTheta = TMath::Cos(TMath::DegToRad()*protonbarRotTheta);

        // lv_p -> TLorentzVector::SetPxPyPzE(lv_probarRot.Px(),lv_probarRot.Py(),lv_probarRot.Pz(),lv_probarRot.E()); 

        // m_protonbarRot = lv_p -> TLorentzVector::M(); 
        // E_protonbarRot = lv_p -> TLorentzVector::E();
        // p_protonbarRot = lv_p->P();
        // px_protonbarRot = lv_p -> TLorentzVector::Px();
        // py_protonbarRot = lv_p -> TLorentzVector::Py();
        // pz_protonbarRot = lv_p -> TLorentzVector::Pz();
        // pt_protonbarRot = sqrt(pow(px_protonbarRot,2)+pow(py_protonbarRot,2));

        // // Rotation !!
        // // piplusRot
        // lR_antihyperon.Rotate(-TMath::DegToRad()*piplusTheta,rotAxisAntiHyperon); 
 
        //**************************************
        // 29 Jan 2021 added
        // Rotation of piplus in lambdabar rest frame update below
        // by finding new pxpypz from new angles

        //
        // 26 Feb 2021 updated
        // After rotation of particles in CM frame
        // Should not also rotate particles in antihyperon rest frame
        // One should do the Lorentz boost in the other way around instead!  
        //
        Float_t Theta_piplusUse;
        // Theta_piplusUse = piplusTheta - pbarThetaCM;    // deduction
        // not this above

        // px_piplusCMrot remains
        // find the pz_piplusCMrot
        // pb_piplusZ = gamma_lam * (p_piplusZ + v_lam * E_pi);   //recall

        Float_t pz_piplusRotnew;
        pz_piplusRotnew = (pz_piplusCMrot / gamma_lam) - (v_lam * E_pi); 

        Theta_piplusUse = TMath::ATan(px_piplusCMrot / pz_piplusRotnew)* TMath::RadToDeg();
        // May 2022 update
        // the angles represent the other direction compare to hyperon side
        Theta_piplusUse = 180 -  Theta_piplusUse; 


        if (Theta_piplusUse < 0){
            Theta_piplusUse = -Theta_piplusUse;
        }        
        if (Theta_piplusUse > 180){
            Theta_piplusUse = 360 - Theta_piplusUse;
        }

        // //revised June
        // TLorentzVector tmp_pbar, tmp_pip;
        // tmp_pbar = *lv_pbar;
        // tmp_pip = *lv_piplus;
        // tmp_pbar.Boost(lv_lbar->BoostVector());
        // tmp_pip.Boost(lv_lbar->BoostVector());
        px_piplusRot = tmp_pip.Px();
        py_piplusRot = tmp_pip.Py();
        pz_piplusRot = tmp_pip.Pz();

        // px_piplusRot = p_pi * TMath::Cos(TMath::DegToRad()*Phi_piplusUse) * TMath::Sin(TMath::DegToRad()*Theta_piplusUse);
        // py_piplusRot = p_pi * TMath::Sin(TMath::DegToRad()*Phi_piplusUse) * TMath::Sin(TMath::DegToRad()*Theta_piplusUse);
        // pz_piplusRot = p_pi * TMath::Cos(TMath::DegToRad()*Theta_piplusUse);

        lv_piplus -> TLorentzVector::SetPxPyPzE(px_piplusRot,py_piplusRot,pz_piplusRot,E_pi); 

        piplusRotPhi = lv_piplus -> TLorentzVector::Phi() * TMath::RadToDeg();
        piplusRotTheta = lv_piplus -> TLorentzVector::Theta() * TMath::RadToDeg();
        piplusRotCosTheta = lv_piplus -> TLorentzVector::CosTheta();

        m_piplusRot = lv_piplus -> TLorentzVector::M(); 
        E_piplusRot = lv_piplus -> TLorentzVector::E();
        p_piplusRot = lv_piplus->P();
        pt_piplusRot = sqrt(pow(px_piplusRot,2)+pow(py_piplusRot,2));


        // TLorentzVector lv_pipRot;
        // lv_pipRot.SetPxPyPzE(px_piplus,py_piplus,pz_piplus,E_piplus);
        // lv_pipRot = lR_antihyperon * lv_pipRot;

        // piplusRotPhi = TMath::RadToDeg()*lv_pipRot.Phi();
        // piplusRotTheta = TMath::RadToDeg()*lv_pipRot.Theta(); 
        // piplusRotCosTheta = TMath::Cos(TMath::DegToRad()*piplusRotTheta);

        // lv_pi -> TLorentzVector::SetPxPyPzE(lv_pipRot.Px(),lv_pipRot.Py(),lv_pipRot.Pz(),lv_pipRot.E()); 

        // m_piplusRot = lv_pi -> TLorentzVector::M(); 
        // E_piplusRot = lv_pi -> TLorentzVector::E();
        // p_piplusRot = lv_pi->P();
        // px_piplusRot = lv_pi -> TLorentzVector::Px();
        // py_piplusRot = lv_pi -> TLorentzVector::Py();
        // pz_piplusRot = lv_pi -> TLorentzVector::Pz();
        // pt_piplusRot = sqrt(pow(px_piplusRot,2)+pow(py_piplusRot,2));

        /////////////////////////////////////////////////////////////////////////////

        // trees and branches filling
        protonTree->Fill();
        piminusTree->Fill();
        protonbarTree->Fill();
        piplusTree->Fill();
        
        lambdaCMTree->Fill();
        protonCMTree->Fill();
        piminusCMTree->Fill();
        lambdabarCMTree->Fill();
        protonbarCMTree->Fill();
        piplusCMTree->Fill();

        pbarpCMTree->Fill();

        lambdaCMrotTree->Fill();
        protonCMrotTree->Fill();
        piminusCMrotTree->Fill();
        lambdabarCMrotTree->Fill();
        protonbarCMrotTree->Fill();
        piplusCMrotTree->Fill();

        protonRotTree->Fill();
        piminusRotTree->Fill();
        protonbarRotTree->Fill();
        piplusRotTree->Fill();

        // Events progress
        cout << "Events" << i << endl;
        }
    st->Stop(); 

    cout << "CPU Time: " << st->CpuTime() << endl;
    // cout << "Proton Theta:" << protonTheta << endl;
    // cout << "Proton Phi:" << protonPhi << endl;
    // cout << "Proton m:" << m_proton << endl;
    // cout << "mtest:" << m_p << endl;
    // cout << "Proton E:" << E_proton << endl;
    // cout << "P px:" << px_proton << endl;
    // cout << "P py:" << py_proton << endl;
    // cout << "P pz:" << pz_proton << endl;
    // cout << "P pt:" << pt_proton << endl;

    // cout << "Piminus Theta:" << piminusTheta << endl;
    // cout << "Piminus Phi:" << piminusPhi << endl;
    // cout << "Piminus m:" << m_piminus << endl;
    // cout << "Piminus E:" << E_piminus << endl;
    // cout << "Pi px:" << px_piminus << endl;
    // cout << "Pi py:" << py_piminus << endl;
    // cout << "Pi pz:" << pz_piminus << endl;
    // cout << "Pi pt:" << pt_piminus << endl;

    ///////////////////////////////////////////
    // cout << "" << endl;
    // cout << "Trying consistence check" << endl;
    // TLorentzVector lv_ppip = lv_proRotCM + lv_pimRotCM ;
    // TLorentzVector lv_pbarpim = lv_probarRotCM + lv_pipRotCM;

    // cout << "compare lorentz vector in CM frame of lambda or lamdabar with the sum of decay particles" << endl;

    // cout << "P mag" <<  "lambda"<< lv_lamRotCM.P() << "p+piminus"<< lv_ppip.P()<< endl;
    // cout << "P mag" << "lambdabar"<< lv_lambarRotCM.P() << "pbar+piplus"<< lv_pbarpim.P()<< endl;
    // cout << "Theta" << "lambda"<<  lv_lamRotCM.Theta() << "p+piminus"<< lv_ppip.Theta()<< endl;
    // cout << "Theta" << "lambdabar"<< lv_lambarRotCM.Theta() << "pbar+piplus"<< lv_pbarpim.Theta()<< endl;
    // cout << "Phi" << "lambda"<<  lv_lamRotCM.Phi() << "p+piminus"<< lv_ppip.Phi()<< endl;
    // cout << "Phi" << "lambdabar"<< lv_lambarRotCM.Phi() << "pbar+piplus"<< lv_pbarpim.Phi()<< endl;
    // cout << "Px" << "lambda"<<  lv_lamRotCM.Px() << "p+piminus"<< lv_ppip.Px()<< endl;
    // cout << "Px" << "lambdabar"<< lv_lambarRotCM.Px() << "pbar+piplus"<< lv_pbarpim.Px()<< endl;
    // cout << "Py" << "lambda"<<  lv_lamRotCM.Py() << "p+piminus"<< lv_ppip.Py()<< endl;
    // cout << "Py" << "lambdabar"<< lv_lambarRotCM.Py() << "pbar+piplus"<< lv_pbarpim.Py()<< endl;
    // cout << "Pz" << "lambda"<<  lv_lamRotCM.Pz() << "p+piminus"<< lv_ppip.Pz()<< endl;
    // cout << "Pz" << "lambdabar"<< lv_lambarRotCM.Pz() << "pbar+piplus"<< lv_pbarpim.Pz()<< endl;
    // cout << "M" << "lambda"<<  lv_lamRotCM.M() << "p+piminus"<< lv_ppip.M()<< endl;
    // cout << "M" << "lambdabar"<< lv_lambarRotCM.M() << "pbar+piplus"<< lv_pbarpim.M()<< endl;
    // cout << "E" << "lambda"<<  lv_lamRotCM.E() << "p+piminus"<< lv_ppip.E()<< endl;
    // cout << "E" << "lambdabar"<< lv_lambarRotCM.E() << "pbar+piplus"<< lv_pbarpim.E()<< endl;

    // cout << "" << endl;
    ///////////////////////////////////////////

    protonTree->Write("",TObject::kWriteDelete);
    piminusTree->Write("",TObject::kWriteDelete);
    protonbarTree->Write("",TObject::kWriteDelete);
    piplusTree->Write("",TObject::kWriteDelete);

    lambdaCMTree->Write("",TObject::kWriteDelete);
    protonCMTree->Write("",TObject::kWriteDelete);
    piminusCMTree->Write("",TObject::kWriteDelete);
    lambdabarCMTree->Write("",TObject::kWriteDelete);
    protonbarCMTree->Write("",TObject::kWriteDelete);
    piplusCMTree->Write("",TObject::kWriteDelete);

    pbarpCMTree->Write("",TObject::kWriteDelete);

    lambdaCMrotTree->Write("",TObject::kWriteDelete);
    protonCMrotTree->Write("",TObject::kWriteDelete);
    piminusCMrotTree->Write("",TObject::kWriteDelete);
    lambdabarCMrotTree->Write("",TObject::kWriteDelete);
    protonbarCMrotTree->Write("",TObject::kWriteDelete);
    piplusCMrotTree->Write("",TObject::kWriteDelete);

    protonRotTree->Write("",TObject::kWriteDelete);
    piminusRotTree->Write("",TObject::kWriteDelete);
    protonbarRotTree->Write("",TObject::kWriteDelete);
    piplusRotTree->Write("",TObject::kWriteDelete);

    // protonTree->Write();
    // piminusTree->Write();
    // f->Write();
    // f->Write("",TObject::kWriteDelete);
    delete f;
    cout << "Output File: testGenllbar.root" << endl;
}

//------------------------------------------------------------------------
// Testing for angles distribution and saving.
void testAngle(Int_t nrEvents=1000000){
    TFile* f = TFile::Open("testAngle.root","RECREATE");
    TRandom3 *r3=new TRandom3();
    r3->SetSeed(time(NULL));
    // TH1D *h3=new TH1D("PhiTRandom3","PhiAngle",100,0,360);
    // TH1D *ht=new TH1D("TestCosThTRandom3","Cos(Theta)",100,-1,1);
    // TH1D *htt=new TH1D("TestThTRandom3","ThetaAngle",100,0,180);
    TStopwatch *st=new TStopwatch();

    TTree *tree=new TTree("Angles","Uniform Disrtibution");
    Float_t Phi, CosTheta, Theta;
    tree->Branch("Phi", &Phi, "Phi/D");
    tree->Branch("CosTheta", &CosTheta, "CosTheta/D");
    tree->Branch("Theta", &Theta, "Theta/D");

    st->Start();
    for (Int_t i=0; i<nrEvents; i++) { 
        // h3->Fill(r3->Uniform(0,1)); 
        // use = r3->Uniform(0,360);
        Phi = r3->Uniform(0,360);    
        CosTheta = r3->Uniform(-1,1);
        Theta = TMath::RadToDeg()*TMath::ACos(CosTheta);
        tree->Fill(); 
        }
    st->Stop(); 
    cout << "CPU Time: " << st->CpuTime() << endl;
    tree->Write();
    delete f;
    cout << "Output File: testAngle.root" << endl;
}
// p.s.
//------------------------------------------------------------------------
// In Lambda Rest frame that having P Piminus
// In Lambdabar Rest frame that having Pbar Piplus and 
//------------------------------------------------------------------------
// In CM frame that with decay product of Lambda: P Piminus
// In CM frame that with decay product of LAmbdabar: Pbar Piplus 
// In CM frame that with PbarP -> LambdabarLambda
//------------------------------------------------------------------------


void CheckLbarL(){
    TFile *f = new TFile("testGenllbar.root");
    TTree *tp = (TTree*) f -> Get("Proton_CMrot");
    TTree *tpi = (TTree*) f -> Get("Piminus_CMrot");
    TTree *tl = (TTree*) f -> Get("Lambda_CMrot");

    float px_protonCMrot,py_protonCMrot,pz_protonCMrot,E_protonCMrot,px_piminusCMrot,py_piminusCMrot,pz_piminusCMrot,E_piminusCMrot;
    tp->SetBranchAddress("px_protonCMrot",&px_protonCMrot);
    tp->SetBranchAddress("py_protonCMrot",&py_protonCMrot);
    tp->SetBranchAddress("pz_protonCMrot",&pz_protonCMrot);
    tp->SetBranchAddress("E_protonCMrot",&E_protonCMrot);
    tpi->SetBranchAddress("px_piminusCMrot",&px_piminusCMrot);
    tpi->SetBranchAddress("py_piminusCMrot",&py_piminusCMrot);
    tpi->SetBranchAddress("pz_piminusCMrot",&pz_piminusCMrot);
    tpi->SetBranchAddress("E_piminusCMrot",&E_piminusCMrot);

    TH1F *flambda = new TH1F("m_lambda","mu_lambda",100,0,10);
    // TH1F *lambdaTh = new TH1F("theta_lambda","theta_lambda",100,0,180);
    // TH1F *lambdaP = new TH1F("phi_lambda","phi_lambda",100,0,360);
    TH1F *Elambda = new TH1F("E_lambda","E_lambda",100,0,10);
    TH1F *Plambda = new TH1F("P_lambda","P_lambda",100,0,10);
    TH1F *Pxlambda = new TH1F("px_lambda","px_lambda",100,0,10);
    TH1F *Pylambda = new TH1F("py_lambda","py_lambda",100,0,10);
    TH1F *Pzlambda = new TH1F("pz_lambda","pz_lambda",100,0,10);
    // TH1F *flambda = new TH1F("m_lambda","mu_lambda",100,0,10);

    int nentries = (int) tl -> GetEntries();

    TLorentzVector protonCMrot;
    TLorentzVector piminusCMrot;
    TLorentzVector lambdaCMrot = protonCMrot+piminusCMrot;

    for(int i=0; i<nentries; i++){
    	tp->GetEntry(i);
    	protonCMrot.SetPxPyPzE(px_protonCMrot,py_protonCMrot,pz_protonCMrot,E_protonCMrot);
    	tpi->GetEntry(i);
    	piminusCMrot.SetPxPyPzE(px_piminusCMrot,py_piminusCMrot,pz_piminusCMrot,E_piminusCMrot);
        TLorentzVector lambda = protonCMrot+piminusCMrot;
    	flambda->Fill(lambdaCMrot.M());
        // lambdaTh->Fill(lambdaCMrot.Theta());
        // lambdaP->Fill(lambdaCMrot.Phi());
        Elambda->Fill(lambdaCMrot.E());
        Plambda->Fill(lambdaCMrot.P());
        Pxlambda->Fill(lambdaCMrot.Px());
        Pylambda->Fill(lambdaCMrot.Py());
        Pzlambda->Fill(lambdaCMrot.Pz());
        }
    new TCanvas;
    flambda->Draw();
    new TCanvas;
    Elambda->Draw();
    new TCanvas;
    Plambda->Draw();
    new TCanvas;
    Pxlambda->Draw();
    new TCanvas;
    Pylambda->Draw();
    new TCanvas;
    Pzlambda->Draw();
}