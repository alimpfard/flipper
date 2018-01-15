/*
FFSSE is a replacement search engine for fanfiction.net search results
Copyright (C) 2017  Marchenko Nikolai

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "Interfaces/tags.h"
#include "Interfaces/db_interface.h"
#include "Interfaces/interface_sqlite.h"
#include "pure_sql.h"
#include <QFile>
#include <QDebug>

namespace interfaces {

void Tags::LoadAlltags()
{
    allTags = ReadUserTags();
}

bool Tags::DeleteTag(QString tag)
{
    return database::puresql::DeleteTagFromDatabase(tag, db);
}

bool Tags::CreateTag(QString tag)
{
    return database::puresql::CreateTagInDatabase(tag, db);
}

QStringList Tags::ReadUserTags()
{
    QStringList tags = database::puresql::ReadUserTags(db);
    if(tags.empty())
    {
        tags = CreateDefaultTagList();
        database::puresql::PushTaglistIntoDatabase(tags,db);
    }
    return tags;
}

bool Tags::SetTagForFic(int ficId, QString tag)
{
    tag = tag.trimmed();
    if(!allTags.contains(tag))
        CreateTag(tag);
    allTags.push_back(tag);
    database::puresql::AssignTagToFanfic(tag, ficId, db);
    return true;
}

bool Tags::RemoveTagFromFic(int ficId, QString tag)
{
    return database::puresql::RemoveTagFromFanfic(tag, ficId, db);
}

QStringList Tags::CreateDefaultTagList()
{
    QStringList temp;
    temp << "smut" << "hidden" << "meh_description" << "unknown_fandom" << "read_queue" << "reading" << "finished" << "disgusting" << "crap_fandom";
    return temp;
}

bool Tags::ExportToFile(QString filename)
{
    QString exportFile = filename;
    QFile::remove(exportFile);
    QSharedPointer<database::IDBWrapper> tagExportInterface (new database::SqliteInterface());
    auto tagExportDb = tagExportInterface->InitDatabase("TagExport", false);
    tagExportInterface->ReadDbFile("dbcode/tagexportinit.sql", "TagExport");
    database::puresql::ExportTagsToDatabase(db, tagExportDb);
    return true;
}

bool Tags::ImportFromFile(QString filename)
{
    QString importFile = filename;
    if(!QFile::exists(importFile))
    {
        qDebug() << "Could not find importfile";
        return false;
    }
    QSharedPointer<database::IDBWrapper> tagImportInterface (new database::SqliteInterface());
    auto tagImportDb = tagImportInterface->InitDatabase("TagExport", false);
    tagImportInterface->ReadDbFile("dbcode/tagexportinit.sql", "TagImport");
    database::puresql::ImportTagsFromDatabase(db, tagImportInterface->GetDatabase());
    return true;
}

}