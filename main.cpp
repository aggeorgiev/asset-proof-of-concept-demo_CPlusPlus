#include <iostream>
#include <vector>

#include <AssetManager.h>
#include <Logger.h>
#include <Dialog.h>
#include <PubSub.h>

using namespace std;
using namespace rage;

int main()
{
    Logger* log1 = new Logger();
    Logger* log2 = new Logger();
    Logger* log3 = new Logger();

    AssetManager& am = AssetManager::getInstance();

    //AssetManager::findAll
    vector<IAsset*> assets = am.findAll();
    for(int i=0, size=assets.size(); i<size; i++) {
        cout << "[Asset] " << assets.at(i)->getId() << endl;
    }

    //AssetManager::unregisterAssetInstance
    delete log2;
    assets = am.findAll();
    for(int i=0, size=assets.size(); i<size; i++) {
        cout << "[Asset] " << assets.at(i)->getId() << endl;
    }

    //AssetManager::findAssetById
    Logger* logger = dynamic_cast<Logger*>(am.findAssetById("Logger_1"));
    logger->log("Hello, World!");

    //AssetManager::findAssetsByClass
    vector<IAsset*> match_results = am.findAssetsByClass("Logger");
    for(int i=0, size=match_results.size(); i<size; i++) {
        IAsset* asset = match_results.at(i);
        Logger* logger = dynamic_cast<Logger*>(asset);
        if (logger) {
            logger->log("Hello, World!");
        }
    }

    //Subscribe and Publish
    PubSub& pubsub  = PubSub::getInstance();
    pubsub.define("Rage.Event");
    pubsub.subscribe("Rage.Event", log1, static_cast< IAsset::CallbackType > ( & Logger::log));
    pubsub.subscribe("Rage.Event", log3, static_cast< IAsset::CallbackType > ( & Logger::log));
    pubsub.publish("Rage.Event", "Hello, World!");

    //Unsubscribe Asset and Publish
    pubsub.unsubscribe("Rage.Event", log3);
    pubsub.publish("Rage.Event", "Hello, World!");

    Logger * dialogLogger = new Logger();
    pubsub.define("Rage.Dialog.Event");
    pubsub.subscribe("Rage.Dialog.Event", dialogLogger, static_cast< IAsset::CallbackType > ( & Logger::log));

    Dialog* dialog = new Dialog("actor", "player");
    dialog->load("script.txt");
    int reponseId;
    while (true) {
        dialog->interact();
        cout << "Option: "; cin >> reponseId;
        cout << endl;
        if (dialog->interact(reponseId) == -1) {
            break;
        }
    }

    return 0;
}
