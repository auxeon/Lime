/*
* Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com
*
* Permission to use, copy, modify, distribute and sell this software
* and its documentation for any purpose is hereby granted without fee,
* provided that the above copyright notice appear in all copies.
* Erin Catto makes no representations about the suitability
* of this software for any purpose.
* It is provided "as is" without express or implied warranty.
*/

#include "Pch.hpp"
#include "Arbiter.hpp"
#include "systems/PhysicsSystem.hpp"

Arbiter::Arbiter(RigidBody2DComponent* b1, RigidBody2DComponent* b2)
{
	if (b1 < b2)
	{
		body1 = b1;
		body2 = b2;
	}
	else
	{
		body1 = b2;
		body2 = b1;
	}

	numContacts = Collide(contacts, body1, body2);

	friction = sqrtf(body1->friction * body2->friction);
}

void Arbiter::Update(Contact* newContacts, int numNewContacts)
{
	Contact mergedContacts[2];

	for (int i = 0; i < numNewContacts; ++i)
	{
		Contact* cNew = newContacts + i;
		int k = -1;
		for (int j = 0; j < numContacts; ++j)
		{
			Contact* cOld = contacts + j;
			if (cNew->feature.value == cOld->feature.value)
			{
				k = j;
				break;
			}
		}

		if (k > -1)
		{
			Contact* c = mergedContacts + i;
			Contact* cOld = contacts + k;
			*c = *cNew;
			if (PhysicsSystem::warmStarting)
			{
				c->Pn = cOld->Pn;
				c->Pt = cOld->Pt;
				c->Pnb = cOld->Pnb;
			}
			else
			{
				c->Pn = 0.0f;
				c->Pt = 0.0f;
				c->Pnb = 0.0f;
			}
		}
		else
		{
			mergedContacts[i] = newContacts[i];
		}
	}

	for (int i = 0; i < numNewContacts; ++i)
		contacts[i] = mergedContacts[i];

	numContacts = numNewContacts;
}


void Arbiter::PreStep(float inv_dt)
{
	const float k_allowedPenetration = 0.01f;
	float k_biasFactor = PhysicsSystem::positionCorrection ? 0.3f : 0.0f;

	for (int i = 0; i < numContacts; ++i)
	{
		Contact* c = contacts + i;

		Vec2 r1 = c->position - Vec2(body1->position.x, body1->position.y);
		Vec2 r2 = c->position - Vec2(body2->position.x, body2->position.y);

		// Precompute normal mass, tangent mass, and bias.
		float rn1 = Dot(r1, c->normal);
		float rn2 = Dot(r2, c->normal);
		float kNormal = body1->invMass + body2->invMass;
		kNormal += body1->invI * (Dot(r1, r1) - rn1 * rn1) + body2->invI * (Dot(r2, r2) - rn2 * rn2);
		c->massNormal = 1.0f / kNormal;

		Vec2 tangent = Cross(c->normal, 1.0f);
		float rt1 = Dot(r1, tangent);
		float rt2 = Dot(r2, tangent);
		float kTangent = body1->invMass + body2->invMass;
		kTangent += body1->invI * (Dot(r1, r1) - rt1 * rt1) + body2->invI * (Dot(r2, r2) - rt2 * rt2);
		c->massTangent = 1.0f / kTangent;

		c->bias = -k_biasFactor * inv_dt * Min(0.0f, c->separation + k_allowedPenetration);

		if (PhysicsSystem::accumulateImpulses)
		{
			// Apply normal + friction impulse
			Vec2 P = c->Pn * c->normal + c->Pt * tangent;

			body1->velocity.x -= body1->invMass * P.x;
			body1->velocity.y -= body1->invMass * P.y;
			body1->angularVelocity -= body1->invI * Cross(r1, P);

			body2->velocity.x += body2->invMass * P.x;
			body2->velocity.y += body2->invMass * P.y;
			body2->angularVelocity += body2->invI * Cross(r2, P);
		}
	}
}

void Arbiter::ApplyImpulse()
{
	RigidBody2DComponent* b1 = body1;
	RigidBody2DComponent* b2 = body2;

	for (int i = 0; i < numContacts; ++i)
	{
		Contact* c = contacts + i;
		c->r1 = c->position - Vec2(b1->position.x,b1->position.y);
		c->r2 = c->position - Vec2(b2->position.x,b2->position.y);

		// Relative velocity at contact
		Vec2 dv = Vec2(b2->velocity.x,b2->velocity.y) + Cross(b2->angularVelocity, c->r2) - Vec2(b1->velocity.x, b1->velocity.y) - Cross(b1->angularVelocity, c->r1);

		// Compute normal impulse
		float vn = Dot(dv, c->normal);

		float dPn = c->massNormal * (-vn + c->bias);

		if (PhysicsSystem::accumulateImpulses)
		{
			// Clamp the accumulated impulse
			float Pn0 = c->Pn;
			c->Pn = Max(Pn0 + dPn, 0.0f);
			dPn = c->Pn - Pn0;
		}
		else
		{
			dPn = Max(dPn, 0.0f);
		}

		// Apply contact impulse
		Vec2 Pn = dPn * c->normal;

		b1->velocity.x -= b1->invMass * Pn.x;
		b1->velocity.y -= b1->invMass * Pn.y;
		b1->angularVelocity -= b1->invI * Cross(c->r1, Pn);

		b2->velocity.x += b2->invMass * Pn.x;
		b2->velocity.y += b2->invMass * Pn.y;
		b2->angularVelocity += b2->invI * Cross(c->r2, Pn);

		// Relative velocity at contact
		dv = Vec2(b2->velocity.x,b2->velocity.y) + Cross(b2->angularVelocity, c->r2) - Vec2(b1->velocity.x,b1->velocity.y) - Cross(b1->angularVelocity, c->r1);

		Vec2 tangent = Cross(c->normal, 1.0f);
		float vt = Dot(dv, tangent);
		float dPt = c->massTangent * (-vt);

		if (PhysicsSystem::accumulateImpulses)
		{
			// Compute friction impulse
			float maxPt = friction * c->Pn;

			// Clamp friction
			float oldTangentImpulse = c->Pt;
			c->Pt = Clamp(oldTangentImpulse + dPt, -maxPt, maxPt);
			dPt = c->Pt - oldTangentImpulse;
		}
		else
		{
			float maxPt = friction * dPn;
			dPt = Clamp(dPt, -maxPt, maxPt);
		}

		// Apply contact impulse
		Vec2 Pt = dPt * tangent;

		b1->velocity.x -= b1->invMass * Pt.x;
		b1->velocity.y -= b1->invMass * Pt.y;
		b1->angularVelocity -= b1->invI * Cross(c->r1, Pt);

		b2->velocity.x += b2->invMass * Pt.x;
		b2->velocity.y += b2->invMass * Pt.y;
		b2->angularVelocity += b2->invI * Cross(c->r2, Pt);
	}
}
