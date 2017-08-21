#include "Settings.hpp"
#include "UIStates.hpp"

//#define USE_STR_MENU_MAP

struct CMenuMapOld {
    EMsg Message;
    EUIState UIState;
    bool Disabled;
};

//##############################################################################

//------------------------------------------------------------------------------
//
CMenuBase::CMenuBase() : mpMenuItems(nullptr), mCount(0), mSelectedIx(-1) {
}

//------------------------------------------------------------------------------
//
void CMenuBase::Load(const CMenuItem *pmenuItems) {
    mCount = 0;
    mSelectedIx = -1;
    mpMenuItems = pmenuItems;
    if (pmenuItems == nullptr)
        return;
    while (pmenuItems->Text != EMsg::None || pmenuItems->pText != nullptr) {
        if (mSelectedIx > mCount && (pmenuItems->Flags & flgSelected) != 0)
                mSelectedIx = mCount;
        ++mCount;
        ++pmenuItems;
    }
}

//------------------------------------------------------------------------------
//
void CMenuBase::Items(std::vector<std::wstring> &names,
                      std::vector<uint8_t> &flags) {
    names.clear();
    flags.clear();

    CLang Lang;
    const CMenuItem *pMenuItem = mpMenuItems;
    while (pMenuItem->Text != EMsg::None || pMenuItem->pText != nullptr) {
        if (pMenuItem->pText != nullptr)
            names.push_back(pMenuItem->pText);
        else
            names.push_back(Lang.Message(pMenuItem->Text));
        flags.push_back(pMenuItem->Flags);
        ++pMenuItem;
    }
}

//------------------------------------------------------------------------------
//
size_t CMenuBase::SelectedIx() const {
    return mSelectedIx;
}

//------------------------------------------------------------------------------
//
void   CMenuBase::SelectedIx(size_t ix) {
    mSelectedIx = ix;
}

//##############################################################################

CUIStateHome::CUIStateHome(EUIState uiState) :
    CUIState(uiState) {
}

void CUIStateHome::Enter(bool /*first = true*/) {
    Settings.Get().Instrument();
}

//void CUIStateHome::Exit(bool commit = false) {
//}

//EUIState CUIStateHome::Event(EUIEvent event, void *pdata) {
//}

//EUIState CUIStateHome::Click(ELng msg) {
//}

EMsg CUIStateHome::Instrument() const {
    return Settings.Get().Instrument();
}

//##############################################################################

CUIStateMenuInst::CUIStateMenuInst(EUIState uiState) : CUIState(uiState) {
}

void CUIStateMenuInst::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::String,     nullptr, EUIState::InstString,     IMenu::flgSelected },
        { EMsg::Wind,       nullptr, EUIState::InstWind,       IMenu::flgNone     },
        { EMsg::Percussion, nullptr, EUIState::InstPercussion, IMenu::flgNone     },
        { EMsg::Test,       nullptr, EUIState::Test,           IMenu::flgDisabled },
        { EMsg::None,       nullptr, EUIState::None,           IMenu::flgNone     }
    };

    if (first)
        Load(MenuItems);
}

//------------------------------------------------------------------------------
//
//void CUIStateMenuInst::Exit(bool commit = false) {
//}

//------------------------------------------------------------------------------
//
EUIState CUIStateMenuInst::Event(EUIEvent event, void *pdata) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//EUIState CUIStateMenuInst::Click(EMsg msg) {
//}

//##############################################################################

//------------------------------------------------------------------------------
//
CUIStateMenuString::CUIStateMenuString(EUIState uiState) : CUIState(uiState) {
}

//------------------------------------------------------------------------------
//
void CUIStateMenuString::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::Violin, nullptr, EUIState::Home, IMenu::flgSelected },
        { EMsg::Viola,  nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Cello,  nullptr, EUIState::Test, IMenu::flgNone     },
        { EMsg::Bass,   nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::None,   nullptr, EUIState::None, IMenu::flgNone      }
    };

    if (first)
        Load(MenuItems);
}

//------------------------------------------------------------------------------
//
void CUIStateMenuString::Exit(bool commit /*= false*/) {
    if (commit && mSelectedIx < mCount) {
        EMsg Label = mpMenuItems[mSelectedIx].Text;
        if (Label != EMsg::None)
            Settings.Get().Instrument(Label);
    }
}

EUIState CUIStateMenuString::Event(EUIEvent event, void *pdata) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//------------------------------------------------------------------------------
//
//EUIState CUIStateMenuString::Click(EMsg msg) {
//}

//##############################################################################

//------------------------------------------------------------------------------
//
CUIStateMenuWind::CUIStateMenuWind(EUIState uiState) :
    CUIState(uiState) {
}

//------------------------------------------------------------------------------
//
void CUIStateMenuWind::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::Flute,   nullptr, EUIState::Home, IMenu::flgSelected },
        { EMsg::Oboe,    nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Bassoon, nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Trumpet, nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::None,    nullptr, EUIState::None, IMenu::flgNone      }
    };

    if (first)
        Load(MenuItems);
}

//------------------------------------------------------------------------------
//
void CUIStateMenuWind::Exit(bool commit /*= false*/) {
    if (commit && mSelectedIx < mCount) {
        EMsg Label = mpMenuItems[mSelectedIx].Text;
        if (Label != EMsg::None)
            Settings.Get().Instrument(Label);
    }
}

//------------------------------------------------------------------------------
//
EUIState CUIStateMenuWind::Event(EUIEvent event, void *pdata) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//------------------------------------------------------------------------------
//
//EUIState CUIStateMenuWind::Click(EMsg msg) {
//}

//##############################################################################

//------------------------------------------------------------------------------
//
CUIStateMenuPercussion::CUIStateMenuPercussion(EUIState uiState) :
    CUIState(uiState) {
}

//------------------------------------------------------------------------------
//
void CUIStateMenuPercussion::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::Drum,       nullptr, EUIState::Home, IMenu::flgSelected },
        { EMsg::Cymbal,     nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Tambourine, nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::None,       nullptr, EUIState::None, IMenu::flgNone     }
    };

    if (first)
        Load(MenuItems);
}

//------------------------------------------------------------------------------
//
void CUIStateMenuPercussion::Exit(bool commit /*= false*/) {
    if (commit && mSelectedIx < mCount) {
        EMsg Label = mpMenuItems[mSelectedIx].Text;
        if (Label != EMsg::None)
            Settings.Get().Instrument(Label);
    }
}

//------------------------------------------------------------------------------
//
EUIState CUIStateMenuPercussion::Event(EUIEvent event, void *pdata) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//------------------------------------------------------------------------------
//
//EUIState CUIStateMenuPercussion::Click(EMsg msg) {
//}
