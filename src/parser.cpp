#include "parser.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "utils.h"
#include "qslog/QsLog.h"


QString Parser::escapeString(QString untrimmedStr)
{
    // Remove problematic characters for file systems that are allowed in RWTHmoodle
    QString escapePattern = "(:|<|>|/|\\\\|\\||\\*|\\^|\\?|\\\"|\\#)";
    QRegExp escapeRegExp(escapePattern, Qt::CaseSensitive);
    QString trimmedStr = untrimmedStr.replace(escapeRegExp, "").trimmed();
    // Limit length as sometimes super long titles are used
    trimmedStr.truncate(100);
    return trimmedStr;
}

void Parser::parseMoodleCourses(QNetworkReply *reply, QStandardItemModel *itemModel)
{
    // Empfangene Nachricht auslesen und als JSON interpretieren
    QByteArray response(reply->readAll());
    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonObject object = document.object();

    if(object.isEmpty())
    {
        QLOG_WARN() << tr("Moodle-Kursinformationen leer bzw. nicht lesbar.");
        return;
    }

    if(object["StatusCode"].toInt() != 0)
    {
        QLOG_ERROR() << tr("Status der Moodle-Kursinformationen nicht ok: ") <<
                        QString(document.toJson());
        return;
    }

    // Array mit allen einzelnen Vorlesungen/Veranstaltungen
    QJsonArray courses = object["Data"].toArray();

    // Für jede Veranstaltung ein neues Strukturelement anlegen
    foreach(QJsonValue element, courses)
    {
        QJsonObject course = element.toObject();

        QString title = course["courseTitle"].toString();
        QString cid = QString::number(course["id"].toInt());
        QJsonObject category = course["category"].toObject();
        QString semester = category["idnumber"].toString();
        QString url = course["url"].toString();

        // Erstellen eines RegExps  für unzulässige Buchstaben im Veranstaltungsnamen
        title = escapeString(title);

        Structureelement *newCourse = new Structureelement(title, QUrl(url), 0, 0, cid, courseItem, moodle);

        Utils::getSemesterItem(itemModel, semester)->appendRow(newCourse);

        QLOG_DEBUG() << tr("Moodle-Veranstaltung") << title << "(" << cid << tr(") hinzugefügt.");
    }
}

void Parser::parseMoodleFiles(QNetworkReply *reply, Structureelement* course)
{
    Structureelement *currentCourse = course;

    QByteArray response = reply->readAll();

    QJsonDocument document = QJsonDocument::fromJson(response);
    QJsonObject object = document.object();

    if(object.isEmpty())
    {
        QLOG_DEBUG() << tr("Moodle-Kursinformationen leer bzw. nicht lesbar.");
        return;
    }

    if(object["StatusCode"].toInt() != 0)
    {
        QLOG_ERROR() << tr("Status der Moodle-Kursinformationen nicht ok: \n") <<
                        "\n" <<
                        QString(document.toJson());
        return;
    }

    if(object["IsError"].toBool())
    {
        QLOG_ERROR() << tr("Moodle-Kursinformationen enthalten einen Fehler: \n") <<
                        "\n" <<
                        QString(document.toJson());
        return;
    }

    QJsonArray files = object["Data"].toArray();
    foreach(QJsonValue element, files)
    {
        QJsonObject file = element.toObject();
        QString topicname;
        QString modulename;
        QString filename;
        QString sourceDirectory;
        int filesize;
        int timestamp;
        QString url;
        QStringList dirParts;

        QJsonObject fileInformation = file["fileinformation"].toObject();

        topicname = escapeString(file["topicname"].toString());
        modulename = escapeString(file["modulename"].toString());
        filename = escapeString(file["filename"].toString());
        sourceDirectory = file["sourceDirectory"].toString();
        filesize = fileInformation["filesize"].toInt();
        timestamp = file["lastModified"].toInt();
        url = file["downloadUrl"].toString();

        // the list with the directories
        QStringList dirs{};
        dirs.append(topicname);
        dirs.append(modulename);
        // modules can contain folders. this gets the folder names, as qstringlist
        dirParts = sourceDirectory.split('/');
        if (dirParts.size() > 1) {
            dirParts.removeFirst();
            dirParts.removeLast();
            dirs += dirParts;
        }

        Structureelement *dir = Utils::getDirectoryItem(currentCourse, dirs);

        Structureelement* newFile = new Structureelement(filename, QUrl(url), timestamp, filesize,
                                                     currentCourse->data(cidRole).toString(),
                                                     fileItem, moodle);

        // Element hinzufügen
        dir->appendRow(newFile);
    }
}
