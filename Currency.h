#ifndef CURRENCY_H
#define CURRENCY_H

#include "Utils.h"
#include <iostream>


/*
 * Class Currency used to monitor bitcoin/euro exchange
 */
class Currency
{
  
public:
  
  Currency(QUrl const url){
    this->c_url = url;
  };
  
  /**
   * @brief Compute and return currency value
   */
  inline double getValue(QString const keyword){
    computeValue(keyword);
    return c_value;
  };
  
  /**
   * @brief Compute currency value
   * @param str: Keyword used to retrieve the currency value (could be "high", "last", ...)
   */
  inline void computeValue(QString const keyword){
    
    QString content = Utils::getURLContent(c_url);
    
    double val = 0.;
    QStringList list = content.split(',');
    
    try {
      for(auto l : list){
        if(l.contains(keyword)){
          val = Utils::extractDouble(l);
          break;
        }
      }
    }
    catch (const std::exception& e) {
      std::cout << "Problems in reading currency exchange " << e.what() << "'\n";
    }
    
    this->c_value = val;
  }
  
  /**
   * @brief Update the url
   */
  inline void update(QUrl qurl){
    this->c_url = qurl;
  }
  
  /**
   * @brief Get a Qstring with the current currency exchange
   *        and the time
   */
  inline QString getString(QString const keyword){
    
    double curr = getValue(keyword);
    std::string str = std::to_string(curr);
    QString qstr = QString::fromStdString("Currency exchange " + str + " at ");
    qstr += Utils::getCurrentTime();
    
    return qstr;
  }
  
  
private:
  
  double c_value; // currency value
  
  QUrl c_url; // url to download currency value
};


#endif

