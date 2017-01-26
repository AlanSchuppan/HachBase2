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
  None, Home, Test, Inst, InstString, InstWind, InstPercussion, Count
};

const char *UIStateName(EUIState stateID);

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
    virtual EUIState Event(EUIEvent event, void *pdata);
    virtual EUIState Click(EMsg msg);
};

inline EUIState CUIState::UIState() const {
    return mUIState;
}

#endif // UISTATE_HPP
