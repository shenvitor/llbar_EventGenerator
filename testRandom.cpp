// created by Vitor Jose Shen
// at Uppsala University
// --------------------------

#include <iostream>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMath.h"



// void testRandom(Int_t nrEvents=500000000)
void testRandom(Int_t nrEvents=100000000)
{

Double_t use, uuse, uuuse;
TRandom *r1=new TRandom();
TRandom2 *r2=new TRandom2();
TRandom3 *r3=new TRandom3();
r3->SetSeed(time(NULL));
// TH1D *h1=new TH1D("h1","TRandom",500,0,1);
// TH1D *h2=new TH1D("h2","TRandom2",500,0,1);
// TH1D *h3=new TH1D("h3","TRandom3",500,0,1);

// TH1D *h1=new TH1D("h1","TRandom",100,0,360);
// TH1D *h2=new TH1D("h2","TRandom2",100,0,360);
TH1D *h3=new TH1D("PhiTRandom3","PhiAngle",100,0,360);
// TH1D *h4=new TH1D("h4","TRandom",100,0,180);
// TH1D *h5=new TH1D("h5","TRandom2",100,0,180);
// TH1D *h6=new TH1D("ThTRandom3","ThetaAngle",100,-90,90);
TH1D *h6=new TH1D("ThTRandom3","ThetaAngle",100,0,180);

TH1D *hc=new TH1D("CosThTRandom3","Cos(Theta)",100,-1,1);
TH1D *ht=new TH1D("TestCosThTRandom3","Cos(Theta)",100,-1,1);
TH1D *htt=new TH1D("TestThTRandom3","ThetaAngle",100,0,180);

TH1D *test=new TH1D("","",100,0,360);;
TH1D *ttest=new TH1D("","",100,0,180);
TH1D *tttest=new TH1D("","",100,-1,1);

test->SetStats(0);
ttest->SetStats(0);
tttest->SetStats(0);

TStopwatch *st=new TStopwatch();

// [0,360]
// st->Start();
// for (Int_t i=0; i<nrEvents; i++) { 
//     // h1->Fill(r1->Uniform(0,1)); 
//     h1->Fill(r1->Uniform(0,360)); 
//     }
// st->Stop(); 
// cout << "Random: " << st->CpuTime() << endl;
// TCanvas *c1=new TCanvas;
// h1->Draw();

// st->Start();
// for (Int_t i=0; i<nrEvents; i++) { 
//     // h2->Fill(r2->Uniform(0,1)); 
//     h2->Fill(r2->Uniform(0,360)); 
//     }
// st->Stop(); 
// cout << "Random2: " << st->CpuTime() << endl;
// TCanvas *c2=new TCanvas;
// h2->Draw();

st->Start();
for (Int_t i=0; i<nrEvents; i++) { 
    // h3->Fill(r3->Uniform(0,1)); 
    use = r3->Uniform(0,360);
    h3->Fill(use); 
    test->Fill(use);
    }
st->Stop(); 
cout << "CPU Time of Random3 for phi: " << st->CpuTime() << endl;
TCanvas *c3=new TCanvas;
// TPad *p3=new TPad;
h3->Draw();
c3->SetLogy();
TPad *subpad1 = new TPad("subpad","",0.6,0.3,0.95,0.65); 
subpad1->Draw(); 
subpad1->cd();
test->Draw();

// [0,180]
// st->Start();
// for (Int_t i=0; i<nrEvents; i++) { 
//     // h1->Fill(r1->Uniform(0,1)); 
//     h4->Fill(r1->Uniform(0,180)); 
//     }
// st->Stop(); 
// cout << "Random: " << st->CpuTime() << endl;
// TCanvas *c4=new TCanvas;
// h4->Draw();
// TMath::Cos(h4)->Draw();

// st->Start();
// for (Int_t i=0; i<nrEvents; i++) { 
//     // h2->Fill(r2->Uniform(0,1)); 
//     h5->Fill(r2->Uniform(0,180)); 
//     }
// st->Stop(); 
// cout << "Random2: " << st->CpuTime() << endl;
// TCanvas *c5=new TCanvas;
// h5->Draw();
// TMath::Cos(h5)->Draw();

st->Start();
for (Int_t i=0; i<nrEvents; i++) { 
    // h3->Fill(r3->Uniform(0,1)); 
    // use = r3->Uniform(-90,90);
    uuse = r3->Uniform(0,180);
    h6->Fill(uuse); 
    ttest->Fill(uuse);
    hc->Fill(TMath::Cos((uuse)*2*TMath::Pi()/360)); 

    uuuse = r3->Uniform(-1,1);
    ht->Fill(uuuse);
    tttest->Fill(uuuse);
    htt->Fill(TMath::RadToDeg()*TMath::ACos(uuuse)); 

    //TMath::DegToRad()
    //TMath::RadToDeg()
    }
st->Stop(); 
cout << "CPU Time of Random3 for theta and cos(theta): " << st->CpuTime() << endl;
TCanvas *c6=new TCanvas;
// TPad *p6 = new TPad;
h6->Draw();
c6->SetLogy();
TPad *subpad2 = new TPad("subpad","",0.6,0.3,0.95,0.65); 
subpad2->Draw(); 
subpad2->cd();
ttest->Draw();
TCanvas *cc=new TCanvas;
hc->Draw();

TCanvas *ct=new TCanvas;
// TPad *pt = new TPad;
ht->Draw();
ct->SetLogy();
TPad *subpad3 = new TPad("subpad","",0.6,0.3,0.95,0.65); 
subpad3->Draw(); 
subpad3->cd();
tttest->Draw();
TCanvas *ctt=new TCanvas;
htt->Draw();

}