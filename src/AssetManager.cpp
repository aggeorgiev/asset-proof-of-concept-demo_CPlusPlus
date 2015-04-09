#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#include <AssetManager.h>

using namespace rage;

AssetManager& AssetManager::getInstance()
{
    static AssetManager instance;
    return instance;
}

string AssetManager::uuidGenerator(string name)
{
    stringstream s;
    s << name << "_" << ++idGenerator;
    return s.str();
}

string AssetManager::registerAssetInstance(IAsset& asset)
{
    string uuid = uuidGenerator(asset.getClassName());
    asset.setId(uuid);
    assets[uuid] = &asset;
    return uuid;
}

bool AssetManager::unregisterAssetInstance(string id)
{
    map<string, IAsset *>::iterator it = assets.find(id);
    if (it != assets.end()) {
        assets.erase(it);
        return true;
    }
    return false;
}

IAsset* AssetManager::findAssetById(string id)
{
    map<string, IAsset *>::iterator it = assets.find(id);
    if (it != assets.end()) {
        return it->second;
    }
    return NULL;
}

vector<IAsset*> AssetManager::findAll()
{
    vector<IAsset*> results;
    for(map<string,IAsset*>::iterator it = assets.begin(); it != assets.end(); ++it) {
        results.push_back(it->second);
    }
    return results;
}


 vector<IAsset*> AssetManager::findAssetsByClass(string className)
 {
    vector<IAsset*> match_results;
    for(map<string,IAsset*>::iterator it = assets.begin(); it != assets.end(); ++it) {
        if(className == it->second->getClassName()) {
            match_results.push_back(it->second);
        }
    }
    return match_results;
 }
