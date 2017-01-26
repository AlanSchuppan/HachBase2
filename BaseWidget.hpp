#ifndef CBASEWIDGET_HPP
#define CBASEWIDGET_HPP

#include <QWidget>

#include "UIState.hpp"

//##############################################################################
// CBaseWidget
//##############################################################################
//##############################################################################

class CBaseWidget : public QWidget {
    Q_OBJECT

protected:
    CUIState *mpUIState;

public:
    CBaseWidget(CUIState *puiState, QWidget *parent = 0);
    virtual ~CBaseWidget();
    const char *Name() const;
    EUIStateID UIStateID() const;
    EUIStateID PrevStateID() const;

    void Enter(bool first = true);
    void Exit(bool commit = false);
    EUIStateID Event(EUIEvent event, void *pdata);
    EUIStateID Click(EMsg msg);

//signals:

//public slots:
};

inline EUIStateID CBaseWidget::UIStateID() const {
    return (mpUIState != nullptr) ? mpUIState->UIStateID() : EUIStateID::None;
}

inline const char *CBaseWidget::Name() const {
    return (mpUIState != nullptr) ? mpUIState->Name() : "???";
}

//##############################################################################

#endif // CBASEWIDGET_HPP
