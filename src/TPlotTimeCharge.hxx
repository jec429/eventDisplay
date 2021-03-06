#ifndef TPlotTimeCharge_hxx_seen
#define TPlotTimeCharge_hxx_seen
#include <vector>

namespace CP {
    class TPlotTimeCharge;
};
class TH2F;
class TObject;
class TGraphErrors;
class TLegend;
class TF1;

/// Plot the digits and 2D hits on a canvas for the current event.  This can
/// be connected to buttons in the event display GUI.
class CP::TPlotTimeCharge {
public:
    /// Create the object to do the plotting. 
    explicit TPlotTimeCharge();
    ~TPlotTimeCharge();

    /// Draw the charge vs time in a graph.
    void DrawTimeCharge();

    /// Fit the charge vs time in a graph.
    void FitTimeCharge();

private:

    /// The graphs...
    TGraphErrors* fXPlaneGraph;
    TGraphErrors* fVPlaneGraph;
    TGraphErrors* fUPlaneGraph;

    /// The legend
    TLegend* fGraphLegend;

    TF1* fElectronLifeFunction;
};

#endif
