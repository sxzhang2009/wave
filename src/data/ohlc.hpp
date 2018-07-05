
#ifndef __OHLC_HPP__
#define __OHLC_HPP__

#include "../common.hpp"
#include "data_frame.hpp"
#include "bar.hpp"

namespace wave
{
  namespace data
  {
    //! contains open, high, low, close
    class ohlc : public data_frame{
    private:
      vec_time_ptr   date;
      vec_double_ptr open;
      vec_double_ptr high;
      vec_double_ptr low;
      vec_double_ptr close;      
      vec_double_ptr volume;
    public:
      ohlc(){
        this->add_empty_column("date",   COL_TIME);
        this->add_empty_column("open",   COL_DOUBLE);
        this->add_empty_column("high",   COL_DOUBLE);
        this->add_empty_column("low",    COL_DOUBLE);
        this->add_empty_column("close",  COL_DOUBLE);
        this->add_empty_column("volume", COL_INT8);

        date   = this->column_data<time_type>("date");
        open   = this->column_data<double>("open");
        high   = this->column_data<double>("high");
        low    = this->column_data<double>("low");
        close  = this->column_data<double>("close");
        volume = this->column_data<double>("volume");
      }

      void append_bar(const bar& t_bar){
        date->push_back(t_bar.time);
        open->push_back(t_bar.open);
        high->push_back(t_bar.high);
        low->push_back(t_bar.low);
        close->push_back(t_bar.close);
        volume->push_back(t_bar.volume);
      }
    };
  }
}
#endif
