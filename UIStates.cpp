#include "Settings.hpp"
#include "UIStates.hpp"
#include "Lang.hpp"

//#define USE_STR_MENU_MAP

//##############################################################################

ITitleModel::~ITitleModel() {
}

//##############################################################################

CTitleModel::CTitleModel(EMsg msg) {
    CLang Lang;
    mTitle = Lang.Message(msg);
}

CTitleModel::CTitleModel(const std::wstring &title) : mTitle(title) {
}

std::wstring CTitleModel::Title() const {
    return mTitle;
}

//##############################################################################

size_t CSelectModel::Count() const {
//    return mCount;
    return mModelItems.size();
}

std::wstring CSelectModel::Text(size_t ix) const {
//    return (ix < mCount) ? mText[ix] : L"???";
    return (ix < mModelItems.size()) ? mModelItems[ix].Text : L"???";
}

uint8_t CSelectModel::Flags(size_t ix) const {
//    return (ix < mCount) ? mFlags[ix] : flgNone;
    return (ix < mModelItems.size()) ? mModelItems[ix].Flags : flgNone;
}

void CSelectModel::Flags(size_t ix, uint8_t flags) {
    // Only Selected and Checked can be changed, so clear all other bits
    flags &= flgSelected | flgChecked;

//    // Only zero or one item can be selected so clear Selected bits, if any
//    for (size_t Ix = 0; Ix < mCount; ++Ix)
//        mFlags[Ix] = mFlags[Ix] & ~flgSelected;

//    // Assume checked will be cleared
//    mModelItems[ix].Flags = mFlags[ix] & ~flgChecked;

//    // Selected and Checked bits have been cleared, so set them as directed
//    mFlags[ix] = mFlags[ix] | flags;

    // Only zero or one item can be selected so clear Selected bits, if any
    for (auto It = mModelItems.begin(); It < mModelItems.end(); ++It)
        It->Flags = It->Flags & ~flgSelected;

    // Assume checked will be cleared
    auto It = mModelItems.begin() + ix;
    It->Flags = It->Flags & ~flgChecked;

    // Selected and Checked bits have been cleared, so set them as directed
    It->Flags = It->Flags | flags;
}

size_t CSelectModel::SelectedIx() const {
//    // Report first selected item (Should only be one)
//    for (size_t Ix = 0; Ix < mCount; ++Ix)
//        if ((mFlags[Ix] & flgSelected) != 0)
//            return Ix;

    // Report first selected item (Should only be one)
    for (auto It = mModelItems.begin(); It < mModelItems.end(); ++It)
        if ((It->Flags & flgSelected) != 0)
            return It - mModelItems.begin();

    // Report none selected
    return -1;
}

EUIState CSelectModel::NextState() const {
//    size_t Ix = SelectedIx();
//    return (Ix < mCount) ? mNextStates[Ix] : EUIState::None;

    // Report first selected item (Should only be one)
    for (auto It = mModelItems.begin(); It < mModelItems.end(); ++It)
        if ((It->Flags & flgSelected) != 0)
            return It->NextState;

    // Report none selected
    return EUIState::None;
}

void CSelectModel::Load(const CSelectItem *pselectItems) {
//    mCount = 0;
//    mText.clear();
//    mFlags.clear();
//    mNextStates.clear();
    mModelItems.clear();
    if (pselectItems == nullptr)
        return;

//    while (pselectItems->Text != EMsg::None || pselectItems->pText != nullptr) {
//        if((pselectItems->Flags & flgOmitted) == 0) {
//            if (pselectItems->pText != nullptr)
//                mText.push_back(pselectItems->pText);
//            else {
//                CLang Lang;
//                mText.push_back(Lang.Message(pselectItems->Text));
//            }
//            mFlags.push_back(pselectItems->Flags);
//            mNextStates.push_back(pselectItems->NextState);
//            ++mCount;
//        }

//        ++pselectItems;
//    }

    while (pselectItems->Text != EMsg::None || pselectItems->pText != nullptr) {
        if((pselectItems->Flags & flgOmitted) == 0) {
            CSelectModelItem SelectModelItem;
            if (pselectItems->pText != nullptr)
                SelectModelItem.Text = pselectItems->pText;
            else {
                CLang Lang;
                SelectModelItem.Text = Lang.Message(pselectItems->Text);
            }
            SelectModelItem.Flags = pselectItems->Flags;
            SelectModelItem.NextState = pselectItems->NextState;
            mModelItems.push_back(SelectModelItem);
        }

        ++pselectItems;
    }
}

