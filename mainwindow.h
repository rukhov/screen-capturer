#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include "SqlImageTableModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Controller& m_controller;
    QPushButton m_startStopButton;
    QListView m_dbView;
    SqlImageTableModel m_tableModel;

public:
    MainWindow(Controller& controller);
    ~MainWindow();

private slots:

    void onCapturingStateChanged(bool);
    void onDataBaseUpdated();
    void onError(QString err);

private:

    void onStartStopClicked();


    void UpdateUIState();
};

#endif // MAINWINDOW_H
