#pragma once

#include "RaluCore.hpp"
#include "NCVector3.hpp"

class NCEntity {
protected:
	rage::IEntity* entity;
	rage::ICheckpoint* checkpoint;
	rage::IPlayer* player;
	rage::IVehicle* vehicle;
	rage::IBlip* blip;
	rage::IColshape* colshape;
	rage::IMarker* marker;
	rage::IObject* object;
	rage::IPickup* pickup;

	std::string strType;
	rage::entity_t hideType;
public:
	void SetEntity(rage::IEntity* entryEntity) { 
		hideType = entryEntity->GetType();
		if (hideType == rage::entity_t::Checkpoint) {
			checkpoint = (rage::ICheckpoint*)entryEntity;
		} else if (hideType == rage::entity_t::Player) {
			player = (rage::IPlayer*)entryEntity;
		} else if (hideType == rage::entity_t::Vehicle) {
			vehicle = (rage::IVehicle*)entryEntity;
		} else if (hideType == rage::entity_t::Blip) {
			blip = (rage::IBlip*)entryEntity;
		} else if (hideType == rage::entity_t::Colshape) {
			colshape = (rage::IColshape*)entryEntity;
		} else if (hideType == rage::entity_t::Marker) {
			marker = (rage::IMarker*)entryEntity;
		} else if (hideType == rage::entity_t::Object) {
			object = (rage::IObject*)entryEntity;
		} else if (hideType == rage::entity_t::Pickup) {
			pickup = (rage::IPickup*)entryEntity;
		}

		entity = entryEntity; 
		strType = Utility::typeEntityToString((uint8_t)entryEntity->GetType());
	};

	rage::IEntity* GetEntity() const { return entity; };
	rage::ICheckpoint* GetCheckpoint() const { return checkpoint; };
	rage::IPlayer* GetPlayer() const { return player; };
	rage::IVehicle* GetVehicle() const { return vehicle; };
	rage::IBlip* GetBlip() const { return blip; };
	rage::IColshape* GetColshape() const { return colshape; };
	rage::IMarker* GetMarker() const { return marker; };
	rage::IObject* GetObject() const { return object; };
	rage::IPickup* GetPickup() const { return pickup; };

	std::string GetType() const { return strType; }

	virtual void ClearEntity();

	uint16_t GetId() const;
	uint32_t GetDimension() const;
	void SetDimension(uint32_t dimension);
	NCVector3* GetPosition() const;
	void SetPosition(NCVector3* pos);
	NCVector3* GetRotation() const;
	void SetRotation(NCVector3* rot);
	uint32_t GetModel() const;
	void SetModel(uint32_t model);
	NCVector3* GetVelocity() const;
	uint8_t GetAlpha() const;
	void SetAlpha(uint8_t alpha);
};