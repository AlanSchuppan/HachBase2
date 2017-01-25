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
        mUIStates.push_back(pmenuMap->State);
        ++pmenuMap;
    }
    if (ui->lwMenu->count() > 0)
        ui->lwMenu->setCurrentRow(0);
}

void CWinMenu::Menu(const CStrIDMenuMap *pmenuMap) {
    CLang Lang;
    ui->lwMenu->clear();
    mLabels.clear();
    mUIStates.clear();
    while (pmenuMap->StringID != EString::None) {
        ui->lwMenu->addItem(QString::fromStdWString(Lang.String(pmenuMap->StringID)));
        mLabels.push_back(pmenuMap->StringID);
        mUIStates.push_back(pmenuMap->State);
        ++pmenuMap;
    }
    if (ui->lwMenu->count() > 0)
        ui->lwMenu->setCurrentRow(0);
}

void CWinMenu::Label(std::wstring label) {
    ui->lblTitle->setText(QString::fromStdWString(label));
}

void CWinMenu::Label(EString stringID) {
    CLang Lang;
    std::wstring Title = Lang.String(stringID);
    ui->lblTitle->setText(QString::fromStdWString(Title));
}

void CWinMenu::on_btnOk_clicked() {
    size_t Row = static_cast<size_t>(ui->lwMenu->currentRow());
    if (Row < mUIStates.size()) {
        EUIStateID StateID = mUIStates[Row];
        UIContext.Get().State(StateID, true); // true => commit
    }
}

void CWinMenu::on_btnCancel_clicked() {
    UIContext.Get().StatePrevious();
}

void EnterHandler(Ui::CWinMenu */*pUI*/, bool /*first*/) {
    // This could be a potential "Enter" handler called via a function pointer
    // determined by the state ID
}

EString CWinMenu::Selection() const {
    size_t Row = static_cast<size_t>(ui->lwMenu->currentRow());
    return (Row < mUIStates.size()) ? mLabels[Row] : EString::None;
}


//##############################################################################
