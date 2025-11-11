#ifndef   __Main_Window__
# define  __Main_Window__

# include <QMainWindow>  // Base class

# include <QObject>  // for Q_OBJECT
# include <QString>  // for QString

# include "log/logType.h"  // for LogType
class QListWidget;
class QTextEdit;
class QLineEdit;
class QPushButton;
class QColor;

class MainWindow final : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onCommandEntered();
    void handleTasksUpdated();
    void handleLogMessage(const QString& msg, LogType logType);

private:
    void setupUi();
    void refreshTaskList();
    void appendLog(const QString& msg, const QColor& color);

    QListWidget* m_taskList  { nullptr };
    QTextEdit*   m_logView   { nullptr };
    QLineEdit*   m_cmdInput  { nullptr };
    QPushButton* m_runButton { nullptr };
};

#endif // __Main_Window__
