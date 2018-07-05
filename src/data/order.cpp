
#include "order.hpp"

namespace wave{
  namespace data{

    /// <summary>
    /// A Market order is an order to buy or sell at the market bid or offer price. A market order may increase the likelihood of a fill 
    /// and the speed of execution, but unlike the Limit order a Market order provides no price protection and may fill at a price far 
    /// lower/higher than the current displayed bid/ask.
    /// Products: BOND, CFD, EFP, CASH, FUND, FUT, FOP, OPT, STK, WAR
    /// </summary>
    order order::market_order(std::string action, double quantity){
      order order;
      order.action = action;
      order.order_type = "MKT";
      order.total_quantity = quantity;
      return order;
    }

    /// <summary>
    /// A Market if Touched (MIT) is an order to buy (or sell)
    /// a contract below (or above) the market.
    /// Its purpose is to take advantage 
    /// of sudden or unexpected changes in share or other
    /// prices and provides investors with a trigger
    /// price to set an order in motion. 
    /// Investors may be waiting for excessive
    /// strength (or weakness) to cease, which might be
    /// represented by a specific price point. 
    /// MIT orders can be used to determine whether or
    /// not to enter the market once a specific price
    /// level has been achieved. This order 
    /// is held in the system until the trigger price
    /// is touched, and is then submitted as a market order.
    /// An MIT order is similar to a 
    /// stop order, except that an MIT sell order is placed
    /// above the current market price, and a stop sell order is placed below
    /// Products: BOND, CFD, CASH, FUT, FOP, OPT, STK, WAR
    /// </summary>
    order order::market_if_touched(std::string action,
            double quantity, double price){
      order order;
      order.action = action;
      order.order_type = "MIT";
      order.total_quantity = quantity;
      order.aux_price = price;
      return order;
    }


    inline void
    order::clone_combo_legs(order_comboleg_list_ptr& dst,
            const order_comboleg_list_ptr& src)
    {
      if (!src.get())
        return;

      dst->reserve(src->size());

      order_comboleg_list::const_iterator iter = src->begin();
      const order_comboleg_list::const_iterator iterEnd = src->end();

      for (; iter != iterEnd; ++iter) {
        const order_comboleg* leg = iter->get();
        if (!leg)
          continue;
        dst->push_back(order_comboleg_ptr(new order_comboleg(*leg)));
      }
    }    
  }
}
