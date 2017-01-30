#ifndef CUISTATES_HPP
#define CUISTATES_HPP

#include "UIState.hpp"
#include "WinHome.hpp"
#include "WinMenu.hpp"

//##############################################################################

class CUIStateHome : public CUIState {
    CWinHome *mpWinHome;
public:
    CUIStateHome(EUIState uiState);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
//    void Exit(bool commit = false) override;
//    EUIState Event(EUIEvent event, void *pdata) override;
//    EUIState Click(EMsg msg) override;
};

inline void CUIStateHome::Widget(CBaseWidget *pwidget) {
    mpWinHome = dynamic_cast<CWinHome *>(pwidget);
}

//##############################################################################

class CUIStateMenuInst : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuInst(EUIState uiState);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
//    void Exit(bool commit = false) override;
//    EUIState Event(EUIEvent event, void *pdata) override;
//    EUIState Click(EMsg msg) override;
};

inline void CUIStateMenuInst::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

class CUIStateMenuString : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuString(EUIState uiState);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
    void Exit(bool commit = false) override;
//    EUIState Event(EUIEvent event, void *pdata) override;
//    EUIState Click(EMsg msg) override;
};

inline void CUIStateMenuString::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

class CUIStateMenuWind : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuWind(EUIState uiState);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
    void Exit(bool commit = false) override;
//    EUIState Event(EUIEvent event, void *pdata) override;
//    EUIState Click(EMsg msg) override;
};

inline void CUIStateMenuWind::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

class CUIStateMenuPercussion : public CUIState {
    CWinMenu *mpWinMenu;
public:
    CUIStateMenuPercussion(EUIState uiState);

    void Widget(CBaseWidget *pwidget);

    void Enter(bool first = true) override;
    void Exit(bool commit = false) override;
//    EUIState Event(EUIEvent event, void *pdata) override;
//    EUIState Click(EMsg msg) override;
};

inline void CUIStateMenuPercussion::Widget(CBaseWidget *pwidget) {
    mpWinMenu = dynamic_cast<CWinMenu *>(pwidget);
}

//##############################################################################

#endif // CUISTATES_HPP
