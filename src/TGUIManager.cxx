#include "TGUIManager.hxx"
#include "TEventDisplay.hxx"

#include <TGFrame.h>
#include <TGButton.h>
#include <TGListBox.h>
#include <TGLabel.h>
#include <TGTextEntry.h>

#include <TEveManager.h>
#include <TEveBrowser.h>

#include <TSystem.h>

CP::TGUIManager::TGUIManager() {
    MakeResultsTab();
    MakeControlTab();
}

void CP::TGUIManager::MakeControlTab() {
    TEveBrowser* browser = gEve->GetBrowser();

    // Define the generic layout.  The last four parameters are the padding
    // around the widgets.
    TGLayoutHints* layoutHints 
        = new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX,
                            2, 2, 2, 2);

    // Embed a new frame in the event browser to have control buttons.
    browser->StartEmbedding(TRootBrowser::kLeft);
    TGMainFrame* mainFrame = new TGMainFrame(gClient->GetRoot(), 1000, 600);
    mainFrame->SetWindowName("Event Control");
    mainFrame->SetCleanup(kDeepCleanup);

    TGVerticalFrame* hf = new TGVerticalFrame(mainFrame);
    TGTextButton* textButton;

    // The general action buttons.
    textButton = new TGTextButton(hf, "Previous Event");
    textButton->SetToolTipText("Go to previous event.");
    textButton->SetTextJustify(36);
    textButton->SetMargins(0,0,0,0);
    textButton->SetWrapLength(-1);
    hf->AddFrame(textButton, layoutHints);
    fPrevEventButton = textButton;

    textButton = new TGTextButton(hf, "Redraw Event");
    textButton->SetToolTipText("Refresh the current view.");
    textButton->SetTextJustify(36);
    textButton->SetMargins(0,0,0,0);
    textButton->SetWrapLength(-1);
    hf->AddFrame(textButton, layoutHints);
    fDrawEventButton = textButton;

    textButton = new TGTextButton(hf, "Next Event");
    textButton->SetToolTipText("Go to previous event.");
    textButton->SetTextJustify(36);
    textButton->SetMargins(0,0,0,0);
    textButton->SetWrapLength(-1);
    hf->AddFrame(textButton, layoutHints);
    fNextEventButton = textButton;

    // Create the buttons to select which types of objects are showed.
    TGCheckButton *checkButton;
    checkButton = new TGCheckButton(hf,"Show Trajectories");
    checkButton->SetToolTipText(
        "Show the GEANT4 trajectories and trajectory points.");
    checkButton->SetTextJustify(36);
    checkButton->SetMargins(0,0,0,0);
    checkButton->SetWrapLength(-1);
    hf->AddFrame(checkButton, layoutHints);
    fShowTrajectoriesButton = checkButton;

    checkButton = new TGCheckButton(hf,"Show G4 Hits");
    checkButton->SetToolTipText(
        "Show the GEANT4 hits.  This shows the energy deposition in the "
        "defined sensitive detectors.");
    checkButton->SetTextJustify(36);
    checkButton->SetMargins(0,0,0,0);
    checkButton->SetWrapLength(-1);
    hf->AddFrame(checkButton, layoutHints);
    checkButton->SetOn();
    fShowG4HitsButton = checkButton;

    checkButton = new TGCheckButton(hf,"Show Recon Objects");
    checkButton->SetToolTipText(
        "Show the reconstructed objects.");
    checkButton->SetTextJustify(36);
    checkButton->SetMargins(0,0,0,0);
    checkButton->SetWrapLength(-1);
    hf->AddFrame(checkButton, layoutHints);
    fShowFitsButton = checkButton;

    /////////////////////
    // Buttons to draw the digits.
    /////////////////////
    textButton = new TGTextButton(hf, "Draw X Digits");
    fDrawXDigitsButton = textButton;
    textButton->SetTextJustify(36);
    textButton->SetMargins(0,0,0,0);
    textButton->SetWrapLength(-1);
    hf->AddFrame(textButton, layoutHints);
    textButton->SetToolTipText("Draw the X digits vs wire number."
                               "  Also show the X hits.");

    textButton = new TGTextButton(hf, "Draw V Digits");
    fDrawVDigitsButton = textButton;
    textButton->SetTextJustify(36);
    textButton->SetMargins(0,0,0,0);
    textButton->SetWrapLength(-1);
    hf->AddFrame(textButton, layoutHints);
    textButton->SetToolTipText("Draw the V digits vs wire number."
                               "  Also show the V hits.");

    textButton = new TGTextButton(hf, "Draw U Digits");
    fDrawUDigitsButton = textButton;
    textButton->SetTextJustify(36);
    textButton->SetMargins(0,0,0,0);
    textButton->SetWrapLength(-1);
    hf->AddFrame(textButton, layoutHints);
    textButton->SetToolTipText("Draw the U digits vs wire number."
                               "  Also show the U hits.");


    checkButton = new TGCheckButton(hf,"Show raw digits");
    checkButton->SetToolTipText(
        "Show the raw, not calibrated digits.");
    checkButton->SetTextJustify(36);
    checkButton->SetMargins(0,0,0,0);
    checkButton->SetWrapLength(-1);
    hf->AddFrame(checkButton, layoutHints);
    fShowRawDigitsButton = checkButton;

    // Do the final layout and mapping.
    mainFrame->AddFrame(hf, layoutHints);
    mainFrame->MapSubwindows();
    mainFrame->Resize();
    mainFrame->MapWindow();
    browser->StopEmbedding();
    browser->SetTabTitle("Control", 0);
}

