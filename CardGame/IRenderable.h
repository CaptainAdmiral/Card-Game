#pragma once
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>

namespace bg = boost::geometry;
typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
typedef bg::model::polygon<point_t> BoundingBox;

class AbstractRender;

class IRenderable {
public:
	IRenderable();
	virtual ~IRenderable();

	//Returning false will cause the render manager to skip the render pass for this object if it is on the render list
	virtual bool isVisible() {
		return true;
	}

	//Returns a reference to the render file to be used during the render pass
	virtual AbstractRender& getRender() = 0;

	//Whether or not to consider bounding box for mouse click hitscan
	//Should be set to true if you want renderable to block mouse clicks
	virtual bool isClickable() {
		return isVisible();
	}

	//Mouse click and mouse release within TODO seconds
	virtual void onClicked() {};

	//On mouse click
	virtual void onMouseClick() {};
	
	//On mouse release
	virtual void onMouseRelease() {};

	virtual float getPosX() {
		return posX;
	}

	virtual float getPosY() {
		return posY;
	}

	virtual void setPos(float x, float y) {
		posX = x;
		posY = y;
		updateBoundingBox();
	}

	virtual void move(float x, float y) {
		posX += x;
		posY += y;
		updateBoundingBox();
	}

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
};