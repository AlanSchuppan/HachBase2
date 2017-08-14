#ifndef UISTATE_HPP
#define UISTATE_HPP

#include "Lang.hpp"

//##############################################################################
// EUIEvent
//##############################################################################
//##############################################################################

enum class EUIEvent {
    None, Count
};

const char *UIEventName(EUIEvent event);

//##############################################################################
// EUIState
//##############################################################################
//##############################################################################

enum class EUIState {
  None, Previous, Home, // Required special states
  Inst, InstString, InstWind, InstPercussion, Test,
  Count // Required count, but is not a valid state
};

const char *UIStateName(EUIState stateID);

//##############################################################################
// CUIStateFuncBase
//##############################################################################
//##############################################################################

//class CUIStateFuncBase {
//public:
//    CUIStateFuncBase();
//    virtual void Enter(bool first = true);
//    virtual void Exit(bool commit = false);
//    //virtual void UIState(EUIState uiState, bool commit = false);
//    virtual EUIState Event(EUIEvent event, void *pdata);
//    //virtual EUIState Click(EMsg msg);
//};

//##############################################################################
// CUIState
//##############################################################################
//##############################################################################

class CUIState {
    EUIState mUIState;
public:
    CUIState(EUIState stateID);
    virtual ~CUIState();

    EUIState UIState() const;
    const char *Name() const;

    virtual void Enter(bool first = true);
    virtual void Exit(bool commit = false);
    virtual void UIState(EUIState uiState, bool commit = false);
    virtual EUIState Event(EUIEvent event, void *pdata);
    virtual EUIState Click(EMsg msg);
};

inline EUIState CUIState::UIState() const {
    return mUIState;
}

#endif // UISTATE_HPP
