/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* Permission to use, copy, modify, distribute and sell this software
* and its documentation for any purpose is hereby granted without fee,
* provided that the above copyright notice appear in all copies.
* Erin Catto makes no representations about the suitability
* of this software for any purpose.
* It is provided "as is" without express or implied warranty.
*/

#ifndef JOINT_HPP
#define JOINT_HPP

#include "Pch.hpp"
#include "MathUtils.hpp"
#include "components/RigidBody2DComponent.hpp"

class RigidBody2DComponent;

struct Joint
{
	Joint() :
		body1(0), body2(0),
		P(0.0f, 0.0f),
		biasFactor(0.2f), softness(0.0f)
	{}

	void Set(RigidBody2DComponent* body1, RigidBody2DComponent* body2, const Vec2& anchor);

	void PreStep(float inv_dt);
	void ApplyImpulse();

	Mat22 M;
	Vec2 localAnchor1, localAnchor2;
	Vec2 r1, r2;
	Vec2 bias;
	Vec2 P;		// accumulated impulse
	RigidBody2DComponent* body1;
	RigidBody2DComponent* body2;
	float biasFactor;
	float softness;
};

#endif