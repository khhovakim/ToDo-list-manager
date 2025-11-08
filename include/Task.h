#ifndef   __Task__
# define  __Task__

# include <QString>  // for QString

class Task
{
public:
    Task() = default;
    explicit Task(const QString& name, bool completed = false)
        : m_name( name ), m_completed( completed )
    {   }

    ~Task() = default;

    const QString& name() const noexcept { return m_name; }
    void setName(const QString& name) { m_name = name; }
    
    bool completed() const noexcept { return m_completed; }
    void setCompleted(bool state) { m_completed = state; }

private:
    QString m_name;
    bool    m_completed { false };
};

#endif // __Task__