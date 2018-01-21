#ifndef EMULATORWINDOW_H
#define EMULATORWINDOW_H

#include <QMainWindow>

namespace Ui {
class EmulatorWindow;
}

class EmulatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmulatorWindow(QWidget *parent = 0);
    ~EmulatorWindow();

private slots:
    void onStartButtonClicked();

private:
    Ui::EmulatorWindow *ui;
};

#endif // EMULATORWINDOW_H
