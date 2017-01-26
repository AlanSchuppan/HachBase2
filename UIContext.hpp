#ifndef UICONTEXT_HPP
#define UICONTEXT_HPP

//#include <QObject>

#include <string>

#include "Lang.hpp"
#include "Singleton.hpp"
#include "BaseWidget.hpp"

//##############################################################################
// CSettings
//##############################################################################
//##############################################################################

class CSettings {
    EMsg mInstrument;
public:
    CSettings();
    EMsg Instrument() const;
    void    Instrument(EMsg instrument);
};

inline EMsg CSettings::Instrument() const {
    return mInstrument;
}

inline void CSettings::Instrument(EMsg instrument) {
    mInstrument = instrument;
}

extern CSettings Settings;

//##############################################################################
// CUIContext
//##############################################################################
//##############################################################################

class CUIContext : public CSingleton {
protected:
    CBaseWidget *mpWidget;
    CBaseWidget *UIStateFind(EUIState uiState);
    static EUIState UIState(CBaseWidget *pwidget);
    void Dump(int id);
public:
    static CSingleton *CreateMe(std::string &name);
    static CBaseWidget *Create(EUIState uiState,
                               CBaseWidget *pprevious = nullptr);
    static bool Test();

    CUIContext(const std::string &name, CBaseWidget *pwidget = nullptr);
   ~CUIContext();

    CBaseWidget *UIState(EUIState uiState, bool commit = false);
    CBaseWidget *UIStatePrevious(bool commit = false);
    void Event(EUIEvent event, void *pdata);
};

extern TSingletonHost<CUIContext> UIContext;

//##############################################################################

#endif // UICONTEXT_HPP
