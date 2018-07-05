

#include "../src/wave.hpp"
#include <unistd.h>

void test_datetime(){
  using namespace std::chrono;
  using namespace wave;
  using namespace wave::utils;

  // struct std::tm tm;
  // std::istringstream ss("16:35:12");
  // ss >> std::get_time(&tm, "%H:%M:%S"); // or just %T in this case
  // std::time_t time = std::mktime(&tm);
  // std::cout<<std::put_time(&tm, "%c")<<std::endl;

  std::chrono::system_clock::time_point tp;
  // std::istringstream ss{"2010-12-30 01:20:30.123456Z"};
  // std::istringstream ss{"2010-12-30 01:20:30.0Z"};
  
  std::istringstream("2010-12-30 01:20:30.0Z")
    >> date::parse("%F %TZ", tp);

  std::cout<<strftime(tp)<<std::endl;
  
  // date::parse("%F %TZ", tp, "2010-12-30 01:20:30.0Z");
    
  std::cout <<
    date::format("%F %T\n",
            time_point_cast<microseconds>(tp));
  
  // std::time_t now_c = std::chrono::system_clock::to_time_t(tp);

  // // const auto ymd = date::year_month_day{tp};

  // auto today = date::floor<date::days>(system_clock::now());
  // // std::cout << today << '\n';

  std::cout <<
    date::format("%F %T\n",
            time_point_cast<microseconds>(system_clock::now()));
  // usleep(1);
  std::cout <<
    date::format("%F %T\n",
            time_point_cast<microseconds>(system_clock::now()));

  std::time_t l = 10000000;
  std::cout<<ctime(&l)<<std::endl;

  l = -10000001;
  std::cout<<ctime(&l)<<std::endl;

  std::cout<<strftime(intptime(l*1000000 + 1));
  
  std::cout<<strftime(intptime((l+1)*1000000 + 2));
  
  // std::cout << "time: " << std::ctime(&now_c);
  // std::cout<<std::chrono::system_clock::now()<<std::endl;
}

void test_data_frame(){
  using namespace wave;
  using namespace wave::utils;
  wave::data::data_frame df;
  wave::vec_int    a;
  wave::vec_double b;
  wave::vec_bool   c;
  wave::vec_string d;
  wave::vec_time   e;
  
  a.push_back(1);
  a.push_back(2);
  a.push_back(4);
  
  b.push_back(1.1);
  b.push_back(1.2);
  b.push_back(1.3);

  c.push_back(true);
  c.push_back(false);
  c.push_back(true);

  d.push_back("AB");
  d.push_back("BC");
  d.push_back("CD");

  
  e.push_back(strptime("2010-12-30 01:20:31.0Z"));
  e.push_back(strptime("2010-12-31 01:20:31.0Z"));
  e.push_back(strptime("2010-12-32 01:20:31.0Z"));
  
  df.set_column("A", a);
  df.set_column("B", b);
  df.set_column("C", c);
  df.set_column("D", d);
  df.set_column("E", e);
  
  df.print();
}

void test_ohlc(){
  using namespace wave;
  using namespace wave::utils;  
  using namespace wave::data;
  
  wave::data::ohlc o;

  time_type tp1 = strptime("2010-12-31 01:20:31.0Z");
  time_type tp2 = strptime("2010-12-30 02:20:31.0Z");
  time_type tp3 = strptime("2010-12-30 03:20:31.0Z");

  o.append_bar(bar(tp1, 100.0, 101.0, 99.0,  100.2));
  o.append_bar(bar(tp2, 101.0, 102.0, 100.0, 100.3));
  o.append_bar(bar(tp3, 102.0, 103.0, 100.0, 100.4));

  o.print();

  std::string s = "USDJPY";
  std::cout<<s.substr(0, s.find('.'))<<std::endl;
  std::cout<<s.substr(s.find('.')+1)<<std::endl; 
}

void test_order(){
  using namespace wave::data;
  order o1 = order::market_order("BUY", 100.0);
  order o2 = order::market_if_touched("SELL", 200.0, 100.1);
}

void test_contract(){
  using namespace wave::data;
  contract c1 = contract::stk("TVIX", "USD", "SMART");
  contract c2 = contract::stk("SPY",  "USD", "SMART");
  contract c3 = contract::forex("USD.JPY");
  contract c4 = contract::index("VIX", "USD", "CBOE");
}

///! test semaphore
semaphore s;
using namespace std::chrono;

system_clock::time_point start;
system_clock::time_point end;

void *inc_x(void *x_void_ptr)
{
  for(int i = 0; i < 10; ++i){
    s.wait();
    // while(!s.try_wait());
    end = system_clock::now();
    printf("hello!\n");
  }  
  // /* increment x to 100 */
  // int *x_ptr = (int *)x_void_ptr;
  // while(++(*x_ptr) < 100);
  // printf("x increment finished\n");
  /* the function must return something - NULL will do */
  return NULL;
}

void test_semaphore(){
  pthread_t inc_x_thread;

  if(pthread_create(&inc_x_thread, NULL, inc_x, NULL)) {
    fprintf(stderr, "Error creating thread\n");
    return;
  }

  usleep(500000);
  
  for(int i = 0; i < 10; ++i){
    start = system_clock::now();    
    s.notify();
    usleep(100000);

    std::cout<<"semaphore takes "
             << duration_cast<std::chrono::microseconds>(end - start).count()
             << " us." << std::endl;
  }
  
  std::cout<<"helle from main thread！"<<std::endl;
  
  /* wait for the second thread to finish */
  if(pthread_join(inc_x_thread, NULL)) {
    fprintf(stderr, "Error joining thread\n");
    return;
  }
}

int main(){
  test_datetime();    
  test_data_frame();
  test_ohlc();
  test_order();
  test_contract();
  test_semaphore();
}
