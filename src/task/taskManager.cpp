#include "task/taskManager.h"

#include <QObject>  // for QObject
#include <QString>  // for QString

#include <vector>    // for std::vector
#include <optional>  // for std::optional
#include <cstddef>   // for std::size_t

#include "log/logType.h"     // for LogeType
#include "log/logManager.h"  // for LogManager
#include "task/task.h"       // for Task

TaskManager* TaskManager::instance()
{
    static TaskManager mgr; // since C++11 thread-safe
    return &mgr;
}

TaskManager::TaskManager(QObject* parent)
    : QObject( parent )
{   }

std::optional<std::size_t> TaskManager::findTaskIndex(const QString& name) const
{
    for ( std::size_t i { 0 }; i < m_tasks.size(); ++i ) {
        if ( m_tasks[i].name() == name ) {
            return i;
        }
    }

    // If we don't find the Task
    return std::nullopt;
}

bool TaskManager::listTasks() const
{
    QString outMsg;
    if ( m_tasks.empty() ) {
        outMsg = "No tasks.";
    } else {
        std::size_t countNonCompleteTasks { 0 };
        for ( const auto& task : m_tasks ) {
            if ( !task.completed() ) {
                ++countNonCompleteTasks;
            }
        }

        outMsg = QString( "%1 tasks listed." ).arg( countNonCompleteTasks );
    }
    LogManager* lm = LogManager::instance();
    lm->log(outMsg, LogType::Success);
    return true;
}


bool TaskManager::addTask(const QString& name)
{
    LogManager* lm = LogManager::instance();
    QString outMsg;
    if ( findTaskIndex(name) ) {
        outMsg = QString( "Error: a task named \"%1\" already exists." )
                    .arg(name);
        lm->log(outMsg, LogType::Error);
        return false;
    }

    m_tasks.emplace_back( name, false );
    outMsg = QString( "Added task: \"%1\"." ).arg(name);
    lm->log(outMsg, LogType::Success);
    emit tasksUpdated();
    return true;
}

bool TaskManager::removeTask(const QString& name)
{
    LogManager* lm = LogManager::instance();
    QString outMsg;
    const auto idx = findTaskIndex(name);
    if ( idx == std::nullopt ) {
        outMsg = QString( "Error: task \"%1\" not found." ).arg(name);
        lm->log(outMsg, LogType::Error);
        return false;
    }

    m_tasks.erase( m_tasks.begin() + idx.value() );
    outMsg = QString( "Removed task: \"%1\"." ).arg(name);
    lm->log(outMsg, LogType::Success);
    emit tasksUpdated();
    return true;
}

bool TaskManager::completeTask(const QString& name)
{
    LogManager* lm = LogManager::instance();
    const auto idx = findTaskIndex(name);
    QString outMsg;
    if ( idx == std::nullopt ) {
        outMsg = QString( "Error: task \"%1\" not found." ).arg(name);
        lm->log(outMsg, LogType::Error);
        return false;
    }

    m_tasks[idx.value()].setCompleted( true );
    outMsg = QString( "Completed task: \"%1\"." ).arg(name);
    lm->log(outMsg, LogType::Success);
    emit tasksUpdated();
    return true;
}
