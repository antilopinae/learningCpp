//module partition

export module A; //primary module interface unit

import :C; //WorldImpl() is now visible only for A.cpp
export import :B; // Hello() is visible when importing A
// export import :C //ERROR: Cannot export a module implementation unit
// export import :C;

//World() is visible by any translation unit importing A
export char const* World()
{
    return WorldImpl();
}

namespace ns //ns is not attached to A
{
    export extern "C++" int ns_f(); //f is not attached to A
    extern "C++" int ns_g(); //g is not attached to A
    export int h(); //h is attached to A
}
