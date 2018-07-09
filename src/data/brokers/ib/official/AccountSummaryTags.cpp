
#include "AccountSummaryTags.hpp"
#include <string>
#include <sstream>

using namespace std;

AccountSummaryTags::AccountSummaryTags() {
  m_tags.push_back("AccountType");
  m_tags.push_back("NetLiquidation");
  m_tags.push_back("TotalCashValue");
  // m_tags.push_back("SettledCash");
  m_tags.push_back("AccruedCash");
  m_tags.push_back("BuyingPower");
  m_tags.push_back("EquityWithLoanValue");
  // m_tags.push_back("PreviousEquityWithLoanValue");
  // m_tags.push_back("GrossPositionValue");
  // m_tags.push_back("ReqTEquity");
  // m_tags.push_back("ReqTMargin");
  // m_tags.push_back("SMA");
  // m_tags.push_back("InitMarginReq");
  // m_tags.push_back("MaintMarginReq");
  // m_tags.push_back("AvailableFunds");
  // m_tags.push_back("ExcessLiquidity");
  // m_tags.push_back("Cushion");
  // m_tags.push_back("FullInitMarginReq");
  // m_tags.push_back("FullMaintMarginReq");
  // m_tags.push_back("FullAvailableFunds");
  // m_tags.push_back("FullExcessLiquidity");
  // m_tags.push_back("LookAheadNextChange");
  // m_tags.push_back("LookAheadInitMarginReq");
  // m_tags.push_back("LookAheadMaintMarginReq");
  // m_tags.push_back("LookAheadAvailableFunds");
  // m_tags.push_back("LookAheadExcessLiquidity");
  // m_tags.push_back("HighestSeverity");
  // m_tags.push_back("DayTradesRemaining");
  // m_tags.push_back("Leverage");
}

string AccountSummaryTags::getAllTags(){
  stringstream ss;
   
  for(int i = 0; i < m_tags.size(); ++i){
    ss << m_tags[i];
    if(i < m_tags.size()-1)
      ss << ",";
  }
  return ss.str();
}

int AccountSummaryTags::getNumTags(){
  return m_tags.size();
}
