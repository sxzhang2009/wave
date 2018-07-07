

#ifndef __CONTRACT_HPP__
#define __CONTRACT_HPP__

// #include "TagValue.h"
#include "../common.hpp"
#include <boost/serialization/shared_ptr.hpp>

namespace wave{
  namespace data{

    /*
      SAME_POS    = open/close leg value is same as combo
      OPEN_POS    = open
      CLOSE_POS   = close
      UNKNOWN_POS = unknown
    */
    enum LegOpenClose { SAME_POS, OPEN_POS, CLOSE_POS, UNKNOWN_POS };

    //! combo legs
    struct comboleg
    {
      comboleg()
        : con_id(0)
        , ratio(0)
        , open_close(0)
        , short_sale_slot(0)
        , exempt_code(-1)
      { }

      int8		con_id;
      int8		ratio;
      std::string	action; //BUY/SELL/SSHORT
      std::string	exchange;
      int8		open_close; // LegOpenClose enum values

      // for stock legs when doing short sale
      int8		short_sale_slot; // 1 = clearing broker, 2 = third party
      std::string	designated_location;
      int		exempt_code;

      bool operator==( const comboleg& other) const
      {
        return (con_id == other.con_id &&
                ratio == other.ratio &&
                open_close == other.open_close &&
                short_sale_slot == other.short_sale_slot &&
                exempt_code == other.exempt_code &&
                action == other.action &&
                exchange == other.exchange &&
                designated_location == other.designated_location);
      }
    };
    typedef ptr_type<comboleg> comboleg_ptr;

    struct delta_neutral_contract
    {
      delta_neutral_contract()
        : con_id(0)
        , delta(0)
        , price(0)
      {}

      int8      con_id;
      double	delta;
      double	price;
    };

    struct contract
    {
      contract()
        : con_id(0)
        , strike(0)
        , include_expired(false)
        , combo_legs(NULL)
      {
      }

      int8		con_id;
      std::string	symbol;
      std::string	sec_type;
      std::string	last_trade_date;
      double	        strike;
      std::string	right; //"C" or "P"
      std::string	multiplier;
      std::string	exchange;
      // pick an actual (ie non-aggregate) exchange
      // that the contract trades on.  DO NOT SET TO SMART.
      std::string	primary_exchange; 
      std::string	currency;
      std::string	local_symbol;
      std::string	trading_class;
      bool		include_expired;
      std::string	sec_id_type;		// CUSIP;SEDOL;ISIN;RIC
      std::string	sec_id;
      
      // COMBOS
      // received in open order 14 and up for all combos
      std::string combolegs_desc; 

      // combo legs
      typedef std::vector<comboleg_ptr> comboleg_list;
      typedef ptr_type<comboleg_list> comboleg_list_ptr;

      comboleg_list_ptr combo_legs;

      // delta neutral contract
      // delta_neutral_contract* delta_neutral_contract;

      static contract stk(std::string t_symbol,
              std::string t_currency,
              std::string t_exchange="SMART",
              std::string t_primary_exchange="");
      
      static contract forex(std::string t_symbol,
              std::string t_exchange = "IDEALPRO");

      static contract index(
          const std::string& t_symbol,
          const std::string& t_currency,
          const std::string& t_exchange);

      friend class boost::serialization::access;
      // When the class Archive corresponds to an output archive, the
      // & operator is defined similar to <<.  Likewise, when the class Archive
      // is a type of input archive the & operator is defined similar to >>.
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {

        ar & con_id;
        ar & symbol;
        ar & sec_type;
        ar & last_trade_date;
        ar & strike;
        ar & right; //"C" or "P"
        ar & multiplier;
        ar & exchange;

        ar & primary_exchange; 
        ar & currency;
        ar & local_symbol;
        ar & trading_class;
        ar & include_expired;
        ar & sec_id_type;		// CUSIP;SEDOL;ISIN;RIC
        ar & sec_id;
        ar & combolegs_desc;
      }

    public:

      // Helpers
      static void clone_combo_legs(comboleg_list_ptr& dst,
              const comboleg_list_ptr& src);
    };
    
    typedef ptr_type<contract> contract_ptr;

  }
}
  
#endif
