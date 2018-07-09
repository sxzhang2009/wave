
#ifndef ACCOUNTSUMMARYTAGS
#define ACCOUNTSUMMARYTAGS

#include <string>
#include <vector>

class AccountSummaryTags{
  std::vector<std::string> m_tags;  
public:

  AccountSummaryTags();
  
  static AccountSummaryTags* get(){
    static AccountSummaryTags* p =
      new AccountSummaryTags();
    return p;
  };
  
  std::string getAllTags();
  int getNumTags();
};

#endif
