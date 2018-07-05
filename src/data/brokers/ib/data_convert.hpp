
#include "../bar.hpp"

#include "official/Contract.h"
#include "official/Order.h"
#include "official/Bar.h"
#include "official/HistoricalTick.h"
#include "../../utils.hpp"

using namespace wave;

namespace wave{
  namespace data{
    namespace ib{

      void convert(wave::data::tick& dst,
              const HistoricalTick& src){
        dst.time  = utils::int8ptime(src.time*1E6);
        dst.price = src.price;
        dst.size  = src.size;
      }

      void convert(wave::data::bar& dst, const Bar& src){
        dst.time = utils::strptime(src.time);
        dst.open = src.open;        
        dst.high = src.high;
        dst.low  = src.low;
        dst.close = src.close;
        dst.volume = src.volume;
      }

      void convert(wave::data::order& dst, const Order& src){
        dst.order_id  = src.orderId;
        dst.client_id = src.clientId;
        dst.perm_id   = src.permId;             
                                             
        // main order fields   // main order 
        dst.total_quantity = src.totalQuantity;
        dst.lmt_price      = src.lmtPrice;      
        dst.aux_price      = src.auxPrice;      

        // extended order fields
        dst.active_start_time = src.activeStartTime;
        dst.active_stop_time  = src.activeStopTime;
        dst.oca_type = src.ocaType;         
        dst.transmit = src.transmit;         
        dst.parent_id = src.parentId;        
        dst.block_order = src.blockOrder;
        dst.sweep_to_fill = src.sweepToFill;    
        dst.display_size  = src.displaySize;    
        dst.trigger_method = src.triggerMethod;   
        dst.outside_rth = src.outsideRth;      
        dst.hidden = src.hidden;           
        dst.all_or_none = src.allOrNone;      
        dst.min_qty = src.minQty;        
        dst.percent_offset = src.percentOffset; 
        dst.override_percentage_constraints = src.overridePercentageConstraints;
        dst.trail_stop_price = src.trailStopPrice;
        dst.trailing_percent = src.trailingPercent;

        // institutional (ie non-cleared) only        
        dst.open_close = src.openClose;
        dst.origin = src.origin;
        dst.short_sale_slot = src.shortSaleSlot;
        dst.exempt_code = src.exemptCode;

        // SMART routing only        
        dst.discretionary_amt = src.discretionaryAmt;
        dst.etrade_only = src.eTradeOnly;
        dst.firm_quote_only = src.firmQuoteOnly;
        dst.nbbo_price_cap = src.nbbo_price_cap;
        dst.opt_outsmart_routing = dst.optOutSmartRouting;

        // BOX exchange orders only
        dst.auction_strategy = src.auctionStrategy;
        dst.starting_price   = src.startingPrice;   
        dst.stock_ref_price  = src.stockRefPrice;
        dst.delta            = src.delta;

        // pegged to stock and VOL orders only
        dst.stock_range_lower = src.stockRangeLower;
        dst.stock_range_upper = src.stockRangeUpper;

        dst.randomize_size  = src.randomizeSize;
        dst.randomize_price = src.randomizePrice;

        // VOLATILITY ORDERS ONLY
        dst.volatility = src.volatility;
        // 1=daily, 2=annual
        dst.volatility_type = src.volatilityType;     
        dst.delta_neutral_order_type = src.deltaNeutralOrderType;
        dst.delta_neutral_aux_price = src.deltaNeutralAuxPrice;
        dst.delta_neutral_con_id = src.deltaNeutralConId;
        dst.delta_neutral_settling_firm = src.deltaNeutralSettlingFirm;
        dst.delta_neutral_clearing_account = src.deltaNeutralClearingAccount;
        dst.delta_neutral_clearing_intent = src.deltaNeutralClearingIntent;
        dst.delta_neutral_openclose = src.deltaNeutralOpenClose;
        dst.delta_neutral_short_sale = src.deltaNeutralShortSale;
        dst.delta_neutral_short_sale_slot = src.deltaNeutralShortSaleSlot;
        dst.delta_neutral_designated_location =
          src.deltaNeutralDesignatedLocation;
        dst.continuous_update = src.continuousUpdate;
        // 1=Average, 2 = BidOrAsk        
        dst.reference_price_type = src.referencePriceType; 

        dst.basis_points = src.basisPoints;
        dst.basis_points_type = src.basisPointsType;

        dst.scale_init_level_size = src.scaleInitLevelSize;      
        dst.scale_subs_level_size = src.scaleSubsLevelSize;      
        dst.scale_price_increment = src.scalePriceIncrement;      
        dst.scale_price_adjust_value = src.scalePriceAdjustValue;   
        dst.scale_price_adjust_interval = src.scalePriceAdjustInterval;
        dst.scale_profit_offset = src.scaleProfitOffset;        
        dst.scale_auto_reset = src.scaleAutoReset;           
        dst.scale_init_position  = src.scaleInitPosition;        
        dst.scale_init_fill_qty  = src.scaleInitFillQty;        
        dst.scale_random_percent = src.scaleRandomPercent;
        dst.scale_table = src.scaleTable;

        dst.what_if = src.whatIf;

        dst.not_held = src.notHeld;
        dst.solicited = src.solicited;

        dst.trigger_price = src.triggerPrice;
        dst.adjusted_stop_price = src.adjustedStopPrice;
        dst.adjusted_stop_limit_price = src.adjustedStopLimitPrice;
        dst.adjusted_trailing_amount = src.adjustedTrailingAmount;
        dst.lmt_price_offset = src.lmtPriceOffset;
        dst.ext_operator = src.extOperator;

        dst.cash_qty = src.cashQty;

        // std::string mifid2DecisionMaker;
        // std::string mifid2DecisionAlgo;
        // std::string mifid2ExecutionTrader;
        // std::string mifid2ExecutionAlgo;

        // don't use auto price for hedge
        dst.dont_use_auto_price_for_hedge = src.dontUseAutoPriceForHedge;

      }

