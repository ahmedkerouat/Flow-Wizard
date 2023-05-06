#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include "aspectratiowidget.h"
#include <QPushButton>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //background
    QString styleSheet = "background-color: #071426;";
    this->setStyleSheet(styleSheet);

    //central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    //main widget added to central widget using AspectRatioWidget
    QWidget *mainWidget = new QWidget(centralWidget);
    mainWidget->setObjectName("mainWidget");
    mainWidget->setStyleSheet("background-color: #2B2D42");
    AspectRatioWidget *aspectRatioWidget = new AspectRatioWidget(mainWidget, 4, 3, centralWidget);
    gridLayout->addWidget(aspectRatioWidget, 0, 0, 1, 1);

    //"hello" message
    QLabel *helloLabel = new QLabel(mainWidget);
    helloLabel->setText("Hello, User.");
    helloLabel->setAlignment(Qt::AlignHCenter);
    helloLabel->setStyleSheet("font-size: 22px; color: white;");
    gridLayout->addWidget(helloLabel, 0, 0, Qt::AlignTop | Qt::AlignHCenter);

    //home button
    QPushButton *homeButton = new QPushButton(mainWidget);
    homeButton->setIcon(QIcon(":/imgs/logoHome.png"));
    homeButton->setIconSize(QSize(64, 64));
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(homeButton, 0, Qt::AlignCenter);

    //button style
    QString buttonStyle = "QPushButton {"
                          "border-radius: 32px;"
                          "border: 0px;"
                          "background-color: #9D4EDD;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #6C2DC7;"
                          "}";
    homeButton->setStyleSheet(buttonStyle);

    setCentralWidget(centralWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
}
