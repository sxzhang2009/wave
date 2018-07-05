
#ifndef __DATA_FRAME_HPP__
#define __DATA_FRAME_HPP__

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "column.hpp"
#include "../utils.hpp"

namespace wave{
  namespace data{

    class data_frame {
    private:
      std::vector<column_ptr> m_data;
      std::vector<std::string> m_keys;
  
    public:

      int num_rows(){
        int n = 0;
        //get the max num of rows for each column
        std::for_each(m_data.begin(), m_data.end(),
                [&n](column_ptr& c){
                  if(n < c->size()){
                    n = c->size();
                  }
                });
        return n;
      }

      int num_cols(){
        return m_data.size();
      }

      template<class T>
      ptr_type<std::vector<T> > column_data(std::string key){
        std::vector<std::string>::iterator it =
          std::find(m_keys.begin(), m_keys.end(), key);
        if(it != m_keys.end()){
          int index = it - m_keys.begin();
          return m_data[index]->as_vec<T>();          
        }else{
          throw std::invalid_argument(
              "the column does not exists.");

        }

      }
      
      template<class T>
      void set_column(std::string key, std::vector<T>& v){
        std::vector<std::string>::iterator it =
          std::find(m_keys.begin(), m_keys.end(), key);
      
        column_ptr col = column::create_from_vec(v);
      
        if(it != m_keys.end()){
          int index = it - m_keys.begin();
          m_data.at(index) = NULL;
          m_data.at(index) = col; //do repleace
        }else{
          m_data.push_back(col); //do append
          m_keys.push_back(key);
        }
      }

      void add_empty_column(std::string key, ColumnDataType t_type){
        std::vector<std::string>::iterator it =
          std::find(m_keys.begin(), m_keys.end(), key);

        column_ptr col = column::create_empty(t_type);
        
        if(it != m_keys.end()){
          int index = it - m_keys.begin();
          m_data.at(index) = NULL;
          m_data.at(index) = col; //do repleace

        }else{
          m_keys.push_back(key); //do append         
          m_data.push_back(col); 
        }
      }
      
      template<class T>
      void delete_column(std::string key){
        std::vector<std::string>::iterator it =
          std::find(m_keys.begin(), m_keys.end(), key);
      
        if(it == m_keys.end()){
          throw std::invalid_argument(
              "the column to delete does not exists.");
        }

        int i = it - m_keys.begin();
        m_keys.erase(it);
        m_data.erase(m_data.begin() + i);
      }

      void print(){
        //print header
        // std::for_each(m_keys.begin(), m_keys.end(),
        //         [](std::string& s){
        //           std::cout<<s<<std::setw(10)<<std::left;
        //         });

        std::cout<<std::endl;
        for(int i = 0; i < m_keys.size(); ++i){
          std::cout<<m_keys[i];
          if(m_data[i]->data_type() == COL_TIME){
            std::cout<<std::setw(35);
          }else{
            std::cout<<std::setw(10);
          }
        }
      
        int nr = num_rows();
        int nc = num_cols();
      
        //printf("nr = %d, nc = %d\n", nr, nc);
      
        for(int r = 0; r < nr; ++r){
          std::cout<<std::endl;        
          for(int c = 0; c < nc; ++c){
            switch(m_data[c]->data_type()){
            case COL_BOOL:
              std::cout<<m_data.at(c)->get<bool>(r)
                       <<std::setw(10); 
              break;
            case COL_INT:
              std::cout<<std::left
                       <<std::setw(10)
                       <<m_data.at(c)->get<int>(r)
                       <<std::setw(10);
              break;
            case COL_INT8:
              std::cout<<std::left
                       <<std::setw(10)
                       <<m_data.at(c)->get<int8>(r)
                       <<std::setw(10);
              break;
            case COL_DOUBLE:
              std::cout<<std::left
                       <<std::setw(10)
                       << m_data.at(c)->get<double>(r)
                       <<std::setw(10);
              break;
            case COL_FLOAT:
              std::cout<<std::left
                       <<std::setw(10)
                       <<m_data.at(c)->get<float>(r)
                       <<std::setw(10);
              break;
            case COL_STRING:
              std::cout<<std::left
                       <<std::setw(10)
                       <<m_data.at(c)->get<std::string>(r)
                       <<std::setw(10);
              break;
            case COL_TIME:
              std::cout<<std::left
                       <<std::setw(35)
                       <<wave::utils::strftime(m_data.at(c)->get<time_type>(r))
                       <<std::setw(35);
              break;              
            default:
              break;
            }
          }
        }

        std::cout<<std::endl;
      
      }
  
    };
  }
}
#endif
