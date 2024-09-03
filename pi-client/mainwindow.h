#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "networkhandler.h"

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

private:
    Ui::MainWindow *ui;

    void populateButtonSlots(int row, int col);

    QGridLayout *gridLayout;

    //Sender *sender;
    NetworkHandler *networkHandler;

private slots:
    void broadcastConnection();
    void onConnectionAccepted();
};
#endif // MAINWINDOW_H
