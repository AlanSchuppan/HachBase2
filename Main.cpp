#include <QApplication>

#include "UIContext.hpp"
#include "MainWidget.hpp"

int main(int argc, char *argv[]) {
    static const int Width = 800;
    static const int Height = 480;

    QApplication a(argc, argv);

    MainWidget WinMain;
    WinMain.setGeometry(0, 0, Width, Height);
    WinMain.setMaximumSize(Width, Height);
    WinMain.setMinimumSize(Width, Height);
//    WinMain.show();

    UIContext.Get().UIState(EUIState::Home);

    return a.exec();
}
