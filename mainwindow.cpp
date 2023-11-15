#include "mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(Controller& controller)
    : QMainWindow(nullptr)
    , m_controller(controller)
    , m_startStopButton(this)
{
    auto layout = new QGridLayout(this);

    layout->addWidget(&m_startStopButton, 0, 0);

    connect(&m_startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(&m_controller, &Controller::CapturingStateChanged, this, &MainWindow::onCapturingStateChanged);

    UpdateUIState();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onStartStopClicked()
{
    m_controller.StartStopCapturing(!m_controller.CapturingState());
}

void MainWindow::UpdateUIState()
{
    if(m_controller.CapturingState())
    {
        m_startStopButton.setText(tr("&Stop"));
    }
    else
    {
        m_startStopButton.setText(tr("&Start"));
    }
}

void MainWindow::onCapturingStateChanged(bool started)
{
    Q_ASSERT(thread()->currentThreadId() == QThread::currentThreadId());

    UpdateUIState();
}
