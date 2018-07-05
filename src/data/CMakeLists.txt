subdirs(brokers/ib/)

aux_source_directory(. data_src)
add_library(data STATIC ${data_src})
