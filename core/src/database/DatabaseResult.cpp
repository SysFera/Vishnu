/**
 * \file DatabaseResult.cc
 * \brief This file implements the DatabaseResult class.
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
 * \date 31/01/2011
 */
#include <sstream>
#include <iostream>
#include "DatabaseResult.hpp"

/**
* \fn DatabaseResult()
* \brief Constructor, raises an exception on error
*/
DatabaseResult:: DatabaseResult(std::vector<std::vector<std::string> > res, std::vector<std::string> namesAttributes){
  fields  = 0;
  tuples  = 0;
  results = res;
  attributesNames = namesAttributes;
}
/**
* \fn ~DatabaseResult()
* \brief Destructor, raises an exception on error
*/
DatabaseResult::~DatabaseResult() {}

/**
* \brief Function to print the database results
* \fn    print()
* \param request The request to process
* \return 0 on success, an error code otherwise
*/
void
DatabaseResult::print() {
  std::vector<std::string> tmp;
  std::vector<std::string>::iterator ii;

  if (getNbTuples() != 0) {
    for (int i = 0; i < static_cast <int> (results.size()); ++i) {
      tmp.clear();
      tmp = results[i];

      for(ii=tmp.begin();ii!=tmp.end();++ii){
        std::cout << *ii <<"  ";
      }
      std::cout << std::endl;
    }
  }
  else {
    std::cout << "There is no data"<<std::endl;
  }

}
/**
* \brief Function to print the attributes names
* \fn    print()
* \param request The request to process
* \return 0 on success, an error code otherwise
*/
void
DatabaseResult::printAttributesNames() {
  std::vector<std::string>::iterator ii;

  for(ii=attributesNames.begin();ii!=attributesNames.end();++ii) {
    std::cout << *ii <<"  ";
  }
  std::cout << std::endl;
}
/**
 * \brief To get the number of tuples
 * \fn size_t getNbTuples()
 * \return 0 on success, an error code otherwise
 */
size_t
DatabaseResult::getNbTuples() const{
return results.size();
}
/**
* \brief To get the number of fields
* \fn getNbFields()
* \return 0 on success, an error code otherwise
*/
size_t
DatabaseResult::getNbFields() const{
  return attributesNames.size();
}

/**
* \brief To get a specific results using its position
* \fn get(size_t position);
* \param position The position of the request
* \return the tuple associated to the postion
*/
std::vector<std::string>
DatabaseResult::get(size_t position) const{

  std::vector<std::string> tmp;

  // size_t always >= 0 since it's an unsigned (Cf. stddef.h)
  if (position > getNbTuples()) {
    return std::vector<std::string>();
  }
  else {
    if (position < getNbTuples()) {
    tmp = results[position];
    }
    return tmp;
  }
}
/**
* \brief To get the number of fields
* \fn get();
* \return all results
*/
std::vector<std::vector<std::string> >
DatabaseResult::getResults() const{
  return results;
}

/**
* \brief To get the first attribut value of the first element
* \fn std::string getFirstElement();
* \return the first attribut value of the first element
*/
std::string
DatabaseResult::getFirstElement() const {
  std::vector<std::string>::iterator ii;

  if (getNbTuples() != 0) {
    std::vector<std::string> tmp = get(0);
    ii=tmp.begin();
    return (*ii);
  }
  else {
    return "";
  }
}
