#include "command/listTaskCmd.h"

#include "task/taskManager.h"  // for TaskManager

bool ListTaskCmd::execute() const
{
    TaskManager* tm = TaskManager::instance();
    return tm->listTasks();
}
