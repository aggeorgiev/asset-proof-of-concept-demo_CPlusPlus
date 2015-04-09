#ifndef PUBSUB_H
#define PUBSUB_H

#include <string>
#include <map>
#include <vector>

#include <IAsset.h>

namespace rage {
    typedef void (IAsset::*CallbackType)(string);
    class PubSub
    {
        struct Subscriber {
            IAsset* pointerInstance;
            CallbackType callback;
        };
        public:
            static PubSub& getInstance();
            bool define(string topic);
            bool subscribe(string topic, IAsset* asset, CallbackType callback);
            bool unsubscribe(string topic, IAsset* asset);
            bool publish(string topic, string message);
        protected:
        private:
            PubSub();
            ~PubSub();
            PubSub(const PubSub&);
            const PubSub& operator=(const PubSub&);
            typedef std::vector<Subscriber> SubscriberList;
            typedef std::map<string, SubscriberList> SubscriberMap;
            SubscriberMap subscribers;
    };
}
#endif // PUBSUB_H
