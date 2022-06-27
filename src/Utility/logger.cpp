#include "./logger.h"
#include <iostream>

namespace Utility {

    CLogger& CLogger::GetInstance() {
        static CLogger instance;
        return instance;
    }

    void CLogger::Log(const etSeverity sev, const std::string& text) const {
        if (m_logStrategy) {
            m_logStrategy->Log(sev, text);
        }
    }

    void CLogger::ChangeLogStrategy(std::shared_ptr<ILogStrategy> strategy) {
        m_logStrategy = strategy;
    }


    void CSilentLogStrategy::Log(const etSeverity sev, const std::string& text) const {
        if (sev == etSeverity::ERROR) {
            std::cout << text << std::endl;
        }
    }

    void CVerboseLogStrategy::Log(const etSeverity sev, const std::string& text) const {
        std::cout << text << std::endl;
    }
}