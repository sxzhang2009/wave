
#include "contract.hpp"

namespace wave{
  namespace data{


    //! create STK contract
    contract contract::stk(std::string t_symbol,
            std::string t_currency,
            std::string t_exchange,
            std::string t_primary_exchange){
      contract contract;
      contract.symbol   = t_symbol;
      contract.sec_type  = "STK";
      contract.currency = t_currency;
      contract.exchange = t_exchange;
      contract.primary_exchange = t_primary_exchange;
      return contract;
    }

    //! create forex contract
    contract contract::forex(std::string t_symbol,
            std::string t_exchange){

      contract contract;
      std::size_t index = t_symbol.find(".");
      contract.symbol = t_symbol.substr(0, index);
      contract.sec_type = "CASH";
      contract.currency = t_symbol.substr(index+1);;
      contract.exchange = t_exchange; //usually "IDEALPRO"

      return contract;
    }

    //! create index contract
    contract contract::index(
        const std::string& t_symbol,
        const std::string& t_currency,
        const std::string& t_exchange){
      contract contract;
      
      contract.symbol = t_symbol; //DAX
      contract.sec_type = "IND";
      contract.currency = t_currency;//"EUR";
      contract.exchange = t_exchange;//"DTB";
      
      return contract;
    }

    inline void
    contract::clone_combo_legs(comboleg_list_ptr& dst,
            const comboleg_list_ptr& src)
    {
      if (!src.get())
        return;

      dst->reserve(src->size());

      comboleg_list::const_iterator iter = src->begin();
      const comboleg_list::const_iterator iterEnd = src->end();

      for (; iter != iterEnd; ++iter) {
        const comboleg* leg = iter->get();
        if (!leg)
          continue;
        dst->push_back(comboleg_ptr(new comboleg(*leg)));
      }
    }
    
  }
}
