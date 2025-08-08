#include "../include/Color4.hpp"


namespace RTCE {


float Color4::R() const { return _rgbaComponents._x; }
float Color4::G() const { return _rgbaComponents._y; }
float Color4::B() const { return _rgbaComponents._z; }
float Color4::A() const { return _rgbaComponents._w; }

float Color4::r() const { return R(); }
float Color4::g() const { return G(); }
float Color4::b() const { return B(); }
float Color4::a() const { return A(); }


}// namespace RTCE