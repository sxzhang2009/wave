
#include "official/Contract.h"
#include "official/Order.h"
#include "official/bar.h"
#include "official/HistoricalTick.h"

#include "../../../utils.hpp"
#include "../../bar.hpp"
#include "../../tick.hpp"
#include "../../order.hpp"
#include "../../contract_details.hpp"

using namespace wave;

namespace wave{
  namespace data{
    namespace ib{

      //! convert ib tick data to tick
      void convert(wave::data::tick& dst,
              const HistoricalTick& src);

      //! convert ib bar data to wave bar
      void convert(wave::data::bar& dst, const Bar& src);

      //! convert ib Order to wave order
      void convert(wave::data::order& dst, const Order& src);

      //! convert wave order to ib Order
      void convert(Order& dst, const wave::data::order& src);

      //! convert ib contract to wave contract
      void convert(wave::data::contract& dst, const Contract& src);

      //! convert wave contract to ib Contract
      void convert(Contract& dst, const wave::data::contract& src);

      //! convert ib ContractDetails to wave contract_details
      void convert(wave::data::contract_details& dst,
              const ContractDetails& src);

      //! convert wave contract_details to ib ContractDetails
      void convert(ContractDetails& dst,
              const wave::data::contract_details& src);
      
    }
  }
}
