#ifndef   __Task_Manager__
# define  __Task_Manager__

# include <QObject>  // for QObject
# include <QString>  // for QString

# include <vector>    // for std::vector
# include <cstddef>   // for std::size_t
# include <optional>  // for std::optional

#include "task.h"         // for Task
#include "log/logType.h"  // for LogType

class TaskManager final : public QObject
{
    Q_OBJECT
public:
    static TaskManager* instance();

    // Non-copyable
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    // operations
    bool addTask(const QString& name);
    bool removeTask(const QString& name);
    bool completeTask(const QString& name);
    bool listTasks();
    /**
     * @brief Returns a formatted list of all tasks.
     *
     * This function compiles all existing tasks into a single QString,
     * typically separated by newlines or commas, suitable for display or output.
     *
     * @return A QString containing the list of all tasks.
     */
    [[nodiscard]]
    QString listOfTasks() const;

    [[nodiscard]]
    const std::vector<Task>& tasks() const noexcept { return m_tasks; }

signals:
    void tasksUpdated();
    void logMessage(const QString& msg, LogType type);

private:
    explicit TaskManager(QObject* parent = nullptr);
    ~TaskManager() override = default;

    /**
     * @brief Finds the index of a task by its name.
     *
     * This function searches for a task with the given name in the task list
     * and returns its index position if found. If no task with the specified
     * name exists, it returns std::nullopt.
     *
     * @param name The name of the task to search for.
     * @return The index of the task if found; otherwise, std::nullopt.
     */
    [[nodiscard]]
    std::optional<std::size_t> findTaskIndex(const QString& name) const;

    std::vector<Task> m_tasks;
};

#endif // __Task_Manager__
