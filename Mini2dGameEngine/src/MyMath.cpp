#include "MyMath.h"

using namespace myMath;


bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}
sf::Vector2f myMath::rotatePointArrounPoint(sf::Vector2f myPoint, sf::Vector2f centerPoint, float rotationAngle)
{
	// Convertendo de graus para radianos e invertendo o sentido de rota��o
	rotationAngle = (rotationAngle) * (PI / 180);

	float s = sin(rotationAngle);
	float c = cos(rotationAngle);

	// Retornando o ponto para 0,0
	myPoint.x -= centerPoint.x;
	myPoint.y -= centerPoint.y;

	// Rotacionando
	float xnew = myPoint.x * c - myPoint.y * s;
	float ynew = myPoint.x * s + myPoint.y * c;

	// Levando o ponto de volta para a posi��o original
	myPoint.x = xnew + centerPoint.x;
	myPoint.y = ynew + centerPoint.y;

	return myPoint;
}

bool myMath::doLinesIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{

	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

sf::Vector2f myMath::calcDisplacement(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
	
	float h = (q2.x - p2.x) * (p1.y - q1.y) - (p1.x - q1.x) * (q2.y - p2.y);
	float t1 = ((p2.y - q2.y) * (p1.x - p2.x) + (q2.x - p2.x) * (p1.y - p2.y)) / h;
	float t2 = ((p1.y - q1.y) * (p1.x - p2.x) + (q1.x - p1.x) * (p1.y - p2.y)) / h;

	if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
	{
		float displacementX =  (1.0f - t1) * (q1.x - p1.x);
		float displacementY = (1.0f - t1) * (q1.y - p1.y);

		return sf::Vector2f(displacementX, displacementY);
	}
	return sf::Vector2f(0,0);
}
double myMath::deg2rad(double angle)
{
	return angle * (PI / 180);
}

double myMath::distBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
{
	float dx = p2.x - p1.x;
	float dy = p2.y - p1.y;
	double dist = sqrt(pow(dx, 2) + pow(dy, 2));
	return dist;
}

ElasticColRes myMath::calcElasticColl(sf::Vector2f velocity1, float mass1, sf::Vector2f velocity2, float mass2)
{
	float xVel = ((((mass1 - mass2) / (mass1 + mass2)) * velocity1.x) + (((2 * mass2) / (mass1 + mass2)) * velocity2.x));
	float yVel = ((((mass1 - mass2) / (mass1 + mass2)) * velocity1.y) + (((2 * mass2) / (mass1 + mass2)) * velocity2.y));
	//float yVel = ((((2 * mass1) / (mass1 + mass2)) * velocity1.y) + (((mass2 - mass1) / (mass1 + mass2)) * velocity2.y));
	//xVel /= 2;
	//yVel /= 2;
	sf::Vector2f deltaSpeed = sf::Vector2f(xVel - velocity1.x, yVel - velocity1.y);
	//std::cout << deltaSpeed.x << "  " << deltaSpeed.y << std::endl;
	float xVel2 = ((((2 * mass1) / (mass1 + mass2)) * velocity1.x) + (((mass2 - mass1) / (mass1 + mass2)) * velocity2.x));
	float yVel2 = ((((2 * mass1) / (mass1 + mass2)) * velocity1.y) + (((mass2 - mass1) / (mass1 + mass2)) * velocity2.y));
	//xVel2 /= 2;
	//yVel2 /= 2;
	//sf::Vector2f deltaSpeed2 = sf::Vector2f(xVel2 - velocity2.x, yVel2 - velocity2.y);
	sf::Vector2f deltaSpeed2 = sf::Vector2f(xVel2 - velocity2.x, yVel2 - velocity2.y);

	myMath::ElasticColRes result;
	result.velocity1 = deltaSpeed;
	result.velocity2 = deltaSpeed2;

	return result;

}