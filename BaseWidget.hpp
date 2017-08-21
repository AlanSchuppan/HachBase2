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
    EUIState UIState() const;
    EUIState PrevStateID() const;

    virtual void Enter(bool first = true);
    virtual void Exit(bool commit = false);
    EUIState Event(EUIEvent event, void *pdata = nullptr);
    EUIState Click(EMsg msg);

//signals:

//public slots:
};

inline EUIState CBaseWidget::UIState() const {
    return (mpUIState != nullptr) ? mpUIState->UIState() : EUIState::None;
}

inline const char *CBaseWidget::Name() const {
    return (mpUIState != nullptr) ? mpUIState->Name() : "???";
}

//##############################################################################

#endif // CBASEWIDGET_HPP
