
#ifndef __CONTRACT_MANAGER_HPP__
#define __CONTRACT_MANAGER_HPP__

#include "contract.hpp"
#include <string>
#include <boost/algorithm/string.hpp>

namespace wave{
  namespace data{
    class contract_manager{
      contract_map m_contracts;
      
    public:
      contract_ptr get_contract(std::string symbol){
        // m_ds_manager.get_data_source(data_source) ->
        //   subscribe_bar(period);
        // std::vector<std::string> strs;
        // boost::split(strs, symbol, boost::is_any_of("/"));
        contract_map::iterator it = m_contracts.find(symbol);
        if(it == m_contracts.end()){
          throw logic_error("could not find the symbol.");
        }
        return it->contract;
      }

      void load_contracts(){
        for (directory_iterator itr(path("./contracts/"));
             itr!=directory_iterator(); ++itr) {
          if(boost::filesystem::is_regular_file(itr->path())){
            contract_map tmp;
            std::ifstream ifs(itr->path().filename());
            boost::archive::binary_iarchive ia(ifs);
            ia >> tmp;
            m_contracts.insert(tmp.begin(), tmp.end());
          }
        }
      }
      
    }
  }
}

#endif
