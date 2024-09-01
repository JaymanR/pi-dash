#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QKeySequenceEdit>
#include <QFormLayout>
#include "hotkeyedit.h"

constexpr int s_rows{1};
constexpr int s_cols{2};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gridLayout(nullptr)
    , selectedButton(nullptr)
    , buttonToolbar(nullptr)
    , recordedKeySequence(nullptr)
    , receiver(new Receiver(this))
{
    ui->setupUi(this);

    //hideButtonToolbar();

    populateButtonSlots(s_rows, s_cols);
    createActions();
    createTrayIcon();

    connect(ui->editorButton, &QPushButton::clicked, this, &MainWindow::showButtonEditor);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::showSettings);

    connect(ui->deviceList, &QListWidget::itemClicked, this, &MainWindow::onDeviceListItemSelect);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::connectAddress);

    connect(receiver, &Receiver::connectionRequest, this, &MainWindow::showConnectionRequests);

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

void MainWindow::hideButtonToolbar()
{
    if (buttonToolbar){
        buttonToolbar->setVisible(false);
    } else {
        QMessageBox::critical(this, "Error", "Error: No Button Toolbar displayed");
    }
}

void MainWindow::updateButtonToolbar(int buttonId)
{
    if (buttonToolbar) {
        buttonToolbar->deleteLater();
        buttonToolbar = nullptr;
    }

    QWidget *buttonEditor = ui->buttonEditor;
    if (buttonEditor) {
        buttonToolbar = new QWidget(buttonEditor);

        QFormLayout *layout = new QFormLayout(buttonToolbar);

        QLabel *titleLabel = new QLabel(buttonToolbar);
        titleLabel->setText(tr("Button %1").arg(buttonId));
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(12);
        titleLabel->setFont(titleFont);
        titleLabel->setAlignment(Qt::AlignCenter); 

        QLabel *nameLabel = new QLabel(buttonToolbar);
        nameLabel->setText(tr("Name"));
        QLineEdit *nameLineEdit = new QLineEdit(buttonToolbar);

        QLabel *hotkeyLabel = new QLabel(buttonToolbar);
        hotkeyLabel->setText(tr("Hotkey"));
        HotkeyEdit *hotkeyEdit = new HotkeyEdit(buttonToolbar);

        /* testing input emulation
        QPushButton *execute = new QPushButton(buttonToolbar);
        execute->setStyleSheet("border: 2px solid white");
        connect(execute, &QPushButton::clicked, this, [hotkeyEdit]() {
            hotkeyEdit->getHotkey().execute();
        });*/

        layout->addRow(titleLabel);
        layout->addRow(nameLabel, nameLineEdit);
        layout->addRow(hotkeyLabel, hotkeyEdit);

        //need to add action and Hotkey later

        buttonToolbar->setLayout(layout);

        QHBoxLayout *editorLayout = qobject_cast<QHBoxLayout*>(buttonEditor->layout());

        editorLayout->addWidget(buttonToolbar);
        editorLayout->setAlignment(buttonToolbar, Qt::AlignCenter);
    } else {
        QMessageBox::critical(this, "Error", "Error: No Button Editor Found");
    }
}

void MainWindow::onKeySequenceChanged(const QKeySequence &keySequence)
{
    recordedKeySequence = keySequence;
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
                connect(buttonSlot, &ButtonSlot::buttonSelected, this, &MainWindow::selectButtonSlot);
                gridLayout->addWidget(buttonSlot, i, j);
                count++;
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

        updateButtonToolbar(buttonId);
    }
}

ButtonSlot* MainWindow::locateButtonSlot(int buttonId, int row, int col)
{
    ButtonSlot *buttonSlot;
    int rowIndex{(buttonId - 1) / col};
    int colIndex{(buttonId - 1) % col};

    if (gridLayout) {
        QLayoutItem *item = gridLayout->itemAtPosition(rowIndex, colIndex);
        if (item) {
            return qobject_cast<ButtonSlot*>(item->widget());
        }
    }
    return nullptr;
}

void MainWindow::showButtonEditor()
{
    ui->mainBody->setCurrentWidget(ui->buttonEditor);
}

void MainWindow::showSettings()
{
    ui->mainBody->setCurrentWidget(ui->settings);
}

void MainWindow::showConnectionRequests(QHostAddress sender, quint16 port)
{
    QListWidget *listWidget = ui->deviceList;

    QString addressString;

    quint32 ipv4Address = sender.toIPv4Address();
    if (ipv4Address != 0) {
        addressString = QHostAddress(ipv4Address).toString();
    } else {
        addressString = sender.toString();
    }

    for (int i{0}; i < listWidget->count(); i++) {
        if (listWidget->item(i)->text().compare(addressString) == 0) {
            return;
        }
    }

    QListWidgetItem *item = new QListWidgetItem(addressString, listWidget);
    listWidget->addItem(item);
}

void MainWindow::onDeviceListItemSelect()
{
    ui->connectButton->setEnabled(true);
}

void MainWindow::connectAddress()
{
    QListWidgetItem *item = ui->deviceList->currentItem();
    //qDebug() << item->text();
    senderAddress = new QHostAddress(item->text());
}
