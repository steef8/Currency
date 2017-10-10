#include <QtWidgets>

#include "Currency.h"



int main(int argc, char* argv[]){

  QApplication a(argc, argv);
  
  // Set up GUI
  QWidget widget;
  QVBoxLayout layout(&widget);
  QTextBrowser textBrowser;
  QPushButton button("Monitor");
  widget.setWindowTitle("Bitcoin/euro exchange");
  widget.resize(400, 400);
  layout.addWidget(&textBrowser);
  layout.addWidget(&button);
  
  // Set up Currency exchange
  QString url = "https://www.bitstamp.net/api/v2/ticker/btceur/";
  QUrl qurl = QUrl(url);
  Currency currency = Currency(qurl);
  currency.update(qurl);
  QString qstr = currency.getString("last");
  textBrowser.append(qstr);
  
  //
  QTimer workTimer;
  workTimer.setInterval(10000);
  
  QObject::connect(&workTimer, &QTimer::timeout, [&]{
    
    currency.update(qurl);
    QString qstr = currency.getString("last");
    textBrowser.append(qstr);
  
  });
  
  //when the button is clicked
  QObject::connect(&button, &QPushButton::clicked, [&]{
    //start work timer
    workTimer.start();
    button.setEnabled(false);
    //stop work timer after 1000 seconds
    QTimer::singleShot(1000000, [&]{
      workTimer.stop();
      button.setEnabled(true);
    });
  });
  
  widget.show();
  
  return a.exec();
}
