#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#ifndef STORAGE_H
#include "storage.h"
#endif
#ifndef NODESPOOL_H
#include "nodespool.h"
#endif
#ifndef SAVELOAD_H
#include "saveload.h"
#endif

class FileManager:
        public Storage,
        public Subscription
{
//_________________________________________________Interface__
public:
    spDistributorIDNode getDistributorIDNode() final override;
    void appendNodeRoot(const spNode& node) final override;
    void appendNode(const spNode& node,
                    const IDNode& idParent) final override;
    void removeNode(const IDNode& id) final override;
    spNode getNode(const IDNode& id) final override;
    void beginChange() final override;
    void endChange() final override;

//____________________________________________Initialization__
public:
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    FileManager() /*= default*/;
    ~FileManager() /*= default*/;
    FileManager(const FileManager&) = delete;
    FileManager& operator =(const FileManager&) = delete;

    void initialize() final override;

public:
    friend QDataStream& operator <<(QDataStream& out,
                                    const FileManager& obj);
    friend QDataStream& operator >>(QDataStream& in,
                                    FileManager& obj);

//____________________________________________________Hidden__
private:
    NodesPool pool_;
    spDistributorIDNode distributor_ =
            spDistributorIDNode(new DistributorIDNode());
    int writeIndicator_ = 0;
    bool isInitialize_= false;

private:
    void reaction() final override;
    void write();
    void read();
//____________________________________________________________
};

#endif // FILEMANAGER_H
