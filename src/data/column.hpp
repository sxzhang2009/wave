
#ifndef __COLUMN_HPP__
#define __COLUMN_HPP__

#include <vector>
#include <string>
#include <memory>
#include "../common.hpp"
#include <boost/pointer_cast.hpp>

namespace wave{
  namespace data{

    enum ColumnDataType {
      COL_UNKNOWN,
      COL_BOOL,  
      COL_INT,
      COL_INT8,
      COL_FLOAT,
      COL_DOUBLE,
      COL_STRING,
      COL_TIME
    };

    template <typename T>
    ColumnDataType col_type() {
      if (std::is_same<T, int>::value)    return COL_INT;
      if (std::is_same<T, int8>::value)   return COL_INT8;      
      if (std::is_same<T, float>::value)  return COL_FLOAT;
      if (std::is_same<T, double>::value) return COL_DOUBLE;
      if (std::is_same<T, bool>::value)   return COL_BOOL;
      if (std::is_same<T, std::string>::value)  return COL_STRING;
      if (std::is_same<T, time_type>::value)  return COL_TIME;
      return COL_UNKNOWN;
    };
    
    class column;
    typedef ptr_type<column> column_ptr;
    
    //! data frame column type
    class column{
    private:
      ColumnDataType m_data_type;
      ptr_type<void> m_values;
    public:

      template<class T>
      std::vector<T>* as(){
        // static_pointer_cast<std::vector<T>
        return boost::static_pointer_cast<std::vector<T> >(m_values).get();
        // return (std::vector<T>*)m_values->data();
      }

      template<class T>
      ptr_type<std::vector<T> > as_vec(){
        // static_pointer_cast<std::vector<T>
        return boost::static_pointer_cast<std::vector<T> >(m_values);
        // return (std::vector<T>*)m_values->data();
      }
      
      template<class T>
      T get(int idx){
        return as<T>()->at(idx);
      }
    
      ColumnDataType data_type(){
        return m_data_type;
      }
    
      column() : m_values(NULL),
                 m_data_type(COL_UNKNOWN){
      }

      // column(ptr_type<void>& t_values,
      //        int t_data_type){
      //   m_values = t_values;
      //   m_data_type = t_data_type;
      // }
      
      ~column(){
        m_values = NULL;        
        if(m_values != NULL){
          m_values = NULL;
        }
      }
    
      template<class T>
      static column_ptr create_from_vec(const std::vector<T>& v){
        std::vector<T>* new_v = new std::vector<T>();
        *new_v = v;

        column_ptr col(new column());        
        col->m_values.reset(new_v);
        col->m_data_type = col_type<T>();
        return col;
      }

      template<class T>
      static column_ptr create_empty(){
        std::vector<T>* new_v = new std::vector<T>();
        
        column_ptr col(new column());        
        col->m_values.reset(new_v);
        col->m_data_type = col_type<T>();
        return col;
      }

      static column_ptr create_empty(ColumnDataType m_type){

        column_ptr col(new column());
        
        switch(m_type){
        case COL_BOOL:
          col->m_values.reset(new vec_bool());
          col->m_data_type = COL_BOOL;
          break;
        case COL_INT:
          col->m_values.reset(new vec_int());
          col->m_data_type = COL_INT;
          break;
        case COL_INT8:
          col->m_values.reset(new vec_int8());
          col->m_data_type = COL_INT8;
          break;          
        case COL_FLOAT:
          col->m_values.reset(new vec_float());
          col->m_data_type = COL_FLOAT;
          break;
        case COL_DOUBLE:
          col->m_values.reset(new vec_double());
          col->m_data_type = COL_DOUBLE;
          break;
        case COL_STRING:
          col->m_values.reset(new vec_string());
          col->m_data_type = COL_STRING;
          break;
        case COL_TIME:
          col->m_values.reset(new vec_time());
          col->m_data_type = COL_TIME;
          break;
        default:
          throw new std::invalid_argument("invid column data type.");
        }

        return col;
      }
      
      
      int size(){
        switch (m_data_type) { 
        case COL_BOOL:
          return as<bool>()->size();
          break;
        case COL_INT:
          return as<int>()->size();
          break;
        case COL_INT8:
          return as<int8>()->size();
          break;
        case COL_DOUBLE:
          return as<double>()->size();
          break;
        case COL_FLOAT:
          return as<float>()->size();
          break;
        case COL_STRING:
          return as<std::string>()->size();
          break;
        case COL_TIME:
          return as<time_type>()->size();
          break;
        default :
          return -1;
        }
      }
    };
    
  }
}
#endif
