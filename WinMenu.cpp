//#include "UIStateIfs.hpp"
#include "UIStates.hpp"
#include "WinMenu.hpp"
#include "ui_WinMenu.h"

//#include <QGraphicsOpacityEffect>

//------------------------------------------------------------------------------
//
CWinMenu::CWinMenu(CUIState *puiState, QWidget *parent) :
    CBaseWidget(puiState, parent),
    ui(new Ui::CWinMenu) {
    ui->setupUi(this);
}

//------------------------------------------------------------------------------
//
CWinMenu::~CWinMenu() {
    delete ui;
}

//------------------------------------------------------------------------------
//
void CWinMenu::on_btnOk_clicked() {
    mpUIState->Event(EUIEvent::BtnOk);
}

//------------------------------------------------------------------------------
//
void CWinMenu::on_btnCancel_clicked() {
    mpUIState->Event(EUIEvent::BtnBack);
}

//------------------------------------------------------------------------------
//
void CWinMenu::on_lwMenu_currentRowChanged(int currentRow) {
    IMenu *pMenu = dynamic_cast<IMenu *>(mpUIState);
    if (pMenu != nullptr)
        pMenu->SelectedIx(static_cast<size_t>(currentRow));
}

//------------------------------------------------------------------------------
//
void EnterHandler(Ui::CWinMenu */*pUI*/, bool /*first*/) {
    // This could be a potential "Enter" handler called via a function pointer
    // determined by the state ID
}

//------------------------------------------------------------------------------
//
void CWinMenu::Enter(bool first) {
    if (mpUIState->Enter(first)) {
        IMenu *pMenu = dynamic_cast<IMenu *>(mpUIState);
        if (pMenu != nullptr) {
            ui->lblTitle->setText(QString::fromStdWString(pMenu->Title()));
            ui->lwMenu->clear();
            std::vector<std::wstring> Names;
            std::vector<uint8_t> Flags;
            pMenu->Items(Names, Flags);
            size_t Count = Names.size();
            for (size_t Ix = 0; Ix < Count; ++Ix) {
                ui->lwMenu->addItem(QString::fromStdWString(Names[Ix]));
                Qt::ItemFlags QtFlags = ui->lwMenu->item(Ix)->flags();
                if ((Flags[Ix] & IMenu::flgDisabled) != 0)
                    QtFlags &= ~Qt::ItemIsEnabled;
                else
                    QtFlags |= Qt::ItemIsEnabled;
                ui->lwMenu->item(Ix)->setFlags(QtFlags);

            }
            if (Count > 0) {
                size_t SelectedIx = pMenu->SelectedIx();
                if (SelectedIx < Count)
                    ui->lwMenu->setCurrentRow(SelectedIx);
            }
        }
    }

//    setWindowOpacity(100.0);

//    QGraphicsOpacityEffect *pEffect0 = new QGraphicsOpacityEffect(ui->lwMenu);
//    pEffect0->setOpacity(0.25);
//    ui->lwMenu->setGraphicsEffect(pEffect0);
//    ui->lwMenu->setAutoFillBackground(true);

//    QGraphicsOpacityEffect *pEffect = new QGraphicsOpacityEffect(this);
//    pEffect->setOpacity(0.25);
//    setGraphicsEffect(pEffect);
//    setAutoFillBackground(true);
}

//------------------------------------------------------------------------------
//
void CWinMenu::Exit(bool commit) {
    mpUIState->Exit(commit);
}

//##############################################################################
