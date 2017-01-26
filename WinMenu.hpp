#ifndef CWINMENU_HPP
#define CWINMENU_HPP

#include <string>
#include <vector>

#include "Lang.hpp"
#include "BaseWidget.hpp"

namespace Ui {
    class CWinMenu;
}

//##############################################################################

struct CStrMenuMap {
    const char *Name;
    EUIStateID State;
};

//##############################################################################

struct CStrIDMenuMap {
    EMsg Message;
    EUIStateID State;
};

//##############################################################################

class CWinMenu : public CBaseWidget {
    Q_OBJECT

public:
    explicit CWinMenu(CUIState *puiState, QWidget *parent = 0);
    ~CWinMenu();
    void Menu(const CStrMenuMap *pmenuMap);
    void Menu(const CStrIDMenuMap *pmenuMap);
    void Disable(const std::vector<bool> &disables);
    void RowSelect(uint32_t ix);
    void Label(std::wstring label);
    void Label(EMsg msg);
    EMsg Selection() const;

//    void Enter(bool first = true) override;

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CWinMenu *ui;
    std::vector<EMsg> mLabels;
    std::vector<EUIStateID> mUIStates;
};

//##############################################################################

#endif // CWINMENU_HPP
