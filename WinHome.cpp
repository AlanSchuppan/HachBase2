#include "WinHome.hpp"
#include "UIContext.hpp"
#include "Lang.hpp"
#include "ui_WinHome.h"

CWinHome::CWinHome(CUIState *puiState, QWidget *parent) :
    CBaseWidget(puiState, parent),
    ui(new Ui::cWinHome) {
    ui->setupUi(this);
    CLang Lang;
    ui->btnStart->setText(QString::fromStdWString(Lang.Message(EMsg::Start)));
}

CWinHome::~CWinHome() {
    delete ui;
}

void CWinHome::on_btnStart_clicked() {
    UIContext.Get().State(EUIState::Inst);
}

void CWinHome::Instrument(EMsg instrument) {
    CLang Lang;
    ui->lblInstrument->setText(QString::fromStdWString(Lang.Message(instrument)));
}
