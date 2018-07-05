
#ifndef __ORDER_HPP__
#define __ORDER_HPP__

// #include "TagValue.h"
// #include "order_condition.h"
// #include "SoftDollarTier.h"

// #include <float.h>
// #include <limits.h>

#include <limits>
#include "../common.hpp"

#define UNSET_DOUBLE  std::numeric_limits<double>::max()
#define UNSET_INTEGER std::numeric_limits<int>::min()

namespace wave{
  namespace data{
    
    enum Origin { CUSTOMER,  FIRM,  UNKNOWN };
    enum AuctionStrategy { AUCTION_UNSET = 0,
                           AUCTION_MATCH = 1,
                           AUCTION_IMPROVEMENT = 2,
                           AUCTION_TRANSPARENT = 3 };

    struct order_comboleg {
      order_comboleg() {
        price = UNSET_DOUBLE;
      }

      double price;
      bool operator==( const order_comboleg& other) const {
        return (price == other.price);
      }
    };
    typedef ptr_type<order_comboleg> order_comboleg_ptr;

    struct order {
      order() //: soft_dollar_tier("", "", "")
      {
        // order identifier
        order_id  = 0;
        client_id = 0;
        perm_id   = 0;

        // main order fields
        total_quantity = 0;
        lmt_price      = UNSET_DOUBLE;
        aux_price      = UNSET_DOUBLE;

        // extended order fields
        active_start_time = "";
        active_stop_time  = "";
        oca_type          = 0;
        transmit          = true;
        parent_id         = 0;
        block_order       = false;
        sweep_to_fill     = false;
        display_size      = 0;
        trigger_method    = 0;
        outside_rth       = false;
        hidden            = false;
        all_or_none       = false;
        min_qty         = UNSET_INTEGER;
        percent_offset  = UNSET_DOUBLE;
        override_percentage_constraints = false;
        trail_stop_price = UNSET_DOUBLE;
        trailing_percent = UNSET_DOUBLE;

        // institutional (ie non-cleared) only
        open_close     = "O";
        origin        = CUSTOMER;
        short_sale_slot = 0;
        exempt_code    = -1;

        // SMART routing only
        discretionary_amt = 0;
        etrade_only       = true;
        firm_quote_only    = true;
        nbbo_price_cap     = UNSET_DOUBLE;
        opt_outsmart_routing = false;

        // BOX exchange orders only
        auction_strategy = AUCTION_UNSET;
        starting_price   = UNSET_DOUBLE;
        stock_ref_price   = UNSET_DOUBLE;
        delta           = UNSET_DOUBLE;

        // pegged to stock and VOL orders only
        stock_range_lower = UNSET_DOUBLE;
        stock_range_upper = UNSET_DOUBLE;

        randomize_price = false;
        randomize_size  = false;

        // VOLATILITY ORDERS ONLY
        volatility            = UNSET_DOUBLE;
        volatility_type        = UNSET_INTEGER;     // 1=daily, 2=annual
        delta_neutral_order_type = "";
        delta_neutral_aux_price  = UNSET_DOUBLE;
        delta_neutral_con_id     = 0;
        delta_neutral_settling_firm = "";
        delta_neutral_clearing_account = "";
        delta_neutral_clearing_intent = "";
        delta_neutral_openclose = "";
        delta_neutral_short_sale = false;
        delta_neutral_short_sale_slot = 0;
        delta_neutral_designated_location = "";
        continuous_update      = false;
        reference_price_type    = UNSET_INTEGER; // 1=Average, 2 = BidOrAsk

        // COMBO ORDERS ONLY
        basis_points      = UNSET_DOUBLE;  // EFP orders only
        basis_points_type = UNSET_INTEGER; // EFP orders only

        // SCALE ORDERS ONLY
        scale_init_level_size  = UNSET_INTEGER;
        scale_subs_level_size  = UNSET_INTEGER;
        scale_price_increment = UNSET_DOUBLE;
        scale_price_adjust_value = UNSET_DOUBLE;
        scale_price_adjust_interval = UNSET_INTEGER;
        scale_profit_offset = UNSET_DOUBLE;
        scale_auto_reset = false;
        scale_init_position = UNSET_INTEGER;
        scale_init_fill_qty = UNSET_INTEGER;
        scale_random_percent = false;
        scale_table = "";

        // What-if
        what_if = false;

        // Not Held
        not_held = false;
        solicited = false;

        trigger_price = UNSET_DOUBLE;
        adjusted_stop_price = UNSET_DOUBLE;
        adjusted_stop_limit_price = UNSET_DOUBLE;
        adjusted_trailing_amount = UNSET_DOUBLE;
        lmt_price_offset = UNSET_DOUBLE;
        ext_operator = "";

        // native cash quantity
        cash_qty = UNSET_DOUBLE;

        // mifid2DecisionMaker = "";
        // mifid2DecisionAlgo = "";
        // mifid2ExecutionTrader = "";
        // mifid2ExecutionAlgo = "";

        // don't use auto price for hedge
        dont_use_auto_price_for_hedge = false;
      }

      // order identifier
      long     order_id;
      long     client_id;
      int      perm_id;

      // main order fields
      std::string action;
      double     total_quantity;
      std::string order_type;
      double   lmt_price;
      double   aux_price;

