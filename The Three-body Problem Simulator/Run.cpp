﻿#include "Engine.h"
#include "Global.h"

// 运行模块
int Engine::run(int TimeLimit)
{
	for (int i = 0; i < CelestialBody::quantity; i++) {
		star[i].getCoordinate().print();
	}

	for (int presentTime = 0; presentTime < TimeLimit; presentTime += DT)
	{
		for (int i = 0; i < CelestialBody::quantity; i++)
		{
			vector<SpaceVector> R(CelestialBody::quantity - 1);
			vector<SpaceVector> F(CelestialBody::quantity - 1);

			SpaceVector resultantForce;
			for (int j = 0; j < CelestialBody::quantity - 1; j++)
			{
				R[j].setSpaceVector(this->star[(i + j + 1) % CelestialBody::quantity].getCoordinate() - this->star[i].getCoordinate());
				F[j].setSpaceVector(R[j], GravitationalConstant * (star[i].getMass() * star[(i + j + 1) % CelestialBody::quantity].getMass() / SQR(R[j].getModulus())));
				resultantForce += F[j];
			}
			star[i].setForce(resultantForce);
			star[i].setAcceleration(star[i].getForce() / star[i].getMass());
			star[i].setVelocity(star[i].getVelocity() + star[i].getAcceleration() * DT);
			star[i].setCoordinate(star[i].getCoordinate() + star[i].getVelocity() * DT);
		}

		// 碰撞检测
		for (int i = 0; i < CelestialBody::quantity; i++) {
			for (int j = i; j < CelestialBody::quantity; j++) {
				if (Space::getDistance(star[i].getCoordinate(), star[j].getCoordinate())<=Engine::CrashJudgingDistance) {
					star[i] += star[j];
				}
			}
		}
	}

	cout << endl;
	for (int i = 0; i < CelestialBody::quantity; i++) {
		star[i].getCoordinate().print();
	}
	return 0;
}
