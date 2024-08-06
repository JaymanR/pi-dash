#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createTrayIcon();

    trayIcon->show();

    setWindowTitle(tr("Pi Dash"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    restoreAction = new QAction(tr("Show"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);

    QIcon svgIcon(":/icons/icons/placeholder.svg");
    trayIcon->setIcon(svgIcon);
    trayIcon->setToolTip(tr("Pi Dash"));

    trayIcon->setContextMenu(trayIconMenu);
}

void MainWindow::setVisible(bool visible)
{
    restoreAction->setEnabled(!visible);
    QMainWindow::setVisible(visible);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!event->spontaneous() || !isVisible()) return;

    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Pi Dash"),
                                 tr("Pi Dash will keep running in the "
                                    "system tray."));
        hide();
        event->ignore();
    }
}
