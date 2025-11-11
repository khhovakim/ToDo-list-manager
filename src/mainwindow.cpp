#include "mainwindow.h"

#include <QObject>          // for QObject::connect
#include <QWidget>          // for QWidget
#include <QVBoxLayout>      // for QVBoxLayout
#include <QHBoxLayout>      // for QHBoxLayout
#include <QLabel>           // for QLabel
#include <QListWidget>      // for QListWidget
#include <QTextEdit>        // for QTextEdit
#include <QLineEdit>        // for QLineEdit
#include <QPushButton>      // for QPushButton
#include <QListWidgetItem>  // for QListWidgetItem

#include "task/taskManager.h"  // for TaskManager
#include "log/logManager.h"    // for LogManager
#include "log/logType.h"       // for LogType
#include "command/cmd.h"       // for Cmd::Ptr
#include "parser/parser.h"     // for Parser::createCmd

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();

    connect(TaskManager::instance(), &TaskManager::tasksUpdated, this, &MainWindow::handleTasksUpdated);
    connect(LogManager::instance(), &LogManager::logUi, this, &MainWindow::handleLogMessage);

    refreshTaskList();
}

void MainWindow::setupUi()
{
    QWidget* central = new QWidget( this );
    setCentralWidget( central );

    // === Base layout ===
    QVBoxLayout* mainLayout = new QVBoxLayout( central );
    mainLayout->setContentsMargins( 10, 10, 10, 10 );
    mainLayout->setSpacing( 10 );

    // === Tasks section ===
    QLabel* tasksLabel = new QLabel("Tasks:");
    QFont labelFont = tasksLabel->font();
    labelFont.setPointSize( 11 );
    labelFont.setBold( true );
    tasksLabel->setFont( labelFont );
    mainLayout->addWidget( tasksLabel );

    m_taskList = new QListWidget();
    m_taskList->setSelectionMode( QAbstractItemView::NoSelection );
    m_taskList->setFocusPolicy( Qt::NoFocus );
    m_taskList->setAlternatingRowColors( true );
    m_taskList->setStyleSheet( R"(
        QListWidget {
            background-color: #f9f9f9;
            border: 1px solid #ccc;
            border-radius: 6px;
            padding: 4px;
        }
        QListWidget::item {
            padding: 6px;
        }
    )" );
    mainLayout->addWidget( m_taskList, 1 );

    // === Log section ===
    QLabel* logLabel = new QLabel( "Log:" );
    logLabel->setFont( labelFont );
    mainLayout->addWidget( logLabel );

    m_logView = new QTextEdit();
    m_logView->setReadOnly( true );
    m_logView->setStyleSheet( R"(
        QTextEdit {
            background-color: #f9f9f9;
            border: 1px solid #ccc;
            font-family: Consolas, monospace;
            border-radius: 6px;
            padding: 6px;
        }
    )" );
    mainLayout->addWidget( m_logView, 1 );

    // === Command input ===
    QHBoxLayout* cmdLayout = new QHBoxLayout();
    m_cmdInput = new QLineEdit();
    m_cmdInput->setPlaceholderText( "Enter a command" );
    m_cmdInput->setMinimumHeight( 32) ;
    m_cmdInput->setStyleSheet( R"(
        QLineEdit {
            padding: 6px 8px;
            border: 1px solid #aaa;
            border-radius: 6px;
            font-size: 10.5pt;
        }
        QLineEdit:focus {
            border-color: #0078d7;
        }
    )" );
    cmdLayout->addWidget( m_cmdInput, 1 );

    m_runButton = new QPushButton( "Run" );
    m_runButton->setMinimumHeight( 32 );
    m_runButton->setStyleSheet( R"(
        QPushButton {
            background-color: #0078d7;
            color: white;
            border-radius: 6px;
            padding: 6px 12px;
        }
        QPushButton:hover {
            background-color: #2894ff;
        }
        QPushButton:pressed {
            background-color: #005a9e;
        }
    )" );
    cmdLayout->addWidget( m_runButton );

    mainLayout->addLayout( cmdLayout );

    // === Connections ===
    connect(m_runButton, &QPushButton::clicked, this, &MainWindow::onCommandEntered);
    connect(m_cmdInput, &QLineEdit::returnPressed, this, &MainWindow::onCommandEntered);

    setWindowTitle("TodoApp — Simple To-Do List");
    resize( 640, 480 );
}

void MainWindow::onCommandEntered()
{
    const QString cmdLine = m_cmdInput->text().trimmed();
    if ( cmdLine.isEmpty() ) {
        m_cmdInput->clear();
        return ;
    }

    const Cmd::Ptr cmd = Parser::createCmd( cmdLine );
    if ( !cmd ) {
        const QString errMsg = QString( "Invalid command: %1" ).arg( cmdLine );
        m_logView->setTextColor(Qt::red);
        m_logView->append(errMsg);
        m_logView->setTextColor(Qt::black);
        m_cmdInput->clear();
        return ;
    }

    cmd->execute();
    m_cmdInput->clear();
}

void MainWindow::handleLogMessage(const QString &message, const LogType logType)
{
    if ( logType == LogType::Error ) {
        m_logView->setTextColor(Qt::red);
    }

    m_logView->append(message);
    m_logView->setTextColor(Qt::black);
}

void MainWindow::handleTasksUpdated()
{
    refreshTaskList();
}


void MainWindow::refreshTaskList()
{
    m_taskList->clear();
    const auto& tasks = TaskManager::instance()->tasks();
    for ( const auto& task : tasks ) {
        QListWidgetItem* item = new QListWidgetItem( task.name(), m_taskList );

        // Make it checkable
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemNeverHasChildren);
        item->setCheckState(task.completed() ? Qt::Checked : Qt::Unchecked);

        m_taskList->addItem(item);
    }

}