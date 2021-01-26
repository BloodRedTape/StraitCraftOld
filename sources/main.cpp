#include <new>
#include "main/application.hpp"
#include "straitcraft.hpp"

using namespace StraitX;

static char sandbox[sizeof(StraitCraft)];


namespace StraitX{
ApplicationConfig GameConfig = {
    {1650, 1050}
};
}//namespace StraitX;

Application *StraitXMain(){
    return new (sandbox)StraitCraft();
}

Result StraitXExit(Application *app){
    (void)app;
    return Result::Success;
}