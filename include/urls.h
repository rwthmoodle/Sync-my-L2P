#ifndef URLS
#define URLS

#include <QString>

const QString releaseUrl = "https://github.com/rwthmoodle/Sync-my-Moodle/releases";
const QString appUpdateUrl = "https://app.rwth-aachen.de/syncmymoodle/version.txt";
const QString moodleApiDomain = "https://moped.ecampus.rwth-aachen.de/";
const QString moodleApiUrlBase = moodleApiDomain + "proxy/api/v2/";
const QString moodleApiDocs = moodleApiUrlBase + "Documentation";
const QString moodleApiUrl = moodleApiUrlBase + "eLearning/Moodle/";
const QString moodleGetMyEnrolledCoursesUrl = moodleApiUrl + "getmyenrolledcourses";
const QString moodleGetFilesUrl = moodleApiUrl + "getfiles";
const QString moodleDownloadFileUrl = moodleApiUrl + "downloadfile";

#endif // URLS

