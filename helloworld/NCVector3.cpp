#include "NCALL.hpp"

NCVector3::NCVector3(float x, float y, float z) {
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
}

std::string NCVector3::ToString() const {
	
	std::ostringstream stringStream;
	stringStream << "Position: X: ";
	stringStream << coord[0];
	stringStream << " Y: ";
	stringStream << coord[1];
	stringStream << " Z: ";
	stringStream << coord[2];
	std::string copyOfStr = stringStream.str();
	
	//str +=  + coord[0];

	return copyOfStr;
}

void NCVector3::Register(LuaVM* rVM) {
	getGlobalNamespace(rVM->GetVM())
	.beginNamespace("mp")
		.beginClass <NCVector3>("Vector3")
			.addConstructor <void(*)(float, float, float)>()
			.addProperty("x", &NCVectorHelper::get <0>, &NCVectorHelper::set <0>)
			.addProperty("y", &NCVectorHelper::get <1>, &NCVectorHelper::set <1>)
			.addProperty("z", &NCVectorHelper::get <2>, &NCVectorHelper::set <2>)
			.addFunction("__tostring", &NCVector3::ToString)
		.endClass()
	.endNamespace();
}