      void convert(Order& dst, const wave::data::order& src){
        dst.orderId = src.order_id;
        dst.clientId = src.client_id;
        dst.permId = src.perm_id;

        // main order fields// main order 
        dst.totalQuantity = src.total_quantity;
        dst.lmtPrice = src.lmt_price; 
        dst.auxPrice = src.aux_price; 

        // extended order fields
        dst.activeStartTime = src.active_start_time; 
        dst.activeStopTime = src.active_stop_time ; 
        dst.ocaType = src.oca_type; 
        dst.transmit = src.transmit; 
        dst.parentId = src.parent_id; 
        dst.blockOrder = src.block_order; 
        dst.sweepToFill = src.sweep_to_fill; 
        dst.displaySize = src.display_size ; 
        dst.triggerMethod = src.trigger_method; 
        dst.outsideRth = src.outside_rth; 
        dst.hidden = src.hidden; 
        dst.allOrNone = src.all_or_none; 
        dst.minQty = src.min_qty; 
        dst.percentOffset = src.percent_offset; 
        dst.overridePercentageConstraints = src.override_percentage_constraints; 
        dst.trailStopPrice = src.trail_stop_price; 
        dst.trailingPercent = src.trailing_percent; 

        // institutional (ie non-cleared) only
        dst.openClose = src.open_close; 
        dst.origin = src.origin; 
        dst.shortSaleSlot = src.short_sale_slot; 
        dst.exemptCode = src.exempt_code; 

        // SMART routing only
        dst.discretionaryAmt = src.discretionary_amt; 
        dst.eTradeOnly = src.etrade_only; 
        dst.firmQuoteOnly = src.firm_quote_only; 
        dst.nbbo_price_cap = src.nbbo_price_cap; 
        src.optOutSmartRouting = src.opt_outsmart_routing; 

        // BOX exchange orders only
        dst.auctionStrategy = src.auction_strategy; 
        dst.startingPrice = src.starting_price; 
        dst.stockRefPrice = src.stock_ref_price ; 
        dst.delta = src.delta; 

        // pegged to stock and VOL orders only
        dst.stockRangeLower = src.stock_range_lower; 
        dst.stockRangeUpper = src.stock_range_upper; 

        dst.randomizeSize = src.randomize_size ; 
        dst.randomizePrice = src.randomize_price; 

        // VOLATILITY ORDERS ONLY
        dst.volatility = src.volatility; 
        // 1;daily, 2;annual
        dst.volatilityType = src.volatility_type; 
        dst.deltaNeutralOrderType = src.delta_neutral_order_type; 
        dst.deltaNeutralAuxPrice = src.delta_neutral_aux_price; 
        dst.deltaNeutralConId = src.delta_neutral_con_id; 
        dst.deltaNeutralSettlingFirm = src.delta_neutral_settling_firm; 
        dst.deltaNeutralClearingAccount = src.delta_neutral_clearing_account; 
        dst.deltaNeutralClearingIntent = src.delta_neutral_clearing_intent; 
        dst.deltaNeutralOpenClose = src.delta_neutral_openclose; 
        dst.deltaNeutralShortSale = src.delta_neutral_short_sale; 
        dst.deltaNeutralShortSaleSlot = src.delta_neutral_short_sale_slot; 
        dst.deltaNeutralDesignatedLocation = 
          src.delta_neutral_designated_location;
 
        dst.continuousUpdate = src.continuous_update; 
        // 1;Average, 2; BidOrAsk
        dst.referencePriceType = src.reference_price_type; 

        dst.basisPoints = src.basis_points; 
        dst.basisPointsType = src.basis_points_type; 

        dst.scaleInitLevelSize = src.scale_init_level_size; 
        dst.scaleSubsLevelSize = src.scale_subs_level_size; 
        dst.scalePriceIncrement = src.scale_price_increment; 
        dst.scalePriceAdjustValue = src.scale_price_adjust_value; 
        dst.scalePriceAdjustInterval = src.scale_price_adjust_interval; 
        dst.scaleProfitOffset = src.scale_profit_offset; 
        dst.scaleAutoReset = src.scale_auto_reset; 
        dst.scaleInitPosition = src.scale_init_position ; 
        dst.scaleInitFillQty = src.scale_init_fill_qty ; 
        dst.scaleRandomPercent = src.scale_random_percent; 
        dst.scaleTable = src.scale_table; 

        dst.whatIf = src.what_if; 

        dst.notHeld = src.not_held; 
        dst.solicited = src.solicited; 

        dst.triggerPrice = src.trigger_price; 
        dst.adjustedStopPrice = src.adjusted_stop_price; 
        dst.adjustedStopLimitPrice = src.adjusted_stop_limit_price; 
        dst.adjustedTrailingAmount = src.adjusted_trailing_amount; 
        dst.lmtPriceOffset = src.lmt_price_offset; 
        dst.extOperator = src.ext_operator; 

        dst.cashQty = src.cash_qty; 

        // std::string mifid2DecisionMaker = 
        // std::string mifid2DecisionAlgo = 
        // std::string mifid2ExecutionTrader = 
        // std::string mifid2ExecutionAlgo = 

        // don't use auto price for hedge
        dst.dontUseAutoPriceForHedge = src.dont_use_auto_price_for_hedge; 

      }

