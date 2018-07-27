/*
Flipper is a replacement search engine for fanfiction.net search results
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
#pragma once
#include "Interfaces/base.h"
#include "core/section.h"
#include "core/fic_genre_data.h"
#include <QScopedPointer>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QReadWriteLock>
#include <QSet>


namespace interfaces {

QHash<QString, QString> CreateCodeToDBGenreConverter();
QHash<QString, QString> CreateDBToCodeGenreConverter();

struct GenreConverter{
    QHash<QString, QString> codeToDB = CreateCodeToDBGenreConverter();
    QHash<QString, QString> dBToCode = CreateDBToCodeGenreConverter();
    QStringList GetDBGenres() { return dBToCode.keys();}
    QStringList GetCodeGenres() { return codeToDB.keys();}
    QString ToDB(QString value){
        QString result;
        if(codeToDB.contains(value))
            result = codeToDB[value];
        return result;
    }
    QString ToCode(QString value){
        QString result;
        if(dBToCode.contains(value))
            result = dBToCode[value];
        return result;
    }
    QStringList GetFFNGenreList(QString genreString){

        QStringList genresList;
        bool hasHurt = false;
        QString fixedGenreString = genreString;
        if(genreString.contains("Hurt/Comfort"))
        {
            hasHurt = true;
            fixedGenreString = fixedGenreString.replace("Hurt/Comfort", "");
        }

        genresList = fixedGenreString.split("/", QString::SkipEmptyParts);
        if(hasHurt)
            genresList.push_back("Hurt/Comfort");
        for(auto& genre: genresList)
            genre = genre.trimmed();
        return genresList;
    }

    void ProcessGenreResult(genre_stats::FicGenreData&);
    void DetectRealGenres(genre_stats::FicGenreData&);

    static GenreConverter Instance();
};

class Genres{
public:
    
    bool IsGenreList(QStringList list);
    bool LoadGenres();
    genre_stats::FicGenreData GetGenreDataForFic(int id);
    QVector<genre_stats::FicGenreData> GetGenreDataForQueuedFics();
    void QueueFicsForGenreDetection(int minAuthorRecs, int minFoundLists);

    QSqlDatabase db;

private:

    QSet<QString> genres;
};




}
