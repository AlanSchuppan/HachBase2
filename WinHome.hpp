#ifndef WINHOME_HPP
#define WINHOME_HPP

#include "Lang.hpp"
#include "UIState.hpp"
#include "BaseWidget.hpp"

namespace Ui {
class cWinHome;
}

class CWinHome : public CBaseWidget
{
    Q_OBJECT

public:
    explicit CWinHome(CUIState *puiState, QWidget *parent = 0);
    ~CWinHome();
    void Instrument(EString instrument);

private slots:
    void on_btnStart_clicked();

private:
    Ui::cWinHome *ui;
};

#endif // WINHOME_HPP
