#pragma once
#include"AbstractRender.h"
#include<string>
#include<unordered_map>

class SkinRegistry {
public:
	SkinRegistry();
	~SkinRegistry();

	template<typename T>
	static AbstractRender *createRenderInstance() { return new T; }; //TODO heap allocation so add documentation to reflect this in whatever method will eventually be called to generate a new render for game objects

	//Registers a new render factory method for a game object
	//Para
	//string skin - the name of the skin to create a render factory for
	//AbstractRender*(*)() newRender - the supplied factory method
	//Usage registerRenderFactory("aSkin_steampunk", createRenderInstance<AbstractRender>);
	static void registerRenderFactory(std::string skin, AbstractRender*(*newRender)());

	//Registers a new render file for a given skin name for a given IGameObject type
	//Para
	//string skin - skin name
	//AbstractRender &render - reference to the render file used for that skin
	//Usage registerSkin<Renderable("skin name", AbstractRender)
	template<typename T>
	static void registerSkin(std::string skin, AbstractRender& render) {
		skinRegistry<T>[skin] = render;
	}

	//Registers the default render file if no skin name is supplied
	//AbstractRender &render - reference to the default render file to be used for that object
	//Usage registerSkin<IRenderable>(AbstractRender)
	template<typename T>
	static void registerDefaultRender(AbstractRender& render) {
		return skinRegistry<T>[""] = render;
	}

	template<typename T>
	static AbstractRender &getRender(std::string skin) {
		return skinRegistry<T>.at(skin);
	}

	template<typename T>
	static AbstractRender &getDefaultRender(std::string skin) {
		return skinRegistry<T>.at("");
	}

	static void registerAllSkins();

private:
	static std::unordered_map<std::string, AbstractRender&(*)()> factoryRegistry;
	template<typename T>
	static std::unordered_map<std::string, T> skinRegistry;
};