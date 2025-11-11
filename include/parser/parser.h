#ifndef   __Command_Parser__
# define  __Command_Parser__

# include <QString>      // for QString
# include <QStringList>  // for QStringList

# include "command/cmd.h"  // for Cmd::Ptr

struct Parser final
{
    Parser() = default;
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;

    /**
     * @brief Parses a command line string and creates the corresponding command object.
     *
     * This function interprets the given input string, identifies the appropriate
     * command type, and returns a Cmd::Ptr representing that command.
     * If the input is invalid or the command type is unrecognized, it returns nullptr.
     *
     * @param  cmdLine The raw command line string to parse.
     * @return A Cmd::Ptr to the created command object, or nullptr if parsing fails.
     */
    static Cmd::Ptr createCmd(const QString& cmdLine);

private:
    // helper parsing functions
    static QString extractArgValue(const QStringList& args);

    template <typename T>
    static Cmd::Ptr createTemplateCmd(const QStringList& args);
};

#endif // __Command_Parser__
