#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include <unistd.h>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "api_ums.hpp"

using namespace std;
using namespace UMS_Data;
using namespace vishnu;

void stress(){
  int i;
  string             	  key  = ""       ;
  string 	     	  pwd  = "admin"  ;
  string 	     	  uid  = "admin_1";
  ConnectOptions 	  cop  ;//= ecoreFactory->createConnectOptions();
  Session                 sess ;
  int res;

  // Setting value
  vishnuInitialize(getenv("VISHNU_CONFIG_FILE"), 0, NULL);

  for (i=0;i<5;i++){
    cout << " In loop : " <<  i << endl;
    res = connect    (uid, pwd, sess, cop );
    if (res) {
      cout << "Connection failed !!! " << endl;
    }
    close(sess.getSessionKey());
  }
}


void forker(int cpt){
  cpt--;
  switch(fork()){
  case 0 :
    stress();
    break;
  case -1 :
    cout << " Fork number " << cpt << " failed " << endl;
    break;
  default :
    if(cpt>0)
      forker(cpt);
    break;
  }
  return;
}


int main(int argc, char** argv){
  int cpt;
  if (argc>1){
    cpt = boost::lexical_cast<int>(argv[1]);
  }
  else{
    cpt = 5;
  }
  forker(cpt);
  return 0;
}
