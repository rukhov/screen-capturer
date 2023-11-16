#include "mainwindow.h"

#include <QGridLayout>
#include <QListWidget>

MainWindow::MainWindow(Controller& controller)
    : QMainWindow(nullptr)
    , m_controller(controller)
    , m_startStopButton(this)
    , m_dbView(this)
{
    setCentralWidget(new QWidget(this));

    auto layout = new QGridLayout(centralWidget());

    layout->addWidget(&m_startStopButton, 0, 0);
    layout->addWidget(&m_dbView, 1, 0);

    connect(&m_startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(&m_controller, &Controller::CapturingStateChanged, this, &MainWindow::onCapturingStateChanged);
    connect(&m_controller, &Controller::DataBaseUpdated, this, &MainWindow::onDataBaseUpdated);

    m_tableModel.setTable("screenshots");
    m_tableModel.setSort(0, Qt::SortOrder::DescendingOrder);

    m_dbView.setViewMode(QListWidget::IconMode);
    m_dbView.setResizeMode(QListWidget::Adjust);
    m_dbView.setLayoutMode(QListView::Batched);
    m_dbView.setBatchSize(5);
    m_dbView.setModel(&m_tableModel);
    m_dbView.setModelColumn(0);
    m_dbView.show();

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

    m_tableModel.select();
}

void MainWindow::onCapturingStateChanged(bool started)
{
    Q_ASSERT(thread()->currentThreadId() == QThread::currentThreadId());

    UpdateUIState();
}

void MainWindow::onDataBaseUpdated()
{
    UpdateUIState();
}
