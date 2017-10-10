#ifndef UTILS_H
#define UTILS_H

#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QTime>

namespace Utils {
  
  /**
   * @brief Extract double value from a Qstring
   */
  inline double extractDouble(const QString &qstr)
  {
    QString num;
    foreach(QChar c, qstr) {
      if (c.isDigit() || c == '.' || c == '-') {
        num.append(c);
      }
    }
    bool ok;
    double ret = num.toDouble(&ok);
    if (ok) {
      return ret;
    } else {
      throw "Cannot extract double value";
    }
  }
  
  
  /**
   * @brief Get content from url
   */
  inline QString getURLContent(QUrl url){
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(url));
    QEventLoop event;
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    return response->readAll();
  }
  
  /**
   * @brief Get current time in hh:mm:ss format
   */
  inline QString getCurrentTime(){
    QTime time = QTime::currentTime();
    return time.toString("hh:mm:ss");
  }
  
  
} // End namespace

#endif

