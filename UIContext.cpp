#include <iostream>
#include <sstream>

#include "WinHome.hpp"
#include "WinMenu.hpp"
//#include "WinList.hpp"
#include "UIState.hpp"
#include "UIStates.hpp"
#include "UIContext.hpp"

using namespace std;

//##############################################################################
// CSettings
//##############################################################################
//##############################################################################

CSettings::CSettings() : mInstrument(EMsg::Violin) {
}

CSettings Settings;

//##############################################################################
// CUIContext
//##############################################################################
//##############################################################################

CBaseWidget *CUIContext::Create(EUIStateID stateID,
                                     CBaseWidget *pprevious) {
    CBaseWidget *pWidget = nullptr;

    switch (stateID) {
    case EUIStateID::Home:
        {
            CUIStateHome *pUIState =
                new CUIStateHome(stateID);
            pWidget = new CWinHome(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIStateID::Inst:
        {
            CUIStateMenuInst *pUIState =
                new CUIStateMenuInst(stateID);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIStateID::InstString:
        {
            CUIStateMenuString *pUIState =
                new CUIStateMenuString(stateID);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIStateID::InstWind:
        {
            CUIStateMenuWind *pUIState =
                new CUIStateMenuWind(stateID);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

    case EUIStateID::InstPercussion:
        {
            CUIStateMenuPercussion *pUIState =
                new CUIStateMenuPercussion(stateID);
            pWidget = new CWinMenu(pUIState, pprevious);
            pUIState->Widget(pWidget);
        }
        break;

//    case EUIStateID::Test:
//        pWidget = new CWinList(new CUIState(stateID), pprevious);
//        break;

    default:
        {
            std::stringstream Message;
            Message << "CUIState::Create(): UI state \""
                    << UIStateName(stateID)
                    << "("
                    << static_cast<uint32_t>(stateID)
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

EUIStateID CUIContext::UIStateID(CBaseWidget *pwidget) {
    return pwidget->UIStateID(); // Result is valid even when pwidget is null
}

CUIContext::CUIContext(const std::string &name,
                                 CBaseWidget *pwidget) :
    CSingleton(name), mpWidget(pwidget) {
}

CUIContext::~CUIContext() {
}

CBaseWidget *CUIContext::StateFind(EUIStateID stateID) {
    CBaseWidget *pWidget = mpWidget;
    EUIStateID StateID =
        (pWidget != nullptr) ? pWidget->UIStateID() : EUIStateID::None;
    while (StateID != stateID && StateID != EUIStateID::None) {
        pWidget = dynamic_cast<CBaseWidget *>(pWidget->parentWidget());
        StateID =
            (pWidget != nullptr) ? pWidget->UIStateID() : EUIStateID::None;
    }
    return (StateID == stateID) ? pWidget : nullptr;
}

CBaseWidget *CUIContext::State(EUIStateID stateID, bool commit) {
    EUIStateID UIStateID =
        (mpWidget != nullptr) ? mpWidget->UIStateID() : EUIStateID::None;
    // If new state is not current state or no state
    if (stateID != EUIStateID::None && stateID != UIStateID) {
        // See if new state already exists
        CBaseWidget *pNextWidget = StateFind(stateID);

        // If new state...
        if (pNextWidget == nullptr) {
            pNextWidget = Create(stateID, mpWidget);
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

CBaseWidget *CUIContext::StatePrevious(bool commit) {
    EUIStateID CurrentState =
        mpWidget->UIStateID(); // Null mpWidget returns EUIState::None
    if (CurrentState == EUIStateID::Home || CurrentState == EUIStateID::None)
        return nullptr;

    CBaseWidget *pPrevWidget =
        dynamic_cast<CBaseWidget *>(mpWidget->parentWidget());
    EUIStateID PrevStateID =
        pPrevWidget->UIStateID(); // Null pPrevWidget returns EUIState::None

    return State(PrevStateID, commit);
}

void CUIContext::Event(EUIEvent event, void *pdata) {
    if (mpWidget != nullptr)
        mpWidget->Event(event, pdata);
}

void CUIContext::Dump(int id) {
    cout << "State " << id << ":" << endl;
    EUIStateID StateID = EUIStateID::None;
    CBaseWidget *pWidget = mpWidget;
    do {
        cout << "  " << pWidget->Name() << endl;
        StateID =
            (pWidget != nullptr) ? pWidget->UIStateID() : EUIStateID::None;
        pWidget = dynamic_cast<CBaseWidget *>(pWidget->parent());
    } while (StateID != EUIStateID::Home && StateID != EUIStateID::None);
}

CSingleton *CUIContext::CreateMe(std::string &name) {
    name = "UIContext";
    return new CUIContext(name);
}

TSingletonHost<CUIContext> UIContext(CUIContext::CreateMe);
