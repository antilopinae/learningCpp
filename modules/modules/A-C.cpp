module A:C; //A-C.cpp //!!! without "export"
//partition module implementation unit

//WorldImpl() is visible by any module unit of A importing C
char const* WorldImpl() { return "World"; }
