// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "ParticleSystem/ParticleCommon.h"
#include "ParticleSystem/ParticleAttributes.h"
#include "ParticleSystem/ParticleEmitter.h"
#include "ParamMod.h"
#include "FeatureColor.h"

namespace pfx2
{

SERIALIZATION_ENUM_DECLARE(EDomain, ,
                           Age,
                           SpawnFraction,
                           Speed,
                           Field,
                           Attribute,                           
                           ViewAngle,
	                       CameraDistance,
	                       Global,
                           Random,

                           // old version
                           _ParentTime,
                           _ParentOrder,
                           _ParentSpeed,
                           _ParentField,

                           _SelfTime = Age,
                           _SelfSpeed = Speed,
	                       _LevelTime = Global
                           )

SERIALIZATION_ENUM_DECLARE(EDomainOwner, ,
                           _None,
                           Self,
                           Parent
                           )

SERIALIZATION_ENUM_DECLARE(EDomainGlobal, ,
                           LevelTime,
	                       TimeOfDay,
	                       ExposureValue
                           )

typedef DynamicEnum<struct SDomainField> EDomainField;
bool Serialize(Serialization::IArchive& ar, EDomainField& value, cstr name, cstr label);


class CDomain
{
public:
	CDomain();

	template<typename TParam, typename TMod>
	void              AddToParam(CParticleComponent* pComponent, TParam* pParam, TMod* pModifier);
	template<typename TBase, typename TStream>
	void              Dispatch(const SUpdateContext& context, const SUpdateRange& range, TStream stream, EModDomain domain) const;

	EModDomain        GetDomain() const;
	EParticleDataType GetDataType() const;
	string            GetSourceDescription() const;
	float             Adjust(float sample) const { return sample * m_domainScale + m_domainBias; }
	void              SerializeInplace(Serialization::IArchive& ar);

protected:
	float m_domainScale;
	float m_domainBias;

private:
	float             GetGlobalValue(EDomainGlobal source) const;
	IParamModContext& GetContext(Serialization::IArchive& ar) const;

private:
	string        m_attributeName;
	EDomain       m_domain;
	EDomainField  m_fieldSource;
	EDomainOwner  m_sourceOwner;
	EDomainGlobal m_sourceGlobal;
	bool          m_spawnOnly;
};

}

#include "DomainImpl.h"
