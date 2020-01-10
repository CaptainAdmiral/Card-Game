#pragma once
#include "RenderType.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>

namespace bg = boost::geometry;
typedef bg::model::point<float, 2, bg::cs::cartesian> point_t;
typedef bg::model::polygon<point_t> BoundingBox;

class AbstractRender;

class IRenderable {
public:
	IRenderable();
	IRenderable(const IRenderable&);
	IRenderable &operator = (const IRenderable&);
	IRenderable(IRenderable&&) = delete; //TODO you deleted these out of sheer lazieness. Come on.
	IRenderable &operator = (IRenderable&&) = delete; //Don't be like that. Write out 6 lines of code.
	//TODO and then do it for the other auto subscription interfaces as well
	
	virtual ~IRenderable();

	//Returning false will cause the render manager to skip the render pass for this object if it is on the render list
	virtual bool isVisible() {
		return visible;
	}

	//Setting to false will cause the render manager to skip the render pass for this object if it is on the render list
	virtual void setVisible(bool vis) {
		visible = vis;
	}

	//Returns a reference to the render file to be used during the render pass
	virtual AbstractRender& getRender() = 0;

	//Whether or not to consider bounding box for mouse click hitscan
	//Should be set to true if you want renderable to block mouse clicks
	virtual bool isClickable() {
		return isVisible();
	}

	virtual RenderType getType() {
		return RenderType::INVALID;
	}

	//As yet unimplemented
	//Mouse click and mouse release within TODO seconds
	virtual void onClicked() {};

	//On mouse click
	virtual void onMouseClick() {};
	
	//On mouse release
	virtual void onMouseRelease() {};

	virtual float getPosX() { return posX; }

	virtual float getPosY() { return posY;  }

	virtual void setPos(float x, float y);

	virtual void move(float x, float y);

	//Immutable getter for IRenderable bounding box
	virtual const BoundingBox &getBoundingBox() {
		return boundingBox;
	}

	//Used to recalculate the IRenderable bounding box
	//Called by every function that changes position
	virtual void updateBoundingBox() {
		boundingBox = calculateBoundingBox();
	}

protected:
	float posX = 0;
	float posY = 0;

	//Used to define the IRenderable bounding box
	virtual BoundingBox calculateBoundingBox() {
		BoundingBox box;
		return box;
	};

private:
	BoundingBox boundingBox;
	bool visible = true;
};