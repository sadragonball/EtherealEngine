#include "render_pass.h"
#include "core/common/assert.hpp"
#include "core/graphics/graphics.h"
#include <bitset>

static std::uint8_t s_index = 0;
static std::uint8_t s_last_index = 0;

std::uint8_t generate_id()
{
    if (s_index == 255)
	{
		gfx::frame();
        s_index++;
	}
    expects(s_index < 256);
	// find the first unset bit
    std::uint8_t idx = s_index++;

    s_last_index = idx;
	return idx;
}


render_pass::render_pass(const std::string& n)
{
	id = generate_id();
	gfx::setViewName(id, n.c_str());
}

void render_pass::bind(frame_buffer* fb) const
{
	expects(fb != nullptr);

	const auto size = fb->get_size();

	gfx::setViewRect(
		id,
		std::uint16_t(0),
		std::uint16_t(0),
		std::uint16_t(size.width),
		std::uint16_t(size.height)
	);

	gfx::setViewScissor(
		id,
		std::uint16_t(0),
		std::uint16_t(0),
		std::uint16_t(size.width),
		std::uint16_t(size.height)
	);

	
	gfx::setViewFrameBuffer(id, fb->handle);
	gfx::touch(id);
	
}

void render_pass::clear(std::uint16_t _flags, std::uint32_t _rgba /*= 0x000000ff */, float _depth /*= 1.0f */, std::uint8_t _stencil /*= 0*/) const
{
	gfx::setViewClear(id
		, _flags
		, _rgba
		, _depth
		, _stencil
	);
}

void render_pass::clear() const
{
	gfx::setViewClear(id
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL
		, 0x000000FF
		, 1.0f
		, 0
	);
}

void render_pass::set_view_proj(const math::transform& v, const math::transform& p)
{
	gfx::setViewTransform(id, &v, &p);
}

void render_pass::set_view_proj_ortho_full(float depth)
{
	static const math::transform p = math::ortho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, depth, gfx::is_homogeneous_depth());
	gfx::setViewTransform(id, {}, &p);
}

void render_pass::reset()
{
    for (std::uint8_t i = 0; i < s_index; ++i)
	{
		gfx::resetView(i);
	}
    s_index = 0;
    s_last_index = 0;
}

std::uint8_t render_pass::get_pass()
{
    return s_last_index;
}