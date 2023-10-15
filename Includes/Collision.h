#pragma once

namespace Engine
{
    bool CheckPointCircle(float px, float py, float cx, float cy, float cr);
    bool CheckCircles(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r);
    bool CheckPointRect(float px, float py, float rx, float ry, float rw, float rh);
    bool CheckRects(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);
    bool CheckRectCircle(float rx, float ry, float rw, float rh, float cx, float cy, float cr, float* hitX, float* hitY);
    bool CheckPointLine(float px, float py, float x1, float y1, float x2, float y2);
    bool CheckCircleLine(float cx, float cy, float cr, float x1, float y1, float x2, float y2, float* closeX, float* closeY);
    bool CheckLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* closeX, float* closeY);
    bool CheckRectLine(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);
}