
#include "data_source_manager.hpp"

namespace wave{
  namespace data{

    ptr_type<data_source_manager>
    data_source_manager::global(){
      static ptr_type<data_source_manager>
        p(new data_source_manager());
      return p;
    }
    
    data_source_manager::data_source_manager() :
      config_file_name("data_source_config.json"){
      load_config();
    }

    data_source_manager::~data_source_manager(){
    }
    
    void data_source_manager::load_config(){
      namespace pt = boost::property_tree;

      BOOST_LOG_TRIVIAL(info) << "reading data source config file "
                              << config_file_name;
      pt::ptree root;
      // Load the json file in this ptree
      pt::read_json(config_file_name, root);

      for (pt::ptree::value_type &dsrc : root.get_child("")){
        std::string name = dsrc.first;
        tag_values config;

        BOOST_LOG_TRIVIAL(trace)
          << "found data source entry \""<<name<<"\"";
        
        for (pt::ptree::value_type &c : dsrc.second.get_child("")) {
          config[c.first] = std::string(c.second.data());
          BOOST_LOG_TRIVIAL(trace) << "found key pair: " <<c.first
                                   <<" = "
                                   <<std::string(c.second.data());
        }
        m_ds_configs[name] = config;
      }

      BOOST_LOG_TRIVIAL(info) << "data source config file loaded.";

      for(auto& config : m_ds_configs){
        //! check if config valid
        string provider = config.second["provider"];
        if(provider == ""){
          RUNTIME_ERROR("must set data provider.");
        }
        
        if(provider == "ib"){
          m_ds[config.first] = ptr_type<data_source_base>
            (new ib::data_source(config.second));
        } else {
          LOGIC_ERROR("not supported data source type.");
        }
      }

      BOOST_LOG_TRIVIAL(info)
        << m_ds_configs.size()
        << " data source instances created.";
    }

    data_source_ptr data_source_manager::get_data_source(
        const std::string ds_name){
      using namespace std;
      using namespace wave::data;
        
      if(m_ds.find(ds_name) != m_ds.end()){
        return m_ds[ds_name];
      } else{
        LOGIC_ERROR("can not find the specific data source.");
      }

      return NULL;
      // //check if has configuration info for ds_name
      // if(m_ds_configs.find(ds_name) == m_ds_configs.end()){
      //   LOGIC_ERROR("can not find the specific data source.");
      // }
        
      // string provider = m_ds_configs[ds_name]["provider"];
      // if(provider == ""){
      //   RUNTIME_ERROR("must set data provider.");
      // }
        
      // // wave::data::data_source_base *p;
      // data_source_ptr p;
        
      // if(provider == "ib"){
      //   p = ptr_type<data_source_base>
      //     (new ib::data_source(m_ds_configs[ds_name]));
      // } else {
      //   LOGIC_ERROR("not supported data source type.");
      // }

      // m_ds[ds_name] = p;
      // return p;
    }

    void data_source_manager::start_data_sources(){
      using namespace boost;
      using namespace wave::data;

      if(m_ds.size() < 1){
        const string msg = "no data source instance to start.";
        BOOST_LOG_TRIVIAL(fatal) << msg;
        RUNTIME_ERROR(msg);
      }
      
      BOOST_LOG_TRIVIAL(info)
        << "starting " << m_ds.size() << " data sources.";
      
      
      for(auto& ds : m_ds){
        m_ds_threads[ds.first] =
          thread(bind(&data_source_base::start,
                          ds.second.get()));
        
        BOOST_LOG_TRIVIAL(info)
          << "data source \"" << ds.first << "\" has started.";
      }
    }

    void data_source_manager::stop_data_sources() {
      using namespace boost;
      using namespace wave::data;

      // threads_map::iterator it =
      //   m_ds_threads.find(ds_name);
      
      // if(it != m_ds_threads.end()){
      //   it->second.interrupt();
      // }

      for(auto& ds : m_ds_threads){
        ds.second.interrupt();
        ds.second.join();
        m_ds[ds.first]->clean();
      }
      
    }
  
  }
}
