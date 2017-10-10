#include "Currency.h"

#include <iostream>

/**/

Currency::Currency(QUrl const url){
  this->c_url = url;
}

/**/

double Currency::getValue(QString const keyword){
  computeValue(keyword);
  return c_value;
}

/**/

void Currency::computeValue(QString const keyword){
  
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

/**/

void Currency::update(QUrl qurl){
  this->c_url = qurl;
}

/**/

QString Currency::getString(QString const keyword){
  
  double curr = getValue(keyword);
  std::string str = std::to_string(curr);
  QString qstr = QString::fromStdString("Currency exchange " + str + " at ");
  qstr += Utils::getCurrentTime();
  
  return qstr;
}




