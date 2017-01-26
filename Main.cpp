#include "UIContext.hpp"
#include "MainWidget.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    static const int Width = 800;
    static const int Height = 480;

    QApplication a(argc, argv);

    MainWidget WinMain;
    WinMain.setGeometry(0, 0, Width, Height);
    WinMain.setMaximumSize(Width, Height);
    WinMain.setMinimumSize(Width, Height);
//    WinMain.show();

    UIContext.Get().State(EUIState::Home);

    return a.exec();
}
