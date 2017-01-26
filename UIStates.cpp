#include "UIStates.hpp"
#include "UIContext.hpp"

//#define USE_STR_MENU_MAP

//##############################################################################

CUIStateHome::CUIStateHome(EUIState uiState) :
    CUIState(uiState), mpWinHome(nullptr) {
}

void CUIStateHome::Enter(bool /*first = true*/) {
    if (mpWinHome == nullptr)
        return;
    mpWinHome->Instrument(Settings.Instrument());
}

//void CUIStateHome::Exit(bool commit = false) {
//}

//EUIState CUIStateHome::Event(EUIEvent event, void *pdata) {
//}

//EUIState CUIStateHome::Click(ELng msg) {
//}

//##############################################################################

CUIStateMenuInst::CUIStateMenuInst(EUIState uiState) :
    CUIState(uiState), mpWinMenu(nullptr) {
}

void CUIStateMenuInst::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "String",     EUIState::InstString     },
        { "Wind",       EUIState::InstWind       },
        { "Percussion", EUIState::InstPercussion },
        { "Test",       EUIState::Test           },
        { nullptr,      EUIState::None           }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::String,     EUIState::InstString     },
        { EMsg::Wind,       EUIState::InstWind       },
        { EMsg::Percussion, EUIState::InstPercussion },
        { EMsg::Test,       EUIState::Test           },
        { EMsg::None,       EUIState::None           }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"Instrument Type");
#else // !USE_STR_MENU_MAP
            CLang Lang;
            mpWinMenu->Label(EMsg::InstrumentType);

            std::vector<bool> Disables;
            const CMsgMenuMap *pMenuMap = MenuMap;
            while (pMenuMap->Message != EMsg::None) {
                Disables.push_back(pMenuMap->Message == EMsg::Test);
                ++pMenuMap;
            }
            mpWinMenu->Disable(Disables);
            mpWinMenu->RowSelect(1);
#endif
        }
    }
}

//void CUIStateMenuInst::Exit(bool commit = false) {
//}

//EUIState CUIStateMenuInst::Event(EUIEvent event, void *pdata) {
//}

//EUIState CUIStateMenuInst::Click(EMsg msg) {
//}

//##############################################################################

CUIStateMenuString::CUIStateMenuString(EUIState uiState) :
    CUIState(uiState), mpWinMenu(nullptr) {
}

void CUIStateMenuString::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "Violin", EUIState::Home },
        { "Viola",  EUIState::Home },
        { "Cello",  EUIState::Test },
        { "Bass",   EUIState::Home },
        { nullptr,  EUIState::None }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::Violin, EUIState::Home },
        { EMsg::Viola,  EUIState::Home },
        { EMsg::Cello,  EUIState::Home },
        { EMsg::Bass,   EUIState::Home },
        { EMsg::None,   EUIState::None }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"String Instruments");
#else // !USE_STR_MENU_MAP
            mpWinMenu->Label(EMsg::String);
#endif
        }
    }
}

void CUIStateMenuString::Exit(bool commit /*= false*/) {
    if (mpWinMenu == nullptr)
        return;
    if (commit) {
        EMsg Label = mpWinMenu->Selection();
        if (Label != EMsg::None)
            Settings.Instrument(Label);
    }
}

//EUIState CUIStateMenuString::Event(EUIEvent event, void *pdata) {
//}

//EUIState CUIStateMenuString::Click(EMsg msg) {
//}

//##############################################################################

CUIStateMenuWind::CUIStateMenuWind(EUIState uiState) :
    CUIState(uiState), mpWinMenu(nullptr) {
}

void CUIStateMenuWind::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "Flute",   EUIState::Home },
        { "Oboe",    EUIState::Home },
        { "Bassoon", EUIState::Home },
        { "Trumpet", EUIState::Home },
        { nullptr,   EUIState::None }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::Flute,   EUIState::Home },
        { EMsg::Oboe,    EUIState::Home },
        { EMsg::Bassoon, EUIState::Home },
        { EMsg::Trumpet, EUIState::Home },
        { EMsg::None,    EUIState::None }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"Wind Instruments");
#else // !USE_STR_MENU_MAP
            mpWinMenu->Label(EMsg::Wind);
#endif
        }
    }
}

void CUIStateMenuWind::Exit(bool commit /*= false*/) {
    if (mpWinMenu == nullptr)
        return;
    if (commit) {
        EMsg Label = mpWinMenu->Selection();
        if (Label != EMsg::None)
            Settings.Instrument(Label);
    }
}

//EUIState CUIStateMenuWind::Event(EUIEvent event, void *pdata) {
//}

//EUIState CUIStateMenuWind::Click(EMsg msg) {
//}

//##############################################################################

CUIStateMenuPercussion::CUIStateMenuPercussion(EUIState uiState) :
    CUIState(uiState), mpWinMenu(nullptr) {
}

void CUIStateMenuPercussion::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "Drum",       EUIState::Home },
        { "Cymbal",     EUIState::Home },
        { "Tambourine", EUIState::Home },
        { nullptr,      EUIState::None }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::Drum,       EUIState::Home },
        { EMsg::Cymbal,     EUIState::Home },
        { EMsg::Tambourine, EUIState::Home },
        { EMsg::None,       EUIState::None }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"Percussion Instruments");
#else // !USE_STR_MENU_MAP
            mpWinMenu->Label(EMsg::Percussion);
#endif
        }
    }
}

void CUIStateMenuPercussion::Exit(bool commit /*= false*/) {
    if (mpWinMenu == nullptr)
        return;
    if (commit) {
        EMsg Label = mpWinMenu->Selection();
        if (Label != EMsg::None)
            Settings.Instrument(Label);
    }
}

//EUIState CUIStateMenuPercussion::Event(EUIEvent event, void *pdata) {
//}

//EUIState CUIStateMenuPercussion::Click(EMsg msg) {
//}