      void convert(wave::data::contract& dst, const Contract& src){
        dst.con_id = src.conId;
        dst.symbol = src.symbol;
        dst.sec_type = src.secType;
        dst.last_trade_date = src.lastTradeDateOrContractMonth;
        dst.strike = src.strike;
        dst.right = src.right;
        dst.multiplier = src.multiplier;
        dst.exchange = src.exchange;
        
        // pick an actual (ie non-aggregate) exchange
        // that the contract trades on.  DO NOT SET TO SMART.
        dst.primary_exchange = src.primaryExchange; 
        dst.currency = src.currency;
        dst.local_symbol = src.localSymbol;
        dst.trading_class = src.tradingClass;
        dst.include_expired = src.includeExpired;
        dst.sec_id_type = src.secIdType;		// CUSIP;SEDOL;ISIN;RIC
        dst.sec_id = src.secId;

        // dst.combolegs_desc = src.comboLegsDescrip; 
        // // combo legs
        // typedef std::vector<ComboLegSPtr> ComboLegList;
        // typedef ptr_type<ComboLegList> ComboLegListSPtr;
        // ComboLegListSPtr comboLegs;
        // // delta neutral contract
        // DeltaNeutralContract* deltaNeutralContract;
      }

      void convert(Contract& dst, const wave::data::contract& src){
        dst.conId = src.con_id; 
        dst.symbol = src.symbol; 
        dst.secType = src.sec_type; 
        dst.lastTradeDateOrContractMonth = src.last_trade_date; 
        dst.strike = src.strike; 
        dst.right = src.right; 
        dst.multiplier = src.multiplier; 
        dst.exchange = src.exchange; 
        
        // pick an actual (ie non-aggregate) exchange
        // that the contract trades on.  DO NOT SET TO SMART.
        dst.primaryExchange =  src.primary_exchange; 
        dst.currency = src.currency; 
        dst.localSymbol = src.local_symbol; 
        dst.tradingClass = src.trading_class; 
        dst.includeExpired = src.include_expired; 
        dst.secIdType = src.sec_id_type // CUSIP = SEDOL = ISIN = RIC
        dst.secId = src.sec_id; 

        // src.combolegs_desc; dst.comboLegsDescrip =  
        // // combo legs
        // typedef std::vector<ComboLegSPtr> ComboLegList = 
        // typedef ptr_type<ComboLegList> ComboLegListSPtr = 
        // ComboLegListSPtr comboLegs = 
        // // delta neutral contract
        // DeltaNeutralContract* deltaNeutralContract = 
      }
      
