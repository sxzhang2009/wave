
#ifndef __DATA_SOURCE_MANAGER_HPP__
#define __DATA_SOURCE_MANAGER_HPP__

#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <unordered_map>
#include <boost/thread.hpp>
#include "data_source_base.hpp"
#include "brokers/ib/data_source.hpp"

namespace wave{
  namespace data{

    typedef std::unordered_map<std::string, wave::tag_values>
    data_source_config;

    typedef std::unordered_map<std::string, boost::thread>
    threads_map;
    
    //! data source manager
    class data_source_manager {
      
    private:
      //! data source configs.
      data_source_config m_ds_configs;

      //! data source objects.
      wave::data::data_source_map m_ds;

      //! config file name.
      const std::string config_file_name;

      //! data source threads
      threads_map   m_ds_threads;

    public:

      //! get a global data source manager instance.
      static ptr_type<data_source_manager> global();

      vec_string available_data_sources(){
        vec_string list;
        for(auto& a : m_ds){
          list.push_back(a.first);
        }
        return list;
      }
      
      //! constructor
      data_source_manager();

      //! destructor
      ~data_source_manager();
      
      //! load data source config from file.
      void load_config();

      //! get a data source object from a given name
      data_source_ptr get_data_source(
          const std::string ds_name);
      
      //! start data source loop
      void start_data_sources();

      //! stop data source loop
      void stop_data_sources();
    };

  }
}
#endif
