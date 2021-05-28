#include "ScriptArgument.hpp"
#include <assert.h>

#include "NCALL.hpp"

ScriptArgument::~ScriptArgument()
{
	reset();
}

/*ScriptArgument::ScriptArgument(const ScriptArgument& p)
{
	set(p);
}*/

void ScriptArgument::reset()
{
	m_eType = ST_INVALID;
}

void ScriptArgument::Push(LuaVM * pVM)
{
	
	switch (GetType())
	{
	case ScriptArgument::ArgumentType::ST_INTEGER:
	{
		luabridge::push(pVM->GetVM(), GetInteger());
		break;
	}
	case ScriptArgument::ArgumentType::ST_BOOL:
	{
		luabridge::push(pVM->GetVM(), GetBool());
		break;
	}
	case ScriptArgument::ArgumentType::ST_FLOAT:
	{
		luabridge::push(pVM->GetVM(), GetFloat());
		break;
	}
	case ScriptArgument::ArgumentType::ST_STRING:
	{
		luabridge::push(pVM->GetVM(), GetString());
		break;
	}
	case ScriptArgument::ArgumentType::ST_ENTITY: {
		if (entity->GetType() == rage::entity_t::Checkpoint) {
			luabridge::push(pVM->GetVM(), entity->External<NCCheckpoint>());
		}
		else if (entity->GetType() == rage::entity_t::Player) {
			luabridge::push(pVM->GetVM(), entity->External<NCPlayer>());
		}
		else if (entity->GetType() == rage::entity_t::Vehicle) {
			luabridge::push(pVM->GetVM(), entity->External<NCVehicle>());
		}
		else if (entity->GetType() == rage::entity_t::Blip) {
			luabridge::push(pVM->GetVM(), entity->External<NCBlip>());
		}
		else if (entity->GetType() == rage::entity_t::Marker) {
			luabridge::push(pVM->GetVM(), entity->External<NCMarker>());
		}
		else if (entity->GetType() == rage::entity_t::Colshape) {
			luabridge::push(pVM->GetVM(), entity->External<NCColshape>());
		}
		else if (entity->GetType() == rage::entity_t::Object) {
			luabridge::push(pVM->GetVM(), entity->External<NCObject>());
		}
		break;
	}
	case ScriptArgument::ArgumentType::ST_REF: {
		//std::cout << (*(*(&r)))->type() << " kek " << std::endl;
		//luabridge::push(pVM->GetVM(), (*(*(&r))));
		std::cout << r->type() << " argument cpp" << std::endl;
		break;
	}
	default:
		assert(0);
		break;
	};
}

void ScriptArgument::set(const ScriptArgument& p)
{
	m_eType = p.GetType();

	switch (m_eType)
	{
	case ST_INVALID:
		break;
	case ST_INTEGER:
		i = p.i;
		break;
	case ST_BOOL:
		b = p.b;
		break;
	case ST_FLOAT:
		f = p.f;
		break;
	case ST_STRING:
		str = p.str;
		break;
	case ST_ENTITY:
		entity = p.entity;
		break;
	case ST_REF:
		r = p.r;
		break;
	}
}