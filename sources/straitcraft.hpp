#ifndef STRAITCRAFT_HPP
#define STRAITCRAFT_HPP

#include <SFML/System/Clock.hpp>
#include "main/application.hpp"
#include "platform/glcontext.hpp"
#include "core/math/vector2.hpp"
#include "servers/display_server.hpp"
#include "graphics_pipeline.hpp"
#include "renderer.hpp"
#include "world.hpp"

using namespace StraitX;

class StraitCraft: public Application{
private:
    Renderer m_Renderer;
    World *m_World;
public:
    StraitCraft();

    ~StraitCraft();

    virtual Result OnInitialize()override;

    virtual void OnUpdate(float dt)override;

    virtual bool OnEvent(const Event &e)override;

    virtual Result OnFinalize()override;
};

#endif //STRAITCRAFT_HPP 