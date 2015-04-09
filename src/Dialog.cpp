#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include <Dialog.h>
#include <PubSub.h>

using namespace rage;

Dialog::~Dialog()
{
    delete dialogTree;
}

int Dialog::load(char * txtFileName)
{
    ifstream dlgFile(txtFileName);
    if (!dlgFile) {
        cout << "File not found." << endl;
        return -1;
    }
    DialogNode * currentDialogNode = NULL;
    string line, strOptions;
    int semicolon_indx, i, j;
    while (getline(dlgFile, line)) {
        if (line.empty()) continue;
        semicolon_indx = line.find(':');
        int id =  atoi(line.substr(0,semicolon_indx).c_str());
        line = line.substr(semicolon_indx+2, line.length());
        i = line.find("->");
        if(i > 0) {
            DialogOptions * dialogOption;
            for(int l=0, size=currentDialogNode->dialogOptions.size(); l<size; l++) {
                if (currentDialogNode->dialogOptions[l]->responseId == id) {
                    dialogOption = currentDialogNode->dialogOptions[l];
                    break;
                }
            }
            dialogOption->responseId = id;
            dialogOption->nextDialogNodeId = atoi(line.substr(i+3, line.length()).c_str());
            line = line.substr(0, i-1);
            dialogOption->text = line;
        } else {
            DialogNode * dialogNode = new DialogNode();
            currentDialogNode = dialogNode;
            dialogNode->dialogNodeId = id;
            i = line.find('[');
            if (i>0) {
                strOptions = line.substr(i+1, line.find(']')-i-1);
                j = strOptions.find(',');
                while(j>=0) {
                    DialogOptions * dialogOption = new DialogOptions();
                    dialogOption->responseId = atoi(strOptions.substr(0, j).c_str());
                    dialogNode->dialogOptions.push_back(dialogOption);
                    strOptions = strOptions.substr(j+1, strOptions.length());
                    j = strOptions.find(',');
                }
                DialogOptions * dialogOption = new DialogOptions();
                dialogOption->responseId = atoi(strOptions.c_str());
                dialogNode->dialogOptions.push_back(dialogOption);
            }
            line = line.substr(0, i-1);
            dialogNode->text = line;
            dialogTree->dialogNodes.push_back(dialogNode);
        }
    }

    dlgFile.close();
    return 1;
}

DialogNode::~DialogNode() {
    for(int i, size=dialogOptions.size(); i<size; i++) {
        delete dialogOptions.at(i);
    }

    dialogOptions.clear();
}

DialogTree::~DialogTree()
{
    for(int i, size=dialogNodes.size(); i<size; i++) {
        delete dialogNodes.at(i);
    }

    dialogNodes.clear();
}

DialogNode* DialogTree::findDialogNodeById(int id)
{
    for(int i=0, size=dialogNodes.size(); i<size; i++) {
        if (dialogNodes[i]->dialogNodeId == id) {
            return dialogNodes[i];
        }
    }
    return NULL;
}

int Dialog::interact(int responseId)
{
    if (dialogTree->dialogNodes.empty()) {
        return -1;
    }

    DialogNode * currentDialogNode = dialogTree->findDialogNodeById(currentDialogNodeId);
    if (currentDialogNode == NULL) {
        return -1;
    }

    if (responseId != 0) {
        PubSub& pubsub  = PubSub::getInstance();
        vector<DialogOptions *> dialogOptions = currentDialogNode->dialogOptions;
        for(int i=0, size=dialogOptions.size();i<size; i++) {
            if (dialogOptions[i]->responseId == responseId) {
                currentDialogNode = dialogTree->findDialogNodeById(dialogOptions[i]->nextDialogNodeId);
                ostringstream stream;
                stream << responseId << " - " << dialogOptions[i]->text;
                pubsub.publish("Rage.Dialog.Event", stream.str());
                break;
            }
        }
    }

    vector<DialogOptions *> dialogOptions = currentDialogNode->dialogOptions;

    cout << currentDialogNode->text << endl;

    if (dialogOptions.empty()) {
            return -1;
    }

    for(int i=0, size=dialogOptions.size();i<size; i++) {
        cout << dialogOptions[i]->responseId << ": " << dialogOptions[i]->text << endl;
    }
    cout << endl;

    return 1;
}
