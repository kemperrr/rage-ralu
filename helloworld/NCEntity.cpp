#include "NCALL.hpp"

void NCEntity::ClearEntity() {
	entity = NULL;
	checkpoint = NULL;
	player = NULL;
	vehicle = NULL;
	blip = NULL;
	colshape = NULL;
	marker = NULL;
	object = NULL;
	pickup = NULL;
}

uint16_t NCEntity::GetId() const {
	return entity->GetId();
}

uint32_t NCEntity::GetDimension() const {
	return entity->GetDimension();
}

void NCEntity::SetDimension(uint32_t dimension) {
	entity->SetDimension(dimension);
}

NCVector3* NCEntity::GetPosition() const {
	rage::vector3 vec = entity->GetPosition();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCEntity::SetPosition(NCVector3* pos) {
	rage::vector3 vec = { pos->coord[0], pos->coord[1], pos->coord[2] };
	entity->SetPosition(vec);
}

NCVector3* NCEntity::GetRotation() const {
	rage::vector3 vec = entity->GetRotation();
	return new NCVector3(vec.x, vec.y, vec.z);
}

void NCEntity::SetRotation(NCVector3* rot) {
	rage::vector3 vec = { rot->coord[0], rot->coord[1], rot->coord[2] };
	entity->SetRotation(vec);
}

uint32_t NCEntity::GetModel() const {
	return entity->GetModel();
}

void NCEntity::SetModel(uint32_t model) {
	entity->SetModel(model);
}

NCVector3* NCEntity::GetVelocity() const {
	rage::vector3 vec = entity->GetVelocity();
	return new NCVector3(vec.x, vec.y, vec.z);
}

uint8_t NCEntity::GetAlpha() const {
	return entity->GetAlpha();
}

void NCEntity::SetAlpha(uint8_t alpha) {
	entity->SetAlpha(alpha);
}