add_library(thread_pool STATIC)
target_sources(thread_pool
    PUBLIC
        FILE_SET cxx_modules_thread_pool TYPE CXX_MODULES FILES
        thread_pool.cpp
)