void CP::TGUIManager::MakeResultsTab() {
    TEveBrowser* browser = gEve->GetBrowser();

    // Embed a new frame in the event browser to select fit objects.
    browser->StartEmbedding(TRootBrowser::kLeft);
    TGMainFrame* mainFrame = new TGMainFrame(gClient->GetRoot(), 1000, 600);
    mainFrame->SetWindowName("Fit Selection");
    mainFrame->SetCleanup(kDeepCleanup);

    TGVerticalFrame* hf = new TGVerticalFrame(mainFrame);

    // Create the listbox for the results.
    fResultsList = new TGListBox(hf);
    fResultsList->SetMultipleSelections(true);
    TGLayoutHints* layoutList = new TGLayoutHints(kLHintsLeft
                                                  | kLHintsTop
                                                  | kLHintsExpandX 
                                                  | kLHintsExpandY);
    hf->AddFrame(fResultsList,layoutList);

    // Create a text entry button to choose a default result.
    TGLabel* txt = new TGLabel(hf,"Default Result");
    TGLayoutHints* layoutHints = new TGLayoutHints(kLHintsLeft
                                                   | kLHintsTop
                                                   | kLHintsExpandX,
                                                   2,2,2,2);
    hf->AddFrame(txt,layoutHints);

    // Create a text entry button to choose a default result.  This also sets
    // the default default result.  It should be possible to override this
    // from the command line!
    fDefaultResult = new TGTextEntry(hf);
    fDefaultResult->SetText("TCaptainRecon/final");

    hf->AddFrame(fDefaultResult,layoutHints);
    
    // Do the final layout and mapping.
    TGLayoutHints* layoutFrame 
        = new TGLayoutHints(kLHintsLeft 
                            | kLHintsTop 
                            | kLHintsExpandX
                            | kLHintsExpandY,
                            2, 2, 2, 2);
    mainFrame->AddFrame(hf, layoutFrame);
    mainFrame->MapSubwindows();
    mainFrame->Resize();
    mainFrame->MapWindow();
    browser->StopEmbedding();
    browser->SetTabTitle("Recon", 0);
}

CP::TGUIManager::~TGUIManager() { }
