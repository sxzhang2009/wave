
#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

// #include "TagValue.h"
#include "../common.hpp"
#include <boost/any.hpp>

namespace wave{
  namespace data{
    using namespace std;

    // typedef std::unordered_map<std::string, boost::any>
    typedef std::unordered_map<std::string, std::string>
    account_summary;
    
    struct account{
      std::string name;
      std::string type;
      double net_value;
      double total_cash;
      double settled_cash;
      double accrued_cash;
      double buying_power;
      double equity_with_load;
      double previous_equity_with_load;
      double gross_possition_value;
      double reqt_equity;
      double reqt_margin;
      double sma;
      double init_margin_req;
      double maint_margin_req;
      double available_funds;
      double excess_liquidity;
      double cushion;
      double day_trade_remaining;
      double leverage;
    };

    class account_map {
    private:
      std::unordered_map<std::string, account> m_accounts;
      
    public:

      //! this interface should only be used by user in stratgy code. 
      account& operator[](std::string key){
        auto it = m_accounts.find(key);
        
        if(it == m_accounts.end()){
          RUNTIME_ERROR(boost::format("can not find account with key %s")
                  % key);
        }

        return it->second;
      }

      //! get or create an account object with a key
      account& get(std::string key){
        auto it = m_accounts.find(key);
        if(it == m_accounts.end()){
          m_accounts.insert(std::make_pair(key, account()));
          return m_accounts.find(key)->second;          
        }

        return it->second;
      }
    };
  }
}

#endif
