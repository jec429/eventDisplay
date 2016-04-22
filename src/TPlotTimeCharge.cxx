#include "TPlotTimeCharge.hxx"
#include "TEventDisplay.hxx"
#include "TGUIManager.hxx"

#include <TEvent.hxx>
#include <TEventContext.hxx>
#include <THit.hxx>
#include <THandle.hxx>
#include <THitSelection.hxx>
#include <TEventFolder.hxx>
#include <CaptGeomId.hxx>
#include <HEPUnits.hxx>

#include <TCanvas.h>
#include <TPad.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TH1F.h>

#include <iostream>
#include <sstream>

CP::TPlotTimeCharge::TPlotTimeCharge()
    : fXPlaneGraph(NULL), fVPlaneGraph(NULL), fUPlaneGraph(NULL),
      fGraphLegend(NULL) { }

CP::TPlotTimeCharge::~TPlotTimeCharge() {}

void CP::TPlotTimeCharge::DrawTimeCharge() {

    CP::TEvent* event = CP::TEventFolder::GetCurrentEvent();

    CP::THandle<CP::THitSelection> hits
        = event->Get<CP::THitSelection>("~/hits/drift");

    if (!hits) return;

    double minTime = 1E+22;
    double maxTime = -1E+22;
    double minCharge = 1.0;
    double maxCharge = -1E+22;
    
    const int maxPoints = 10000;
    double time[maxPoints];
    double timeRMS[maxPoints];
    double charge[maxPoints];
    double chargeUnc[maxPoints];
    int points;

    // Fill the graph for the U hits
    points = 0;
    for (CP::THitSelection::iterator h = hits->begin();
         h != hits->end(); ++h) {
        if (!CP::GeomId::Captain::IsUWire((*h)->GetGeomId())) continue;
        time[points] = (*h)->GetTime()/unit::microsecond;
        timeRMS[points] = (*h)->GetTimeRMS()/unit::microsecond;
        charge[points] = (*h)->GetCharge();
        chargeUnc[points] = (*h)->GetChargeUncertainty();
        ++points;
        minTime = std::min((*h)->GetTime(),minTime);
        maxTime = std::max((*h)->GetTime(),maxTime);
        minCharge = std::min((*h)->GetCharge(),minCharge);
        maxCharge = std::max((*h)->GetCharge(),maxCharge);
        if (points>=maxPoints) break;
    }
    if (fUPlaneGraph) delete fUPlaneGraph;
    fUPlaneGraph
        = new TGraphErrors(points,time,charge,timeRMS,chargeUnc);

    // Fill the graph for the V hits.
    points = 0;
    for (CP::THitSelection::iterator h = hits->begin();
         h != hits->end(); ++h) {
        if (!CP::GeomId::Captain::IsVWire((*h)->GetGeomId())) continue;
        time[points] = (*h)->GetTime()/unit::microsecond;
        timeRMS[points] = (*h)->GetTimeRMS()/unit::microsecond;
        charge[points] = (*h)->GetCharge();
        chargeUnc[points] = (*h)->GetChargeUncertainty();
        ++points;
        minTime = std::min((*h)->GetTime(),minTime);
        maxTime = std::max((*h)->GetTime(),maxTime);
        minCharge = std::min((*h)->GetCharge(),minCharge);
        maxCharge = std::max((*h)->GetCharge(),maxCharge);
        if (points>=maxPoints) break;
    }
    if (fVPlaneGraph) delete fVPlaneGraph;
    fVPlaneGraph
        = new TGraphErrors(points,time,charge,timeRMS,chargeUnc);

    // Fill the graph for the X hits.
    points=0;
    for (CP::THitSelection::iterator h = hits->begin();
         h != hits->end(); ++h) {
        if (!CP::GeomId::Captain::IsXWire((*h)->GetGeomId())) continue;
        time[points] = (*h)->GetTime()/unit::microsecond;
        timeRMS[points] = (*h)->GetTimeRMS()/unit::microsecond;
        charge[points] = (*h)->GetCharge();
        chargeUnc[points] = (*h)->GetChargeUncertainty();
        ++points;
        minTime = std::min((*h)->GetTime(),minTime);
        maxTime = std::max((*h)->GetTime(),maxTime);
        minCharge = std::min((*h)->GetCharge(),minCharge);
        maxCharge = std::max((*h)->GetCharge(),maxCharge);
        if (points>=maxPoints) break;
    }
    if (fXPlaneGraph) delete fXPlaneGraph;
    fXPlaneGraph
        = new TGraphErrors(points,time,charge,timeRMS,chargeUnc);

    TCanvas* canvas = NULL;
    canvas = (TCanvas*) gROOT->FindObject("canvasTimeCharge");
    if (!canvas) {
        canvas=new TCanvas("canvasTimeCharge","Hit Times and Charges",500,300);
    }
    canvas->SetTopMargin(0.07);
    canvas->SetRightMargin(0.04);
    
    std::ostringstream titleStream;
    titleStream << "Hit Times and Charges"
                << " (Run: " << event->GetContext().GetRun()
                << " Event: " << event->GetContext().GetEvent()
                << ")";
    titleStream << ";Time #pm #Deltat_{rms} (#mus)";
    titleStream << ";Charge #pm #sigma (electrons)";
        
    TH1F* frame = gPad->DrawFrame(minTime/unit::microsecond,
                                  minCharge,
                                  maxTime/unit::microsecond,
                                  maxCharge,
                                  titleStream.str().c_str());
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->GetXaxis()->SetTitleOffset(1.2);

    fUPlaneGraph->SetMarkerColor(kGreen+2);
    fUPlaneGraph->SetMarkerStyle(21);
    fUPlaneGraph->Draw("P");

    fVPlaneGraph->SetMarkerColor(kBlue);
    fVPlaneGraph->SetMarkerStyle(21);
    fVPlaneGraph->Draw("P");

    fXPlaneGraph->SetMarkerColor(kRed);
    fXPlaneGraph->SetMarkerStyle(20);
    fXPlaneGraph->Draw("P");

    if (fGraphLegend) delete fGraphLegend;
    fGraphLegend = new TLegend(0.87,0.85,0.97,0.95);
    fGraphLegend->AddEntry(fXPlaneGraph,"X Hits","p");
    fGraphLegend->AddEntry(fVPlaneGraph,"V Hits","p");
    fGraphLegend->AddEntry(fUPlaneGraph,"U Hits","p");
    fGraphLegend->Draw();

    gPad->Update();
}