#ifndef   __Task__
# define  __Task__

# include <QString>  // for QString

# include <utility>  // for std::move

class Task
{
public:
    explicit Task(QString  name, const bool completed = false)
        : m_name( std::move( name ) ), m_completed( completed )
    {   }

    ~Task() = default;

    [[nodiscard]]
    const QString& name() const noexcept { return m_name; }

    [[nodiscard]]
    bool completed() const noexcept { return m_completed; }
    void setCompleted(const bool state) { m_completed = state; }

private:
    QString m_name;
    bool    m_completed;
};

#endif // __Task__
