
/**
 * \file Options.hpp
 * \brief This file defines a class to handle command line options.
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */


#ifndef OPTIONS_HPP
#define OPTIONS_HPP

//C++ standard library
#include <typeinfo>
#include <iostream>

// Boost Headers
#include <boost/program_options.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace po = boost::program_options;
class Options;

/**
 * \class Configuration
 * \brief Standard configuration class.
 */

class Configuration {

public:
  /**
   * \brief Default constructor
   */
  Configuration();

  /**
   * \brief Constructor by variable
   * \param pgName: The program name
   */

  explicit
  Configuration(const std::string& pgName);

  /**
   * \brief get the program name
   * \return the program name as std::string
   */
  const std::string&
  getPgName() const;

  /**
   * \brief Get the configuration file
   * \return the configuration file as std::string
   */
  const std::string&
  getConfigFile() const;


  /**
   * \brief Set a new configuration file
   * \param configFile: the new configuration file to set
   */
  void
  setConfigFile(const std::string& configFile);

private:
  /**
   * \brief  Program name
   */

  std::string pgName;

  /**
   * \brief configuration file
   */

  std::string configFile;
};

/**
 * \brief function type used to map environnement variable name
 */
typedef boost::function1<std::string, std::string> func1;


/**
 * \enum Group_type
 * \brief A convenient type allowing to group options
 */
typedef enum {
  GENERIC = 0,/*!< a generic group of options allowed for all commands  */
  CONFIG,/*!<  configuration options   */
  ENV,/*!< environment variables  */
  HIDDEN /*!< options that will not shown to the user */
} Group_type;


/**
 * \class Options
 * \brief Used to process the users command line parameters
 */
class Options {

public:

  /**
   * \brief Constructor by variable taking a string in parameter
   * \param name the name of the command which uses the option
   */
  explicit
  Options(const std::string& name);



  /**
   * \brief Constructor by variable taking a command configuration in parameter
   * \param c The configuration
   */
  explicit
  Options(boost::shared_ptr<Configuration> c);


  /**
   * \brief function allowing to get the configuration
   * \return the configuration
   */
  boost::shared_ptr<Configuration>
  getConfiguration()const;



  /**
   * \brief function allowing to add a new non-typed option
   * \param name: the name of the option
   * \param desc: brief description of the option
   * \param group: a group which option belongs to
   */
  void
  add(const std::string& name,const std::string& desc, const Group_type & group);

  /**
   *
   * \brief function provinding a way to add a typed option
   * \param name: the name of the option
   * \param desc: brief description of the option
   * \param group: a group which option belongs to
   * \param value: the value of the option when option is provided in
   * command line
   * \param required: for required option
   */

  template<class T>
  void
  add(const std::string& name,
      const std::string& desc,
      const Group_type& group,
      T& value,
      int required = 0) {
    po::options_description tmp_options;
    po::typed_value<T>* optionvalue=po::value<T>(&value);

    if (required) {
      optionvalue=optionvalue->required();
    }

    tmp_options.add_options()(name.c_str(),optionvalue,desc.c_str());

    // Set the group
    setGroup(tmp_options,group);
  }
  /**
   *
   * \brief Function providing another way to add a typed option
   * \param name: the name of the option
   * \param desc: brief description of the option
   * \param group: a group which option belongs to
   * \param userFunc: The user defined function (callback)
   * command line
   * \param required: for required option
   */

  template<typename T>
  void
  add(const std::string& name,
      const std::string& desc,
      const Group_type& group,
      boost::function1<void, T>& userFunc,
      int required=0 ) {
    po::options_description tmp_options;
    po::typed_value<T>* optionvalue=po::value<T>()->notifier(userFunc);

    if (required) {
      optionvalue=optionvalue->required();
    }

    tmp_options.add_options()(name.c_str(),optionvalue,desc.c_str());

    // Set the group
    setGroup(tmp_options,group);
  }

  /**
   * \brief To set position of options
   * \param name: the name of the option
   * \param pos :  the required position
   */

  void
  setPosition(const std::string& name, int pos);

  /**
   * \brief To parse command line
   * \param ac: The number of parameters of the command
   * \param av: the names of all paramters
   */

  void
  parse_cli(int ac, char* av[]);

  /**
   * \brief To parse config file
   */

  void
  parse_cfile();

  /**
   * \brief To parse environement variable
   * \param name_mapper: a functor providing a simple name from the conventional
   * name of the environment variable
   * Ex: for VISHNU_CONFIG_FILE, it returns configFile
   */

  void
  parse_env (const func1 & name_mapper);

  /**
   * \brief To notify all  user-defined functions (callback)
   */

  void
  notify ();

  /**
   * \brief To check if an option is provided after parsing the command
   * line
   * \param key: The name of the option
   * \return The number odf occurrences of the options (0 or 1)
   */

  int
  count (const std::string& key) const;

  /**
   * \brief To check if a value is stored
   */

  bool
  empty () const {
    return vm.empty();
  }

  /**
   * \brief To get the value of options
   * \param key: the name of the option
   * \return The value of the option
   */

  template<class T>
  const T &
  get(const std::string& key) const {
    return(vm[key.c_str()].template as<T>());
  }

  /**
   * \brief to print the set of options allowed by a command
   * \param os: Where options wiil be printed.
   * \param opt: the options to print.
   * \return the stream where the options are printed.
   */

  friend
  std::ostream&
  operator<<(std::ostream &os,const Options & opt);

  /**
   * \brief returns a string with all positional parameters in the correct order
   * \return the positional parameters separated by spaces. e.g., "param1 param2... paramn"
   */
  std::string
  getPositionalOptString() const;

  /**
   * \brief The default destructor
   */

  virtual ~Options();

private:
  /**
   * \brief  store a command configuration
   */
  boost::shared_ptr<Configuration> conf;

  /**
   * \brief  Generic option description
   */

  po::options_description generic_options;

  /**
   * \brief Configuration option description
   */

  po::options_description config_options;

  /**
   * \brief Hidden option description
   */

  po::options_description hidden_options ;

  /**
   * \brief environment variable option description
   */
  po::options_description env_options;

  /**
   * \brief map storing all parsed options
   */
  mutable po::variables_map vm;

  /**
   * \brief option position in a command line
   */

  po::positional_options_description position;

  /**
   * \brief a private function used to set option group
   * \param tmp_options: the set of options to group
   * \param group      : the group to set
   */

  void
  setGroup (const po::options_description& tmp_options, const Group_type& group);
};

/**
 * \brief A helper function to simplify the display of vector
 * \param os: an ostream to write data in
 * \param v: a vector to print
 * \return the ostream in which the data is written
 */
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));

  return os;
}


#endif
