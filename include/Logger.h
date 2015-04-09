#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include <IAsset.h>

namespace rage {
    class Logger : public IAsset
    {
        public:
            Logger();
            virtual ~Logger();
            virtual string getClassName() {return "Logger";};
            virtual void log(string message);
            typedef void (Logger::*LogFunction)(string);
        protected:
        private:
    };
}
#endif // LOGGER_H
