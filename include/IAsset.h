#ifndef IASSET_H
#define IASSET_H

#include <string>

using namespace std;

namespace rage {
    class IAsset
    {
        public:
            virtual string getClassName() = 0;
            void setId(string id) {this->id = id;};
            string getId() {return this->id;};
            typedef void (IAsset::*CallbackType)(string);
        protected:
        private:
            string id;
    };
}
#endif // IASSET_H
