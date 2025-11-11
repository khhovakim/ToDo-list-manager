#ifndef   __Log_Manager__
# define  __Log_Manager__

# include <QObject>  // Base class

# include <QString>  // for QString

# include "logType.h"  // for LogType

class LogManager final : public QObject
{
    Q_OBJECT
public:
    [[nodiscard]]
    static LogManager* instance();

    // Non-copyable
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    void log(const QString& msg, LogType type);

signals:
    void logUi(const QString& msg, LogType type);

private:
    explicit LogManager(QObject* parent = nullptr)
        : QObject( parent )
    {   }
    ~LogManager() override = default;
};


#endif // __Log_Manager__