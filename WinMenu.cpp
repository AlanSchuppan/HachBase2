#include "WinMenu.hpp"
#include "ui_WinMenu.h"
#include "UIState.hpp"
#include "Lang.hpp"
#include "UIContext.hpp"

CWinMenu::CWinMenu(CUIState *puiState, QWidget *parent) :
    CBaseWidget(puiState, parent),
    ui(new Ui::CWinMenu) {
    ui->setupUi(this);
}

CWinMenu::~CWinMenu() {
    delete ui;
}

void CWinMenu::Menu(const CStrMenuMap *pmenuMap) {
    ui->lwMenu->clear();;
    mUIStates.clear();
    while (pmenuMap->Name != nullptr) {
        ui->lwMenu->addItem(pmenuMap->Name);
        mUIStates.push_back(pmenuMap->UIState);
        ++pmenuMap;
    }
    if (ui->lwMenu->count() > 0)
        ui->lwMenu->setCurrentRow(0);
}

void CWinMenu::Menu(const CMsgMenuMap *pmenuMap) {
    CLang Lang;
    ui->lwMenu->clear();
    mLabels.clear();
    mUIStates.clear();
    while (pmenuMap->Message != EMsg::None) {
        ui->lwMenu->addItem(QString::fromStdWString(Lang.Message(pmenuMap->Message)));
        mLabels.push_back(pmenuMap->Message);
        mUIStates.push_back(pmenuMap->UIState);
        ++pmenuMap;
    }
    if (ui->lwMenu->count() > 0)
        ui->lwMenu->setCurrentRow(0);
}

void CWinMenu::Disable(const std::vector<bool> &disables) {
    size_t MenuCount = static_cast<size_t>(ui->lwMenu->count());
    size_t DisableCount = disables.size();
    for (size_t Ix = 0; Ix < MenuCount; ++Ix) {
        bool Disabled = (Ix < DisableCount && disables[Ix]);
        Qt::ItemFlags Flags = ui->lwMenu->item(Ix)->flags();
        if (Disabled)
            Flags &= ~Qt::ItemIsEnabled;
        else
            Flags |= Qt::ItemIsEnabled;
        ui->lwMenu->item(Ix)->setFlags(Flags);
    }
}

void CWinMenu::RowSelect(uint32_t ix) {
    if (ix < static_cast<uint32_t>(ui->lwMenu->count())) {
        Qt::ItemFlags Flags = ui->lwMenu->item(ix)->flags();
        if ((Flags & Qt::ItemIsEnabled) != 0)
            ui->lwMenu->setCurrentRow(ix);
    }
}

void CWinMenu::Label(std::wstring label) {
    ui->lblTitle->setText(QString::fromStdWString(label));
}

void CWinMenu::Label(EMsg msg) {
    CLang Lang;
    std::wstring Title = Lang.Message(msg);
    ui->lblTitle->setText(QString::fromStdWString(Title));
}

void CWinMenu::on_btnOk_clicked() {
    size_t Row = static_cast<size_t>(ui->lwMenu->currentRow());
    if (Row < mUIStates.size()) {
        EUIState UIState = mUIStates[Row];
        UIContext.Get().UIState(UIState, true); // true => commit
    }
}

void CWinMenu::on_btnCancel_clicked() {
    UIContext.Get().UIStatePrevious();
}

void EnterHandler(Ui::CWinMenu */*pUI*/, bool /*first*/) {
    // This could be a potential "Enter" handler called via a function pointer
    // determined by the state ID
}

EMsg CWinMenu::Selection() const {
    size_t Row = static_cast<size_t>(ui->lwMenu->currentRow());
    return (Row < mUIStates.size()) ? mLabels[Row] : EMsg::None;
}


//##############################################################################
