#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <IAsset.h>

using namespace std;

namespace rage {
    class AssetManager
    {
        public:
            static AssetManager& getInstance();
            string registerAssetInstance(IAsset& asset);
            bool unregisterAssetInstance(string id);
            vector<IAsset*> findAll();
            IAsset* findAssetById(string id);
            vector<IAsset*> findAssetsByClass(string className);
        protected:
        private:
            AssetManager(): idGenerator(0){};
            ~AssetManager(){delete &assets;};
            AssetManager(const AssetManager&);
            const AssetManager& operator=(const AssetManager&);
            map<string, IAsset*> assets;
            string uuidGenerator(string name);
            int idGenerator;
    };
}
#endif // ASSETMANAGER_H
