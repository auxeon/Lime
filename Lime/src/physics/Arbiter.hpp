/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Arbiter.hpp
Purpose: Collision contact resolver
Language: c++
Platform: Windows
Project: CS529_finalproject
Author: Abhikalp Unakal, abhikalp.unakal, 60001619
- End Header --------------------------------------------------------*/
#ifndef ARBITER_HPP
#define ARBITER_HPP

#include "Pch.hpp"
#include "MathUtils.hpp"
#include "components/RigidBody2DComponent.hpp"

class RigidBody2DComponent;

union FeaturePair
{
	struct Edges
	{
		char inEdge1;
		char outEdge1;
		char inEdge2;
		char outEdge2;
	} e;
	int value;
};

struct Contact
{
	Contact() : Pn(0.0f), Pt(0.0f), Pnb(0.0f) {}

	Vec2 position;
	Vec2 normal;
	Vec2 r1, r2;
	float separation;
	float Pn;	// accumulated normal impulse
	float Pt;	// accumulated tangent impulse
	float Pnb;	// accumulated normal impulse for position bias
	float massNormal, massTangent;
	float bias;
	FeaturePair feature;
};

struct ArbiterKey
{
	ArbiterKey(RigidBody2DComponent* b1, RigidBody2DComponent* b2)
	{
		if (b1 < b2)
		{
			body1 = b1; body2 = b2;
		}
		else
		{
			body1 = b2; body2 = b1;
		}
	}

	RigidBody2DComponent* body1;
	RigidBody2DComponent* body2;
};

struct Arbiter
{
	enum { MAX_POINTS = 2 };

	Arbiter(RigidBody2DComponent* b1, RigidBody2DComponent* b2);

	void Update(Contact* contacts, int numContacts);

	void PreStep(float inv_dt);
	void ApplyImpulse();

	Contact contacts[MAX_POINTS];
	int numContacts;

	RigidBody2DComponent* body1;
	RigidBody2DComponent* body2;

	// Combined friction
	float friction;
};

// This is used by std::set
inline bool operator < (const ArbiterKey& a1, const ArbiterKey& a2)
{
	if (a1.body1 < a2.body1)
		return true;

	if (a1.body1 == a2.body1 && a1.body2 < a2.body2)
		return true;

	return false;
}

int Collide(Contact* contacts, RigidBody2DComponent* body1, RigidBody2DComponent* body2);

#endif
