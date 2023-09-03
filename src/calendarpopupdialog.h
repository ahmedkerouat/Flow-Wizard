#include <QDialog>
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>

class CalendarPopupDialog : public QDialog {
    Q_OBJECT
public:
    CalendarPopupDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Date");
        setFixedSize(300, 250);
        setStyleSheet("background-color: #071426;");

        QVBoxLayout *layout = new QVBoxLayout(this);

        calendarWidget = new QCalendarWidget(this);
        layout->addWidget(calendarWidget);

        QPushButton *okButton = new QPushButton("OK", this);
        okButton->setStyleSheet("color:white;background-color:#009ace;border:none;");
        layout->addWidget(okButton);

        QDate currentDate = QDate::currentDate();
           calendarWidget->setMinimumDate(QDate(currentDate.year(), 1, 1));
           calendarWidget->setMaximumDate(QDate(currentDate.year(), 12, 31));

           QString calendarStylesheet =
               "QCalendarWidget QToolButton {"
               "    height: 30px;"
               "    width: 80px;"
               "    color: white;"
               "    font-size: 12px;"
               "    icon-size: 16px, 16px;"
               "    background-color: #071426;"
               "}"
               "QCalendarWidget QMenu {"
               "    width: 150px;"
               "    left: 20px;"
               "    color: white;"
               "    font-size: 12px;"
               "    background-color: #071426;"
               "}"
               "QCalendarWidget QSpinBox {"
               "    width: 80px;"
               "    font-size: 12px;"
               "    color: white;"
               "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #cccccc, stop: 1 #333333);"
               "    selection-background-color: #071426;"
               "    selection-color: #009ace;"
               "}"
               "QCalendarWidget QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; width: 16px; }"
               "QCalendarWidget QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; width: 16px; }"
               "QCalendarWidget QSpinBox::up-arrow { width: 16px; height: 16px; }"
               "QCalendarWidget QSpinBox::down-arrow { width: 16px; height: 16px; }"
               "QCalendarWidget QWidget { alternate-background-color: #071426; }"
               "QCalendarWidget QAbstractItemView:enabled {"
               "    font-size: 12px;"
               "    color: rgb(180, 180, 180);"
               "    background-color: #071426;"
               "    selection-background-color: #071426;"
               "    selection-color: #009ace;"
               "}"
               "QCalendarWidget QWidget#qt_calendar_navigationbar {"
               "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #cccccc, stop: 1 #333333);"
               "}"
               "QCalendarWidget QAbstractItemView:disabled {"
               "    color: #071426;"
               "}";
                                        ;
           calendarWidget->setStyleSheet(calendarStylesheet);

        connect(okButton, &QPushButton::clicked, this, &CalendarPopupDialog::accept);
    }

    QDate getSelectedDate() const {
        return calendarWidget->selectedDate();
    }

private:
    QCalendarWidget *calendarWidget;
};
