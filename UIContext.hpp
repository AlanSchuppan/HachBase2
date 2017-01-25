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
    EString mInstrument;
public:
    CSettings();
    EString Instrument() const;
    void    Instrument(EString instrument);
};

inline EString CSettings::Instrument() const {
    return mInstrument;
}

inline void CSettings::Instrument(EString instrument) {
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
    CBaseWidget *StateFind(EUIStateID stateID);
    static EUIStateID UIStateID(CBaseWidget *pwidget);
    void Dump(int id);
public:
    static CSingleton *CreateMe(std::string &name);
    static CBaseWidget *Create(EUIStateID state,
                               CBaseWidget *pprevious = nullptr);
    static bool Test();

    CUIContext(const std::string &name, CBaseWidget *pwidget = nullptr);
   ~CUIContext();

    CBaseWidget *State(EUIStateID stateID, bool commit = false);
    CBaseWidget *StatePrevious(bool commit = false);
    void Event(EUIEvent event, void *pdata);
};

extern TSingletonHost<CUIContext> UIContext;

//##############################################################################

#endif // UICONTEXT_HPP
