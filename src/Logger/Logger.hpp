#pragma once
#include <iostream>
#include <string>

class Logger {
public:
    enum Level {
        TRACE,
        DEBUG,
        VERBOSE,
        INFO,
        WARNING,
        ERROR,
        FATAL,
    };

    static std::ostream& trace()
    {
        return (the().m_level <= TRACE ? std::cout : the().m_nullStream);
    }

    static std::ostream& debug()
    {
        return (the().m_level <= DEBUG ? std::cout : the().m_nullStream);
    }

    static std::ostream& verbose()
    {
        return (the().m_level <= VERBOSE ? std::cout : the().m_nullStream);
    }

    static std::ostream& info()
    {
        return (the().m_level <= INFO ? std::cout : the().m_nullStream);
    }

    static std::ostream& warning()
    {
        return (the().m_level <= WARNING ? std::cout : the().m_nullStream);
    }

    static std::ostream& error()
    {
        return (the().m_level <= ERROR ? std::cout : the().m_nullStream);
    }

    static std::ostream& fatal()
    {
        return (the().m_level <= FATAL ? std::cout : the().m_nullStream);
    }

private:
    class NullStream : public std::ostream {
    public:
        NullStream()
            : std::ostream(nullptr)
        {
            // Default constructor
        }
        NullStream(const NullStream&)
            : std::ostream(nullptr)
        {
            // Copy constructor
        }
    };

    Logger()
        : m_nullStream()
        , m_level(INFO)
    {
        // Default constructor
    }

    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& the()
    {
        static Logger logger;
        return logger;
    }

    Logger::NullStream m_nullStream;
    Level m_level;
};
