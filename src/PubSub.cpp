#include <iostream>
#include <PubSub.h>

using namespace rage;

PubSub& PubSub::getInstance()
{
    static PubSub instance;
    return instance;
}

PubSub::PubSub()
{
    //ctor
}

PubSub::~PubSub()
{
    //dtor
}

bool PubSub::define(string topic)
{
    map<string, SubscriberList>::iterator it;
    it = subscribers.find(topic);
    if (it == subscribers.end()) {
        SubscriberList subscriberList;
        subscribers[topic] = subscriberList;
    }

    return false;
}

bool PubSub::subscribe(string topic, IAsset* asset, CallbackType callback)
{
    map<string, SubscriberList>::iterator it;
    it = subscribers.find(topic);
    if (it != subscribers.end()) {
        Subscriber sub;
        sub.pointerInstance = asset;
        sub.callback = callback;
        it->second.push_back(sub);
        return true;
    }

    return false;
}

bool PubSub::unsubscribe(string topic, IAsset* asset)
{
    map<string, SubscriberList>::iterator it;
    it = subscribers.find(topic);
    if (it != subscribers.end()) {
        for(int i=0, size=it->second.size(); i<size; i++) {
            if (it->second.at(i).pointerInstance == asset) {
                it->second.erase(it->second.begin() + i);
                return true;
            }
        }
    }
    return false;
}

bool PubSub::publish(string topic, string message)
{
    map<string, SubscriberList>::iterator it;
    it = subscribers.find(topic);
    if (it != subscribers.end()) {
        SubscriberList subscriberList = it->second;
        for(int i=0, size=subscriberList.size(); i<size; i++) {
            (subscriberList.at(i).pointerInstance->*subscriberList.at(i).callback)("[" + topic + "] " + message);
        }
        return true;
    }

    return false;
}
