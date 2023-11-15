#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Controller.h"

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Controller& m_controller;
    QPushButton m_startStopButton;

public:
    MainWindow(Controller& controller);
    ~MainWindow();

private slots:

    void onCapturingStateChanged(bool started);

private:

    void onStartStopClicked();


    void UpdateUIState();
};

#endif // MAINWINDOW_H
