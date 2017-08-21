#ifndef WINHOME_HPP
#define WINHOME_HPP

#include "BaseWidget.hpp"

//##############################################################################

namespace Ui {
    class cWinHome;
}

class CUIState;

class CWinHome : public CBaseWidget
{
    Q_OBJECT

public:
    explicit CWinHome(CUIState *puiState, QWidget *parent = 0);
    ~CWinHome();
//    void Instrument(EMsg instrument);
    void Enter(bool first = true) override;

private slots:
    void on_btnStart_clicked();

private:
    Ui::cWinHome *ui;
};

//##############################################################################

#endif // WINHOME_HPP