      void convert(wave::data::contract_details& dst,
              const ContractDetails& src){
        dst.m_contract = src.contract;
        dst.market_name = src.marketName;
        dst.min_tick = src.minTick;
        dst.order_types = src.orderTypes;
        dst.valid_exchanges = src.validExchanges;
        dst.price_magnifier = src.priceMagnifier;
        dst.under_conid = src.underConId;
        dst.long_name = src.longName;
        dst.contract_month = src.contractMonth;
        dst.industry = src.industry;
        dst.category = src.category;
        dst.subcategory = src.subcategory;
        dst.timezone_id = src.timeZoneId;
        dst.trading_hours = src.tradingHours;
        dst.liquid_hours = src.liquidHours;
        dst.ev_rule = src.evRule;
        dst.ev_multiplier = src.evMultiplier;
        dst.md_size_multiplier = src.mdSizeMultiplier;
        dst.agg_group = src.aggGroup;
        dst.under_symbol = src.underSymbol;
        dst.under_sec_type = src.underSecType;
        dst.market_rule_ids = src.marketRuleIds;
        dst.real_expiration_date = src.realExpirationDate;
        dst.last_trade_time = src.lastTradeTime;

        dst.cusip = src.cusip;
        dst.ratings = src.ratings;
        dst.desc_append = src.descAppend;
        dst.bond_type = src.bondType;
        dst.coupon_type = src.couponType;
        dst.callable = src.callable;
        dst.putable = src.putable;
        dst.coupon = src.coupon;
        dst.convertible = src.convertible;
        dst.maturity = src.maturity;
        dst.issue_date = src.issueDate;
        dst.next_option_date = src.nextOptionDate;
        dst.next_option_type = src.nextOptionType;
        dst.next_option_partial = src.nextOptionPartial;
        dst.notes = src.nodes;
      }

      void convert(ContractDetails& dst,
              const wave::data::contract_details& dst){
        dst.contract = src.m_contract; 
        dst.marketName = src.market_name; 
        dst.minTick = src.min_tick; 
        dst.orderTypes = src.order_types; 
        dst.validExchanges = src.valid_exchanges; 
        dst.priceMagnifier = src.price_magnifier; 
        dst.underConId = src.under_conid; 
        dst.longName = src.long_name; 
        dst.contractMonth = src.contract_month; 
        dst.industry = src.industry; 
        dst.category = src.category; 
        dst.subcategory = src.subcategory; 
        dst.timeZoneId = src.timezone_id; 
        dst.tradingHours = src.trading_hours; 
        dst.liquidHours = src.liquid_hours; 
        dst.evRule = src.ev_rule; 
        dst.evMultiplier = src.ev_multiplier; 
        dst.mdSizeMultiplier = src.md_size_multiplier; 
        dst.aggGroup = src.agg_group; 
        dst.underSymbol = src.under_symbol; 
        dst.underSecType = src.under_sec_type; 
        dst.marketRuleIds = src.market_rule_ids; 
        dst.realExpirationDate = src.real_expiration_date; 
        dst.lastTradeTime = src.last_trade_time; 

        dst.cusip = src.cusip; 
        dst.ratings = src.ratings; 
        dst.descAppend = src.desc_append; 
        dst.bondType = src.bond_type; 
        dst.couponType = src.coupon_type; 
        dst.callable = src.callable; 
        dst.putable = src.putable; 
        dst.coupon = src.coupon; 
        dst.convertible = src.convertible; 
        dst.maturity = src.maturity; 
        dst.issueDate = src.issue_date; 
        dst.nextOptionDate = src.next_option_date; 
        dst.nextOptionType = src.next_option_type; 
        dst.nextOptionPartial = src.next_option_partial; 
        dst.nodes = src.notes; 
      }
      
    }
  }
}
