#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    //void setIcon(int index);
    //void iconActivated(QSystemTrayIcon::ActivationReason reason);
    //void showMessage();
    //void messageClicked();

private:
    Ui::MainWindow *ui;

    void createActions();
    void createTrayIcon();

    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif // MAINWINDOW_H
