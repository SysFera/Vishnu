#include "InternalVishnuException.hpp"

#include <map>                          // for map

#include "VishnuException.hpp"          // for VishnuException, etc

InternalVishnuException::InternalVishnuException(InternalVishnuException& e):SystemException(e){
  mtype = VishnuException::INTERNAL;
}

InternalVishnuException::InternalVishnuException(int msg, std::string msgComp):SystemException(msg, msgComp){
  mtype = VishnuException::INTERNAL;
}

InternalVishnuException::InternalVishnuException(){
  mtype = VishnuException::INTERNAL;
}

std::string
InternalVishnuException::getMsg(){
  if (mval>=0 && mval<INNBERR){
    return mp[mval];
  }
  return "Unknown Internal error code.\n";
}
