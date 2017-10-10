#ifndef CURRENCY_H
#define CURRENCY_H

#include "Utils.h"


/*
 * Class Currency used to monitor bitcoin/euro exchange
 */
class Currency
{
  
public:
  
  Currency(QUrl const url);
  
  /**
   * @brief Compute and return currency value
   */
  double getValue(QString const keyword);
  
  /**
   * @brief Compute currency value
   * @param str: Keyword used to retrieve the currency value (could be "high", "last", ...)
   */
  void computeValue(QString const keyword);
  
  /**
   * @brief Update the url
   */
  void update(QUrl qurl);
  
  /**
   * @brief Get a Qstring with the current currency exchange
   *        and the time
   */
  QString getString(QString const keyword);
  
private:
  
  double c_value; // currency value
  
  QUrl c_url; // url to download currency value
};


#endif

