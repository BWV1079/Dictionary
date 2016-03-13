#ifndef SAVELOAD_H
#define SAVELOAD_H

#ifndef INCLUSION_FOR_ABSTRACTION
#include "../../inclusion_for_abstraction.h"
#endif

class SaveLoad
{
public:
    SaveLoad(){}
    ~SaveLoad(){}

public:
    enum class LoadResult {OK, NotFound, Open, MagicInvalid, VersionInvalid, EndingInvalid, Read};
    enum class SaveResult {OK, Open, Write};

    template <typename T>
    SaveResult save (const QString& adress, T& t);
    template <typename T>
    LoadResult load (const QString& adress, T& t);

private:
    const QString sequence_magic = "thesaurus!""№;;%::?**())";
    const QString sequence_ending = "end@$^*)";
    const QString extension_temp = ".temp";

private:
    template <typename T>
    SaveResult write (QFile& file, T& t);
    template <typename T>
    LoadResult read (QFile& file, T& t);
};


template <typename T>
SaveLoad::SaveResult SaveLoad::save(const QString& adress, T& t)
{
    //Если файла с требуем именем нет, просто создаем его и записываем в него информацию
    QFile file(adress);
    if (!file.exists()) return write(file, t);

    //Если файл с требуемым именем существует,
    //создаем временный файл, и информацию записываем в него
    QFile file_temp(adress + extension_temp);
    SaveResult result = write(file_temp, t);
    if(result != SaveResult::OK) return result;

    //Удаляем старый файл с требуемым именем и переименовываем временный
    file.remove();
    file_temp.rename(file.fileName());
    //Проверка удаления и переименования файлов не осуществляется,
    //так как не ведет к сбою программы и учитывается в алгоритме

    return SaveResult::OK;
}
//--------------------------------------------------------------------
template <typename T>
SaveLoad::SaveResult SaveLoad::write(QFile& file, T& t)
{
    if(!file.open(QIODevice::WriteOnly)) return SaveResult::Open;
    SaveResult result = SaveResult::OK;
    try{
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_4);
        out << quint16(QDataStream::Qt_5_4);
        out << sequence_magic;
        out << t;
        out << sequence_ending;
    }
    catch(...){
        result = SaveResult::Write;
    }
    file.close();
    return result;
}
//**********************************************************************************************************
template <typename T>
SaveLoad::LoadResult SaveLoad::load(const QString& adress, T& t)
{
    QFile file(adress);
    QFile file_temp(adress + extension_temp);

    //Если файла с требуемым именем нет, проверяем наличие временного файла
    //если и временного файла нет, выводим NotFound
    //если есть, переименовываем его и читаем
    if(!file.exists()){
        if(!file_temp.exists()) return LoadResult::NotFound;
        file_temp.rename(file.fileName());
        return read(file_temp, t);
    }

    //если файл с требуемым именем есть, а временного файла нет, то просто читаем файл
    if(!file_temp.exists()) return read(file, t);

    //если временный файл есть, читаем из него информацию вместо требуемого файла
    int result = (int) read(file_temp, t);

    //если чтение из временного файла закончилось ошибкой, удаляем его и читаем
    //информацию из треуемого файла
    if(result){
        file_temp.remove();
        return read(file,t);
    }

    //в противном случае (чтение временного файла закончилось успехом),
    // удаляем требуемый файл и переименовываем временный
    file.remove();
    file_temp.rename(file.fileName());
    //Проверка удаления и переименования файлов не осуществляется,
    //так как не ведет к сбою программы и учитывается в алгоритме

    return LoadResult::OK;
}
//--------------------------------------------------------------------
template <typename T>
SaveLoad::LoadResult SaveLoad::read(QFile& file, T& t)
{
    if(!file.open(QIODevice::ReadOnly)) return LoadResult::Open;
    LoadResult result = LoadResult::OK;
    try
    {
        quint16 _version;
        QString _sequence_magic;
        QString _sequence_ending;

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_4);

        in >> _version;
        if(_version != quint16(QDataStream::Qt_5_4)) result = LoadResult::VersionInvalid;
        in >> _sequence_magic;
        if(_sequence_magic != sequence_magic) result = LoadResult::MagicInvalid;
        in >> t;
        in >> _sequence_ending;
        if(_sequence_ending != sequence_ending) result = LoadResult::EndingInvalid;
    }
    catch(...){
        result = LoadResult::Read;
    }
    file.close();
    return result;
}
//**********************************************************************************************************

#endif // SAVELOAD_H

