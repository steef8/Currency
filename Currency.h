#ifndef CURRENCY_H
#define CURRENCY_H

#include "Utils.h"
#include <iostream>


/**
 *
 */
class Currency
{
  
public:
  /**/
  Currency(QUrl const url){
    this->c_url = url;
  };
  
  /**/
  inline double getValue(QString const str){
    computeValue(str);
    return c_value;
  };
  
  /**/
  inline void computeValue(QString const str){
    
    QString content = Utils::getURLContent(c_url);
    
    double val = 0.;
    QStringList list = content.split(',');
    
    try {
      for(auto l : list){
        if(l.contains(str)){
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
  
  /**/
  inline void update(QUrl qurl){
    this->c_url = qurl;
  }
  
  /**/
  inline QString getString(QString const keyword){
    
    double curr = getValue(keyword);
    std::string str = std::to_string(curr);
    QString qstr = QString::fromStdString("Currency exchange " + str + " at ");
    qstr += Utils::getCurrentTime();
    
    return qstr;
  }
  
  
private:
  /**/
  double c_value;
  /**/
  QUrl c_url;
};


#endif

