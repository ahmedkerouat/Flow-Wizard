#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include "aspectratiowidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QFileDialog>
#include <QFile>
#include <QInputDialog>
#include <QRandomGenerator>


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
    mainWidget->setStyleSheet("background-color:  #071426");
    AspectRatioWidget *aspectRatioWidget = new AspectRatioWidget(mainWidget, 4, 3, centralWidget);
    gridLayout->addWidget(aspectRatioWidget, 0, 0, 1, 1);

    //"hello" message
    QLabel *helloLabel = new QLabel(mainWidget);
    helloLabel->setText("Hello, User.");
    helloLabel->setAlignment(Qt::AlignHCenter);
    helloLabel->setStyleSheet("font-size: 44px; color: white;");
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
                          "background-color: #071426;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #009ace;"
                          "}";

    homeButton->setStyleSheet(buttonStyle);
    goalsButton->setStyleSheet(buttonStyle);
    habitsButton->setStyleSheet(buttonStyle);
    inspirationButton->setStyleSheet(buttonStyle);
    notesButton->setStyleSheet(buttonStyle);

    connect(notesButton, &QPushButton::clicked, [=]() { on_notesButton_clicked(notesButton,centralWidget, mainLayout, buttonLayout, mainWidget, helloLabel, gridLayout, aspectRatioWidget); });
    connect(homeButton, &QPushButton::clicked, [=]() { resetWindow(notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget); });
    connect(inspirationButton, &QPushButton::clicked,[=](){on_inspirationButton_clicked(centralWidget, mainWidget, notesButton, mainLayout, buttonLayout, helloLabel,gridLayout,aspectRatioWidget);});


    //add the layout to the grid layout
    gridLayout->addLayout(mainLayout, 0, 0, Qt::AlignTop | Qt::AlignHCenter);

    setCentralWidget(centralWidget);
    mainLayout->removeItem(mainLayout->itemAt(0));
    if (homeButton)
            {
                homeButton->setEnabled(false);
            }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetWindow(QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget)
{
    helloLabel->setVisible(false);
    if (centralWidget()->findChild<QWidget*>("notesWidget"))
    {
        QWidget* notesWidget = centralWidget()->findChild<QWidget*>("notesWidget");
        QWidget* mainWidget = centralWidget()->findChild<QWidget*>("mainWidget");
        gridLayout->removeWidget(notesWidget);
        delete notesWidget;
        mainLayout->addWidget(mainWidget); // Add mainWidget back to the mainLayout
        if (notesButton)
        {
            notesButton->setEnabled(true);
        }

    }
    if (centralWidget()->findChild<QWidget*>("inspirationWidget")){
        QWidget* inspirationWidget = centralWidget()->findChild<QWidget*>("inspirationWidget");
        gridLayout->removeWidget(inspirationWidget);
        delete inspirationWidget;
    }
}

