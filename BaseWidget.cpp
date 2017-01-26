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

EUIState CBaseWidget::PrevStateID() const {
    EUIState UIState = EUIState::None;
    if (mpUIState != nullptr && mpUIState->UIState() != EUIState::Home) {
        CBaseWidget *pBaseWidget = dynamic_cast<CBaseWidget *>(parentWidget());
        if (pBaseWidget != nullptr)
            UIState = pBaseWidget->UIState();
    }
    return UIState;
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

EUIState CBaseWidget::Event(EUIEvent event, void *pdata) {
    return (mpUIState != nullptr)
        ? mpUIState->Event(event, pdata) : EUIState::None;
}

EUIState CBaseWidget::Click(EMsg msg) {
    return  (mpUIState != nullptr)
        ? mpUIState->Click(msg) : EUIState::None;
}

//##############################################################################
