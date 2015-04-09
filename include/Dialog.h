#ifndef DIALOG_H
#define DIALOG_H

#include <vector>

#include <IAsset.h>

namespace rage {

    class DialogOptions
    {
        public:
            DialogOptions(){};
            virtual ~DialogOptions(){};
            string text;
            int responseId;
            int nextDialogNodeId;
    };

    class DialogNode
    {
        public:
            DialogNode(){};
            virtual ~DialogNode();
            string text;
            int dialogNodeId;
            vector<DialogOptions *> dialogOptions;
    };

    class DialogTree
    {
        public:
            DialogTree(){};
            virtual ~DialogTree();
            int load(char * txtFileName);
            DialogNode* findDialogNodeById(int id);
            vector<DialogNode *> dialogNodes;
        private:

    };

    class Dialog : public IAsset
    {
        public:
            Dialog(string actor, string player) : actorId(actor), playerId(player), currentDialogNodeId(1){dialogTree = new DialogTree();};
            virtual ~Dialog();
            virtual string getClassName() {return "Dialog";};
            int load(char * txtFileName);
            int interact(int responseId = 0);
        protected:
        private:
            string actorId;
            string playerId;
            int currentDialogNodeId;
            DialogTree * dialogTree;
    };
}
#endif // DIALOG_H
