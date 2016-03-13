#ifndef FILEMANAGER_H
#include "filemanager.h"
#endif

//_________________________________________________Interface__

spDistributorIDNode FileManager::getDistributorIDNode()
{
    return distributor_;
}

void FileManager::appendNodeRoot(const spNode& node)
{
    pool_.appendNode(node);
}

void FileManager::appendNode(const spNode &node, const IDNode& idParent)
{
    pool_.appendNode(node);
}

void FileManager::removeNode(const IDNode& id)
{
    pool_.removeNode(id);
}

spNode FileManager::getNode(const IDNode &id)
{
    return pool_.get(id);
}

void FileManager::beginChange()
{
    ++writeIndicator_;
}

void FileManager::endChange()
{
    --writeIndicator_;
    if(writeIndicator_ < 0)
        throw std::logic_error("FileManager::endChange");
    if(writeIndicator_ == 0 && isInitialize_) write();
}

//____________________________________________Initialization__

FileManager::FileManager(){}

FileManager::~FileManager()
{
    if(writeIndicator_)
        std::cerr << "Logic error (FileManager::~FileManager)\n";
}

void FileManager::initialize()
{
    NodesPool tmp(std::move(pool_));
    read();
    if(pool_.getIDNodes().size() == 0)
        pool_ = std::move(tmp);
    subscribe(&pool_);
    isInitialize_ = true;
}

QDataStream& operator<<(QDataStream& out, const FileManager& obj)
{
    out << obj.pool_;
    out << *obj.distributor_;
    return out;
}

QDataStream& operator>>(QDataStream& in, FileManager& obj)
{
    in >> obj.pool_;
    in >> *obj.distributor_;
    return in;
}

//____________________________________________________Hidden__

void FileManager::reaction()
{
    if(writeIndicator_ == 0 && isInitialize_) write();
}

void FileManager::write()
{
    SaveLoad sl;
    auto result = sl.save(QDir::currentPath() + "\\data.txt", *this);
    if(result != SaveLoad::SaveResult::OK)
        throw std::logic_error("FileManager::write");
}

void FileManager::read()
{
    if(!QFile::exists(QDir::currentPath() + "\\data.txt")) write();
    SaveLoad sl;
    auto result = sl.load(QDir::currentPath() + "\\data.txt", *this);
    if(result != SaveLoad::LoadResult::OK)
        throw std::logic_error("FileManager::read");
}
