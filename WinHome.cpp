#include "WinHome.hpp"
#include "UIStates.hpp"
#include "ui_WinHome.h"

//------------------------------------------------------------------------------
//
CWinHome::CWinHome(CUIState *puiState, QWidget *parent) :
    CBaseWidget(puiState, parent),
    ui(new Ui::cWinHome) {
    ui->setupUi(this);
    CLang Lang;
    ui->btnStart->setText(QString::fromStdWString(Lang.Message(EMsg::Start)));
}

//------------------------------------------------------------------------------
//
CWinHome::~CWinHome() {
    delete ui;
}

//------------------------------------------------------------------------------
//
void CWinHome::on_btnStart_clicked() {
    if (mpUIState != nullptr)
        mpUIState->UIState(EUIState::Inst);
}

//------------------------------------------------------------------------------
//
void CWinHome::Enter(bool first) {
    CLang Lang;
    CUIStateHome *pUIStateHome = dynamic_cast<CUIStateHome *>(mpUIState);
    std::wstring Inst(Lang.Message(pUIStateHome->Instrument()));
    ui->lblInstrument->setText(QString::fromStdWString(Inst));
}
