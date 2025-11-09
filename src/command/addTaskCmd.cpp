#include "command/addTaskCmd.h"

#include <QString>  // for QString

#include <utility>  // for std::move

#include "task/taskManager.h"  // for TaskManager

AddTaskCmd::AddTaskCmd(QString taskName)
    : m_taskName( std::move( taskName ) )
{   }

bool AddTaskCmd::execute() const
{
    TaskManager* tm = TaskManager::instance();
    return tm->addTask( m_taskName );
}
