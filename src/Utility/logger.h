#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <memory>

namespace Utility {
    enum class etSeverity {
        INFO,
        ERROR
    };

    class ILogStrategy {
    public:
        virtual void Log(const etSeverity sev, const std::string& text) const = 0;
    };

    class CSilentLogStrategy : public ILogStrategy {
    public:
        virtual void Log(const etSeverity sev, const std::string& text) const;
    };

    class CVerboseLogStrategy : public ILogStrategy {
    public:
        virtual void Log(const etSeverity sev, const std::string& text) const;
    };

    class CLogger {
    private:
        CLogger() = default;
        CLogger(const CLogger& r) = delete;
        CLogger& operator=(CLogger& r) = delete;
    public:
        static CLogger& GetInstance();
        void Log(const etSeverity sev, const std::string& text) const;
        void ChangeLogStrategy(std::shared_ptr<ILogStrategy> strategy);
    protected:
        std::shared_ptr<ILogStrategy> m_logStrategy;
    };
}

#endif