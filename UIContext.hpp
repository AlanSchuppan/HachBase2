#ifndef UICONTEXT_HPP
#define UICONTEXT_HPP

//#include <QObject>

#include <string>

#include "Lang.hpp"
#include "Singleton.hpp"
#include "BaseWidget.hpp"

//##############################################################################
// CUIContext
//##############################################################################
//##############################################################################

class CUIContext : public CSingleton {
protected:
    CBaseWidget *mpWidget;
    CBaseWidget *UIStateFind(EUIState uiState);
    static EUIState UIState(CBaseWidget *pwidget);
    EUIState UIStatePrevious();
    void Dump(int id);
public:
    static CSingleton *CreateMe(std::string &name);
    static CBaseWidget *Create(EUIState uiState,
                               CBaseWidget *pprevious = nullptr);
    static bool Test();

    CUIContext(const std::string &name, CBaseWidget *pwidget = nullptr);
   ~CUIContext();

    CBaseWidget *UIState(EUIState uiState, bool commit = false);
    void Event(EUIEvent event, void *pdata);
};

extern TSingletonHost<CUIContext> UIContext;

//##############################################################################

#endif // UICONTEXT_HPP
