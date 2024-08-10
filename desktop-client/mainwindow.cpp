#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCoreApplication>
#include <QMessageBox>

#include <QDebug>

constexpr int s_rows{2};
constexpr int s_cols{3};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gridLayout(nullptr)
    , selectedButton(nullptr)
{
    ui->setupUi(this);

    ui->buttonToolbar->setVisible(false);

    populateButtonSlots(s_rows, s_cols);
    createActions();
    createTrayIcon();

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
    trayIcon->show();
}

void MainWindow::populateButtonSlots(int row, int col)
{
    QWidget *buttonContainer = ui->buttonEditor->findChild<QWidget*>("buttonContainer");
    if (buttonContainer) {
        if (!gridLayout) {
            gridLayout = new QGridLayout(buttonContainer);
        }
        buttonContainer->setMaximumSize(500, 300);

        buttonContainer->maximumSize();

        int count{1};

        for (int i{0}; i < row; i++) {
            for (int j{0}; j < col; j++) {
                ButtonSlot *buttonSlot = new ButtonSlot(buttonContainer, count);
                count++;

                connect(buttonSlot, &ButtonSlot::buttonSelected, this, &MainWindow::selectButtonSlot);

                gridLayout->addWidget(buttonSlot, i, j);
            }
        }

        buttonContainer->setLayout(gridLayout);
    }
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

void MainWindow::selectButtonSlot(int buttonId)
{

    ButtonSlot *newButtonSlot = locateButtonSlot(buttonId, s_rows, s_cols);
    if (newButtonSlot) {
        if (selectedButton != newButtonSlot && selectedButton != nullptr) {
            selectedButton->setSelected(false);
        }
        selectedButton = newButtonSlot;
        selectedButton->setSelected(true);
    }
}

ButtonSlot* MainWindow::locateButtonSlot(int buttonId, int row, int col)
{
    ButtonSlot *buttonSlot;
    int rowIndex{(buttonId - 1)/ col};
    int colIndex{(buttonId - 1) % col};

    if (gridLayout) {
        QLayoutItem *item = gridLayout->itemAtPosition(rowIndex, colIndex);
        if (item) {
            return qobject_cast<ButtonSlot*>(item->widget());
        }
    }
    return nullptr;
}
