#pragma once
class Scene {
public:
	Scene(const char* name) : name(name) { }
	~Scene() { delete[] name; }

	const char* getName() const { return name; }
private:
	const char* name;

};	