void MainWindow::on_notesButton_clicked(QPushButton *notesButton, QWidget *centralWidget, QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QWidget *mainWidget, QLabel *helloLabel, QGridLayout *gridLayout, AspectRatioWidget *aspectRatioWidget)
{
    resetWindow(notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

    if (notesButton)
    {
        notesButton->setEnabled(false);
    }

    QWidget *notesWidget = new QWidget(centralWidget);
    notesWidget->setObjectName("notesWidget");
    notesWidget->setStyleSheet("background-color: #071426");
    AspectRatioWidget *notesAspectRatioWidget = new AspectRatioWidget(notesWidget, 4, 4, centralWidget);
    gridLayout->addWidget(notesAspectRatioWidget, 1, 0, 5, 1);

    //scroll area for the notes
    QScrollArea *scrollArea = new QScrollArea(notesWidget);
    scrollArea->setWidgetResizable(true);

    // text edit widget for the notepad
    QTextEdit *notepad = new QTextEdit(scrollArea);
    notepad->setObjectName("notepad");
    notepad->setStyleSheet("background-color: #2B2D42; color: white;");

    scrollArea->setWidget(notepad);

    QString button3Style = "QPushButton {"
                           "background-color: #009ace;"
                           "color: white;"
                           "border: none;"
                           "padding: 8px 16px;"
                           "border-radius: 4px;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: #1C82E7;"
                           "}"
                           "QPushButton:pressed {"
                           "background-color: #1669C6;"
                           "}";
    // save button
    QPushButton *saveButton = new QPushButton("Save");
    connect(saveButton, &QPushButton::clicked, [notepad]() {
        QString text = notepad->toPlainText();

        QString filePath = notepad->property("filePath").toString();

        // If the file path is not set, prompt for a file name
        if (filePath.isEmpty()) {
            bool gotOk = false;
            QString fileName = QInputDialog::getText(notepad, "Save File", "Enter file name:", QLineEdit::Normal, "", &gotOk);
            if (gotOk) {
                QString defaultFolder = QDir::currentPath();
                QString folderPath = defaultFolder + QDir::separator() + "savedFiles";
                QDir().mkpath(folderPath);

                filePath = folderPath + QDir::separator() + fileName + ".txt";

                // Check if the file already exists
                if (QFile::exists(filePath)) {
                    int fileCount = 1;
                    QString baseFileName = fileName;
                    while (QFile::exists(filePath)) {
                        fileName = baseFileName + "_" + QString::number(fileCount);
                        filePath = folderPath + QDir::separator() + fileName + ".txt";
                        fileCount++;
                    }
                }
                gotOk = false;
            }
        }

        // Save the file
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << text;
            file.close();

            notepad->setProperty("filePath", filePath);
        }
    });


    QPushButton *newButton = new QPushButton("New");
    connect(newButton, &QPushButton::clicked, [notepad]() {
        notepad->clear();
        notepad->setProperty("filePath", "");  // Reset the file path
    });

    QPushButton *loadButton = new QPushButton("Load");
    connect(loadButton, &QPushButton::clicked, [notepad]() {
        QString defaultFolder = QDir::currentPath();
        QString folderPath = defaultFolder + QDir::separator() + "savedFiles";
        QString filePath = QFileDialog::getOpenFileName(notepad, "Load File", folderPath);
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString loadedText = stream.readAll();
            file.close();

            notepad->setPlainText(loadedText);
            notepad->setProperty("filePath", filePath);  // Set the file path
        }
    });

    loadButton->setStyleSheet(button3Style);
    saveButton->setStyleSheet(button3Style);
    newButton->setStyleSheet(button3Style);

    QHBoxLayout *button3Layout = new QHBoxLayout();
    button3Layout->addWidget(saveButton);
    button3Layout->addWidget(newButton);
    button3Layout->addWidget(loadButton);

    // Main layout for the notes widget
    QVBoxLayout *mainNotesLayout = new QVBoxLayout(notesWidget);
    mainNotesLayout->addLayout(button3Layout);
    mainNotesLayout->addWidget(scrollArea);

    notesWidget->setLayout(mainNotesLayout);

    // Hide Hello message
    helloLabel->setVisible(false);
}

void MainWindow::on_inspirationButton_clicked(QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget)
{
    resetWindow(notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

    if (inspirationButton)
    {
        inspirationButton->setEnabled(false);
    }

        QWidget *inspirationWidget = new QWidget(centralWidget);
        inspirationWidget->setObjectName("inspirationWidget");
        inspirationWidget->setStyleSheet("background-color: red;");
        inspirationWidget->setMinimumSize(500,500);
        AspectRatioWidget *inspirationAspectRatioWidget = new AspectRatioWidget(inspirationWidget, 4, 4, centralWidget);
        gridLayout->addWidget(inspirationAspectRatioWidget, 1, 0, 5, 1);

        QFile quotes(":/motivation/mfile.txt");
            if(!quotes.open(QIODevice::ReadOnly | QIODevice::Text)){
                return;
            }

            QList<QString> allQuotes;
            QTextStream in(&quotes);

            while (!in.atEnd()) {
                QString quoteDisplayed = in.readLine();
                allQuotes.append(quoteDisplayed);
            }

            quotes.close();

            int randomNumber = QRandomGenerator::global()->bounded(allQuotes.size());
            QString quoteDisplayed = allQuotes[randomNumber];


        QLabel *quoteLabel = new QLabel(quoteDisplayed, inspirationAspectRatioWidget);
        quoteLabel->setWordWrap(true);
        quoteLabel->setAlignment(Qt::AlignCenter);
        quoteLabel->setStyleSheet("font-size: 24px; color: white;");

        QVBoxLayout *inspirationLayout = new QVBoxLayout(inspirationWidget);
        inspirationLayout->addWidget(quoteLabel);
        inspirationWidget->setLayout(inspirationLayout);

}
