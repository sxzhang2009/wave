
#ifndef __CONTRACT_DETAILS_HPP__
#define __CONTRACT_DETAILS_HPP__

// #include "TagValue.h"
#include "../common.hpp"
#include "contract.hpp"

namespace wave{
  namespace data{

    class contract_details;
    typedef std::map<std::string, contract_details> contract_map;
    
    struct contract_details
    {
      contract_details()
        : min_tick(0)
        , price_magnifier(0)
        , under_conid(0)
        , ev_multiplier(0)
        , callable(false)
        , putable(false)
        , coupon(0)
        , convertible(false)
        , next_option_partial(false)
      {
      }

      contract_ptr      contract;
      std::string	market_name;
      double	        min_tick;
      std::string	order_types;
      std::string	valid_exchanges;
      int8		price_magnifier;
      int		under_conid;
      std::string	long_name;
      std::string	contract_month;
      std::string	industry;
      std::string	category;
      std::string	subcategory;
      std::string	timezone_id;
      std::string	trading_hours;
      std::string	liquid_hours;
      std::string	ev_rule;
      double	        ev_multiplier;
      int		md_size_multiplier;
      int		agg_group;
      std::string	under_symbol;
      std::string	under_sec_type;
      std::string       market_rule_ids;
      std::string       real_expiration_date;
      std::string       last_trade_time;       

      // TagValueListSPtr secid_list;

      // BOND values
      std::string	cusip;
      std::string	ratings;
      std::string	desc_append;
      std::string	bond_type;
      std::string	coupon_type;
      bool		callable;
      bool		putable;
      double	        coupon;
      bool		convertible;
      std::string	maturity;
      std::string	issue_date;
      std::string	next_option_date;
      std::string	next_option_type;
      bool		next_option_partial;
      std::string	notes;               

      friend class boost::serialization::access;

      //! serialize contract details
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & contract;             
        ar & market_name;           
        ar & min_tick;              
        ar & order_types;           
        ar & valid_exchanges;       
        ar & price_magnifier;       
        ar & under_conid;           
        ar & long_name;             
        ar & contract_month;        
        ar & industry;              
        ar & category;              
        ar & subcategory;           
        ar & timezone_id;           
        ar & trading_hours;         
        ar & liquid_hours;          
        ar & ev_rule;               
        ar & ev_multiplier;         
        ar & md_size_multiplier;    
        ar & agg_group;              
        ar & under_symbol;          
        ar & under_sec_type;        
        ar & market_rule_ids;       
        ar & real_expiration_date;  
        ar & last_trade_time;

        ar & cusip;               
        ar & ratings;             
        ar & desc_append;         
        ar & bond_type;           
        ar & coupon_type;         
        ar & callable;            
        ar & putable;             
        ar & coupon;              
        ar & convertible;         
        ar & maturity;            
        ar & issue_date;          
        ar & next_option_date;    
        ar & next_option_type;    
        ar & next_option_partial; 
        ar & notes;               
      }
    };

    
  }
}

#endif
