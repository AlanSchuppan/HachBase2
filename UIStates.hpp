#ifndef CUISTATES_HPP
#define CUISTATES_HPP

#include "UIState.hpp"
#include "WinHome.hpp"
#include "WinMenu.hpp"

//##############################################################################

class CUIStateHome : public CUIState {
    CWinHome *mpWinHome;
public:
    CUIStateHome(EUIStateID uiStateID);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
//    void Exit(bool commit = false) override;
//    EUIStateID Event(EUIEvent event, void *pdata) override;
//    EUIStateID Click(EStringID stringID) override;
};

inline void CUIStateHome::Widget(CBaseWidget *pwidget) {
    mpWinHome = dynamic_cast<CWinHome *>(pwidget);
}

//##############################################################################

class CUIStateMenuInst : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuInst(EUIStateID uiStateID);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
//    void Exit(bool commit = false) override;
//    EUIStateID Event(EUIEvent event, void *pdata) override;
//    EUIStateID Click(EStringID stringID) override;
};

inline void CUIStateMenuInst::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

class CUIStateMenuString : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuString(EUIStateID uiStateID);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
    void Exit(bool commit = false) override;
//    EUIStateID Event(EUIEvent event, void *pdata) override;
//    EUIStateID Click(EStringID stringID) override;
};

inline void CUIStateMenuString::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

class CUIStateMenuWind : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuWind(EUIStateID uiStateID);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
    void Exit(bool commit = false) override;
//    EUIStateID Event(EUIEvent event, void *pdata) override;
//    EUIStateID Click(EStringID stringID) override;
};

inline void CUIStateMenuWind::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

class CUIStateMenuPercussion : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuPercussion(EUIStateID uiStateID);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
    void Exit(bool commit = false) override;
//    EUIStateID Event(EUIEvent event, void *pdata) override;
//    EUIStateID Click(EStringID stringID) override;
};

inline void CUIStateMenuPercussion::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

#endif // CUISTATES_HPP
