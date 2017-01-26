#include "UIStates.hpp"
#include "UIContext.hpp"

//#define USE_STR_MENU_MAP

//##############################################################################

CUIStateHome::CUIStateHome(EUIStateID uiStateID) :
    CUIState(uiStateID), mpWinHome(nullptr) {
}

void CUIStateHome::Enter(bool /*first = true*/) {
    if (mpWinHome == nullptr)
        return;
    mpWinHome->Instrument(Settings.Instrument());
}

//void CUIStateHome::Exit(bool commit = false) {
//}

//EUIStateID CUIStateHome::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateHome::Click(ELng msg) {
//}

//##############################################################################

CUIStateMenuInst::CUIStateMenuInst(EUIStateID uiStateID) :
    CUIState(uiStateID), mpWinMenu(nullptr) {
}

void CUIStateMenuInst::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "String",     EUIStateID::InstString     },
        { "Wind",       EUIStateID::InstWind       },
        { "Percussion", EUIStateID::InstPercussion },
        { "Test",       EUIStateID::Test           },
        { nullptr,      EUIStateID::None           }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::String,     EUIStateID::InstString     },
        { EMsg::Wind,       EUIStateID::InstWind       },
        { EMsg::Percussion, EUIStateID::InstPercussion },
        { EMsg::Test,       EUIStateID::Test           },
        { EMsg::None,       EUIStateID::None           }
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

//EUIStateID CUIStateMenuInst::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuInst::Click(EMsg msg) {
//}

//##############################################################################

CUIStateMenuString::CUIStateMenuString(EUIStateID uiStateID) :
    CUIState(uiStateID), mpWinMenu(nullptr) {
}

void CUIStateMenuString::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "Violin", EUIStateID::Home },
        { "Viola",  EUIStateID::Home },
        { "Cello",  EUIStateID::Test },
        { "Bass",   EUIStateID::Home },
        { nullptr,  EUIStateID::None }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::Violin, EUIStateID::Home },
        { EMsg::Viola,  EUIStateID::Home },
        { EMsg::Cello,  EUIStateID::Test },
        { EMsg::Bass,   EUIStateID::Home },
        { EMsg::None,   EUIStateID::None }
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

//EUIStateID CUIStateMenuString::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuString::Click(EMsg msg) {
//}

//##############################################################################

CUIStateMenuWind::CUIStateMenuWind(EUIStateID uiStateID) :
    CUIState(uiStateID), mpWinMenu(nullptr) {
}

void CUIStateMenuWind::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "Flute",   EUIStateID::Home },
        { "Oboe",    EUIStateID::Home },
        { "Bassoon", EUIStateID::Home },
        { "Trumpet", EUIStateID::Home },
        { nullptr,   EUIStateID::None }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::Flute,   EUIStateID::Home },
        { EMsg::Oboe,    EUIStateID::Home },
        { EMsg::Bassoon, EUIStateID::Home },
        { EMsg::Trumpet, EUIStateID::Home },
        { EMsg::None,    EUIStateID::None }
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

//EUIStateID CUIStateMenuWind::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuWind::Click(EMsg msg) {
//}

//##############################################################################

CUIStateMenuPercussion::CUIStateMenuPercussion(EUIStateID uiStateID) :
    CUIState(uiStateID), mpWinMenu(nullptr) {
}

void CUIStateMenuPercussion::Enter(bool first /*= true*/) {
#ifdef USE_STR_MENU_MAP
    static const CStrMenuMap MenuMap[] {
        { "Drum",       EUIStateID::Home },
        { "Cymbal",     EUIStateID::Home },
        { "Tambourine", EUIStateID::Home },
        { nullptr,      EUIStateID::None }
    };
#else // !USE_STR_MENU_MAP
    static const CMsgMenuMap MenuMap[] {
        { EMsg::Drum,       EUIStateID::Home },
        { EMsg::Cymbal,     EUIStateID::Home },
        { EMsg::Tambourine, EUIStateID::Home },
        { EMsg::None,       EUIStateID::None }
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

//EUIStateID CUIStateMenuPercussion::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuPercussion::Click(EMsg msg) {
//}
