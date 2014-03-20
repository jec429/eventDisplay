#ifndef TGUIManager_hxx_seen
#define TGUIManager_hxx_seen

#include <TGButton.h>
#include <TGListBox.h>
#include <TGTextEntry.h>

namespace CP {
    class TGUIManager;
}


/// This creates the GUI interface for the event display, and then provides
/// handles so that other functions can connect to the interface.  A pointer
/// to each interface widget can be accessed by a method named by it's
/// function.  For instance, the "Read Next Event" button is named
/// "GetNextEventButton()", and returns a TGButton pointer.  This is managed
/// by the CP::TEventDisplay class which returns it via the GetGUI() method.
///
/// \note This does not connect any actions to the buttons.  It only
/// constructs the GUI and then allows access to the GUI widget.
///
/// \note The default state of widgets (e.g. the button widgets) is set when
/// the widget is created.  This is how the default drawing attributes can be
/// set.
class CP::TGUIManager {
public:
    /// Actually construct all the GUI.
    TGUIManager();
    ~TGUIManager();

    //////////////////////
    // CONTROL TAB WIDGETS
    //////////////////////

    /// Get the next event button widget.
    TGButton* GetNextEventButton() {return fNextEventButton;}

    /// Get the redraw current event button widget.
    TGButton* GetDrawEventButton() {return fDrawEventButton;}

    /// Get the previous event button widget.
    TGButton* GetPrevEventButton() {return fPrevEventButton;}

    /// Get the check button selecting if reconstruction objects are shown.
    TGButton* GetShowFitsButton() {return fShowFitsButton;}

    /// Get the check button selecting if trajectories should be shown.
    TGButton* GetShowTrajectoriesButton() {return fShowTrajectoriesButton;}

    /// Get the check button selecting if G4 hits should be shown.
    TGButton* GetShowG4HitsButton() {return fShowG4HitsButton;}

    /// Get the button to draw the X plane digits.
    TGButton* GetDrawXDigitsButton() {return fDrawXDigitsButton;}

    /// Get the button to draw the V plane digits.
    TGButton* GetDrawVDigitsButton() {return fDrawVDigitsButton;}

    /// Get the button to draw the U plane digits.
    TGButton* GetDrawUDigitsButton() {return fDrawUDigitsButton;}

    /// Get the button to select if raw or calibrated digits should be drawn.
    TGButton* GetShowRawDigitsButton() {return fShowRawDigitsButton;}

    /// Get the check button selecting if hits associated with shown
    /// reconstruction objects should be drawn.
    TGButton* GetShowFitsHitsButton() {return fShowFitsHitsButton;}

    /// Get the button to show constituent clusters of an object or not.
    TGButton* GetShowConstituentClustersButton() 
        {return fShowConstituentClustersButton;}

    /// Get the button to select if raw or calibrated digits should be drawn.
    TGButton* GetShowClusterUncertaintyButton() 
        {return fShowClusterUncertaintyButton;}

    //////////////////////
    // RESULTS TAB WIDGETS
    //////////////////////

    /// Get the list box with the select results to show.
    TGListBox* GetResultsList() {return fResultsList;}

    /// The get text entry widget for the default result to show.
    TGTextEntry* GetDefaultResult() {return fDefaultResult;}

private:

    /// Make a tab in the browser for control buttons.
    void MakeControlTab();

    ////////////////////////////////////////
    // Widgets in the control tab.
    ////////////////////////////////////////
    TGButton* fNextEventButton;
    TGButton* fDrawEventButton;
    TGButton* fPrevEventButton;
    TGButton* fShowFitsButton;
    TGButton* fShowTrajectoriesButton;
    TGButton* fShowG4HitsButton;
    TGButton* fDrawUDigitsButton;
    TGButton* fDrawVDigitsButton;
    TGButton* fDrawXDigitsButton;
    TGButton* fShowRawDigitsButton;
    TGButton* fShowFitsHitsButton;
    TGButton* fShowConstituentClustersButton;
    TGButton* fShowClusterUncertaintyButton;

    /// Make a tab in the browser to select algorithms shown.
    void MakeResultsTab();
    
    ////////////////////////////////////////
    // Widgets in the results tab.
    ////////////////////////////////////////

    /// A widget containing a list of possible TAlgorithmResult object names
    /// to be displayed (when selected).
    TGListBox* fResultsList;

    /// A regular expression to select the default result(s) to be selected.
    TGTextEntry* fDefaultResult;

};
#endif