//##############################################################################

struct CMenuMapOld {
    EMsg Message;
    EUIState UIState;
    bool Disabled;
};

//##############################################################################

//------------------------------------------------------------------------------
//
CMenuBase::CMenuBase(EMsg titleID) : mpMenuItems(nullptr), mCount(0),
                                     mSelectedIx(-1), mTitleID(titleID) {
}

//------------------------------------------------------------------------------
//
void CMenuBase::Load(const CMenuItem *pmenuItems) {
    mCount = 0;
    mSelectedIx = -1;
    mpMenuItems = pmenuItems;
    if (pmenuItems == nullptr)
        return;

    while (pmenuItems->Text != EMsg::None || pmenuItems->pText != nullptr) {
        if (mSelectedIx > mCount && (pmenuItems->Flags & flgSelected) != 0)
                mSelectedIx = mCount;
        ++mCount;
        ++pmenuItems;
    }
}

//------------------------------------------------------------------------------
//
void CMenuBase::Items(std::vector<std::wstring> &names,
                      std::vector<uint8_t> &flags) const {
    names.clear();
    flags.clear();

    CLang Lang;
    const CMenuItem *pMenuItem = mpMenuItems;
    while (pMenuItem->Text != EMsg::None || pMenuItem->pText != nullptr) {
        if (pMenuItem->pText != nullptr)
            names.push_back(pMenuItem->pText);
        else
            names.push_back(Lang.Message(pMenuItem->Text));
        flags.push_back(pMenuItem->Flags);
        ++pMenuItem;
    }
}

//------------------------------------------------------------------------------
//
size_t CMenuBase::SelectedIx() const {
    return mSelectedIx;
}

//------------------------------------------------------------------------------
//
void   CMenuBase::SelectedIx(size_t ix) {
    mSelectedIx = ix;
}

//------------------------------------------------------------------------------
//
std::wstring CMenuBase::Title() {
    CLang Lang;
    return Lang.Message(mTitleID);
}

//##############################################################################

CUIStateHome::CUIStateHome(EUIState uiState) :
    CUIState(uiState) {
}

bool CUIStateHome::Enter(bool /*first = true*/) {
    Settings.Get().Instrument();
    return true;
}

//void CUIStateHome::Exit(bool commit = false) {
//}

//EUIState CUIStateHome::Event(EUIEvent event, void *pdata) {
//}

//EUIState CUIStateHome::Click(ELng msg) {
//}

EMsg CUIStateHome::Instrument() const {
    return Settings.Get().Instrument();
}

//##############################################################################

CUIStateMenuInst::CUIStateMenuInst(EUIState uiState) :
    CUIState(uiState), CMenuBase(EMsg::InstrumentType) {
}

bool CUIStateMenuInst::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::String,     nullptr, EUIState::InstString,     IMenu::flgSelected },
        { EMsg::Wind,       nullptr, EUIState::InstWind,       IMenu::flgNone     },
        { EMsg::Percussion, nullptr, EUIState::InstPercussion, IMenu::flgNone     },
        { EMsg::Test,       nullptr, EUIState::Test,           IMenu::flgNone     },
        //{ EMsg::Test,       nullptr, EUIState::Test,           IMenu::flgDisabled },
        { EMsg::None,       nullptr, EUIState::None,           IMenu::flgNone     }
    };

    if (first)
        Load(MenuItems);
    return first;
}

//------------------------------------------------------------------------------
//
//void CUIStateMenuInst::Exit(bool commit = false) {
//}

//------------------------------------------------------------------------------
//
EUIState CUIStateMenuInst::Event(EUIEvent event, void * /*pdata*/) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//EUIState CUIStateMenuInst::Click(EMsg msg) {
//}

