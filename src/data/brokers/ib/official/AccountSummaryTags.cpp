
#include "AccountSummaryTags.hpp"
#include <string>
#include <sstream>

using namespace std;

string AccountSummaryTags::AccountType = "AccountType";
string AccountSummaryTags::NetLiquidation = "NetLiquidation";
string AccountSummaryTags::TotalCashValue = "TotalCashValue";
string AccountSummaryTags::SettledCash = "SettledCash";
string AccountSummaryTags::AccruedCash = "AccruedCash";
string AccountSummaryTags::BuyingPower = "BuyingPower";
string AccountSummaryTags::EquityWithLoanValue = "EquityWithLoanValue";
string AccountSummaryTags::PreviousEquityWithLoanValue =
  "PreviousEquityWithLoanValue";
string AccountSummaryTags::GrossPositionValue = "GrossPositionValue";
string AccountSummaryTags::ReqTEquity = "ReqTEquity";
string AccountSummaryTags::ReqTMargin = "ReqTMargin";
string AccountSummaryTags::SMA = "SMA";
string AccountSummaryTags::InitMarginReq = "InitMarginReq";
string AccountSummaryTags::MaintMarginReq = "MaintMarginReq";
string AccountSummaryTags::AvailableFunds = "AvailableFunds";
string AccountSummaryTags::ExcessLiquidity = "ExcessLiquidity";
string AccountSummaryTags::Cushion = "Cushion";
string AccountSummaryTags::FullInitMarginReq = "FullInitMarginReq";
string AccountSummaryTags::FullMaintMarginReq = "FullMaintMarginReq";
string AccountSummaryTags::FullAvailableFunds = "FullAvailableFunds";
string AccountSummaryTags::FullExcessLiquidity = "FullExcessLiquidity";
string AccountSummaryTags::LookAheadNextChange = "LookAheadNextChange";
string AccountSummaryTags::LookAheadInitMarginReq = "LookAheadInitMarginReq";
string AccountSummaryTags::LookAheadMaintMarginReq = "LookAheadMaintMarginReq";
string AccountSummaryTags::LookAheadAvailableFunds = "LookAheadAvailableFunds";
string AccountSummaryTags::LookAheadExcessLiquidity = "LookAheadExcessLiquidity";
string AccountSummaryTags::HighestSeverity = "HighestSeverity";
string AccountSummaryTags::DayTradesRemaining = "DayTradesRemaining";
string AccountSummaryTags::Leverage = "Leverage";

string AccountSummaryTags::getAllTags(){
  stringstream ss;
  ss << AccountType << ","
     << NetLiquidation << ","
     << TotalCashValue << ","
     << SettledCash << ","
     << AccruedCash << ","
     << BuyingPower << ","
     << EquityWithLoanValue << ","
     << PreviousEquityWithLoanValue << ","
     << GrossPositionValue << ","
     << ReqTEquity << ","
     << ReqTMargin << ","
     << SMA << ","
     << InitMarginReq << ","
     << MaintMarginReq << ","
     << AvailableFunds << ","
     << ExcessLiquidity << ","
     << Cushion << ","
     << FullInitMarginReq << ","
     << FullMaintMarginReq << ","
     << FullAvailableFunds << ","
     << FullExcessLiquidity << ","
     << LookAheadNextChange << ","
     << LookAheadInitMarginReq << ","
     << LookAheadMaintMarginReq << ","
     << LookAheadAvailableFunds << ","
     << LookAheadExcessLiquidity << ","
     << HighestSeverity << ","
     << DayTradesRemaining << ","
     << Leverage;

  return ss.str();
}
