#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "button.h"

constexpr int s_rows{1};
constexpr int s_cols{2};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gridLayout(nullptr)
{
    ui->setupUi(this);

    populateButtonSlots(s_rows, s_cols);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateButtonSlots(int row, int col)
{
    QWidget *buttonContainer = ui->buttonContainer;

    if (buttonContainer) {
        if(!gridLayout) {
            gridLayout = new QGridLayout(buttonContainer);
        }
        buttonContainer->setMaximumSize(500, 500);

        int count{1};
        for (int i{0}; i < row; i++) {
            for (int j{0}; j < col; j++) {
                Button *button = new Button(buttonContainer, count);
                //connect(button, &Button::clicked, this, /*some function*/);
                gridLayout->addWidget(button, i, j);
                count++;
            }
        }
        buttonContainer->setLayout(gridLayout);
    }
}
