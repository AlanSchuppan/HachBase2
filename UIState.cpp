#include <stdint.h>

#include "UIState.hpp"

//##############################################################################
// CStateNameMap
//##############################################################################
//##############################################################################

struct CStateNameMap {
    EUIStateID StateID;
    const char *Name;
};

static const CStateNameMap StateNameMap[] = {
    { EUIStateID::None,           "None"                  },
    { EUIStateID::Home,           "WinHome"               },
    { EUIStateID::Inst,           "WinMenu - Instrument"  },
    { EUIStateID::InstString,     "WinMenu - String"      },
    { EUIStateID::InstWind,       "WinMenu - Wind"        },
    { EUIStateID::InstPercussion, "WinMenu - Percussion"  },
    { EUIStateID::Test,           "WinList"               },
};

static const uint32_t cStateNameMapCount =
    sizeof(StateNameMap) / sizeof(*StateNameMap);

const char *UIStateName(EUIStateID stateID) {
    static_assert(static_cast<uint32_t>(EUIStateID::Count)==cStateNameMapCount,
                  "Potentially incomplete table: StateNameMap");
    for (uint32_t Ix = 0; Ix < cStateNameMapCount; ++Ix)
        if (StateNameMap[Ix].StateID == stateID)
            return StateNameMap[Ix].Name;
    return "???";
}

//##############################################################################
// CUIState
//##############################################################################
//##############################################################################

CUIState::CUIState(EUIStateID uiStateID) : mUIStateID(uiStateID) {
}

CUIState::~CUIState() {
}

const char *CUIState::Name() const {
    return UIStateName(mUIStateID);
}

void CUIState::Enter(bool /*first = true*/) {
}

void CUIState::Exit(bool /*commit = false*/) {
}

EUIStateID CUIState::Event(EUIEvent /*event*/, void * /*pdata*/) {
    return EUIStateID::None;
}

EUIStateID CUIState::Click(EStringID /*stringID*/) {
    return EUIStateID::None;
}
