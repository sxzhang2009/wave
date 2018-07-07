
#include "../common.hpp"

#include <boost/exception/all.hpp>
#include <boost/config.hpp>
#include <boost/dll/import.hpp>

#include "strategy_manager.hpp"

namespace wave{
  namespace strategy{
    namespace dll = boost::dll;

    int strategy_manager::run_strategy(){
      using namespace wave::strategy;
      namespace fs = boost::filesystem;

      typedef std::vector<boost::shared_ptr<strategy_base> >
        strategy_list;
      
      strategy_list sts;

      const std::string strategy_path = "./strategy/";
        
      BOOST_LOG_TRIVIAL(info) << "loading strategy from folder "
                              << strategy_path;

      fs::directory_iterator end_iter;
      // fs::directory_iterator begin_itr(fs::path(strategy_path));
      // fs::directory_iterator itr;

      fs::directory_iterator itr{fs::path(strategy_path)};

      for(fs::directory_iterator itr{fs::path(strategy_path)};
          itr != fs::directory_iterator(); ++itr){
        if(fs::is_regular_file(itr->path())){
      
          boost::shared_ptr<strategy_base> sb;
      
          try{
            sb = dll::import<strategy_base>(           
                itr->path(),  // path to the library and library name
                "strategy",  // name of the symbol to import
                dll::load_mode::append_decorations);
          } catch(...) {
            std::exception_ptr p = std::current_exception();
            // std::cout << boost::current_exception_diagnostic_information()
            //           << std::endl;
            BOOST_LOG_TRIVIAL(warning)
              << "can not load file "
              << itr->path().filename()
              <<" got error : "
              << boost::current_exception_diagnostic_information();
            
            continue;
          }

          sb->start();
          sts.push_back(sb);
              
          BOOST_LOG_TRIVIAL(info) << "loaded strategy "
                                  << sb->name() << " from "
                                  << itr->path().filename();
        }
        // itr++;
      }

      BOOST_LOG_TRIVIAL(info) << "waiting strategy to finish. ";

      for(strategy_list::iterator it = sts.begin();
          it != sts.end(); ++it){
        (*it)->wait_stop();
      }
      // //! wait strategry to exit
      // for(auto& sb : sts){
      //   sb->wait_stop();
      // }

    }

    // //! find strategry libraries
    // for (fs::directory_iterator itr(fs::path(strategy_path));
    //      itr != end_iter; ++itr) {

    // }      
  }
}
