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

    // create the buttons
    QPushButton *homeButton = new QPushButton(mainWidget);
    homeButton->setIcon(QIcon(":/imgs/logoHome.png"));
    homeButton->setIconSize(QSize(64, 64));
    homeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *goalsButton = new QPushButton(mainWidget);
    goalsButton->setIcon(QIcon(":/imgs/logoGoals.png"));
    goalsButton->setIconSize(QSize(64, 64));
    goalsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *habitsButton = new QPushButton(mainWidget);
    habitsButton->setIcon(QIcon(":/imgs/logoHabits.png"));
    habitsButton->setIconSize(QSize(64, 64));
    habitsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *inspirationButton = new QPushButton(mainWidget);
    inspirationButton->setIcon(QIcon(":/imgs/logoInspiration.png"));
    inspirationButton->setIconSize(QSize(64, 64));
    inspirationButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *notesButton = new QPushButton(mainWidget);
    notesButton->setIcon(QIcon(":/imgs/logoNotes.png"));
    notesButton->setIconSize(QSize(64, 64));
    notesButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    //create the layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addWidget(goalsButton);
    buttonLayout->addWidget(habitsButton);
    buttonLayout->addWidget(homeButton);
    buttonLayout->addWidget(inspirationButton);
    buttonLayout->addWidget(notesButton);

    //create a spacer
    QSpacerItem *spacer = new QSpacerItem(40, 200, QSizePolicy::Preferred, QSizePolicy::Minimum);
    mainLayout->addItem(spacer);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addItem(spacer);

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
    goalsButton->setStyleSheet(buttonStyle);
    habitsButton->setStyleSheet(buttonStyle);
    inspirationButton->setStyleSheet(buttonStyle);
    notesButton->setStyleSheet(buttonStyle);


    //add the layout to the grid layout
    gridLayout->addLayout(mainLayout, 0, 0, Qt::AlignTop | Qt::AlignHCenter);


    setCentralWidget(centralWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
}
