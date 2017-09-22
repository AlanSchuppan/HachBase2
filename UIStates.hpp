#ifndef CUISTATES_HPP
#define CUISTATES_HPP

#include <vector>
#include <string>

#include "UIState.hpp"
#include "WinHome.hpp"
#include "WinMenu.hpp"

//##############################################################################

class ITitleModel {
public:
    virtual ~ITitleModel();
    virtual std::wstring Title() const = 0;
};

//##############################################################################

class CTitleModel : public ITitleModel {
public:
    CTitleModel(EMsg msg);
    CTitleModel(const std::wstring &title);

    virtual std::wstring Title() const override;
private:
    std::wstring mTitle;
};

//##############################################################################

class ISelectModel {
public:
    static const uint8_t flgNone = 0, flgDisabled = 1, flgOmitted = 2,
                         flgSelected = 4, flgChecked = 8;
    virtual size_t       Count() const = 0;
    virtual std::wstring Text(size_t ix) const = 0;
    virtual uint8_t      Flags(size_t ix) const = 0;
    virtual void         Flags(size_t Ix, uint8_t flags) = 0;
    virtual EUIState     NextState() const = 0;
    virtual size_t       SelectedIx() const = 0;

//    virtual uint8_t Item(size_t ix, std::wstring &text) const = 0;
//    virtual size_t  SelectedIx() const = 0;
//    virtual void    SelectedIx(size_t ix) = 0;
//    virtual bool    Checked(size_t ix);
//    virtual void    Checked(size_t ix, bool checked);
};

//##############################################################################

struct CSelectItem {
    EMsg      Text;
    wchar_t *pText;
    EUIState NextState;
    uint8_t  Flags;
};

struct CSelectModelItem {
    std::wstring Text;
    uint8_t      Flags;
    EUIState     NextState;
};

class CSelectModel : public ISelectModel {
public:
    virtual size_t       Count() const override;
    virtual std::wstring Text(size_t ix) const override;
    virtual uint8_t      Flags(size_t ix) const override;
    virtual void         Flags(size_t ix, uint8_t flags) override;
    virtual EUIState     NextState() const override;
    virtual size_t       SelectedIx() const override;

    void Load(const CSelectItem *pselectItems);

private:
//    size_t mCount;
//    std::vector<std::wstring> mText;
//    std::vector<uint8_t> mFlags;
//    std::vector<EUIState> mNextStates;
    std::vector<CSelectModelItem> mModelItems;
};

//##############################################################################

class IMenu {
public:
    static const uint8_t flgNone = 0, flgDisabled = 1, flgSelected = 2;
    virtual std::wstring Title() = 0;
    virtual void Items(std::vector<std::wstring> &names,
                       std::vector<uint8_t> &flags) const = 0;
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

class CMenuModel : public ITitleModel, public ISelectModel {
public:
    CMenuModel(EMsg titleID);
    virtual size_t       Count() const;
    virtual std::wstring Text(size_t ix) const;
    virtual uint8_t      Flags(size_t ix) const;
    virtual void         Flags(size_t Ix, uint8_t flags);

protected:
    std::wstring mTitle;
    EMsg mTitleID;
//    std::vector<std::wstring> mStrings;
//    std::vector<EMsg> mMsgIDs;
    std::vector<uint8_t> mFlags;
    size_t mCount;
    size_t mSelectedIx;

    void Load(const CMenuItem *pmenuItems);
};

class CMenuBase : public IMenu {
public:
    CMenuBase(EMsg titleID);

    // IMenu
    std::wstring Title() override;
    void Items(std::vector<std::wstring> &names,
               std::vector<uint8_t> &flags) const override;
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
