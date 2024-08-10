#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QCloseEvent>
#include <QGridLayout>
#include "buttonslot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setVisible(bool visible) override;

public slots:


protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

    void createActions();
    void createTrayIcon();

    void hideButtonToolbar();
    void updateButtonToolbar(int buttonId);

    void populateButtonSlots(int row, int col);
    void selectButtonSlot(int buttonId);
    ButtonSlot* locateButtonSlot(int buttonId, int row, int col);

    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QGridLayout *gridLayout;
    ButtonSlot *selectedButton;

    QWidget *buttonToolbar;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif // MAINWINDOW_H
