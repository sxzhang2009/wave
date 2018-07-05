
#ifndef __DATA_SOURCE_MANAGER_HPP__
#define __DATA_SOURCE_MANAGER_HPP__

#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <unordered_map>
#include "brokers/ib/data_source.hpp"

namespace wave{
  namespace data{

    typedef std::unordered_map<std::string, wave::tag_values>
    data_source_config;
    
    class data_source_manager{
      data_source_config m_ds_configs;
      data_source_map m_ds;      
      static const config_file_name = "data_source_config.json";
    public:

      void data_source_manager(){
        load_config();
      }
      
      void load_config(){
        namespace pt = boost::property_tree;

        pt::ptree root;
        // Load the json file in this ptree
        pt::read_json(config_file_name, root);

        for (pt::ptree::value_type &dsrc : root.get_child("")){
          std::string name = dsrc.first;
          key_values config;
          for (pt::ptree::value_type &c : dsrc.second.get_child("")) {
            config[c.first] = std::string(c.second.data());
          }
          m_ds_configs[name] = config;
        }
      }

      data_source_ptr get_data_source(const std::string ds_name){
        using namespace std;

        if(m_ds.find(ds_name) != m_ds.end()){
          return m_ds[ds_name];
        }

        //check if has configuration info for ds_name
        if(m_ds_configs.find(ds_name) == m_ds_configs.end()){
          throw logic_error("can not find the specific data source.");
        }
        
        string provider = m_ds_configs[ds_name]["provider"];
        wave::data::data_source_base *p;

        switch(provider){
        case 'ib' :
          p = new wave::data::ib::data_source(m_ds_configs[ds_name]);
          return data_source_ptr(p)
          break;
        default:
          break;
        }
      }
    }

  }
}
#endif
