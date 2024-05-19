#include "db_program_2.h"
#include "function/program.h"
#include "../dbinteraction.h"
db_program_2::db_program_2(QObject *parent)
    : QObject(parent)
{
    Dispatcher::getDispatcher()->Register("mobileallHadPrograms",std::bind(&db_program_2::allHadPrograms, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobilepmOnplay",std::bind(&db_program_2::pmOnplay, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobilesearchSinger",std::bind(&db_program_2::searchSinger, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobilesingerSound",std::bind(&db_program_2::singerSound, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobileonClickPm",std::bind(&db_program_2::onClickPm, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobilegetClickPm",std::bind(&db_program_2::getClickPm, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobilePlayProgram",std::bind(&db_program_2::mobilePlayProgram, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobileStopProgram",std::bind(&db_program_2::mobileStopProgram, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobilePauseProgram",std::bind(&db_program_2::mobilePauseProgram, this,std::placeholders::_1));
    Dispatcher::getDispatcher()->Register("mobileRestoreProgram",std::bind(&db_program_2::mobileRestoreProgram, this,std::placeholders::_1));
}

QJsonObject db_program_2::allHadPrograms(QJsonObject &obj)
{
    QSqlQuery query;
    QJsonArray pmlist;
    query.exec("SELECT * FROM program");
    while(query.next()){
        QJsonObject pm;
        pm.insert("pmId",query.value(0).toInt());
        pm.insert("playDuration",query.value(4).toString());
        pm.insert("pmName",query.value(1).toString());
        pm.insert("startDate",query.value(5).toString());
        pm.insert("endDate",query.value(6).toString());
        pm.insert("startTime",query.value(9).toString());
        pm.insert("pmTyp",query.value(2).toString());
        pm.insert("pmStatue",QVariant(query.value(7)).toBool());
        pm.insert("weekCnt",query.value(8).toInt());
        pmlist.append(pm);
    }
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", pmlist}
    };
}

QJsonObject db_program_2::pmOnplay(QJsonObject &obj)
{
    QString pmStatue = (obj.value("pmStatue").toBool() ? "1" : "0");
    QSqlQuery query;
    QJsonArray pmlist;
    query.exec("SELECT * FROM program WHERE pm_statue = " + pmStatue);
    while(query.next()){
        QJsonObject pm;
        pm.insert("pmId",query.value(0).toInt());
        pm.insert("playType",query.value(3).toString());
        pm.insert("playDuration",query.value(4).toString());
        pm.insert("pmName",query.value(1).toString());
        pm.insert("startDate",query.value(5).toString());
        pm.insert("endDate",query.value(6).toString());
        pm.insert("startTime",query.value(9).toString());
//        pm.insert("pmTyp",query.value(2).toString());
        pm.insert("pmStatue",QVariant(query.value(7)).toBool());
        pm.insert("weekCnt",query.value(8).toInt());
        pmlist.append(pm);

    }
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", pmlist}
    };
}

QJsonObject db_program_2::searchSinger(QJsonObject &obj)
{
    QSqlQuery query;
    QJsonArray singerlist;
    query.exec("SELECT * FROM singer");
    while(query.next()){
        QJsonObject singer;
        singer.insert("singerId",query.value(0).toInt());
        singer.insert("singer_Name",query.value(1).toString());
        singer.insert("singer_Picture",query.value(2).toString());
        singerlist.append(singer);
    }
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", singerlist}
    };
}

QJsonObject db_program_2::singerSound(QJsonObject &obj)
{
    QString singerName = obj.value("singerName").toString();
    QSqlQuery query;
    QJsonArray soundlist;
    query.exec("SELECT file_no,file_name,sound_picture FROM FILE WHERE singer_no = (SELECT singer_no FROM singer WHERE singer_name = '"+singerName+"')");
    while(query.next()){
        QJsonObject sound;
        sound.insert("soundId",query.value(0).toInt());
        sound.insert("soundName",query.value(1).toString());
        sound.insert("sound_Picture",query.value(2).toString());
        soundlist.append(sound);
    }
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", soundlist}
    };
}

QJsonObject db_program_2::onClickPm(QJsonObject &obj)
{
    QJsonArray singId = obj.value("sing_Ids").toArray();
    QJsonArray devsId = obj.value("devsId").toArray();
    QString singids = "";
    for (int i = 0; i < singId.size(); ++i) {
        int value = singId.at(i).toInt();
        if (i == 0){
            singids += value;
        }else{
            singids += ","+value;
        }
    }
    for (int i = 0; i < devsId.size(); ++i) {
        AddProgramDev(23424, devsId.at(i).toInt());
    }
    QSqlQuery query;
    QJsonArray soundlist;
    query.exec("SELECT file_no,file_Duration,sound_picture,file_name,file_type FROM FILE WHERE file_no IN ("+singids+")");
    while(query.next()){
        QJsonObject sound;
        sound.insert("sing_Id",query.value(0).toInt());
        sound.insert("sing_Duration",query.value(1).toString());
        sound.insert("sing_Picture",query.value(2).toString());
        sound.insert("sing_Name",query.value(3).toString());
        sound.insert("playType",query.value(4).toString());
        soundlist.append(sound);
//        AddFileToProgram(23424, query.value(0).toInt(), 1);
    }
    // uid ,sid devsId,//生成一个节目，在节目力添加歌曲，添加设备
//    QString name = "NAME";
//    QString playtype = ".mp3";
//    QTime time =QTime::fromString("01:00:00", "hh:mm:ss");
//    AddProgram(23424, name, 0, playtype, time);
//    obj.insert("pmNo",23424);
//    AddProgramDev(23424, devNo);
//    QJsonObject obj1 ;
//    obj1.insert("pmNo",3);

//    Dispatcher::getDispatcher()->Dispatch("playProgram",obj1);
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", soundlist}
    };
}

