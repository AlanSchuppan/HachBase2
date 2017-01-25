#include "BaseWidget.hpp"

#include <iostream>

#define DEBUG_ME

using namespace std;

//##############################################################################
// CBaseWidget
//##############################################################################
//##############################################################################

CBaseWidget::CBaseWidget(CUIState *puiState, QWidget *parent) :
    QWidget(parent),
    mpUIState(puiState) {
}

CBaseWidget::~CBaseWidget() {
  delete mpUIState;
}

EUIStateID CBaseWidget::PrevStateID() const {
    EUIStateID UIStateID = EUIStateID::None;
    if (mpUIState != nullptr && mpUIState->UIStateID() != EUIStateID::Home) {
        CBaseWidget *pBaseWidget = dynamic_cast<CBaseWidget *>(parentWidget());
        if (pBaseWidget != nullptr)
            UIStateID = pBaseWidget->UIStateID();
    }
    return UIStateID;
}

void CBaseWidget::Enter(bool first) {
#ifdef DEBUG_ME
    cout << "CBaseWidget::Enter(): "
         << ((mpUIState != nullptr) ? mpUIState->Name() : "???")
         << ((first) ? " first" : " again") << endl;
#endif
    if (mpUIState != nullptr)
        mpUIState->Enter(first);
}

void CBaseWidget::Exit(bool commit) {
#ifdef DEBUG_ME
    cout << "CBaseWidget::Exit(): "
         << ((mpUIState != nullptr) ? mpUIState->Name() : "???")
         << ((commit) ? " commit" : " cancel") << endl;
#endif
    if (mpUIState != nullptr)
        mpUIState->Exit(commit);
}

EUIStateID CBaseWidget::Event(EUIEvent event, void *pdata) {
    return (mpUIState != nullptr)
        ? mpUIState->Event(event, pdata) : EUIStateID::None;
}

EUIStateID CBaseWidget::Click(EStringID stringID) {
    return  (mpUIState != nullptr)
        ? mpUIState->Click(stringID) : EUIStateID::None;
}

//##############################################################################
