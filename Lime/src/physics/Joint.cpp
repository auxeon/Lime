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

#include "Pch.hpp"
#include "Joint.hpp"
#include "components/RigidBody2DComponent.hpp"
#include "systems/PhysicsSystem.hpp"

void Joint::Set(RigidBody2DComponent* b1, RigidBody2DComponent* b2, const Vec2& anchor)
{
	body1 = b1;
	body2 = b2;

	Mat22 Rot1(body1->rotation.z);
	Mat22 Rot2(body2->rotation.z);
	Mat22 Rot1T = Rot1.Transpose();
	Mat22 Rot2T = Rot2.Transpose();

	localAnchor1 = Rot1T * (anchor - Vec2(body1->position.x, body1->position.y));
	localAnchor2 = Rot2T * (anchor - Vec2(body2->position.x, body2->position.y));

	P.Set(0.0f, 0.0f);

	softness = 0.0f;
	biasFactor = 0.2f;
}

void Joint::PreStep(float inv_dt)
{
	// Pre-compute anchors, mass matrix, and bias.
	Mat22 Rot1(body1->rotation.z);
	Mat22 Rot2(body2->rotation.z);

	r1 = Rot1 * localAnchor1;
	r2 = Rot2 * localAnchor2;

	// deltaV = deltaV0 + K * impulse
	// invM = [(1/m1 + 1/m2) * eye(2) - skew(r1) * invI1 * skew(r1) - skew(r2) * invI2 * skew(r2)]
	//      = [1/m1+1/m2     0    ] + invI1 * [r1.y*r1.y -r1.x*r1.y] + invI2 * [r1.y*r1.y -r1.x*r1.y]
	//        [    0     1/m1+1/m2]           [-r1.x*r1.y r1.x*r1.x]           [-r1.x*r1.y r1.x*r1.x]
	Mat22 K1;
	K1.col1.x = body1->invMass + body2->invMass;	K1.col2.x = 0.0f;
	K1.col1.y = 0.0f;								K1.col2.y = body1->invMass + body2->invMass;

	Mat22 K2;
	K2.col1.x = body1->invI * r1.y * r1.y;		K2.col2.x = -body1->invI * r1.x * r1.y;
	K2.col1.y = -body1->invI * r1.x * r1.y;		K2.col2.y = body1->invI * r1.x * r1.x;

	Mat22 K3;
	K3.col1.x = body2->invI * r2.y * r2.y;		K3.col2.x = -body2->invI * r2.x * r2.y;
	K3.col1.y = -body2->invI * r2.x * r2.y;		K3.col2.y = body2->invI * r2.x * r2.x;

	Mat22 K = K1 + K2 + K3;
	K.col1.x += softness;
	K.col2.y += softness;

	M = K.Invert();

	Vec2 p1 = Vec2(body1->position.x, body1->position.y) + r1;
	Vec2 p2 = Vec2(body2->position.x, body2->position.y) + r2;
	Vec2 dp = p2 - p1;

	if (PhysicsSystem::positionCorrection)
	{
		bias = -biasFactor * inv_dt * dp;
	}
	else
	{
		bias.Set(0.0f, 0.0f);
	}

	if (PhysicsSystem::warmStarting)
	{
		// Apply accumulated impulse.
		body1->velocity.x -= body1->invMass * P.x;
		body1->velocity.y -= body1->invMass * P.y;
		body1->angularVelocity -= body1->invI * Cross(r1, P);

		body2->velocity.x += body2->invMass * P.x;
		body2->velocity.x += body2->invMass * P.y;
		body2->angularVelocity += body2->invI * Cross(r2, P);
	}
	else
	{
		P.Set(0.0f, 0.0f);
	}
}

void Joint::ApplyImpulse()
{
	Vec2 dv = Vec2(body2->velocity.x, body2->velocity.y) + Cross(body2->angularVelocity, r2) - Vec2(body1->velocity.x, body1->velocity.y) - Cross(body1->angularVelocity, r1);

	Vec2 impulse;

	impulse = M * (bias - dv - softness * P);

	body1->velocity.x -= body1->invMass * impulse.x;
	body1->velocity.y -= body1->invMass * impulse.y;
	body1->angularVelocity -= body1->invI * Cross(r1, impulse);

	body2->velocity.x += body2->invMass * impulse.x;
	body2->velocity.y += body2->invMass * impulse.y;
	body2->angularVelocity += body2->invI * Cross(r2, impulse);

	P += impulse;
}