QJsonObject db_program_2::getClickPm(QJsonObject &obj)
{
    QString userId = QString::number(obj.value("userId").toInt());;
    QSqlQuery query;
    QJsonArray sing;
    QJsonObject dataobj;
    query.exec("SELECT program.pm_no,program.pm_name,program.mobile_user_id,file.file_name,singer.singer_name FROM program "
               "LEFT JOIN `pm_file` ON `pm_file`.pm_no = program.pm_no "
               "LEFT JOIN `file` ON `file`.file_no = `pm_file`.file_no "
               "LEFT JOIN singer ON singer.singer_no = `file`.singer_no "
               "WHERE program.mobile_user_id = "+userId);

    while(query.next()){

        QJsonObject sound;
        sound.insert("singName",query.value(3).toString());
        sound.insert("singerName",query.value(4).toString());
        dataobj.insert("pmNo",query.value(0).toInt());
        sing.append(sound);
    }
    dataobj.insert("sing",sing);
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", dataobj}
    };
}

QJsonObject db_program_2::mobilePlayProgram(QJsonObject &obj)
{
    QJsonArray singId = obj.value("sing_Ids").toArray();
    QString devsId = QString::number(obj.value("devsId").toInt());
    QString singids = "";
    for (int i = 0; i < singId.size(); ++i) {
        int value = singId.at(i).toInt();
        if (i == 0){
            singids += value;
        }else{
            singids += ","+value;
        }
    }
    QSqlQuery query;
    QSqlQuery query2;
    QSqlQuery query3;
    QSqlQuery query4;
    QJsonArray pmNolist;
//    query.exec("INSERT INTO program (pm_name) VALUES ('mobile_1')");
//    query2.exec("INSERT INTO pm_file (pm_no,file_no) VALUES ((SELECT pm_no FROM `program` WHERE pm_name = 'mobile_1'),94)");
//    query3.exec("INSERT INTO pm_dev (dev_no,pm_no) VALUES (5114,(SELECT pm_no FROM `program` WHERE pm_name = 'mobile_1'))");
    query4.exec("SELECT pm_no FROM `program` WHERE pm_name = 'mobile_1'");
    QJsonObject pmNo;
    while(query4.next()){
        pmNo.insert("pmNo",query4.value(0).toInt());
        pmNo.insert("status",true);
        pmNolist.append(pmNo);
    }
//    QJsonObject obj1 ;
//    obj1.insert("pmNo",3);

    Dispatcher::getDispatcher()->Dispatch("playProgram",pmNo);
    QSqlQuery query5;
    query5.exec("UPDATE program SET pm_statue = '1' WHERE pm_name IN ('mobile_1')");

    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", pmNolist}
    };
}

QJsonObject db_program_2::mobileStopProgram(QJsonObject &obj)
{
    QString pmNo = QString::number(obj.value("pmNo").toInt());
    QJsonObject obj1 ;
    obj1.insert("pmNo",obj.value("pmNo").toInt());
    QSqlQuery query;
    Dispatcher::getDispatcher()->Dispatch("stopPlayProgram",obj1);
    query.exec("UPDATE program SET pm_statue = '0' WHERE pm_no IN ("+pmNo+")");

    QJsonObject pmNoss;
    pmNoss.insert("pmNo",obj.value("pmNo").toInt());
    QJsonArray pmNolist;
    pmNolist.append(pmNoss);
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", pmNolist}
    };
}

QJsonObject db_program_2::mobilePauseProgram(QJsonObject &obj)
{
    QString pmNo = QString::number(obj.value("pmNo").toInt());
    QJsonObject obj1 ;
    obj1.insert("pmNo",obj.value("pmNo").toInt());
    QSqlQuery query;
    Dispatcher::getDispatcher()->Dispatch("pausePlayProgram",obj1);
//    query.exec("UPDATE program SET pm_statue = '0' WHERE pm_no IN ("+pmNo+")");

    QJsonObject pmNoss;
    pmNoss.insert("pmNo",obj.value("pmNo").toInt());
    QJsonArray pmNolist;
    pmNolist.append(pmNoss);
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", pmNolist}
    };
}

QJsonObject db_program_2::mobileRestoreProgram(QJsonObject &obj)
{
    QString pmNo = QString::number(obj.value("pmNo").toInt());
    QJsonObject obj1 ;
    obj1.insert("pmNo",obj.value("pmNo").toInt());
    QSqlQuery query;
    Dispatcher::getDispatcher()->Dispatch("restorePlayProgram",obj1);
//    query.exec("UPDATE program SET pm_statue = '0' WHERE pm_no IN ("+pmNo+")");

    QJsonObject pmNoss;
    pmNoss.insert("pmNo",obj.value("pmNo").toInt());
    QJsonArray pmNolist;
    pmNolist.append(pmNoss);
    return QJsonObject{
     {"code", 200},
     {"message", "成功"},
     {"data", pmNolist}
    };
}
