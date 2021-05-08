/****************************************************************************
** This file is part of Sync-my-L2P.
**
** Sync-my-L2P is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Sync-my-L2P is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Sync-my-L2P.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/


#include <QStringBuilder>
#include <QClipboard>
#include <QApplication>
#include <QRegularExpression>

#include "structureelement.h"

Structureelement::Structureelement(QString name, QUrl url, int time, qint32 size, QString cid, MyItemType typeEX, MyItemSystem systemEX)
    :QStandardItem(name),
     size(size),
     included(true),
     url(url),
     cid(cid),
     time(QDateTime::fromMSecsSinceEpoch(qint64(1000) * time)),
     typeEX(typeEX),
     systemEX(systemEX)
{
    synchronised = NOT_SYNCHRONISED;
    chooseIcon();
}

// Überladener Konstruktor für Nachrichtenelemente, welche nicht heruntergeladen werden können.
Structureelement::Structureelement(QString body, QString topic, QString author, int time, QString cid, MyItemType typeEX, MyItemSystem systemEX)
    :QStandardItem(topic),
     included(true),
     cid(cid),
     time(QDateTime::fromMSecsSinceEpoch(qint64(1000) * time)),
     body(body),
     topic(topic),
     author(author),
     typeEX(typeEX),
     systemEX(systemEX)
{
    synchronised = NOT_SYNCHRONISED;
    chooseIcon();
}

QVariant Structureelement::data(int role) const
{
    switch(role)
    {
    case includeRole:
        return included;
    case urlRole:
        return url;
    case sizeRole:
        return size;
    case dateRole:
        return time;
    case bodyRole:
        return body;
    case topicRole:
        return topic;
    case authorRole:
        return author;
    case synchronisedRole:
        return synchronised;
    case cidRole:
        return cid;
    case typeEXRole:
        return typeEX;
    case systemEXRole:
        return systemEX;
    case Qt::StatusTipRole:
    {
        QString statustip;
        if (typeEX == fileItem)
        {
            statustip.append(text() % " - ");
            if (size > 1048576)
                statustip.append(QString::number(size/1048576.0,'f',2) % " MB");
            else
                 statustip.append(QString::number(size/1024.0,'f',2) % " KB");

            statustip.append(" - " % time.toString("ddd dd.MM.yyyy hh:mm"));

            statustip.append(" - ");
            switch(synchronised)
            {
            case NOW_SYNCHRONISED:
            case SYNCHRONISED:
                    statustip.append("synchronisiert");
                    break;
            case NOT_SYNCHRONISED:
            default:
                statustip.append("nicht synchronisiert");
            }
        }
        else if (typeEX == messageItem)
        {
            statustip.append(text() % " - ");
            statustip.append(author);
            statustip.append(" - " % time.toString("ddd dd.MM.yyyy hh:mm"));
        }
        return statustip;
    }
    case Qt::ForegroundRole:
        if (included)
        {
            if (synchronised == NOW_SYNCHRONISED)
                return QBrush(Qt::green);
            else if (synchronised == SYNCHRONISED)
                return QBrush(Qt::darkGreen);
            else
                // Use system default color
                return QStandardItem::data(role);
        }
        else
        {
            return QBrush(Qt::red);
        }
    case Qt::FontRole:
    {
        QFont Font;
        // Semester und Veranstaltungen fett darstellen
        Font.setBold(typeEX == courseItem || typeEX == semesterItem);
        return Font;
    }
    default:
        return QStandardItem::data(role);
    }
}

/// Icon anhand des Types und der Dateiendung auswählen
void Structureelement::chooseIcon()
{
    if(typeEX == fileItem)
    {
        QString filename = text();
        // Hinzufügen des endungsabhängigen Icons
        // PDF
        if (filename.contains(QRegularExpression(".pdf$", QRegularExpression::CaseInsensitiveOption)))
        {
           setIcon(QIcon(":/icons/pdf.png"));
        }
        // Videos
        else if (filename.contains(QRegularExpression(".mp4$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".wmv$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".webm$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".flv$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".ogv$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".mp4$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".avi$", QRegularExpression::CaseInsensitiveOption)))
        {
            setIcon(QIcon(":/icons/video.png"));
        }
        // Musik
        else if (filename.contains(QRegularExpression(".mp3$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".aac$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".ogg$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".flac$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".wav$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".wma$", QRegularExpression::CaseInsensitiveOption)))
        {
            setIcon(QIcon(":/icons/audio.png"));
        }
        // Textdokument
                else if (filename.contains(QRegularExpression(".doc$", QRegularExpression::CaseInsensitiveOption)) ||
                         filename.contains(QRegularExpression(".docx$", QRegularExpression::CaseInsensitiveOption)) ||
                         filename.contains(QRegularExpression(".odt$", QRegularExpression::CaseInsensitiveOption)))
                {
                    setIcon(QIcon(":/icons/document.png"));
                }
        // Kalkulationsdokument
                else if (filename.contains(QRegularExpression(".xls$", QRegularExpression::CaseInsensitiveOption)) ||
                         filename.contains(QRegularExpression(".xlsx$", QRegularExpression::CaseInsensitiveOption)) ||
                         filename.contains(QRegularExpression(".ods$", QRegularExpression::CaseInsensitiveOption)))
                {
                    setIcon(QIcon(":/icons/sheet.png"));
                }
        // Präsentationsdokument
                else if (filename.contains(QRegularExpression(".ppt$", QRegularExpression::CaseInsensitiveOption)) ||
                         filename.contains(QRegularExpression(".pptx$", QRegularExpression::CaseInsensitiveOption)) ||
                         filename.contains(QRegularExpression(".odp$", QRegularExpression::CaseInsensitiveOption)))
                {
                    setIcon(QIcon(":/icons/slideshow.png"));
                }
        // BMP
        else if (filename.contains(QRegularExpression(".bmp$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".jpg$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".png$", QRegularExpression::CaseInsensitiveOption)) ||
                 filename.contains(QRegularExpression(".gif$", QRegularExpression::CaseInsensitiveOption)))
        {

            setIcon(QIcon(":/icons/picture.png"));
        }
        // Archivefiles
        else if (filename.contains(QRegularExpression(".rar$", QRegularExpression::CaseInsensitiveOption))||
                filename.contains(QRegularExpression(".zip$", QRegularExpression::CaseInsensitiveOption))||
                filename.contains(QRegularExpression(".jar$", QRegularExpression::CaseInsensitiveOption)))
        {
            setIcon(QIcon(":/icons/archive.png"));
        }
        else
        {
            setIcon(QIcon(":/icons/otherFile.png"));
        }
    }
    else if(typeEX == courseItem)
    {
        setIcon(QIcon(":/icons/course.png"));
    }
    else if(typeEX == directoryItem)
    {
        setIcon(QIcon(":/icons/directory.png"));
    }
    else if(typeEX == semesterItem)
    {
        setIcon(QIcon(":/icons/semester.png"));
    }
    else if(typeEX == messageItem)
    {
        setIcon(QIcon(":/icons/mail.png"));
    }
}

/// Vergleich zwischen zwei Items für Sortierung.
/// Ordner haben Vorrang vor Dateien und sonst wird alphabetisch sortiert.
bool Structureelement::operator< (const QStandardItem& other) const
{

    if ((typeEX != fileItem) && (other.type() == fileItem))
    {
        return true;
    }
    else if ((typeEX == fileItem) && (other.type() != fileItem))
    {
        return false;
    }
    else if (typeEX == messageItem)
    {
        return (data(dateRole) < other.data(dateRole));
    }
    else
    {
        return (text().toLower() < other.text().toLower());
    }
}

/// Überladene Funktion für das Setzen der Daten
void Structureelement::setData(const QVariant &value, int role)
{
    switch(role)
    {
    case includeRole:
        this->included = value.toBool();
        break;
    case urlRole:
        this->url = value.toUrl();
        break;
    case sizeRole:
        this->size = value.toInt();
        break;
    case dateRole:
        this->time = value.toDateTime();
        break;
    case synchronisedRole:
        this->synchronised = static_cast<synchroniseStatus>(value.toInt());
        break;
    case cidRole:
        this->cid = value.toString();
        break;
    default:
        QStandardItem::setData(value, role);
    }
}
