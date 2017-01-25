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

//EUIStateID CUIStateHome::Click(EStringID stringID) {
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
        { "Test",       EUIStateID::None           },
//        { "Test",       EUIStateID::Test           },
        { nullptr,      EUIStateID::None           }
    };
#else // !USE_STR_MENU_MAP
    static const CStrIDMenuMap MenuMap[] {
        { EString::String,     EUIStateID::InstString     },
        { EString::Wind,       EUIStateID::InstWind       },
        { EString::Percussion, EUIStateID::InstPercussion },
        { EString::Test,       EUIStateID::None           },
//        { EString::Test,       EUIStateID::Test           },
        { EString::None,       EUIStateID::None           }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"Instrument Type");
#else // !USE_STR_MENU_MAP
            CLang Lang;
            mpWinMenu->Label(EString::InstrumentType);
#endif
        }
    }
}

//void CUIStateMenuInst::Exit(bool commit = false) {
//}

//EUIStateID CUIStateMenuInst::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuInst::Click(EStringID stringID) {
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
    static const CStrIDMenuMap MenuMap[] {
        { EString::Violin, EUIStateID::Home },
        { EString::Viola,  EUIStateID::Home },
        { EString::Cello,  EUIStateID::Test },
        { EString::Bass,   EUIStateID::Home },
        { EString::None,   EUIStateID::None }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"String Instruments");
#else // !USE_STR_MENU_MAP
            mpWinMenu->Label(EString::String);
#endif
        }
    }
}

void CUIStateMenuString::Exit(bool commit /*= false*/) {
    if (mpWinMenu == nullptr)
        return;
    if (commit) {
        EString Label = mpWinMenu->Selection();
        if (Label != EString::None)
            Settings.Instrument(Label);
    }
}

//EUIStateID CUIStateMenuString::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuString::Click(EStringID stringID) {
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
    static const CStrIDMenuMap MenuMap[] {
        { EString::Flute,   EUIStateID::Home },
        { EString::Oboe,    EUIStateID::Home },
        { EString::Bassoon, EUIStateID::Home },
        { EString::Trumpet, EUIStateID::Home },
        { EString::None,    EUIStateID::None }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"Wind Instruments");
#else // !USE_STR_MENU_MAP
            mpWinMenu->Label(EString::Wind);
#endif
        }
    }
}

void CUIStateMenuWind::Exit(bool commit /*= false*/) {
    if (mpWinMenu == nullptr)
        return;
    if (commit) {
        EString Label = mpWinMenu->Selection();
        if (Label != EString::None)
            Settings.Instrument(Label);
    }
}

//EUIStateID CUIStateMenuWind::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuWind::Click(EStringID stringID) {
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
    static const CStrIDMenuMap MenuMap[] {
        { EString::Drum,       EUIStateID::Home },
        { EString::Cymbal,     EUIStateID::Home },
        { EString::Tambourine, EUIStateID::Home },
        { EString::None,       EUIStateID::None }
    };
#endif

    if (first) {
        if (mpWinMenu != nullptr) {
            mpWinMenu->Menu(MenuMap);
#ifdef USE_STR_MENU_MAP
            mpWinMenu->Label(L"Percussion Instruments");
#else // !USE_STR_MENU_MAP
            mpWinMenu->Label(EString::Percussion);
#endif
        }
    }
}

void CUIStateMenuPercussion::Exit(bool commit /*= false*/) {
    if (mpWinMenu == nullptr)
        return;
    if (commit) {
        EString Label = mpWinMenu->Selection();
        if (Label != EString::None)
            Settings.Instrument(Label);
    }
}

//EUIStateID CUIStateMenuPercussion::Event(EUIEvent event, void *pdata) {
//}

//EUIStateID CUIStateMenuPercussion::Click(EStringID stringID) {
//}
