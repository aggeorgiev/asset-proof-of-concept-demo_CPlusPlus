#ifndef IMANAGERABSTRACT_H
#define IMANAGERABSTRACT_H
#include <string>

using namespace std;

namespace rage {

    template <class T>
    class IManagerAbstract
    {
        public:
            virtual T registerAssetInstance()=0; // must be template
            virtual T findAssetById(string id)=0;
            virtual T findAssetByClass(string className)=0; // using reflection
            virtual T findOneAssetByClass(string className)=0; // ...
        protected:
        private:
    };

}

#endif // IMANAGERABSTRACT_H
