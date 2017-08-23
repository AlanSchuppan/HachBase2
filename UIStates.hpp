#ifndef CUISTATES_HPP
#define CUISTATES_HPP

#include <vector>
#include <string>

#include "UIState.hpp"
#include "WinHome.hpp"
#include "WinMenu.hpp"

//##############################################################################

class IMenu {
public:
    static const uint8_t flgNone = 0, flgDisabled = 1, flgSelected = 2;
    virtual std::wstring Title() = 0;
    virtual void Items(std::vector<std::wstring> &names,
                       std::vector<uint8_t> &flags) = 0;
    virtual size_t SelectedIx() const = 0;
    virtual void   SelectedIx(size_t ix) = 0;
};

//##############################################################################

struct CMenuItem {
    EMsg      Text;
    wchar_t *pText;
    EUIState NextState;
    uint8_t  Flags;
};

class CMenuBase : public IMenu {
public:
    CMenuBase(EMsg titleID);

    // IMenu
    std::wstring Title() override;
    void Items(std::vector<std::wstring> &names,
                           std::vector<uint8_t> &flags) override;
    virtual size_t SelectedIx() const;
    virtual void   SelectedIx(size_t ix);

protected:
    const CMenuItem  *mpMenuItems;
    size_t mCount;
    size_t mSelectedIx;
    EMsg mTitleID;

    void Load(const CMenuItem *pmenuItems);
};

//##############################################################################

class CUIStateHome : public CUIState {
public:
    CUIStateHome(EUIState uiState);

    // CUIState
    bool Enter(bool first = true) override;
    // void Exit(bool commit = false) override;
    // EUIState Event(EUIEvent event, void *pdata) override;
    // EUIState Click(EMsg msg) override;

    EMsg Instrument() const;
};

//##############################################################################

class CUIStateMenuInst : public CUIState, public CMenuBase {
public:
    CUIStateMenuInst(EUIState uiState);

//    void Widget(CBaseWidget *pwidget);

    // CUIState
    bool Enter(bool first = true) override;
    //    void Exit(bool commit = false) override;
    EUIState Event(EUIEvent event, void *pdata) override;
    //    EUIState Click(EMsg msg) override;

    // IMenu
    // std::wstring Title() override;
    // void Items(std::vector<std::wstring> &names,
    //            std::vector<uint8_t> &flags) override;
    // size_t  SelectedIx() const override;
    // void    SelectedIx(size_t ix) override;
};

//##############################################################################

class CUIStateMenuString : public CUIState, public CMenuBase {
public:
    CUIStateMenuString(EUIState uiState);

    // CUIState
    bool Enter(bool first = true) override;
    void Exit(bool commit = false) override;
    EUIState Event(EUIEvent event, void *pdata) override;
    //    EUIState Click(EMsg msg) override;

    // IMenu
    // std::wstring Title() override;
    // void Items(std::vector<std::wstring> &names,
    //            std::vector<uint8_t> &flags) override;
    // size_t  SelectedIx() const override;
    // void    SelectedIx(size_t ix) override;
};

//##############################################################################

class CUIStateMenuWind : public CUIState, public CMenuBase {
public:
    CUIStateMenuWind(EUIState uiState);

    // CUIState
    bool Enter(bool first = true) override;
    void Exit(bool commit = false) override;
    EUIState Event(EUIEvent event, void *pdata) override;
    // EUIState Click(EMsg msg) override;

    // IMenu
    // std::wstring Title() override;
    // void Items(std::vector<std::wstring> &names,
    //            std::vector<uint8_t> &flags) override;
    // size_t  SelectedIx() const override;
    // void    SelectedIx(size_t ix) override;
};

//##############################################################################

class CUIStateMenuPercussion : public CUIState, public CMenuBase {
public:
    CUIStateMenuPercussion(EUIState uiState);

    // IMenu
    bool Enter(bool first = true) override;
    void Exit(bool commit = false) override;
    EUIState Event(EUIEvent event, void *pdata) override;
    // EUIState Click(EMsg msg) override;

    // IMenu
    // std::wstring Title() override;
    // void Items(std::vector<std::wstring> &names,
    //            std::vector<uint8_t> &flags) override;
    // size_t  SelectedIx() const override;
    // void    SelectedIx(size_t ix) override;
};

//##############################################################################

#endif // CUISTATES_HPP
