#ifndef CWINMENU_HPP
#define CWINMENU_HPP

#include <string>
#include <vector>

#include "BaseWidget.hpp"

namespace Ui {
    class CWinMenu;
}

//##############################################################################

class CWinMenu : public CBaseWidget {
    Q_OBJECT

public:
    explicit CWinMenu(CUIState *puiState, QWidget *parent = 0);
    ~CWinMenu();

    // CBaseWidget
    void Enter(bool first = true) override;
    void Exit(bool commit = false) override;

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
    void on_lwMenu_currentRowChanged(int currentRow);

private:
    Ui::CWinMenu *ui;
};

//##############################################################################

#endif // CWINMENU_HPP
