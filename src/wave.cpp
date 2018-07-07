
#include "wave.hpp"
#include <boost/exception/all.hpp>
#include <boost/config.hpp>
#include <boost/dll/import.hpp>

namespace dll = boost::dll;

// int main(int argc, char* argv[]){

//   using namespace wave::strategy;
//   using namespace boost::filesystem;
  
//   std::vector<boost::shared_ptr<strategy_base> >  sts;
  
//   //! find strategry libraries
//   for (directory_iterator itr(path("./strategy/"));
//        itr!=directory_iterator(); ++itr) {
//     if(is_regular_file(itr->path())){
      
//       boost::shared_ptr<strategy_base> sb;
      
//       try{
//         sb = dll::import<strategy_base>(           
//             itr->path(),  // path to the library and library name
//             "strategy",  // name of the symbol to import
//             dll::load_mode::append_decorations);              
//         sb->start();
//         sts.push_back(sb);
//       } catch(...) {
//         std::exception_ptr p = std::current_exception();
//         std::clog << boost::current_exception_diagnostic_information()
//                   << std::endl;
//       }
//     }
//   }

//   //! wait strategry to exit
//   for(auto& sb : sts){
//     sb->wait_stop();
//   }
  
//   return 0;
// }
