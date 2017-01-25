#ifndef UISTATE_HPP
#define UISTATE_HPP

//##############################################################################
// EStringID
//##############################################################################
//##############################################################################

enum class EStringID {
  None, Test
};

//##############################################################################
// EUIEvent
//##############################################################################
//##############################################################################

enum class EUIEvent {
    None, Count
};

const char *UIEventName(EUIEvent event);

//##############################################################################
// EUIStateID
//##############################################################################
//##############################################################################

enum class EUIStateID {
  None, Home, Test, Inst, InstString, InstWind, InstPercussion, Count
};

const char *UIStateName(EUIStateID stateID);

//##############################################################################
// CUIState
//##############################################################################
//##############################################################################

class CUIState {
    EUIStateID mUIStateID;
public:
    CUIState(EUIStateID stateID);
    virtual ~CUIState();

    EUIStateID UIStateID() const;
    const char *Name() const;

    virtual void Enter(bool first = true);
    virtual void Exit(bool commit = false);
    virtual EUIStateID Event(EUIEvent event, void *pdata);
    virtual EUIStateID Click(EStringID stringID);
};

inline EUIStateID CUIState::UIStateID() const {
    return mUIStateID;
}

#endif // UISTATE_HPP