//##############################################################################

//------------------------------------------------------------------------------
//
CUIStateMenuString::CUIStateMenuString(EUIState uiState) :
    CUIState(uiState), CMenuBase(EMsg::String) {
}

//------------------------------------------------------------------------------
//
bool CUIStateMenuString::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::Violin, nullptr, EUIState::Home, IMenu::flgSelected },
        { EMsg::Viola,  nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Cello,  nullptr, EUIState::Test, IMenu::flgNone     },
        { EMsg::Bass,   nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::None,   nullptr, EUIState::None, IMenu::flgNone     }
    };

    if (first)
        Load(MenuItems);
    return first;
}

//------------------------------------------------------------------------------
//
void CUIStateMenuString::Exit(bool commit /*= false*/) {
    if (commit && mSelectedIx < mCount) {
        EMsg Label = mpMenuItems[mSelectedIx].Text;
        if (Label != EMsg::None)
            Settings.Get().Instrument(Label);
    }
}

//------------------------------------------------------------------------------
//
EUIState CUIStateMenuString::Event(EUIEvent event, void * /* pdata */) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//------------------------------------------------------------------------------
//
//EUIState CUIStateMenuString::Click(EMsg msg) {
//}

//##############################################################################

//------------------------------------------------------------------------------
//
CUIStateMenuWind::CUIStateMenuWind(EUIState uiState) :
    CUIState(uiState), CMenuBase(EMsg::Wind) {
}

//------------------------------------------------------------------------------
//
bool CUIStateMenuWind::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::Flute,   nullptr, EUIState::Home, IMenu::flgSelected },
        { EMsg::Oboe,    nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Bassoon, nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Trumpet, nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::None,    nullptr, EUIState::None, IMenu::flgNone     }
    };

    if (first)
        Load(MenuItems);
    return first;
}

//------------------------------------------------------------------------------
//
void CUIStateMenuWind::Exit(bool commit /*= false*/) {
    if (commit && mSelectedIx < mCount) {
        EMsg Label = mpMenuItems[mSelectedIx].Text;
        if (Label != EMsg::None)
            Settings.Get().Instrument(Label);
    }
}

//------------------------------------------------------------------------------
//
EUIState CUIStateMenuWind::Event(EUIEvent event, void * /* pdata */) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//------------------------------------------------------------------------------
//
//EUIState CUIStateMenuWind::Click(EMsg msg) {
//}

//##############################################################################

//------------------------------------------------------------------------------
//
CUIStateMenuPercussion::CUIStateMenuPercussion(EUIState uiState) :
    CUIState(uiState), CMenuBase(EMsg::Percussion) {
}

//------------------------------------------------------------------------------
//
bool CUIStateMenuPercussion::Enter(bool first /*= true*/) {
    static const CMenuItem MenuItems[] = {
        { EMsg::Drum,       nullptr, EUIState::Home, IMenu::flgSelected },
        { EMsg::Cymbal,     nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::Tambourine, nullptr, EUIState::Home, IMenu::flgNone     },
        { EMsg::None,       nullptr, EUIState::None, IMenu::flgNone     }
    };

    if (first)
        Load(MenuItems);
    return first;
}

//------------------------------------------------------------------------------
//
void CUIStateMenuPercussion::Exit(bool commit /*= false*/) {
    if (commit && mSelectedIx < mCount) {
        EMsg Label = mpMenuItems[mSelectedIx].Text;
        if (Label != EMsg::None)
            Settings.Get().Instrument(Label);
    }
}

//------------------------------------------------------------------------------
//
EUIState CUIStateMenuPercussion::Event(EUIEvent event, void * /* pdata */) {
    switch(event) {
    case EUIEvent::BtnBack:
        UIState(EUIState::Previous, false);
        break;

    case EUIEvent::BtnOk:
        if (mSelectedIx < mCount)
            UIState(mpMenuItems[mSelectedIx].NextState, true);
        break;

    default:
        break;
    }

    return EUIState::None;
}

//------------------------------------------------------------------------------
//
//EUIState CUIStateMenuPercussion::Click(EMsg msg) {
//}
