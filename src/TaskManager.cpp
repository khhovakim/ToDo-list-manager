#include "TaskManager.h"

#include <QObject>  // for QObject
#include <QString>  // for QString

#include <vector>    // for std::vector
#include <optional>  // for std::optional
#include <cstddef>   // for std::size_t

#include "Task.h"     // for Task
#include "LogType.h"  // for LogType

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

    // if don't find the Task
    return std::nullopt;
}

QString TaskManager::listOfTasks() const
{
    if ( m_tasks.empty() ) return QString( "No tasks." );

    QString out;
    for ( const auto& task : m_tasks ) {
        out.append(
            QString("%1 - %2\n")
                .arg(task.name())
                .arg(task.completed() ? "Completed" : "Pending")
        );
    }

    return out;
}

bool TaskManager::addTask(const QString& name, QString& outMsg)
{
    if ( findTaskIndex(name) ) {
        outMsg = QString( "Error: a task named \"%1\" already exists." )
                    .arg(name);
        emit logMessage(outMsg, LogType::Error);
        return false;
    }

    m_tasks.emplace_back( name, false );
    outMsg = QString( "Added task: \"%1\"." ).arg(name);
    emit logMessage(outMsg, LogType::Success);
    emit tasksUpdated();
    return true;
}

bool TaskManager::removeTask(const QString& name, QString& outMsg)
{
    auto idx = findTaskIndex(name);
    if ( idx == std::nullopt ) {
        outMsg = QString( "Error: task \"%1\" not found." ).arg(name);
        emit logMessage(outMsg, LogType::Error);
        return false;
    }

    m_tasks.erase( m_tasks.begin() + idx.value() );
    outMsg = QString( "Removed task: \"%1\"." ).arg(name);
    emit logMessage(outMsg, LogType::Success);
    emit tasksUpdated();
    return true;
}

bool TaskManager::completeTask(const QString& name, QString& outMsg)
{
    auto idx = findTaskIndex(name);
    if ( idx == std::nullopt ) {
        outMsg = QString( "Error: task \"%1\" not found." ).arg(name);
        emit logMessage(outMsg, LogType::Error);
        return false;
    }

    m_tasks[idx.value()].setCompleted( true );
    outMsg = QString( "Completed task: \"%1\"." ).arg(name);
    emit logMessage(outMsg, LogType::Success);
    emit tasksUpdated();
    return true;
}
