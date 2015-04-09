#include <AssetManager.h>
#include <Logger.h>

using namespace std;
using namespace rage;

Logger::Logger()
{
    AssetManager& am  = AssetManager::getInstance();
    am.registerAssetInstance(*this);
}

void Logger::log(string message)
{
    cout << "[" << this->getId() << "] " << message << endl;
}

Logger::~Logger()
{
    AssetManager& am  = AssetManager::getInstance();
    am.unregisterAssetInstance(this->getId());
}
