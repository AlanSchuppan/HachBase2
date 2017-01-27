#include <iostream>
#include <sstream>

#include "WinHome.hpp"
#include "WinMenu.hpp"
#include "UIStates.hpp"
#include "UIContext.hpp"

using namespace std;

//##############################################################################
// CUIContext
//##############################################################################
//##############################################################################

CBaseWidget *CUIContext::Create(EUIState uiState, CBaseWidget *pprevious) {
    CBaseWidget *pWidget = nullptr;

    switch (uiState) {
    case EUIState::Home:
        {
            CUIStateHome *pUIState =
                new CUIStateHome(uiState);
            pWidget = new CWinHome(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIState::Inst:
        {
            CUIStateMenuInst *pUIState =
                new CUIStateMenuInst(uiState);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIState::InstString:
        {
            CUIStateMenuString *pUIState =
                new CUIStateMenuString(uiState);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIState::InstWind:
        {
            CUIStateMenuWind *pUIState =
                new CUIStateMenuWind(uiState);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIState::InstPercussion:
        {
            CUIStateMenuPercussion *pUIState =
                new CUIStateMenuPercussion(uiState);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

//    case EUIState::Test:
//        pWidget = new CWinList(new CUIState(uiState), pprevious);
//        break;

    default:
        {
            std::stringstream Message;
            Message << "CUIState::Create(): UI state \""
                    << UIStateName(uiState)
                    << "("
                    << static_cast<uint32_t>(uiState)
                    << ")\" is not implemented.";
            throw std::runtime_error(Message.str());
        }
    }

    if (pWidget != nullptr) {
        // Make sure background is painted
        pWidget->setAttribute(Qt::WA_OpaquePaintEvent, false);
        pWidget->setAttribute(Qt::WA_NoSystemBackground, false);
        pWidget->setAutoFillBackground(true);
    }

    return pWidget;
}

EUIState CUIContext::UIState(CBaseWidget *pwidget) {
    return pwidget->UIState(); // Result is valid even when pwidget is null
}

CUIContext::CUIContext(const std::string &name,
                                 CBaseWidget *pwidget) :
    CSingleton(name), mpWidget(pwidget) {
}

CUIContext::~CUIContext() {
}

CBaseWidget *CUIContext::UIStateFind(EUIState uiState) {
    CBaseWidget *pWidget = mpWidget;
    EUIState StateID =
        (pWidget != nullptr) ? pWidget->UIState() : EUIState::None;
    while (StateID != uiState && StateID != EUIState::None) {
        pWidget = dynamic_cast<CBaseWidget *>(pWidget->parentWidget());
        StateID =
            (pWidget != nullptr) ? pWidget->UIState() : EUIState::None;
    }
    return (StateID == uiState) ? pWidget : nullptr;
}

CBaseWidget *CUIContext::UIState(EUIState uiState, bool commit) {
    EUIState UIState =
        (mpWidget != nullptr) ? mpWidget->UIState() : EUIState::None;
    if (uiState == EUIState::Previous)
        uiState = UIStatePrevious();
    // If new state is not current state or no state
    if (uiState != EUIState::None && uiState != UIState) {
        // See if new state already exists
        CBaseWidget *pNextWidget = UIStateFind(uiState);

        // If new state...
        if (pNextWidget == nullptr) {
            pNextWidget = Create(uiState, mpWidget);
            if (mpWidget != nullptr)
                mpWidget->Exit(commit);
//            {
//                CBaseWidget *pPrevWidget = dynamic_cast<CBaseWidget *>(mpWidget);
//                if (pPrevWidget != nullptr)
//                    pPrevWidget->Exit(commit);
//            }
            if (pNextWidget != nullptr) {
                pNextWidget->Enter(); // Enter first time
            }
            mpWidget = pNextWidget;
        }

        // If state already exists...,
        else {
            // Remove states from top of stack before arriving at desired state
            while (mpWidget != pNextWidget) {
                mpWidget->Exit(commit);
                CBaseWidget *pPrevWidget =
                    dynamic_cast<CBaseWidget *>(mpWidget->parentWidget());
                mpWidget->close();
                mpWidget = pPrevWidget;
                mpWidget->Enter(false); // Enter again
            }
        }
        mpWidget->show();
    }
    Dump(0);
    return mpWidget;
}

EUIState CUIContext::UIStatePrevious() {
    EUIState CurrentState =
        mpWidget->UIState(); // Null mpWidget returns EUIState::None
    if (CurrentState == EUIState::Home || CurrentState == EUIState::None)
        return EUIState::None;

    CBaseWidget *pPrevWidget =
        dynamic_cast<CBaseWidget *>(mpWidget->parentWidget());
    return (pPrevWidget != nullptr) ? pPrevWidget->UIState() : EUIState::None;
}

void CUIContext::Event(EUIEvent event, void *pdata) {
    if (mpWidget != nullptr)
        mpWidget->Event(event, pdata);
}

void CUIContext::Dump(int id) {
    cout << "State " << id << ":" << endl;
    EUIState StateID = EUIState::None;
    CBaseWidget *pWidget = mpWidget;
    do {
        cout << "  " << pWidget->Name() << endl;
        StateID =
            (pWidget != nullptr) ? pWidget->UIState() : EUIState::None;
        pWidget = dynamic_cast<CBaseWidget *>(pWidget->parent());
    } while (StateID != EUIState::Home && StateID != EUIState::None);
}

CSingleton *CUIContext::CreateMe(std::string &name) {
    name = "UIContext";
    return new CUIContext(name);
}

TSingletonHost<CUIContext> UIContext(CUIContext::CreateMe);
