#include "Collision.h"
#include <cmath>

float distance(float x1, float y1, float x2, float y2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    return sqrtf((dx * dx) + (dy * dy));
}

/// -------------------------------------------------------------------------------------
/// <summary>
/// Check the collision between a point an a circle
/// </summary>
/// <param name="px">the point's position on the x axis</param>
/// <param name="py">the point's position on the y axis</param>
/// <param name="cx">the circle's position on the x axis</param>
/// <param name="cy">the circle's position on the y axis</param>
/// <param name="cr">the circle's radius</param>
/// <returns>if there is a collision, it returns true</returns>
bool Engine::CheckPointCircle(float px, float py, float cx, float cy, float cr)
{
    // Créer un vecteur entre le point et le centre du cercle:
    float vecX = px - cx;
    float vecY = py - cy;

    // Calculer la magnitude du vecteur:
    float distance = sqrtf((vecX * vecX) + (vecY * vecY));

    // Il y a une collision si la magnitude est plus petite que le radius du cercle:
    return distance <= cr;
}

/// -------------------------------------------------------------------------------------
/// <summary>
/// Checks the collisions between two circles
/// </summary>
/// <param name="c1x">the first circle's position on the x axis</param>
/// <param name="c1y">the first circle's position on the y axis</param>
/// <param name="c1r">the first circle's radius</param>
/// <param name="c1x">the second circle's position on the x axis</param>
/// <param name="c1y">the second circle's position on the y axis</param>
/// <param name="c1r">the second circle's radius</param>
/// <returns>if there is a collision, it returns true</returns>
bool Engine::CheckCircles(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
    // Faire un vector entre les deux cercles:
    float vecX = c1x - c2x;
    float vecY = c1y - c2y;

    // Calculer la magnitude du vecteur:
    float distance = sqrtf((vecX * vecX) + (vecY * vecY));

    // Il y a une collision si la magnitude est plus petite que 
    // la somme des deux rayons :
    return distance <= (c1r + c2r);
}

/// -------------------------------------------------------------------------------------
/// <summary>
/// Checks the collisions between a point and a rectangle.
/// </summary>
/// <param name="px">the point's position on the x axis</param>
/// <param name="py">the point's position on the y axis</param>
/// <param name="rx">the rectangle's position on the x axis</param>
/// <param name="ry">the rectangle's position on the y axis</param>
/// <param name="rw">the rectangle's width</param>
/// <param name="rh">the rectangle's height</param>
/// <returns>if there is a collision, it returns true</returns>
bool Engine::CheckPointRect(float px, float py, float rx, float ry, float rw, float rh)
{
    return px >= rx && py >= ry && px <= (rx + rw) && py <= (ry + rh);
}

/// -------------------------------------------------------------------------------------
/// <summary>
/// Checks the collisions between two rectangles
/// </summary>
/// <param name="r1x">the first rectangle's position on the x axis</param>
/// <param name="r1y">the first rectangle's position on the y axis</param>
/// <param name="r1w">the first rectangle's width</param>
/// <param name="r1h">the first rectangle's height</param>
/// <param name="r2x">the second rectangle's position on the x axis</param>
/// <param name="r2y">the second rectangle's position on the y axis</param>
/// <param name="r2w">the second rectangle's width</param>
/// <param name="r2h">the second rectangle's height</param>
/// <returns>if there is a collision, it returns true</returns>
bool Engine::CheckRects(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
{
    return (r1x <= (r2x + r2w) && (r1x + r1w) >= r2x && r1y <= (r2y + r2h) && (r1y + r1h) >= r2y);
}

/// -------------------------------------------------------------------------------------
/// <summary>
/// Checks the collisions between a rectangle and a circle
/// </summary>
/// <param name="rx">the rectangle's position on the x axis</param>
/// <param name="ry">the rectangle's position on the y axis</param>
/// <param name="rw">the rectangle's width</param>
/// <param name="rh">the rectangle's height</param>
/// <param name="cx">the circle's position on the x axis</param>
/// <param name="cy">the circle's position on the y axis</param>
/// <param name="cr">the circle's radius</param>
/// <returns>if there is a collision, it returns true</returns>
bool Engine::CheckRectCircle(float rx, float ry, float rw, float rh, float cx, float cy, float cr, float* hitX, float* hitY)
{
    if (CheckPointRect(cx, cy, rx, ry, rw, rh))
    {
        *hitX = cx;
        *hitY = cy;
        return true;
    }

    float tx = cx;
    float ty = cy;

    // Choisir le côté le plus proche :
    if (tx < rx) tx = rx;
    if (tx > rx + rw) tx = rx + rw;
    if (ty < ry) ty = ry;
    if (ty > ry + rh) ty = ry + rh;

    *hitX = tx;
    *hitY = ty;
    return CheckPointCircle(tx, ty, cx, cy, cr);
}

bool Engine::CheckPointLine(float px, float py, float x1, float y1, float x2, float y2)
{
    float d1 = distance(px, py, x1, y1);
    float d2 = distance(px, py, x2, y2);
    float len = distance(x1, y1, x2, y2);
    float epsilon = 0.1f;

    return d1 + d2 >= len - epsilon &&
        d1 + d2 <= len + epsilon;
}

bool Engine::CheckCircleLine(float cx, float cy, float cr, float x1, float y1, float x2, float y2, float* closeX, float* closeY)
{
    bool p1inside = CheckPointCircle(x1, y1, cx, cy, cr);
    bool p2inside = CheckPointCircle(x2, y2, cx, cy, cr);

    if (p1inside || p2inside)
    {
        return true;
    }

    float vecAx = x2 - x1;
    float vecAy = y2 - y1;
    float vecBx = cx - x1;
    float vecBy = cy - y1;

    float vecA_ls = vecAx * vecAx + vecAy * vecAy;

    float dot = (vecAx * vecBx + vecAy * vecBy) / vecA_ls;

    *closeX = x1 + (dot * vecAx);
    *closeY = y1 + (dot * vecAy);

    bool onSegment = CheckPointLine(*closeX, *closeY, x1, y1, x2, y2);
    if (!onSegment)
    {
        return false;
    }

    float dist = distance(*closeX, *closeY, cx, cy);
    return dist <= cr;
}

bool Engine::CheckLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* closeX, float* closeY)
{
    float a1 = x2 - x1;
    float a2 = x4 - x3;
    float b1 = y2 - y1;
    float b2 = y4 - y3;
    float c1 = x1 - x3;
    float c2 = y1 - y3;

    float ua = (a2 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    float ub = (a1 * c2 - b1 * c1) / (a1 * b2 - a2 * b1);

    *closeX = x1 + (ua * (x2 - x1));
    *closeY = y1 + (ua * (y2 - y1));

    return (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1);
}

bool Engine::CheckRectLine(float x1, float y1, float x2, float y2,
    float rx, float ry, float rw, float rh)
{
    if (CheckPointRect(x1, y1, rx, ry, rw, rh) ||
        CheckPointRect(x2, y2, rx, ry, rw, rh))
    {
        return true;
    }

    float lx, ly;
    bool left = CheckLines(x1, y1, x2, y2, rx, ry, rx, ry + rh, &lx, &ly);

    float rrx, rry;
    bool right = CheckLines(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh, &rrx, &rry);

    float tx, ty;
    bool top = CheckLines(x1, y1, x2, y2, rx, ry, rx + rw, ry, &tx, &ty);

    float bx, by;
    bool bottom = CheckLines(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh, &bx, &by);

    return left || right || top || bottom;
}