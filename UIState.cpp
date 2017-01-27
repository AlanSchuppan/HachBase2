#include <stdint.h>

#include "UIContext.hpp"
#include "UIState.hpp"

//##############################################################################
// CStateNameMap
//##############################################################################
//##############################################################################

struct CStateNameMap {
    EUIState StateID;
    const char *Name;
};

static const CStateNameMap StateNameMap[] = {
    { EUIState::None,           "None"                  },
    { EUIState::Previous,       "Previous"              },
    { EUIState::Home,           "WinHome"               },
    { EUIState::Inst,           "WinMenu - Instrument"  },
    { EUIState::InstString,     "WinMenu - String"      },
    { EUIState::InstWind,       "WinMenu - Wind"        },
    { EUIState::InstPercussion, "WinMenu - Percussion"  },
    { EUIState::Test,           "Test"                  },
};

static const uint32_t cStateNameMapCount =
    sizeof(StateNameMap) / sizeof(*StateNameMap);

const char *UIStateName(EUIState stateID) {
    static_assert(static_cast<uint32_t>(EUIState::Count)==cStateNameMapCount,
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

CUIState::CUIState(EUIState uiState) : mUIState(uiState) {
}

CUIState::~CUIState() {
}

const char *CUIState::Name() const {
    return UIStateName(mUIState);
}

void CUIState::Enter(bool /*first = true*/) {
}

void CUIState::Exit(bool /*commit = false*/) {
}

void CUIState::UIState(EUIState uiState, bool commit) {
    UIContext.Get().UIState(uiState, commit);
}

EUIState CUIState::Event(EUIEvent /*event*/, void * /*pdata*/) {
    return EUIState::None;
}

EUIState CUIState::Click(EMsg /*msg*/) {
    return EUIState::None;
}
