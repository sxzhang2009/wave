
#include "../data/contract_details.hpp"
#include <boost/python.hpp>

using namespace wave::data;

BOOST_PYTHON_MODULE(wave)
{
  class_<contract>("contract")
    .def_readwrite("con_id", &contract::con_id)
    .def_readwrite("symbol", &contract::symbol)            
    .def_readwrite("sec_type", &contract::set_type)
    .def_readwrite("last_trade_date", &contract::last_trade_date)   
    .def_readwrite("strike", &contract::strike)            
    .def_readwrite("right", &contract::right) 
    .def_readwrite("multiplier", &contract::multiplier)         
    .def_readwrite("exchange", &contract::exchange)          
    .def_readwrite("primary_exchange", &contract::primary_exchange)  
    .def_readwrite("currency", &contract::currency)
    .def_readwrite("local_symbol", &contract::local_symbol)
    .def_readwrite("trading_class", &contract::trading_class)      
    .def_readwrite("include_expired", &contract::include_expired)
    .def_readwrite("sec_id_type", &contract::sec_id_type)	    
    .def_readwrite("sec_id", &contract::sec_id)
    .def_readwrite("combolegs_desc", &contract::combolegs_desc);

  class_<contract_details>("contract_details")
    .def_readwrite("contract",             &contract_details::contract)
    .def_readwrite("market_name",          &contract_details::market_name)           
    .def_readwrite("min_tick",             &contract_details::min_tick)
    .def_readwrite("order_types",          &contract_details::order_types)           
    .def_readwrite("valid_exchanges",      &contract_details::valid_exchanges)       
    .def_readwrite("price_magnifier",      &contract_details::price_magnifier)       
    .def_readwrite("under_conid",          &contract_details::under_conid)           
    .def_readwrite("long_name",            &contract_details::long_name)             
    .def_readwrite("contract_month",       &contract_details::contract_month)        
    .def_readwrite("industry",             &contract_details::industry)              
    .def_readwrite("category",             &contract_details::category)              
    .def_readwrite("subcategory",          &contract_details::subcategory)           
    .def_readwrite("timezone_id",          &contract_details::timezone_id)           
    .def_readwrite("trading_hours",        &contract_details::trading_hours)         
    .def_readwrite("liquid_hours",         &contract_details::liquid_hours)          
    .def_readwrite("ev_rule",              &contract_details::ev_rule)               
    .def_readwrite("ev_multiplier",        &contract_details::ev_multiplier)         
    .def_readwrite("md_size_multiplier",   &contract_details::md_size_multiplier)    
    .def_readwrite("agg_group",            &contract_details::agg_group)             
    .def_readwrite("under_symbol",         &contract_details::under_symbol)          
    .def_readwrite("under_sec_type",       &contract_details::under_sec_type)        
    .def_readwrite("market_rule_ids",      &contract_details::market_rule_ids)       
    .def_readwrite("real_expiration_date", &contract_details::real_expiration_date)  
    .def_readwrite("last_trade_time",      &contract_details::last_trade_time);
}

