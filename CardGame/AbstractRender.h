#pragma once
#include "RenderWrapper.h"
#include "Camera.h"
#include <string>
#include <boost/geometry/geometries/geometries.hpp>

namespace bg = boost::geometry;
typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
typedef bg::model::polygon<point_t> BoundingBox;

class IRenderable;

class AbstractRender {
public:
	AbstractRender();
	virtual ~AbstractRender();

	virtual void render(IRenderable &renderable, RenderWrapper &wrapper) = 0;
};