      // extended order fields
      std::string tif;           // "Time in Force" - DAY, GTC, etc.
      std::string active_start_time;	// for GTC orders
      std::string active_stop_time;	// for GTC orders
      std::string oca_group;      // one cancels all group name
      int         oca_type;       // 1 = CANCEL_WITH_BLOCK, 2 = REDUCE_WITH_BLOCK, 3 = REDUCE_NON_BLOCK
      std::string order_ref;  // order reference
      bool     transmit;  // if false, order will be created but not transmited
      long     parent_id;   // Parent order Id, to associate Auto STP or TRAIL orders with the original order.
      bool     block_order;
      bool     sweep_to_fill;
      int      display_size;
      int      trigger_method; // 0=Default, 1=Double_Bid_Ask, 2=Last, 3=Double_Last, 4=Bid_Ask, 7=Last_or_Bid_Ask, 8=Mid-point
      bool     outside_rth;
      bool     hidden;
      std::string good_after_time;    // Format: 20060505 08:00:00 {time zone}
      std::string good_till_date;     // Format: 20060505 08:00:00 {time zone}
      std::string rule80A; // Individual = 'I', Agency = 'A', AgentOtherMember = 'W', IndividualPTIA = 'J', AgencyPTIA = 'U', AgentOtherMemberPTIA = 'M', IndividualPT = 'K', AgencyPT = 'Y', AgentOtherMemberPT = 'N'
      bool     all_or_none;
      int      min_qty;
      double   percent_offset; // REL orders only
      bool     override_percentage_constraints;
      double   trail_stop_price; // TRAILLIMIT orders only
      double   trailing_percent;

      // financial advisors only
      std::string fa_group;
      std::string fa_profile;
      std::string fa_method;
      std::string fa_percentage;

      // institutional (ie non-cleared) only
      std::string open_close; // O=Open, C=Close
      Origin   origin;    // 0=Customer, 1=Firm
      int      short_sale_slot; // 1 if you hold the shares, 2 if they will be delivered from elsewhere.  Only for Action="SSHORT
      std::string designated_location; // set when slot=2 only.
      int      exempt_code;

      // SMART routing only
      double   discretionary_amt;
      bool     etrade_only;
      bool     firm_quote_only;
      double   nbbo_price_cap;
      bool     opt_outsmart_routing;

      // BOX exchange orders only
      int      auction_strategy; // AUCTION_MATCH, AUCTION_IMPROVEMENT, AUCTION_TRANSPARENT
      double   starting_price;
      double   stock_ref_price;
      double   delta;

      // pegged to stock and VOL orders only
      double   stock_range_lower;
      double   stock_range_upper;

      bool randomize_size;
      bool randomize_price;

      // VOLATILITY ORDERS ONLY
      double   volatility;
      int      volatility_type;     // 1=daily, 2=annual
      std::string delta_neutral_order_type;
      double   delta_neutral_aux_price;
      long     delta_neutral_con_id;
      std::string delta_neutral_settling_firm;
      std::string delta_neutral_clearing_account;
      std::string delta_neutral_clearing_intent;
      std::string delta_neutral_openclose;
      bool     delta_neutral_short_sale;
      int      delta_neutral_short_sale_slot;
      std::string delta_neutral_designated_location;
      bool     continuous_update;
      int      reference_price_type; // 1=Average, 2 = BidOrAsk

      // COMBO ORDERS ONLY
      double   basis_points;      // EFP orders only
      int      basis_points_type;  // EFP orders only

      // SCALE ORDERS ONLY
      int      scale_init_level_size;
      int      scale_subs_level_size;
      double   scale_price_increment;
      double   scale_price_adjust_value;
      int      scale_price_adjust_interval;
      double   scale_profit_offset;
      bool     scale_auto_reset;
      int      scale_init_position;
      int      scale_init_fill_qty;
      bool     scale_random_percent;        
      std::string scale_table;

      // HEDGE ORDERS
      std::string hedge_type;  // 'D' - delta, 'B' - beta, 'F' - FX, 'P' - pair
      std::string hedge_param; // 'beta=X' value for beta hedge, 'ratio=Y' for pair hedge

      // Clearing info
      std::string account; // IB account
      std::string settling_firm;
      std::string clearing_account; // True beneficiary of the order
      std::string clearing_intent; // "" (Default), "IB", "Away", "PTA" (PostTrade)

      // ALGO ORDERS ONLY
      std::string algo_strategy;

      // TagValueListSPtr algo_params;
      // TagValueListSPtr smart_combo_routing_params;

      std::string algo_id;

      // What-if
      bool     what_if;

      // Not Held
      bool     not_held;
      bool     solicited;

      // models
      std::string model_code;

      // order combo legs
      typedef std::vector<order_comboleg_ptr> order_comboleg_list;
      typedef ptr_type<order_comboleg_list> order_comboleg_list_ptr;

      order_comboleg_list_ptr order_combolegs;

      // TagValueListSPtr order_misc_options;

      //VER PEG2BENCH fields:
      int ref_contract_id;
      double pegged_change_amount;
      bool is_pegged_change_amount_decrease;
      double reference_change_amount;
      std::string reference_exch_id;
      std::string adjusted_order_type;
      double trigger_price;
      double adjusted_stop_price;
      double adjusted_stop_limit_price;
      double adjusted_trailing_amount;
      int adjustableTrailingUnit;
      double lmt_price_offset;

      // std::vector<ptr_type<order_condition>> conditions;
      // bool conditions_cancel_order;
      // bool conditions_ignore_rth;

      // ext operator
      std::string ext_operator;

      // SoftDollarTier soft_dollar_tier;

      // native cash quantity
      double cash_qty;

      // std::string mifid2DecisionMaker;
      // std::string mifid2DecisionAlgo;
      // std::string mifid2ExecutionTrader;
      // std::string mifid2ExecutionAlgo;

      // don't use auto price for hedge
      bool dont_use_auto_price_for_hedge;

    public:

      // Helpers
      static void clone_combo_legs(order_comboleg_list_ptr& dst,
              const order_comboleg_list_ptr& src);

      static order market_if_touched(std::string action,
              double quantity, double price);

      static order market_order(std::string action, double quantity);
        
    };

  }
}
#endif
